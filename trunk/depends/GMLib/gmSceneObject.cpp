/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmSceneObject.cpp
 *
 *  Implementation of the SceneObject class.
 *
 *  \date   2008-07-22
 */


#include "gmPoint.h"
#include "gmLight.h"
#include "gmSceneObject.h"

#include "gmVisualizer.h"


namespace GMlib {





  unsigned int SceneObject::_free_name = 1;


  /*! SceneObject( const Vector<float,3>& trans  = Vector3D<float>(0,0,0), const Point<float,3>&  scale   = Point3D<float>(1,1,1), const Vector<float,3>& rotate = Vector3D<float>(1,0,0), Angle a=0 )
   *  \brief default and standard constructor
   *
   *  Default and standard constructor.
   *  First rotates, then scales and finaly translates the object.
   */
  SceneObject::SceneObject (
    const Vector<float,3>& trans_vector,
    const Point<float,3>&  scale,
    const Vector<float,3>& rot_axel,
    Angle a
  ) :_scale(scale) {

    _parent = 0;
    _matrix.translate(trans_vector);




    Vector3D<float> ra = rot_axel;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    _matrix.rotateGlobal(a, u, v);

    _name	            = _free_name++;
    _active	          = false;
    _local_cs         = true;
    _type_id          = GM_SO_TYPE_SCENEOBJECT;
    _lighted          = true;
    _opaque           = true;
    _visible          = true;
    _selected         = false;
    _material         = GMmaterial::Obsidian;
    _color            = GMcolor::Red;

    _collapsed        = false;
    _collapsed_dlist  = 0;
    generateCollapsedDList();

    _children.clear();
  }


  /*! SceneObject::SceneObject( const SceneObject& d )
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  SceneObject::SceneObject( const SceneObject& d ) {

    _parent           = 0;
    _matrix	          = d._matrix;
    _children	        = d._children;
    _lighted          = d._lighted;
    _opaque           = d._opaque;
    _sphere	          = d._sphere;
    _scale            = d._scale;
    _name	            = _free_name++;
    _active	          = false;
    _local_cs         = d._local_cs;
    _type_id          = d._type_id;
    _visible          = d._visible;
    _selected         = d._selected;
    _color            = d._color;
    _material         = d._material;

    _collapsed        = d._collapsed;
    _collapsed_dlist  = 0;
    generateCollapsedDList();
  }


  /*! SceneObject::~SceneObject()
   *  \brief Default Destructor
   *
   *  Default Destructor
   */
  SceneObject::~SceneObject() {

    for(int i=0; i < _children.getSize(); i++) {
      if( _children[i] ) {

        _children[i]->setParent(0);
        remove( _children[i] );
        delete _children[i];
      }
    }

    if( _collapsed_dlist )
      glDeleteLists( _collapsed_dlist, 1 );
  }


  /*! void SceneObject::_fillObj( Array<SceneObject*>& )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::_fillObj( Array<SceneObject*>& disp_objs ) {

    if(_sphere.isValid())
      disp_objs += this;
    for(int i=0; i< _children.getSize(); i++)
      _children[i]->_fillObj(disp_objs);
  }


  /*! int SceneObject::_prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* mother=0)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int SceneObject::_prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* parent) {

    int nr = 1;
    _scene  = s;

    _parent=parent;

    Light * pl  = dynamic_cast<Light *>(this);
    if(pl) obj += pl;

    mat.push();

    _prepareDisplay(mat.back());
    mat.back() = mat.back() * getMatrix();

    _present = mat.back();
    _global_total_sphere = _global_sphere = _present*_sphere;


    if(_scale.isActive()) {

      _global_sphere *= _scale.getMax();
      _global_sphere %= _scale.getScale();
      _global_total_sphere *= _scale.getMax();
      _global_total_sphere %= _scale.getScale();
    }
    for( int i = 0; i < _children.getSize(); i++ ) {

      nr += _children[i]->_prepare(obj,mat,s,this);
      _global_total_sphere += _children[i]->getSurroundingSphere();
    }

    mat.pop();
    return nr;
  }


  /*! void SceneObject::_prepareDisplay( const HqMatrix<float,3>& mat )
   *  \brief Pending Documentation
   *
   *  Made specially for DisplayObject's
   */
  void SceneObject::_prepareDisplay( const HqMatrix<float,3>& /*mat*/ ) {}


  /*! void culling( Array<SceneObject*>&, const Frustum& );
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::culling( Array<SceneObject*>& disp_objs, const Frustum& f ) {

    //if(!_visible) return;
    if(!_sphere.isValid())
      return;

    int k = f.isInterfering(getSurroundingSphere());

    if( k < 0 )
      return;	// Outside

    // Inside
    if( k > 0 ) {

      if(_visible)
        disp_objs += this; // added check for visible, children don't automatic follow anymore
      for( int i = 0; i < _children.getSize(); i++ )
        _children[i]->culling( disp_objs, f );
//        _children[i]->_fillObj( disp_objs );
    }
    else { // if(k == 0)     Intersecting

      if( _visible && f.isInterfering( _global_sphere ) >= 0 )
        disp_objs += this;
      for( int i = 0; i < _children.getSize(); i++ )
        _children[i]->culling( disp_objs, f );
    }


  }


  /*! void displayCollapsed()
   *  \brief Display of collapsed object
   *
   *  Display of collapsed object
   */
  void SceneObject::displayCollapsed() {

    glCallList( _collapsed_dlist );
  }


  /*! SceneObject* SceneObject::find(unsigned int name)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* SceneObject::find(unsigned int name) {

    SceneObject* d;

    if(name == _name)	return this;
    for(int i=0; i < _children.getSize(); i++)
      if( (d = _children(i)->find(name)) ) return d;
    return 0;
  }


  void SceneObject::generateCollapsedDList() {

    if( _collapsed_dlist )
      glDeleteLists( _collapsed_dlist, 1 );

    _collapsed_dlist = glGenLists( 1 );

    float ir = 0.07f;
    glNewList( _collapsed_dlist, GL_COMPILE ); {

      glBegin(GL_QUAD_STRIP); {

        glVertex3f( ir,-ir,-ir ); glVertex3f( ir, ir,-ir );
        glVertex3f( ir,-ir, ir ); glVertex3f( ir, ir, ir );
        glVertex3f(-ir,-ir, ir ); glVertex3f(-ir, ir, ir );
        glVertex3f(-ir,-ir,-ir ); glVertex3f(-ir, ir,-ir );
        glVertex3f( ir,-ir,-ir ); glVertex3f( ir, ir,-ir );
      } glEnd();

      glBegin(GL_QUADS); {

        glVertex3f(-ir,-ir,-ir ); glVertex3f( ir,-ir,-ir );
        glVertex3f( ir,-ir, ir ); glVertex3f(-ir,-ir, ir );
        glVertex3f(-ir, ir,-ir ); glVertex3f(-ir, ir, ir );
        glVertex3f( ir, ir, ir ); glVertex3f( ir, ir,-ir );
      } glEnd();

    } glEndList();

  }


  const Color& SceneObject::getColor() const {

    return _color;
  }


  Color& SceneObject::getColor() {

    return _color;
  }


  const Material& SceneObject::getMaterial() const {

    return _material;
  }


  Material& SceneObject::getMaterial() {

    return _material;
  }


  /*! HqMatrix<flaot,3>& SceneObject::getMatrix()
   *  \brief Pending Documentation
   *
   *  Made specially for Cameras
   */
  HqMatrix<float,3>& SceneObject::getMatrix()	{

    return _matrix;
  }


  /*! const	GL_Matrix& SceneObject::getMatrixParentGlobal() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  const	HqMatrix<float,3>& SceneObject::getMatrixParentGlobal() const {

    return _parent->getMatrixGlobal();
  }


  /*! Sphere<float,3>	SceneObject::getSurroundingSphereClean() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3> SceneObject::getSurroundingSphereClean() const {

    Sphere<float,3> sp;

    for(int i=0; i< _children.getSize(); i++)
      sp += _children(i)->getSurroundingSphereClean();
    if(_type_id!=GM_SO_TYPE_CAMERA && _type_id!=GM_SO_TYPE_LIGHT) sp += _global_sphere;
    return sp;
  }

  const Array<Visualizer*>& SceneObject::getVisualizers() const {

    return _visualizers;
  }


  /*! void SceneObject::insert(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::insert(SceneObject* obj) {

    if(obj)
    {
      _children.insert(obj);
      obj->_parent=this;
    }
  }

  void SceneObject::insertVisualizer( Visualizer* visualizer ) {

    if( _visualizers.exist( visualizer ) )
      return;

    visualizer->set( this );
    _visualizers += visualizer;
  }


  bool SceneObject::isLighted() const {

    return _lighted;
  }


  /*! void localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localDisplay() {

    for( int i = 0; i < _visualizers.getSize(); ++i )
      _visualizers[i]->display();
  }


  void SceneObject::localDisplayActive() {

    localSelect();
  }


  void SceneObject::localDisplaySelection() {

    localSelect();
  }


  /*! void localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localSelect()  {

    for( int i = 0; i < _visualizers.getSize(); ++i )
      _visualizers[i]->select();
  }


  /*! void localSimulate(double dt)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localSimulate( double /*dt*/ ) {}


  /*! void SceneObject::remove(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::remove(SceneObject* obj) {

    if(obj)
      if(!_children.remove(obj))
        for(int i=0; i< _children.getSize(); i++)
          _children[i]->remove(obj);
  }

  void SceneObject::removeVisualizer( Visualizer* visualizer ) {

    _visualizers.remove( visualizer );
  }


  /*! void SceneObject::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::reset() {

    _matrix.reset();
  }


  /*! void SceneObject::rotate(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::rotate(Angle a, const Vector<float,3>& rot_axel) {

    Vector3D<float> ra = rot_axel;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    _matrix.rotate(a, u, v);
  }


  /*! void SceneObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    Vector3D<float> ra = d;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;
    _matrix.rotate(a, u, v, p);
  }


  /*! void SceneObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::rotateGlobal( Angle a, const Vector<float,3>& rot_axel ) {

    Vector3D<float> ra = rot_axel;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    _matrix.rotateGlobal(a, u, v);
  }


  /*! void SceneObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    Vector3D<float> ra = d;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    _matrix.rotateGlobal(a, u, v, p);
  }


  /*! void SceneObject::scale(const Point<float,3>& scale_factor)
   *  \brief Pending Documentation
   *
   *  ( Only geometry )
   */
  void SceneObject::scale(const Point<float,3>& scale_factor) {
    for(int i=0; i<_children.getSize(); i++)
    {
      Point3D<float> tr = -(_children[i]->_matrix*Point<float,3>(0.0f));
      _children[i]->translate(scale_factor%tr);
      _children[i]->scale(scale_factor);
    }
    _scale.scale(scale_factor);
    _sphere = _scale.scaleSphere(_sphere);
  }


  void SceneObject::setColor( const Color& c ) {

    _color = c;
  }


  void SceneObject::setLighted( bool lighted ) {

    _lighted = lighted;
  }


  /*! void SceneObject::setMaterial(const Material& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::setMaterial( const Material& m ) {

    _material = m;
  }


  void SceneObject::setMatrix( const HqMatrix<float,3>& mat ) {

    _matrix = mat;
  }


  /*! void SceneObject::setSurroundingSphere(const Sphere<float,3>& b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::setSurroundingSphere(const Sphere<float,3>& b) {

    _sphere = b;
  }


  /*! void SceneObject::_simulate( double dt )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::simulate( double dt ) {

    glPushMatrix();
    localSimulate(dt);
    glPopMatrix();

    for(int i=0; i< _children.size(); i++)
      _children[i]->simulate(dt);
  }

  /*! void SceneObject::translate(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::translate(const Vector<float,3>& trans_vector) {

    _matrix.translate(trans_vector);
  }


  /*! void SceneObject::translateGlobal(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::translateGlobal(const Vector<float,3>& trans_vector) {

    _matrix.translateGlobal(trans_vector);
  }


  /*! void SceneObject::updateSurroundingSphere(const Point<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::updateSurroundingSphere(const Point<float,3>& p) {

    _sphere += p;
  }

}

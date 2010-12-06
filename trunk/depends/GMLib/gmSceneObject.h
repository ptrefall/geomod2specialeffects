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



/*! \file gmSceneObject.h
 *  \brief Interface to the Scene Object class
 *
 *  Pending Detailed Documentation
 *
 *  \date   2008-07-22
 *
 *  \todo
 *  - Move variable documentation physicaly out of the header file.
 *  - Translage documentation text for the class, from Norwegian to English
 */

#ifndef __gmSCENEOBJECT_H__
#define __gmSCENEOBJECT_H__


// STL includes
#include <string>

// local
#include "gmMaterial.h"
#include "gmFrustum.h"
#include "gmScaleObject.h"




namespace GMlib{


  class Camera;
  class Scene;
  class Light;
  class Visualizer;


  enum GM_SO_TYPE {

    // Basic Types
    GM_SO_TYPE_SCENEOBJECT                    = 0x0001,
    GM_SO_TYPE_CAMERA                         = 0x0002,
    GM_SO_TYPE_LIGHT                          = 0x0003,
    GM_SO_TYPE_SELECTOR                       = 0x0050,
    GM_SO_TYPE_SELECTOR_GRID                  = 0x0051,

    // Point
    GM_SO_TYPE_POINT                          = 0x0200,

    // Curves
    GM_SO_TYPE_CURVE                          = 0x1000,
    GM_SO_TYPE_CURVE_BEZIER                   = 0x1001,
    GM_SO_TYPE_CURVE_BSPLINE                  = 0x1002,
    GM_SO_TYPE_CURVE_ERBS                     = 0x1003,

    // Surfaces
    GM_SO_TYPE_SURFACE                        = 0x2000,
    GM_SO_TYPE_SURFACE_BEZIER                 = 0x2001,
    GM_SO_TYPE_SURFACE_BSPLINE                = 0x2002,
    GM_SO_TYPE_SURFACE_ERBS                   = 0x2003,

    // Volumes
    GM_SO_TYPE_VOLUME                         = 0x3000
  };








  /*! \class SceneObject gmSceneObject.h <gmSceneObject>
   *  \brief SceneObject is the base class for anything that steps onto a Scene
   *
   * 	It contains as private, a unique name for indentification used in Select(), and an array containg all its children.
   *
   * 	Further, as protected members, two matrices for local transformation of the object, and a SurroundingSphere that always should be made.
   *
   *
   * 				Det er to virtuelle funksjoner localDisplay og localSelect
   * 					som alle avledede klasser må ha sin versjon av.
   * 				Arbeidsdelingen er slik at display og select foretar
   * 					transformasjonen lagret i matrix, og displayer alle
   * 					sub-objektene til objektet. Men etter transformasjonen
   * 					og før sub-objektene displayes kalles localDisplay
   * 					(eventuelt localSelect). I localDisplay kan en så
   * 					displaye det som ikke displayes i sub-objektene og/eller
   * 					foreta transformasjoner av sub-objekter for
   * 					å simulere bevegelser.
   * 				Det er også en insertSubObject-funksjon som avledede klasser
   * 				    kan bruke for å lage sub-objekt. Hvis en avledet klasse
   * 					trenger tilgang til et objekt for bevegelsessimulering
   * 					bør den lage en egen peker for det.
   * 		public:
   * 				Konstuktør med mulige default verdier og sletter
   * 				En display funksjon for displaying av objektet.
   * 				En select funksjon for plukking(select) av objektet med mus.
   * 				En simulate funksjon for at objektet kan bevege subobjekter.
   * 				En find funksjon for å finne en funksjon med et gitt navn.
   * 				En rotate, scale og translate funksjon for å
   * 				   posisjonere objektet relativt i forhold til morsobjektet
   */
  class SceneObject {
  public:

    SceneObject(
      const Vector<float,3>& trans  = Vector3D<float>(0,0,0),
      const Point<float,3>&  scale  = Point3D<float>(1,1,1),
      const Vector<float,3>& rotate = Vector3D<float>(1,0,0),
      Angle a=0);

    SceneObject( const SceneObject& d );
    virtual ~SceneObject();

    virtual void                edit(int selector_id);
    virtual void                edit(SceneObject* lp);
    virtual void                edit();
    virtual void                editPos(Vector<float,3> delta);
    virtual void                enableChildren( bool enable = true );
    SceneObject*                find(unsigned int name);
    bool                        flipSelected();
    Point<float,3>              getCenterPos() const;
    Array<SceneObject*>&        getChildren();
    const Color&                getColor() const;
    Color&                      getColor();
    virtual std::string         getIdentity() const;
    const Material&             getMaterial() const;
    Material&                   getMaterial();
    virtual HqMatrix<float,3>&  getMatrix();
    const HqMatrix<float,3>&    getMatrixGlobal() const;
    const HqMatrix<float,3>&    getMatrixParentGlobal() const;
    unsigned int                getName() const;
    SceneObject*                getParent();
    Scene*                      getScene();
    bool                        getSelected();
    Sphere<float,3>             getSurroundingSphere() const;
    Sphere<float,3>             getSurroundingSphereClean() const;
    int                         getTypeId();
    const Array<Visualizer*>&   getVisualizers() const;
    void                        insert(SceneObject* obj);
    virtual void                insertVisualizer( Visualizer* visualizer );
    bool                        isCollapsed() const;
    bool                        isLighted() const;
    bool                        isOpaque() const;
    bool                        isSelected() const;
    virtual bool                isVisible() const;
    void                        remove(SceneObject* obj);
    virtual void                removeVisualizer( Visualizer* visualizer );
    virtual void                rotate(Angle a, const Vector<float,3>& rot_axel);
    virtual void                rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    virtual void                rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                scale(const Point<float,3>& scale_factor);
    virtual void                selectEvent(int selector_id);
    virtual void                setCollapsed(bool c);
    void                        setColor( const Color& c );
    void                        setLighted( bool lighted );
    void                        setMaterial(const Material& m);
    void                        setMatrix( const HqMatrix<float,3>& mat );
    void                        setOpaque( bool o );
    void                        setParent(SceneObject* obj);
    void                        setSelected(bool s);
    virtual void                setVisible( bool v, int prop = 0 );
    virtual bool                toggleCollapsed();
    virtual bool                toggleVisible();
    virtual void                translate(const Vector<float,3>& trans_vector);
    virtual void                translateGlobal(const Vector<float,3>& trans_vector);




  protected:

    friend class Scene;
    friend class Camera;

    int                         _type_id;
    Array<SceneObject*>	        _children;
    Scene*                      _scene;		//! Den aktuelle scenen til displayhierarkiet
    SceneObject*                _parent;	//! the mother in the hierarchy (tree). moved here from private
    HqMatrix<float,3>           _matrix;	//! The difference matrix from mother to this.
    HqMatrix<float,3>           _present;	//! The difference matrix from global to this.
    ScaleObject                 _scale;		//! The scaling for this and the children.
    bool                        _local_cs;	//! Using local coordinate system, default is true
    bool                        _active;		//! This variable is only for camera.
    Sphere<float,3>             _global_sphere;			//! for this object
    Sphere<float,3>             _global_total_sphere;	//! included all children
    bool                        _selected;
    bool                        _visible;	//! culling on invisible items
    bool                        _collapsed;	//! represented by a small cube
    unsigned int                _collapsed_dlist;
    Material                    _material;
    Color                       _color;
    bool                        _lighted;
    bool                        _opaque;
    Array<Visualizer*>          _visualizers;

    virtual void                culling( Array<SceneObject*>&, const Frustum& );
    virtual void                displayCollapsed();
    virtual void                generateCollapsedDList();
    virtual void                localDisplay();
    virtual void                localDisplayActive();
    virtual void                localDisplaySelection();
    virtual void                localSelect();
    virtual void                localSimulate(double dt);
    void                        reset();
    void                        setSurroundingSphere( const Sphere<float,3>& b );
    void                        updateSurroundingSphere( const Point<float,3>& p );


    virtual void                simulate( double dt );


  private:
    static unsigned int         _free_name;	//! For automatisk name-generations.
    unsigned int                _name;		//! Unic name for this object, used for selecting
    Sphere<float,3>             _sphere;	//! Surrounding sphere for this object

    void                        _display();
    void                        _displayActive();
    void                        _displaySelection();
    void                        _fillObj( Array<SceneObject*>& );
    int                         _prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* mother = 0);
    virtual void                _prepareDisplay(const HqMatrix<float,3>& m);
    void                        _select(int what = -1);



  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  public:

    template <typename T_Stream>
    friend T_Stream& operator << ( T_Stream& out, SceneObject& s ) {

      out << s._type_id << GMseparator::Object;
      out << s._matrix  << GMseparator::Object
          << s._scale   << GMseparator::Object;

  /*		if(st)
      {
        out << _object.size() << GMseparator::Object;
        for(int i=0; i<_object.size(); i++)
          if(st>1 || (_object[i]->typeId() != 2))
            out << *(_object[i]);
      }*/
      return out;
    }

    template <typename T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, SceneObject& s ) {

      static Separator os(GMseparator::Object);

      in >> s._type_id  >> os;
      in >> s._matrix   >> os >> s._scale >> os;
  /*		if(st)
      {
        int nr;
        in >> nr >> os;
        for(int i=0; i<nr; i++)
            _object += newDisplayObject(in);
      }*/
      return in;
    }

    template <typename T_Stream>
    SceneObject( T_Stream& in, int st ) {

      in >> *this;

      _name	      = _free_name++;
      _active	    = false;
      _local_cs   = true;
      _visible    = true;
      _collapsed  = false;
    }

    #endif

  };


}


// Include inline SceneObject class implementations
#include "gmSceneObject.c"



#endif  // __gmSCENEOBJECT_H__

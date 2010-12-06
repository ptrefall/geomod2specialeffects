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



/*! \file gmSelector.c
 *  \brief Pending Description
 *
 *  Detailed File Description
 *
 *  \date   2008-08-04
 */



#include "gmSphere3D.h"

namespace GMlib {


  template <typename T, int n>
  int Selector<T,n>::_display_list = 0;

  template <typename T, int n >
  unsigned int Selector<T,n>::_no_selectors = 0;



  /*! Selector<T,n>::Selector( Point<T,n>& mp, int id, SceneObject* parent, T r, const Color& c, Selector<T,n>* root )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  Selector<T,n>::Selector( Point<T,n>& mp, int id, SceneObject* parent, T r, const Color& c, Selector<T,n>* root )
    : _position(mp) {

    Sphere<float,3> ts(Point<float,3>(float(0)),0.866);
    setSurroundingSphere(ts);
    _type_id	= GM_SO_TYPE_SELECTOR;
    _id			= id;
    _parent		= parent;
    _enabled			= true;
    _default	= c;
    _marked		= c.getInverse();
    _selected	= false;
    _root		= root;
    translate( _position.toFloat() );
    if(r != 1.0) scale(Vector3D<float>(r,r,r));
    if(!_display_list) _makeDisplayList();
    _no_selectors++;
  }


  /*! Selector<T,n>::Selector(const Selector<T,n>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  Selector<T,n>::Selector(const Selector<T,n>& s) : DisplayObject(s), _position( s._position ) {

    _type_id	= GM_SO_TYPE_SELECTOR;
    _id			= s._id;
    _parent		= s._parent;
    _enabled			= s._enabled;
    _default	= s._default;
    _marked		= s._marked;
    _root		= s._root;
    _selected	= false;
    if(!_display_list) _makeDisplayList();
    _no_selectors++;
  }



  /*!virtual Selector<T,n>::~Selector()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Selector<T,n>::~Selector() {

    _no_selectors--;

    if( _display_list && !_no_selectors ) {
      glDeleteLists(_display_list, 1);
      _display_list = 0;
    }
  }



  /*!
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  void Selector<T,n>::_makeDisplayList() {

    _display_list = glGenLists(1);

    Sphere3D rep( 0.07, 10, 10 );
    glNewList(_display_list, GL_COMPILE);	// Lager displayliste for en kube
      rep.display();
//      glBegin(GL_QUAD_STRIP);
//        glVertex3f( 0.5,-0.5,-0.5 ); glVertex3f( 0.5, 0.5,-0.5 );
//        glVertex3f( 0.5,-0.5, 0.5 ); glVertex3f( 0.5, 0.5, 0.5 );
//        glVertex3f(-0.5,-0.5, 0.5 ); glVertex3f(-0.5, 0.5, 0.5 );
//        glVertex3f(-0.5,-0.5,-0.5 ); glVertex3f(-0.5, 0.5,-0.5 );
//        glVertex3f( 0.5,-0.5,-0.5 ); glVertex3f( 0.5, 0.5,-0.5 );
//      glEnd();
//      glBegin(GL_QUADS);
//        glVertex3f(-0.5,-0.5,-0.5 ); glVertex3f( 0.5,-0.5,-0.5 );
//        glVertex3f( 0.5,-0.5, 0.5 ); glVertex3f(-0.5,-0.5, 0.5 );
//        glVertex3f(-0.5, 0.5,-0.5 ); glVertex3f(-0.5, 0.5, 0.5 );
//        glVertex3f( 0.5, 0.5, 0.5 ); glVertex3f( 0.5, 0.5,-0.5 );
//      glEnd();
    glEndList();
  }


  /*! void Selector<T,n>::allEnable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  all children on
   */
  template <typename T, int n>
  void Selector<T,n>::allEnable() {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)
        s->enableAll();
    }
  }


  /*! void Selector<T,n>::allDisable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  all children off
   */
  template <typename T, int n>
  void Selector<T,n>::allDisable() {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)
        s->disableAll();
    }
  }




  /*! void	Selector<T,n>::disable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::disable() {

    _enabled=false;
    allEnable();

    if(_root)
      _root->enable();
  }


  /*! void	Selector<T,n>::disableAll()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::disableAll() {

    _enabled = false;
    allEnable();
  }


  /*! virtual void	Selector<T,n>::edit()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::edit() {

    _parent->selectEvent(_id);
  }


  /*! void	Selector<T,n>::editPos(Vector<float,3> dp)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::editPos(Vector<float,3> dp) {

    HqMatrix<float,3> invmat = _present;
    invmat.invertOrthoNormal();
    _position+=Point<T,n>(invmat*dp);
    translate(invmat*dp);
    _parent->edit(_id);
  }


  /*! void	Selector<T,n>::enable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::enable() {

    _enabled=true;

    if( _root )
      _root->disable();

    allDisable();
  }


  /*! void	Selector<T,n>::enableAll()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::enableAll() {

    _enabled = true;
    allEnable();
  }


  /*! std::string	Selector<T,n>::getIdentity() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  std::string	Selector<T,n>::getIdentity() const {

    return "Selector";
  }


  /*! bool	Selector<T,n>::isEnabled() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Is the children or my self on?
   */
  template <typename T, int n>
  bool	Selector<T,n>::isEnabled() const {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)
        if(s->isEnabled())
          return true;
    }
    return _enabled;
  }


  /*! void Selector<T,n>::localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  void Selector<T,n>::localDisplay() {

    if(_enabled) {

      glPushAttrib( GL_LIGHTING_BIT );
        glDisable(GL_LIGHTING);
        if(_selected)	glColor(_marked);
        else			glColor(_default);
        glCallList(_display_list);
      glPopAttrib();
    }
  }


  /*! void Selector<T,n>::localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  void Selector<T,n>::localSelect() {

    if(_enabled)
       glCallList(_display_list);
  }


  /*! bool Selector<T,n>::toggle()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  visibility
   */
  template <typename T, int n>
  inline
  bool Selector<T,n>::toggle() {

    _enabled=!_enabled;
    return _enabled;
  }


  /*! void Selector<T,n>::update()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void Selector<T,n>::update() {

    Vector<T,n> d= _position - _pos;
    translate(d.toFloat());
    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s = dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)  s->translate(-d.toFloat());  // don't bring children
    }
  }


  /*! void Selector<T,n>::update( const Point<T,n>& p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void Selector<T,n>::update( const Point<T,n>& p ) {

    Vector<T,n> d=p-_position;
    _position=p;
    translate(d.toFloat());
    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s = dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)  s->translate(-d.toFloat());  // don't bring children
    }
  }

}

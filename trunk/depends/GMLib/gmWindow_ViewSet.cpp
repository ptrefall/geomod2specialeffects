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



/*! \file gmWindow_ViewSet.cpp
 *	\brief Pending Description
 *
 *  Implementation of the ViewSet class.
 *
 *  \date   2008-07-28
 */



// Header
#include "gmWindow.h"


namespace GMlib {



  /*! ViewSet::ViewSet(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::ViewSet(Camera* cam) : _root(cam) {

    if(cam)	_cameras += cam;
    _border_color = GMcolor::White;
  }


  /*! ViewSet::ViewSet(const ViewSet& viewset)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::ViewSet(const ViewSet& viewset) {

    int i;
    _cameras = viewset._cameras;
    _vp_w = viewset._vp_w;
    _vp_h = viewset._vp_h;
    _border_color = viewset._border_color;
    _root = viewset._root;
    for( i = 0; i < viewset._borders.getSize(); i++)
      _borders += new ViewBorder( *( viewset._borders(i)) );
    _root._corr( _borders ,viewset._borders );
    for( i = 0; i < _borders.getSize(); i++ )
      _borders[i]->_corr( _borders, viewset._borders );
    prepare(_vp_w, _vp_h );
  }


  /*! ViewSet::~ViewSet()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet::~ViewSet() {

    for(int i=0; i<_borders.getSize(); i++)	delete _borders[i];
  }


  /*! ViewSet& ViewSet::operator=(const ViewSet& viewset)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  ViewSet& ViewSet::operator=(const ViewSet& viewset) {

    int i;
    for(i=0; i<_borders.size(); i++) delete _borders[i];
    _borders.resetSize();
    _cameras = viewset._cameras;
    _vp_w = viewset._vp_w;
    _vp_h = viewset._vp_h;
    _border_color = viewset._border_color;
    _root = viewset._root;
    for(i=0; i<viewset._borders.getSize(); i++)
      _borders += new ViewBorder(*(viewset._borders(i)));
    for(i=0; i<_borders.getSize(); i++)
      _borders[i]->_corr(_borders, viewset._borders);
    _root._corr( _borders, viewset._borders);
    prepare( _vp_w, _vp_h);
    return *this;
  }


  /*! void ViewSet::_drawCamera(bool stereo)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_drawCamera(bool stereo) {

    _drawBorder();
    for( int i = 0; i < _cameras.getSize(); i++ )
      _cameras[i]->go( stereo );
  }


  /*! bool ViewSet::_find(int x, int y, Camera*& cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *
   *	\param[in] x
   *	\param[in] y
   *	\param[out] cam
   *	\return Status result of the search.
   */
  bool ViewSet::_find(int x, int y, Camera*& cam) {

    cam = 0;
    _selected_borders.resetSize();
    _root._find( x, y, cam, _selected_borders);

    if( _selected_borders.getSize() >0 )
      return false;

    return true;
  }


  /*! int ViewSet::getSize()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  int ViewSet::getSize() {

    return _cameras.getSize();
  }


  /*! void ViewSet::_reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_reset() {

    _selected_borders.resetSize();
  }


  /*! void ViewSet::_setBorderColor(const Color& bc)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void ViewSet::_setBorderColor(const Color& bc) {

    _border_color = bc;
  }


  /*! Camera* ViewSet::operator[](int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera* ViewSet::operator[](int i) {

    return _cameras[i];
  }

}

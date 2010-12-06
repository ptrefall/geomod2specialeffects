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



/*! \file gmWindow_View.c
 *	\brief Inline View class implementations
 *
 *  Inline implementations of the View class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {



  /*! View::View(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(Camera* cam) {

    _camera = cam;
    _border = 0;
  }


  /*! View::View(ViewBorder* border)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(ViewBorder* border) {

    _camera = 0;
    _border = border;
  }


  /*! View::View(const View& view)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(const View& view) {

    _camera = view._camera;
    _border = view._border;
  }


  /*! void View::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void View::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow) {

    if( _border )
      _border = nw[ow.index(_border)];
  }


  /*! int View::_getSize( bool split_vertically )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int View::_getSize( bool split_vertically ) {

    if( _border )
      return _border->_getSize( split_vertically );
    else {

      int w1, w2, h1, h2;
      _camera->getViewport( w1, w2, h1, h2 );
      if( split_vertically )
        return w2 - w1;
      else
        return h2 - h1;
    }
  }


  /*! bool View::_isCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool View::_isCamera(Camera* cam)	{

    return _camera == cam;
  }


  /*! void View::_split(Camera* new_cam, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Splitting this in two
   */
  inline
  void View::_split(Camera* new_cam, bool split_vertically, double d) {

    if(_camera) {

      _border = new ViewBorder( _camera, new_cam, split_vertically, d );
      _camera = 0;
    }
    else {

      _border = 0;
      _camera = new_cam;
    }
  }

}

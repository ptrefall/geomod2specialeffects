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



/*! \file gmWindow_ViewBorder.c
 *	\brief Inline ViewBorder class implementations
 *
 *  Inline implementations of the ViewBorder class.
 *
 *  \date   2008-08-03
 */



namespace GMlib {



  /*! ViewBorder::ViewBorder( Camera* cam_to_split, Camera* new_cam, bool v, double r )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  ViewBorder::ViewBorder( Camera* cam_to_split, Camera* new_cam, bool v, double r )
    : _vertical(v), _displacement(r), _child_lt(cam_to_split), _child_rb(new_cam)
  {}


  /*! ViewBorder::ViewBorder(const ViewBorder& w)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  ViewBorder::ViewBorder(const ViewBorder& w)
    : _vertical(w._vertical), _displacement(w._displacement), _child_lt(w._child_lt), _child_rb(w._child_rb)
  {}


  /*! void ViewBorder::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow) {

    _child_lt._corr( nw, ow );
    _child_rb._corr( nw, ow );
  }


  /*! void ViewBorder::_display()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_display() {

    glRecti( _x1, _y1, _x2, _y2 );
  }


  /*! void ViewBorder::_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders) {

    if(x>(_x1-5) && x<(_x2+5) && y>(_y1-5) && y<(_y2+5)) borders += this;

    _child_lt._find(x,y,cam,borders);
    _child_rb._find(x,y,cam,borders);
  }


  /*! int  ViewBorder::_getSize(bool vertical)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int  ViewBorder::_getSize(bool vertical) {

    if(vertical == _vertical)
      return _child_lt._getSize(vertical) + _child_rb._getSize(vertical);
    else
      return min( _child_lt._getSize(vertical), _child_rb._getSize(vertical) );
  }


  /*! View* ViewBorder::_hasCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View* ViewBorder::_hasCamera(Camera* cam) {

    if(_child_lt._isCamera(cam))
      return &_child_rb;
    else if(_child_rb._isCamera(cam))
      return &_child_lt;
    else
      return 0;
  }


  /*! bool ViewBorder::_isVertical()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool ViewBorder::_isVertical() {

    return _vertical;
  }


  /*! void ViewBorder::_move(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_move(int x, int y) {

    int l_size = _child_lt._getSize(_vertical);
    int r_size = _child_rb._getSize(_vertical);

    if(_vertical) {

      l_size = _x1-l_size;
      r_size += _x2;
      if((x > l_size && x < _x1)||(x > _x2 && x < r_size))
        _displacement = (double)(x-l_size)/(r_size-l_size);
    }
    else
    {
      l_size = _y1-l_size;
      r_size += _y2;
      if((y > l_size && y < _y1)||(y > _y2 && y < r_size))
        _displacement = (double)(y-l_size)/(r_size-l_size);
    }
  }


  /*! void ViewBorder::_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders) {

    borders.insert(this);
    if(_vertical) {

      _x1 = x1 + int(_displacement*(x2-x1)) - 1;
      _x2 = _x1 + 2;
      _y1 = y1-2;
      _y2 = y2+2;
      _child_lt._prepare( x1, y1, _x1, y2, borders );
      _child_rb._prepare( _x2, y1, x2, y2, borders );
    }
    else {

      _y1 = y1 + int( _displacement * (y2-y1) ) - 1;
      _y2 = _y1 + 2;
      _x1 = x1-2;
      _x2 = x2+2;
      _child_lt._prepare( x1, y1, x2, _y1, borders );
      _child_rb._prepare( x1, _y2, x2, y2, borders );
    }
  }


  /*! void ViewBorder::_removeCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_removeCamera(Camera* cam) {

    _child_lt._removeCamera(cam);
    _child_rb._removeCamera(cam);
  }


  /*! void ViewBorder::_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d) {

    _child_lt._splitCamera( cam_to_split, new_cam, split_vertically, d );
    _child_rb._splitCamera( cam_to_split, new_cam, split_vertically, d );
  }

}

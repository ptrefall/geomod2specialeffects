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



/*! \file gmSelectorGrid.c
 *  \brief Pending Description
 *
 *  Detailed File Description
 *
 *  \date   2008-08-04
 */



namespace GMlib {




  /*! SelectorGrid::SelectorGrid( Point<T,n>& mp, SceneObject* parent, const Color& c )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  SelectorGrid<T,n>::SelectorGrid( Point<T,n>& mp, SceneObject* parent, const Color& c ) : Selector<T,n>( mp, -1, parent ) {

    this->_type_id	= GM_SO_TYPE_SELECTOR_GRID;
    this->_default	= c;
    this->_marked		= c.getInverse();
    this->_root		= NULL;
    this->_scale.reset();
    translate( -mp.toFloat());

    Sphere<float,3> ts(Point<float,3>(float(0)),0.866);
    this->setSurroundingSphere(ts);
  }


  /*! void SelectorGrid::add(Point<T,n>& p1, Point<T,n>& p2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  inline
  void SelectorGrid<T,n>::add(Point<T,n>& p1, Point<T,n>& p2) {

    _c += &p1;
    _c += &p2;
  }



  /*! void SelectorGrid::localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  add a new line
   */
  template <typename T, int n>
  void SelectorGrid<T,n>::localDisplay() {

    if(this->_enabled) {

      glPushAttrib( GL_LIGHTING_BIT ); {

        glDisable( GL_LIGHTING );

        if(this->_selected)
          glColor(this->_marked);
        else
          glColor(this->_default);

        glBegin(GL_LINES); {

          for(int i=0;i<_c.getSize();i++)
            glPoint(_c[i]);

        } glEnd();

      } glPopAttrib();
    }
  }


  /*! void SelectorGrid::localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void SelectorGrid<T,n>::localSelect() {}

}

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



/*! \file gmSelector.h
 *  \brief Interface to the Selector class
 *
 *  Interface to the Selector class
 *
 *  \date 2008-08-04
 */


#ifndef __gmSELECTOR_H__
#define __gmSELECTOR_H__


#include "gmDisplayObject.h"


namespace GMlib{


  /*! \class Selector gmSelector.h <gmSelector>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  class Selector: public DisplayObject {
  public:
    Selector(const Selector<T,n>& s);
    Selector(Point<T,n>& mp, int id, SceneObject* parent, T r=1, const Color& c = Color(0.0,0.0,0.7), Selector<T,n>* root=NULL );
    virtual ~Selector();

    void	                editPos(Vector<float,3> dp);
    void	                disable();
    void	                disableAll();
    void	                enable();
    void	                enableAll();
    bool	                isEnabled() const;
    bool	                toggle();
    void                  update();
    void	                update(const Point<T,n>& p);

    // *******************
    // Derived functions
    // from SceneObject
    virtual void	        edit();
    std::string	          getIdentity() const;


  protected:
    bool			            _enabled;
    Selector<T,n>*        _root;
    Color		            _default;
    Color		            _marked;

    void                  allDisable();
    void                  allEnable();
    void                  localDisplay();
    void                  localSelect();


  private:
    static unsigned int   _no_selectors;
    static int		        _display_list;
    int				            _id;
    SceneObject*	        _parent;
    Point<T,n>&		        _position;

    void                  _makeDisplayList();

  }; // END class Selector

} // END namespace GMlib

// Include inline Selector class implementations
#include "gmSelector.c"






#endif // __gmSELECTOR_H__

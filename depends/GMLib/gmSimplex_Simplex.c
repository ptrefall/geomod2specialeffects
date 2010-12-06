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



/*! \file gmSimplex_Simplex.c
 *  File Description
 *
 *  \date   2008-06-17
 */


namespace GMlib {






  /*! Simplex<T,n,m>::Simplex(const Point<T,n>& p)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex() {
    (*this)[0] = Point<T,n>( T(0) );
  }


/*! Simplex<T,n,m>::Simplex(const Point<T,n>& p)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex( const Point<T,n>& p ) {
    (*this)[0] = p;
  }


  /*! Simplex<T,n,m>::Simplex(const Point<T,n>& p1, const Point<T,n>& p2)
   *  \brief Constructor
   *
   *  Detailed description of
   *  the constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex(const Point<T,n>& p1, const Point<T,n>& p2) {
    (*this)[0] = p1;
    (*this)[1] = p2;
  }


  /*! Simplex<T,n,m>::Simplex(const Point<T,n>& p1, const Point<T,n>& p2, const Point<T,n>& p3)
   *  \brief  Constructor
   *
   *  Detailed description of
   *  the constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex(const Point<T,n>& p1, const Point<T,n>& p2, const Point<T,n>& p3) {
    (*this)[0] = p1;
    (*this)[1] = p2;
    (*this)[2] = p3;
  }


  /*! Simplex<T,n,m>::Simplex(const Arrow<T,n>& a)
   *  \brief  Constructor
   *
   *  Detailed description of
   *  the constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex(const Arrow<T,n>& a) {
    (*this)[0] = a.pos();
    (*this)[1] = a.pos()+a.dir();
  }


  /*! Simplex<T,n,m>::Simplex(const Vector<Point<T,n>,m>& s)
   *  \brief Constructor
   *
   *  Detailed description of
   *  the constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex(const SubSpace<T,n,m-1>& s) {
    (*this)[0] = s.posC();
    for(int i=1; i<m; i++)(*this)[i] = s.posC()+s.dirC(i-1);
  }


  /*! Simplex<T,n,m>::Simplex(const Vector<Point<T,n>,m>& s)
   *  \brief  Default Copy Constructor
   *
   *  Detailed description of the default
   *  copy constructor
   */
  template <typename T, int n, int m>
  inline
  Simplex<T,n,m>::Simplex( const Vector<Point<T,n>,m>& copy ) :  Vector<Point<T,n>,m>(copy) {}


  ///*! Simplex<T,n,m>::Point<T,n>	closestPoint(const Point<T,n>& p)
  // *  \brief  Returns the state set
  // *
  // *  Detailed description
  // *
  // *  \return returns an int representing the state set
  // */
  //template <typename T, int n, int m>
  //inline
  //Point<T,n> Simplex<T,n,m>::closestPoint(const Point<T,n>& p) const {
  //}

  /*! Simplex<T,n,m>::Vector<T,n> distanceVector(const Point<T,n>& p) const
   *  \brief  Returns the state set
   *
   *  Detailed description
   *
   *  \return returns an int representing the state set
   */
  template <typename T, int n, int m>
  inline
  Vector<T,n> Simplex<T,n,m>::distanceVector( const Point<T,n>& p ) const {

    return (p-closestPoint(p)).toVector();
  }

  /*! Simplex<T,n,m>::T distanceTo(const Point<T,n>& p) const
   *  \brief  Returns the state set
   *
   *  Detailed description
   *
   *  \return returns an int representing the state set
   */
  template <typename T, int n, int m>
  inline
  T Simplex<T,n,m>::distanceTo( const Point<T,n>& p ) const {

    return distanceVector(p).length();
  }

  /*! Simplex<T,n,m>::T distanceTo(const Point<T,n>& p) const
   *  \brief  Returns the state set
   *
   *  Detailed description
   *
   *  \return returns an int representing the state set
   */
  template <typename T, int n, int m>
  inline
  T Simplex<T,n,m>::distanceAlong( const Point<T,n>& p, int i ) const {
    return ( p - this->pos() ) * this->dir( i ) / ( this->dir(i).length() );
  }

  /*! Simplex<T,n,m>::Vector<Simplex<T,n,m-1>,m+2> sub()
   *  \brief  Returns the state set
   *
   *  Detailed description
   *
   *  \return returns an int representing the state set
   */
  template <typename T, int n, int m>
  inline
  Vector<Simplex<T,n,m-1>,m+2> Simplex<T,n,m>::sub() {
  }

  /*! Point<T,n> Simplex<T,n,m>::closestPoint(const Point<T,n>& p) const
   *  \brief  Returns the state set
   *
   *  Detailed description
   *
   *  \return returns an int representing the state set
   */
  template <typename T, int n, int m>
  inline
  Point<T,n> Simplex<T,n,m>::closestPoint(const Point<T,n>& p) const {
    /*
    Matrix<T,m-1,n> v;
    for(int i=1; i<m; i++) v[i-1] = (*this)(i)-(*this)(0);atu
    SqMatrix<T,m-1> ms = v.multMeTrans();
    ms.invert();
    cout << "MS:\n" << ms << endl;
    cout << "X:\n" << (ms*(v*p)) << endl << endl;
    return (*this)(0) + (ms*(v*p))*v;
    */

    Matrix<T,m,n+1> v;// = reinterpret_cast<const Vector<Vector<T,n>,m>&>(*this);
    for(int i=1; i<m; i++)
    {
      v[i] =  reinterpret_cast<const Vector<T,n+1>&>((*this)(i));
      v[i][n] = T(1);
    }

    Point<T,n+1> pp = p;
    pp[n] = T(1);
    SqMatrix<T,n+1> ms = v.multTransMe();
    std::cout << "MS:\n" << ms << std::endl;
    ms.invert();
    std::cout << "MS:\n" << ms << std::endl;
    //	UnitVector<T,m> x = ms*(pp*v);
    //cout << "X:\n" << x << endl << endl;

    //	return x*v;
    return p;
  }

}

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



/*! \file gmDVector.c
 *
 *  Implementation of the Dynamic Vector class
 *
 *  \date   2008-07-17
 */


// STL includes
#include <algorithm>



namespace GMlib {


  /*! DVector<T>::DVector(int i)
   *  \brief
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>::DVector(int i) {
    _p = (i>4 ? new T[i]:_init);
    _n=i;
  }


  /*! DVector<T>::DVector(int i, T val)
   *  \brief Standard initializing (all elements equal)
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>::DVector(int i, T val) {
    _p = (i>4 ? new T[i]:_init);
    _n=i;
    for( int j = 0; j < _n; j++ )
      _p[j] = val;
  }


  /*! DVector<T>::DVector(int i, const T p[])
   *  \brief Standard initializing from c-array
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>::DVector(int i, const T p[]) {
    _p = (i>4 ? new T[i]:_init);
    _n=i;
    _cpy( _p );
  }


  /*! DVector<T>::DVector(const DVector<T>& v)
   *  \brief Copy constructor
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>::DVector(const DVector<T>& v) {
    _n=0; _p = _init;
    _cpy(v);
  }


  /*! DVector<T>::~DVector()
   *  \brief Destructor (Pending documentation)
   *
   *  NB! According to invariant
   */
  template<typename T>
  inline
  DVector<T>::~DVector() {
    if(_p != _init) delete [] _p;
  }


  /*! void  DVector<T>::_cpy(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void  DVector<T>::_cpy(const DVector<T>& v)
  {
    if(v._n>4 && v._n>_n)
    {
      if (_p != _init) delete [] _p;
      _p = new T[v._n];
    }
    _n = v._n;
    for(int i=0; i<_n; i++) _p[i] = v._p[i];
  }


  /*! void  DVector<T>::_cpy(const T p[])
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void  DVector<T>::_cpy(const T p[]) {

    for(int i=0; i<_n; i++) _p[i] = p[i];
  }


  /*! void DVector<T>::append(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void DVector<T>::append(const DVector<T>& v) {
    if(v._n > 0)
    {
      int j = _n + v._n;
      if(j>4)
      {
        T* tmp = new T[j];
        for(j=0; j<_n; j++) tmp[j] = _p[j];
        if(_p != _init) delete [] _p;
        _p = tmp;
      }
      for(j=0; j<v._n; j++) _p[j+_n] = v(j);
      _n += v._n;
    }
  }


  /*! void DVector<T>::append(T val, int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void DVector<T>::append(T val, int i) {
    if(i < 1) return;
    increaseDim(i, val);
  }


  /*! void DVector<T>::clear(T v)
   *  \brief All elements set to "v", (dimension not changed).
   *
   *  All elements set to "v", (dimension not changed).
   */
  template <typename T>
  inline
  void DVector<T>::clear(T v) {
    for(int i=0; i<_n; i++) _p[i] = v;
  }


  /*! int DVector<T>::getDim() const
   *  \brief Returning the vector dimention
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  int DVector<T>::getDim() const	{
    return _n;
  }


  /*! T DVector<T>::getLength() const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T DVector<T>::getLength() const {
    T r=T(0);
    for(int i=0; i<_n; i++) r += (*this)(i)*(*this)(i);
    return sqrt(r);
  }


  /*! T* DVector<T>::getPtr() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T* DVector<T>::getPtr() const {
    return _p;
  }


  /*! DVector<T>& DVector<T>::getReversed() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::getReversed() const {
    static DVector<T> ret;
    ret.setDim(_n);
    for(int i=0; i<_n; i++)
      ret[i] = _p[_n-1-i];
    return ret;
  }


  /*! DVector<T>& DVector<T>::getSubVector(int start, int end) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::getSubVector(int start, int end) const {
    static DVector<T> ret;
    if(start < 0)	start = 0;
    if(end > _n)		end = _n;
    if(start < end)
    {
      ret.setDim(end-start);
      int u=0;
      for(int i=start; i<end; i++)
        ret[u++] = _p[i];
    }
    else
      ret.setDim(0);
    return ret;
  }


  /*! T& DVector<T>::getSum() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T& DVector<T>::getSum() const {
    static T ret;
    ret = T(0);
    for(int i=0; i<_n; i++) ret += _p[i];
    return ret;
  }


  /*! T& DVector<T>::getSum(int start, int end) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T& DVector<T>::getSum(int start, int end) const {
    static T ret;
    if(start < 0)	start = 0;
    if(end   > _n)	end = _n;
    ret = T(0);
    for(int i=start; i<end; i++) ret += _p[i];
    return ret;
  }


  /*! void  DVector<T>::increaseDim(int i, T val, bool at_end)
   *  \brief Increasing the dimention of the vector.
   *
   *  Increasing the dimention of the vector.
   *  The previous contents is intact, but if "at_end=false"
   *  then the previous contents is moved to the end of the vector.
   *  The new element is initialized by "val".
   */
  template <typename T>
  inline
  void  DVector<T>::increaseDim(int i, T val, bool at_end) {
    if(i>0)
    {
      int j = _n + i;
      int k = (at_end ? _n:0);
      int r = (at_end ? 0:i);
      if(j>4)
      {
        T* tmp = new T[j];
        for(j=r; j<r+_n; j++) tmp[j] = _p[j-r];
        if(_p != _init) delete [] _p;
        _p = tmp;
      }
      else if(!at_end)
        for(j=_n-1; j>=0; j--) _p[j+i] = _p[j];
      for(j=k; j<i+k; j++) _p[j] = val;
      _n += i;
    }
  }


  /*! void DVector<T>::putFirst(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void DVector<T>::putFirst(const DVector<T>& v) {
    if(v._n>0)
    {
      int j = _n+v._n;
      if(j>4)
      {
        T* tmp = new T[j];
        for(j=0; j<_n; j++) tmp[j+v._n] = _p[j];
        if(_p != _init) delete [] _p;
        _p = tmp;
      }
      else
        for(j=_n-1; j>=0; j--) _p[j+v._n] = _p[j];
      for(j=0; j<v._n; j++) _p[j] = v(j);
      _n += v._n;
    }
  }


  /*! void DVector<T>::putFirst(T val, int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void DVector<T>::putFirst(T val, int i) {
    if(i < 1) return;
    increaseDim(i,val,false);
  }


  /*! void  DVector<T>::resetDim(int i)
   *  \brief  Keep the previous contents intact if possible.
   *
   *  Keep the previous contents intact if possible.
   *  Realocating and cleaning up the memory
   *  This function is safe but slow.
   */
  template <typename T>
  inline
  void  DVector<T>::resetDim(int i) {

    int j, k = std::min(i,_n);
    T* tmp = ( i > 4 ? new T[i] : _init );

    for( j = 0; j < k; j++ )
      tmp[j] = _p[j];

    for(; j < i; j++)
      tmp[j] = T();

    if( _p != _init )
      delete [] _p;

    _n = i;
    _p = tmp;
  }


  /*! void  DVector<T>::setDim(int i)
   *  \brief Keep the previous contents intact if possible.
   *
   *  Keep the previous contents intact if possible.
   *  Set dim to i, but if the previous dim is greater than i then
   *  the memory is not realocated and therefor not accessable later!!
   *  This function is the speedy one.
   */
  template <typename T>
  inline
  void  DVector<T>::setDim(int i) {
    if(i>4 && i>_n)
    {
      if( _p != _init ) delete [] _p;
      _p = new T[i];
    }
    _n = i;
  }


  /*! Array<T>&	DVector<T>::toArray() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  Array<T>&	DVector<T>::toArray() const {
    static Array<T> a;
    a.setSize( getDim() );
    for(int i=0; i<_n; i++) a[i] = (*this)(i);
    return a;
  }


  /*! T&  DVector<T>::operator[](int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  T&  DVector<T>::operator[](int i) {
  #ifdef DEBUG
    if (i<0 || i>=_n) cerr << "Error index " << i << " is outside(0," << _n << ")\n";
  #endif
    return _p[i];
  }


  /*! const T&  DVector<T>::operator()(int i) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  const T&  DVector<T>::operator()(int i) const {
  #ifdef DEBUG
    if (i<0 || i>=_n) cerr << "Error index " << i << " is outside(0," << _n << ")\n";
  #endif
    return _p[i];
  }


  /*! bool DVector<T>::operator < (const DVector<T>& v) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  bool DVector<T>::operator < (const DVector<T>& v) const {
    return getLength() < v.getLength();
  }


  /*! DVector<T>& DVector<T>::operator+=(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>& DVector<T>::operator+=(const DVector<T>& v) {
  #ifdef DEBUG
    if (_n != v.getDim())
      cerr << "Vector dimension error, dim=" << _n << " ,dim=" << v._getDim() << endl;
  #endif
    if(_n==0)
    {//This ensures that an empty DVector stil can be += with another DVector.
     //This is usefull with the * and ^ operators which utilize lokal variables that are empty.
     //In other words this makes posible a DVector<DVector<T> > .
      _cpy(v);
    }
    else
    {
      for (int i=0; i <_n; i++) _p[i] += v._p[i];
    }
    return *this;
  }


  /*! DVector<T>& DVector<T>::operator-=(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>& DVector<T>::operator-=(const DVector<T>& v) {
  #ifdef DEBUG
    if (_n != v.getDim())
      cerr << "Vector dimension error, dim=" << _n << " ,dim=" << v.getDim() << endl;
  #endif
    for (int i=0; i <_n; i++) _p[i] -= v._p[i];
    return *this;
  }


  /*! DVector<T>	DVector<T>::operator+(const DVector<T>& a) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>	DVector<T>::operator+(const DVector<T>& a) const {
    DVector<T> na=(*this);
    return na += a;
  }


  /*! DVector<T>	DVector<T>::operator-(const DVector<T>& a) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template<typename T>
  inline
  DVector<T>	DVector<T>::operator-(const DVector<T>& a) const {
    DVector<T> na=(*this);
    return na -= a;
  }


  /*! DVector<T>& DVector<T>::operator*=( double d )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::operator*=( double d ) {
    for(int i=0; i<_n; i++) _p[i] *= d;
    return *this;
  }


  /*! DVector<T>& DVector<T>::operator/=(double d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::operator/=(double d) {
    for(int i=0; i<_n; i++) _p[i] /= d;
    return *this;
  }


  /*! DVector<T> DVector<T>::operator*(double d) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T> DVector<T>::operator*(double d) const {
    DVector<T> ret = *this;
    return ret *= d;
  }


  /*! DVector<T> DVector<T>::operator / (double d) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T> DVector<T>::operator / (double d) const {
    DVector<T> ret = *this;
    return ret /= d;
  }


  /*! DVector<T>& DVector<T>::operator=(const DVector<T>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::operator=(const DVector<T>& v)	{
    _cpy(v); return *this;
  }


  /*! DVector<T>& DVector<T>::operator=(T p[])
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  DVector<T>& DVector<T>::operator=(T p[]) {
    _cpy(p); return *this;
  }

}

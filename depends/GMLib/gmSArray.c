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



/*! \file gmSArray.c
 *
 *  Implementation of the Sortable Array class.
 *
 *  \date   2008-07-09
 */


namespace GMlib {



  template <typename T>
  inline
  SArray<T>::SArray( int n ) : Array<T>(n) {

    _sorted = false;
  }


  template <typename T>
  inline
  SArray<T>::SArray( int n, T t ) : Array<T>(n,t) {

    _sorted = false;
  }


  template <typename T>
  inline
  SArray<T>::SArray( int n, const T* p ) : Array<T>(n,p) {

    _sorted = false;
  }


  template <typename T>
  inline
  SArray<T>::SArray( const Array<T>& ar ) : Array<T>(ar) {

    _sorted = false;
  }


  template <typename T>
  inline
  SArray<T>::SArray( const ArrayT<T>& ar ) : Array<T>(ar) {

    _sorted = false;
  }


  template <typename T>
  inline
  SArray<T>::SArray( const SArray<T>& ar ) : Array<T>(ar) {

    _sorted = ar._sorted;
  }


  template <typename T>
  inline
  void SArray<T>::clear(){

    Array<T>::clear();
    _sorted = false;
  }


  template <typename T>
  void SArray<T>::insertAlways( const T& t, bool first ) {

    int i;

    // Expand the array if nessesary
    this->expand();


    if( _sorted ) {
      for (i = this->_no_elements; i > 0 && t < this->_data_ptr[i-1]; --i) {

        this->_data_ptr[i] = this->_data_ptr[i-1];
      }

      this->_data_ptr[i] = t;

    } else if(first) {
      for(i = this->_no_elements; i > 0; i--) {

        this->_data_ptr[i] = this->_data_ptr[i-1];
      }

      this->_data_ptr[0] = t;

    }
    else {

      this->_data_ptr[this->_no_elements] = t;
    }

    this->_no_elements++;
  }


  template <typename T>
  Array<int> SArray<T>::getSortedIndex() {

    if( this->_no_elements == 0) { return Array<int>(0); }

    int i, j, k;
    Array<int> ar;

    ar.setSize( this->_no_elements );

    for(i = 0; i < this->_no_elements; i++) {
      ar[i] = i;
    }

    for(i = 0; i < this->_no_elements - 1; i++) {
      for(k = i, j = i+1; j < this->_no_elements; j++) {
        if( this->_data_ptr[ar[j]] < this->_data_ptr[ar[k]] ) { k = j; }
      }
      ar.swap(i, k);
    }
    return ar;
  }


  template <typename T>
  inline
  bool SArray<T>::removeIndex( int index ) {

    if( index < 0 || index >= this->_no_elements ) {
      return false;
    }

    // Move array forward
    this->_no_elements--;
    if(_sorted) {
      for(int j = index; j < this->_no_elements; j++) {

        this->_data_ptr[j] = this->_data_ptr[j+1];
      }

    } else if(index != this->_no_elements) {
      this->_data_ptr[index] = this->_data_ptr[this->_no_elements];
    }
    return true;
  }


  template <typename T>
  inline
  void SArray<T>::setSorted( bool sort ) {

    _sorted = sort;
  }


  template <typename T>
  void SArray<T>::sort() {

    int	i,j,k;

    _sorted = true;

    for(i = 0; i < this->_no_elements - 1; i++) {
      for(k = i, j = i+1; j < this->_no_elements; j++) {
        if(this->_data_ptr[j] < this->_data_ptr[k]) { k = j; }
      }

      if(i != k) { this->swap(i, k); }
    }
  }


  template <typename T>
  void SArray<T>::sortD() {

    int	i,j,k;

    _sorted = true;

    for(i = 0; i < this->_no_elements - 1; i++) {
      for(k = i, j = i+1; j < this->_no_elements; j++) {
        if( (*this->_data_ptr[j]) < this->_data_ptr[k]) { k = j; }
      }

      if(i != k) { this->swap(i, k); }
    }
  }


  template <typename T>
  inline
  SArray<T>& SArray<T>::operator = ( const Array<T>& ar ) {

    _sorted = false;
    return Array<T>::operator=(ar);
  }


  template <typename T>
  inline
  SArray<T>& SArray<T>::operator = ( const ArrayT<T>& ar ) {

    _sorted = false;
    return Array<T>::operator=(ar);
  }


  template <typename T>
  inline
  SArray<T>& SArray<T>::operator = ( const SArray<T>& ar ) {

    _sorted = ar._sorted;
    return SArray<T>::operator=(ar);
  }

}

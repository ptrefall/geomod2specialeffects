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



/*! \file gmPERBSTriangle.c
 *
 *  Implementation of the PERBSTriangle template class.
 *
 *  \date   2010-03-25
 */


namespace GMlib {

  template <typename T>
  PERBSTriangle<T>::PERBSTriangle( PBezierTriangle<T>* c0, PBezierTriangle<T>* c1, PBezierTriangle<T>* c2 ) {

    _basis = new ERBSEvaluator<long double>();
    _basis->set( 0.0, 1.0 );

    _c.setDim( 3 );
    _c[0] = c0; insertPatch( c0 );
    _c[1] = c1; insertPatch( c1 );
    _c[2] = c2; insertPatch( c2 );


    Parametrics<T,2>::setSurroundingSphere( Sphere<float,3>( Vector3D<float>(0.0,0.0,0.0),0.01) );

  }


  template <typename T>
  PERBSTriangle<T>::~PERBSTriangle() {

    for( int i = 0; i < _c.getDim(); i++ )
      SceneObject::remove( _c[i] );

    if( _basis )
      delete _basis;
  }

  template <typename T>
  inline
  void PERBSTriangle<T>::edit( SceneObject *obj ) {

    int i;
    for( i = 0; i < _c.getDim(); i++ )
      if( _c[i] == obj )
        goto edit_loop_break;

    edit_loop_break:

    // If Bezier Patch
    PBezierTriangle<T> *bezier = dynamic_cast<PBezierTriangle<T>*>(_c[i]);
    if( bezier )
      bezier->updateCoeffs( _c[i]->getPos() - _c[i]->evaluateParent( 0.5, 0.5, 0, 0 )(0)(0) );

    PTriangle<T>::replot();
  }

  template <typename T>
  inline
  void PERBSTriangle<T>::eval( T u, T v, T w ) {


    this->_p.setDim( 2, 2 );

    DVector<T> Au;  getB( Au, u, 2 );
    DVector<T> Av;  getB( Av, v, 2 );
    DVector<T> Aw;  getB( Aw, w, 2 );

    T sum = Au[0] + Av[0] + Aw[0];
    T sum2 = sum*sum;

    T Bu = Au[0]/sum;
    T Bv = Av[0]/sum;
    T Bw = Aw[0]/sum;

    T duBu = Au[1] * ( sum - Au[0] ) / sum2;
    T dvBu = Av[1] * Au[0] / sum2;
    T dwBu = Aw[1] * Au[0] / sum2;

    T duBv = Au[1] * ( sum - Av[0] ) / sum2;
    T dvBv = Av[1] * Av[0] / sum2;
    T dwBv = Aw[1] * Av[0] / sum2;

    T duBw = Au[1] * ( sum - Aw[0] ) / sum2;
    T dvBw = Av[1] * Aw[0] / sum2;
    T dwBw = Aw[1] * Aw[0] / sum2;




    DMatrix< Vector<T,3> > p0 = _c[0]->evaluateParent( u, v, 2, 2 );
    DMatrix< Vector<T,3> > p1 = _c[1]->evaluateParent( v, w, 2, 2 );
    DMatrix< Vector<T,3> > p2 = _c[2]->evaluateParent( w, u, 2, 2 );

    this->_p[0][0] = p0[0][0] * Bu + p1[0][0] * Bv + p2[0][0] *Bw;

    this->_p[1][0] =
        ( p0[0][1] - p0[1][0] ) * Bu + p0[0][0] * ( duBv - duBu ) +        // der u-v
        ( p1[1][0] - p1[1][1] ) * Bv + p1[0][0] * ( dvBv - dvBu ) +
        ( p2[1][1] - p2[0][1] ) * Bw + p2[0][0] * ( dwBv - dwBu );

    this->_p[0][1] =
        ( p0[1][1] - p0[1][0] ) * Bu + p0[0][0] * ( duBw - duBu ) +        // der u-w
        ( p1[0][1] - p1[1][1] ) * Bv + p1[0][0] * ( dvBw - dvBu ) +
        ( p2[1][0] - p2[0][1] ) * Bw + p2[0][0] * ( dwBw - dwBu );

    this->_p[1][1] = this->_p[0][1] - this->_p[1][0];
  }

  template <typename T>
  inline
  void PERBSTriangle<T>::getB( DVector<T>& B, T t, int d ) {

    B.setDim(d+1);
    B[0] = 1 - _basis->operator()(t);  // (*_evaluator)(t)
    B[1] = - _basis->getDer1();
    B[2] = - _basis->getDer2();
  }

  template <typename T>
  inline
  T PERBSTriangle<T>::getEndPU() {

    return T(1);
  }

  template <typename T>
  inline
  T PERBSTriangle<T>::getEndPV() {

    return T(1);
  }

  template <typename T>
  std::string PERBSTriangle<T>::getIdentity() const {

    return "PERBSTriangle";
  }

  template <typename T>
  inline
  DVector< PTriangle<T>* >& PERBSTriangle<T>::getLocalPatches() {

    return _c;
  }

  template <typename T>
  inline
  T PERBSTriangle<T>::getStartPU() {

    return T(0);
  }

  template <typename T>
  inline
  T PERBSTriangle<T>::getStartPV() {

    return T(0);
  }

  template <typename T>
  inline
  void PERBSTriangle<T>::hideLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( false, -1 );
  }

  template <typename T>
  inline
  void  PERBSTriangle<T>::insertPatch( PTriangle<T> *patch ) {

    patch->replot( 10 );
    patch->setVisible( false );
    patch->setCollapsed( true );
    insert( patch );
  }

  template <typename T>
  inline
  bool PERBSTriangle<T>::isLocalPatchesVisible() const {

    for( int i = 0; i < _c.getDim(); i++ )
      if( _c(i)->isVisible() )
        return true;

    return false;
  }

  template <typename T>
  inline
  void PERBSTriangle<T>::showLocalPatches() {

    for( int i = 0; i < _c.getDim(); i++ )
      _c[i]->setVisible( true, -1 );
  }






} // END namespace GMlib


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



/*! \file gmScene.h
 *  \brief Interface to the Scene Object
 *
 *  Interface to the Scene Object
 *
 *  \date 2008-07-23
 *
 *  \todo
 *  Rewrite the Scene class documentation, and translate it into english
 */


#ifndef __gmSCENE_H__
#define __gmSCENE_H__


// locale GMlib includes
#include "gmPoint.h"
#include "gmTimer.h"
//#include "gmArray.h" // maby gmSArray.h
#include "gmSArray.h"
#include "gmSortObject.h"
#include "gmFrustum.h"


namespace GMlib{

  class SceneObject;
  class Camera;
  class Light;



  /*! \class Scene gmScene.h <gmScene>
   *  \brief Pending Documentation cleanup, and general documentation
   *
   *	Inneholder: Scenen er startnoden i ojecttreet
   *
   *		privat;
   *				En array av pekere til førstenode objektene i ojecttreet
   *		public:
   *				Konstuktør med mulige default verdier og sletter
   *				En display funksjon for displaying av objektet.
   *				En select funksjon for plukking(select) av objektet med mus.
   *				En simulate funksjon for at objektet kan bevege seg eller subobjekter.
   *				En find funksjon for å finne en funksjon med et gitt navn.
   *				En insert funksjon for å legge inn et nytt førstenode objekt
   *				En remove funksjon for å fjerne et førstenode objekt
   *				En operator [] som returnerer et gitt føstenode-element.
   *				En funksjon size() som gir antallet føstenode-element.
   *				En funksjon getMatrix(obj,mat,type) som gir transformasjonsmatrisen
   *				   fra scenen til og med obj hvis type er 1 og til obj hvis type er 2.
   */
  class Scene {
  public:
    Scene();
    Scene( SceneObject* obj );
    Scene( const Scene&  s );
    virtual ~Scene();

    SceneObject*          find(unsigned int name);
    SceneObject*          getActiveObject();
    double                getElapsedTime();
    Array<Light*>&        getLights();
    Array<SceneObject*>&  getSelectedObjects();
    int                   getSize();
    int                   getSizeTotal();
    Sphere<float,3>       getSphere();
    Sphere<float,3>       getSphereClean() const;
    double                getTimeScale();
    virtual void          insert(SceneObject* obj);
    bool                  isRunning();
    void                  prepare();
    void                  remove(SceneObject* obj);
    void                  removeSelection( SceneObject* obj );
    void                  resetTime();

    void                  setTimeScale(double s);
    void                  start();
    void                  stop();

    SceneObject*          operator [] (int i);
    SceneObject*          operator () (int i);
    Scene&                operator =  (const Scene& sc);


  protected:
    Array<SceneObject*>   _sel_objs;
    SceneObject           *_active_obj;

    bool                  isVisible( SceneObject* obj );
    void                  simulate();

  private:
    friend class Camera;

    void                  _lighting();
    void                  _display( bool blend_sorted );
    void                  _displayActive();
    void                  _displaySelection();
    void                  _select( int type_id );
    virtual void          _culling( const Frustum& f, bool on = true );
    void                  _blending( Camera* cam );

    Array<SceneObject*>   _scene;
    Array<SceneObject*>	  _disp_objs;
    SArray< SortObject<SceneObject*, float> >   _disp_opaque;
    SArray< SortObject<SceneObject*, float> >   _disp_translucent;

    Array<Light*>         _lights;
    Array<HqMatrix<float,3> >                   _matrix_stack;

    GMTimer               _timer;
    bool                  _timer_active;
    double                _timer_time_elapsed;
    double                _timer_time_scale;

  }; // END class Scene


} // END namespace GMlib

// Include inline Scene class implementations
#include "gmScene.c"

#endif // __gmSCENE_H__

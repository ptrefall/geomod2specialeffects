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



/*! \file gmWindow_GMWindow.cpp
 *	\brief Pending Description
 *
 *  Implementation of the View class.
 *
 *  \date   2008-07-28
 */


// STL
#include <cstdio>


// Header
#include "gmWindow.h"


namespace GMlib {




  /*! GMWindow::GMWindow()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::GMWindow() {

    _stereo	= false;
    _running = false;
    _isbig	 = false;
    _target  = NULL;
    _sun	 = NULL;
    _move	 = 0.0;
    _active_cam = 0;
    stop();
  }


  /*! GMWindow::GMWindow(const GMWindow&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::GMWindow( const GMWindow& gw ) : Scene() {

    (*this) = gw;
  }


  /*! GMWindow::~GMWindow()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow::~GMWindow() {

    int i;
    if(_sun) delete _sun;
    for(i=0; i<_cameras.getSize(); i++)
    {
      remove(_cameras[i]);
      delete _cameras[i];
    }
    Light * light;
    for(i=_lights.getSize()-1; i>=0; i=_lights.getSize()-1)
    {
      light = _lights.back();
      removeLight(light);
      delete light;
    }
  }


  void GMWindow::clearScene() {

    if( _running )
      Scene::stop();

    for(int i = 0; i < _sel_objs.getSize(); i++)
      _sel_objs[i]->setSelected( false );
    _sel_objs.clear();

    _active_obj = 0x0;

    //_rotation_object  = 0x0;
    //_locked_object    = 0x0

    Array<SceneObject*> rmobjs;
    for( int i = 0; i < getSize(); i++ )
      rmobjs += operator[](i);

    for( int i = 0; i < rmobjs.getSize(); i++ ) {

      Camera* cam   = dynamic_cast<Camera*>( rmobjs[i] );
      Light* light  = dynamic_cast<Light*>( rmobjs[i] );

      if( cam )
        removeCamera( cam );
      else if( light )
        removeLight( light );
      else
        remove( rmobjs[i] );

      delete rmobjs[i];
    }

    if( _running )
      Scene::start();
  }


  /*! void GMWindow::insertCamera(Camera* cam, bool insert_in_scene)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::insertCamera(Camera* cam, bool insert_in_scene) {

    cam->setScene(this);
    _cameras += cam;
    if(insert_in_scene)	insert(cam);
  }


  /*! void GMWindow::insertLight(Light* light, bool insert_in_scene)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::insertLight(Light* light, bool insert_in_scene) {

    _lights += light;
    light->enable();

    SceneObject* obj = dynamic_cast<SceneObject*>(light);

    if(insert_in_scene && obj)
      insert(obj);
  }


  /*! void GMWindow::popViewSet(int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::popViewSet(int i) {

    _view_set_stack.back()._removeCamera(i);
  }


  /*! bool GMWindow::removeCamera(Camera *)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::removeCamera(Camera * cam) {

    if(_cameras.getSize() < 2)
      return false;

    int i = _cameras.getIndex(cam);
    if(i>0)
    {
      for(int j=1; j<_view_set_stack.getSize(); j++)
        _view_set_stack[j].removeCamera(_cameras[_active_cam]);

      remove(cam);
      _cameras.removeIndex(i);
      return true;
    }
    return false;
  }


  /*! bool GMWindow::removeLight(Light* light)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::removeLight(Light* light) {

    int i = _lights.getIndex(light);
    if(i>=0)
    {
      SceneObject* obj = dynamic_cast<SceneObject*>(light);

      if(obj)
        remove(obj);

      _lights.removeIndex(i);
      light->disable();

      return true;
    }
    return false;
  }


  /*! void GMWindow::scaleDayLight(double)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::scaleDayLight(double d) {

    _sun->scaleDayLight(d);
  }


  /*! void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::setViewSet(int new_c, int old_c, bool split_vertically, double d) {

    if(new_c<1 || new_c>=_cameras.getSize() || old_c <1 || old_c>=_cameras.getSize() || d<=0 || d>=1) {

      return;
    }
    if(_default_only) {

      _view_set_stack += ViewSet(_cameras[new_c]);
      _default_only = false;
    }
    else
      _view_set_stack.back()._insertCamera(_cameras[old_c],_cameras[new_c], split_vertically,d);

    _view_set_stack.back().prepare(_w,_h);
  }


  /*! bool GMWindow::toggleStereo()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::toggleStereo() {

    _stereo = !_stereo;
    return _stereo;
  }


  /*! GMWindow& GMWindow::operator=(const GMWindow& gw)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  GMWindow& GMWindow::operator=(const GMWindow& gw) {

    Scene::operator=(gw);
    _cameras	= gw._cameras;
    _lights	= gw._lights;
    _sun	= gw._sun;
    for(int i=0; i<_cameras.getSize(); i++)
      _cameras[i]->setScene(this);

    _stereo	= false;
    _running = false;
    _isbig	 = false;
    _sel_objs.clear();
    _view_set_stack = gw._view_set_stack;				// Active camera set
    reshape(_w,_h);
    return *this;
  }



  #ifndef GL_MULTISAMPLE
  #define GL_MULTISAMPLE  0x809D
  #endif
  /*! void GMWindow::init()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void GMWindow::init() {

//    cout << "GMWindow::init()" << endl;
    //	glClearColor(0.0,0.0,0.0,1.0);
    glEnable (GL_MULTISAMPLE);  // BB tst

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    // glEnable(GL_NORMALIZE);
    // glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_GREATER,0.1);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(_sun)
      _sun->scaleDayLight(1.0);
    insertCamera(new Camera(Point3D<float>(10,10,5),Point3D<float>(-10,-10,-5),Vector3D<float>(0,0,-1)));
    _view_set_stack += ViewSet(_cameras[0]);
    _view_set_stack.back().prepare(_w,_h);
    _default_only = true;
    int numberoflights;
    glGetIntegerv(GL_MAX_LIGHTS,&numberoflights);
    char s[32];
    std::sprintf( s, "Max number of lights %d\n", numberoflights );
    message(s);
    //char *extensions = NULL;
      //extensions = (char *)glGetString(GL_EXTENSIONS);
      //_message(extensions);
  }


  /*! bool GMWindow::toggleRun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool GMWindow::toggleRun() {

    if( ( _running = !_running ) )
      start();
    else
      stop();

    return _running;
  }

}

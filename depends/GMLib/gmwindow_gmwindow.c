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



/*! \file gmWindow_GMWindow.c
 *	\brief Inline GMWindow class implementations
 *
 *  Inline implementations of the View class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {



  /*! Camera* GMWindow::getCam()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  Camera* GMWindow::getCam() {
    int i;
    find(100,100,i);
    if(i>0)
      return _cameras[i];
    else
      return NULL;
  }


  /*! void GMWindow::insertSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::insertSun() {

    _sun = new Sun(); _sun->enable();
  }


  inline
  bool GMWindow::isRunning() const {

    return _running;
  }


  /*! bool GMWindow::isStereoEnabled()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::isStereoEnabled() const {

    return _stereo;
  }


  /*! void GMWindow::removeSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::removeSun() {

    if(_sun) {

      delete _sun;
      _sun = NULL;
    }
  }


  /*! void GMWindow::reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reset() {

    init();
  }


  /*! void GMWindow::setSunDirection(Angle d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::setSunDirection(Angle d) {

    if(_sun)
      _sun->rotateGlobal(d,Vector3D<float>(1.0,1.0,0.0));
  }


  /*! void GMWindow::swapBuffers()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::swapBuffers() {}


  /*! void GMWindow::display(void)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::display() {

    if( _active_cam > -1 )
      _cameras[_active_cam]->move((float)_move);

    simulate();
    prepare();
    if(_stereo) {

      glDrawBuffer(GL_BACK_LEFT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _view_set_stack.back()._drawCamera();
      swapBuffers();
      glDrawBuffer(GL_BACK_RIGHT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _view_set_stack.back()._drawCamera(true);
    }
    else
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _view_set_stack.back()._drawCamera();
    }
    swapBuffers();
  }


  /*! void GMWindow::reshape(int w, int h)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reshape(int w, int h) {

    _w = w; _h = h;
    _view_set_stack.back().prepare(_w,_h);
  }


  /*! void GMWindow::message( const std::string& str)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( const std::string& /* str */ ) {}


  /*! void GMWindow::message( SceneObject* d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( SceneObject* /* obj */ ) {}


  /*! void GMWindow::message( Point<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( Point<float,3>& /* p */ ) {}


  /*! bool GMWindow::find(int x, int y, int& index)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::find(int x, int y, int& index) {

    if(x<0 || x>_w || y<0 || y>_h)		// Outside window
    {
      index = 0;
      _view_set_stack.back()._reset();
      return false;
    }

    Camera* cam;
    if(_view_set_stack.back()._find(x,y,cam))		// Camera found
    {
      index = _cameras.index(cam);
      return true;
    }
    else								// border found
    {
      index = -1;
      return false;
    }
  }


  /*! void GMWindow::moveBorder(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::moveBorder(int x, int y) {

    if(x>0 && x <_w && y>0 && y<_h)
      (_view_set_stack.back())._moveBorder(x,y);
  }

}

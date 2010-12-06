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



/*! \file gmWindow.h
 *
 *  Interface for the Window and "Camera" View classes.
 *
 *  \date   2008-07-28
 */


#ifndef __gmWINDOW_H__
#define __gmWINDOW_H__


// GMlib includes
#include "gmCamera.h"
#include "gmLight.h"
#include "gmMaterial.h"



namespace GMlib {


  class View;
  class ViewBorder;
  class ViewSet;
  class GMWindow;


  /*! \class View gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class View {
	public:
		View( Camera* cam = 0x0 );
		View( ViewBorder* border );
		View( const View& view );

	private:
		friend class ViewSet;
		friend class ViewBorder;

		Camera*				_camera;
		ViewBorder*		_border;


		void 					_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow);
		void 					_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders);
		int  					_getSize(bool split_vertically = true);
		bool 					_isCamera(Camera* cam);
		void 					_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders);
		void 					_removeCamera(Camera* cam);
		void 					_split(Camera* new_cam, bool split_vertically, double d);
		void 					_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d);

	}; // END class View










  /*! \class ViewBorder gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class ViewBorder {
	public:
		ViewBorder(Camera* cam_to_split, Camera* new_cam, bool v, double r);
		ViewBorder(const ViewBorder& w);

	private:
		friend class ViewSet;
		friend class View;

		bool			_vertical;		/// True if border is vertical
		double		_displacement;
		int				_x1, _x2, _y1, _y2;	/// Pixel-index of the border
		View			_child_lt;
		View			_child_rb;

		void 			_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow);
		void 			_display();
		void 			_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders);
		int  			_getSize(bool vertical=true);
		View* 		_hasCamera(Camera* cam);
		bool 			_isVertical();
		void 			_move(int x, int y);
		void 			_prepare( int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders );
		void 			_removeCamera(Camera* cam);
		void 			_splitCamera(Camera* cam_to_split, Camera* new_cam, bool vertical, double d);


	}; // END class ViewBorder










  /*! \class ViewSet gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class ViewSet {
	public:
		ViewSet(Camera* cam=0);
		ViewSet(const ViewSet& viewset);
		~ViewSet();

		int  								getSize();
		Point2D<int> 				getViewPortSize();
		void 								prepare(int w, int h);
		void 								removeCamera(Camera*);

		ViewSet& 						operator=(const ViewSet& viewset);
		bool 								operator<(const ViewSet& viewset)const;


	private:
		friend class GMWindow;

		int									_vp_w; // ViewPort size ( Width )
		int 								_vp_h;	// Viewport size ( height )
		Array<Camera*>			_cameras;
		Array<ViewBorder*>	_borders;
		View								_root;
    Color							_border_color;

		Array<ViewBorder*>	_selected_borders;


		void 								_drawBorder();
		void 								_drawCamera(bool stereo=false);
		bool 								_find(int x, int y, Camera*& cam);
		bool 								_insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically=true, double d=0.5);
		void 								_moveBorder(int x, int y);
		void 								_removeCamera(int i);
		void 								_reset();
    void 								_setBorderColor(const Color& bc);

		Camera* 						operator[](int i);

	}; // END class ViewSet










  /* \class GMWindow gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class GMWindow : public Scene {
  public:
    GMWindow();
    GMWindow(const GMWindow&);

    virtual ~GMWindow();


    virtual void            clearScene();
    Camera*                 getCam();
    void                    insertCamera(Camera* cam, bool insert_in_scene = false);

    void                    insertLight(Light* light, bool insert_in_scene = false);
    void                    insertSun();
    bool                    isRunning() const;
    bool                    isStereoEnabled() const;
    void                    popViewSet(int i);
    bool                    removeCamera(Camera * cam);
    bool                    removeLight(Light* light);
    void                    removeSun();
    void                    reset();

    void                    scaleDayLight(double d);
    void                    setSunDirection(Angle d);
    void                    setViewSet(int new_c, int old_c=1, bool split_vertically=true, double d=0.5);

    virtual bool            toggleRun();
    bool                    toggleStereo();


    GMWindow&               operator=(const GMWindow& gw);

    // Cameras light and sun
    Array<Camera*>	        _cameras;
    Array<Light*>	          _lights;
    Sun*			              _sun;

    // Viewport size
    int				              _w;
    int                     _h;					// GMWindow size in viewport coordinates.


    Array<ViewSet>          _view_set_stack;  /// Active camera set

    // index of active camera, old/previous x and y mouse positions
    int				              _active_cam;

    double					        _move;


    bool                    find(int x, int y, int& index);
    virtual void            message( const std::string& str);
    virtual void            message( SceneObject* d);
    virtual void            message( Point<float,3>& p);
    void                    moveBorder(int x, int y);

    void                    display();
    virtual void            init();
    void                    reshape(int w, int h);
    virtual void            swapBuffers();


  private:
    bool			              _stereo;

    SceneObject*	          _target;		/// NB!!!! take a look at this variable not used proper today.....
    //SceneObject*	          _rot_obj;		/// Storing Rotating object from pressed down to move, restored in butten up.
//    int				              _viewmode;		/// State for Camera moving in plane, the two states acting opposit
    bool			              _running;		/// Used to stor the state of simulation while mouse/keboard temporary turn off simulation
    bool			              _isbig;			/// State of one window functionality have been used (see _mouseDoubleClick on right knob)
    bool			              _default_only;	/// Only default camera present



  }; // END class GMWindow

} // END namespace GMlib



// Include inline View class implementations
#include "gmWindow_View.c"

// Inlclude inline ViewBorder class implementations
#include "gmWindow_ViewBorder.c"

// Include inline ViewSet class implementations
#include "gmWindow_ViewSet.c"

// Include inline GMWindow class implementations
#include "gmWindow_GMWindow.c"



#endif // __gmWINDOW_H__

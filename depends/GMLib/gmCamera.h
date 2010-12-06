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



/*! \file gmCamera.h
 *
 *  Interface for the Camera class.
 *
 *  \date   2008-07-26
 *
 *	\todo
 *	- Translate the already documented parts into English
 */


#ifndef __gmCAMERA_H__
#define __gmCAMERA_H__


// GMlib includes
#include "gmStream.h"
#include "gmDisplayObject.h"
#include "gmScene.h"


namespace GMlib {


	/*!	\class Camera gmCamera.h <gmCamera>
	 *	\brief	The Camera class
	 *
	 *	Inneholder:
	 *		privat;
	 *				Et navn for identifikasjon i select funksjonaliteten.
	 *				To matriser for lokal transformasjon av objektet.
	 *				En Omsluttende kule til objektet som må lages.
	 *				En array av pekere til alle sub-objektene til dette objektet
	 *		public:
	 *				Konstuktør med mulige default verdier og sletter
	 *				En display funksjon for displaying av objektet.
	 *				En select funksjon for plukking(select) av objektet med mus.
	 *				En simulate funksjon for at objektet kan bevege subobjekter.
	 *				En find funksjon for å finne en funksjon med et gitt navn.
	 *				En rotate, scale og translate funksjon for å
	 *				   posisjonere objektet relativt i forhold til morsobjektet
	 *		protected:
	 *				Det er to virtuelle funksjoner localDisplay og localSelect
	 *					som alle avledede klasser må ha sin versjon av.
	 *				Arbeidsdelingen er slik at display og select foretar
	 *					transformasjonen lagret i matrix, og displayer alle
	 *					sub-objektene til objektet. Men etter transformasjonen
	 *					og før sub-objektene displayes kalles localDisplay
	 *					(eventuelt localSelect). I localDisplay kan en så
	 *					displaye det som ikke displayes i sub-objektene og/eller
	 *					foreta transformasjoner av sub-objekter for
	 *					å simulere bevegelser.
	 *				Det er også en insert-funksjon som avledede klasser
	 *				    kan bruke for å lage sub-objekt. Hvis en avledet klasse
	 *					trenger tilgang til et objekt for bevegelsessimulering
	 *					bør den lage en egen peker for det.
	 */
	class Camera : public DisplayObject {
	public:
		Camera( Scene& s = _default_scene );
		Camera( Scene* s );

		Camera( const Point<float,3>&  pos,
			const Point<float,3>&  look_at_pos);

		Camera( const Point<float,3>&  pos,
			const Vector<float,3>& dir,
			const Vector<float,3>& up,
			float zoom=1);

		virtual ~Camera();

		void										decreaseEyeDist(double delta=0.01);
		void										decreaseFocalDist(double delta=1);
		virtual double					deltaTranslate(DisplayObject * obj);
		void                    enableCulling( bool enable = true );
    void                    enableBlendSort( bool enable = true );
		SceneObject*						findSelectObject(int, int, int type_id=0);
		Array<SceneObject* >		findSelectObjects(int xmin, int ymin, int xmax, int ymax, int type_id=0);
		float                   getAngleTan() const;
		double									getDistanceToObject(int, int);
		double									getDistanceToObject(SceneObject* obj);
		float									  getFarPlane() const;
		float									  getFocalLength() const;
		std::string 						getIdentity() const;
		HqMatrix<float,3>&			getMatrix();
		float									  getNearPlane() const;
		float									  getRatio() const;
		void										getViewport(int& w1, int& w2, int& h1, int& h2) const;
		int											getViewportW() const;
		int											getViewportH() const;
		virtual void 						go(bool stereo=false);	// Running the Camera.
		void										increaseEyeDist(double delta=0.01);
		void										increaseFocalDist(double delta=1);
		bool 										isCoordSysVisible() const;
		bool                    isCulling() const;
    bool                    isBlendSortEnabled() const;
		bool 										isFrustumVisible() const;
		virtual SceneObject*		lockTargetAtPixel(int,int);
		void 										reset();						// To be used when changing Camera.
		virtual void 						reshape(int w1, int h1, int w2, int h2);		// To be used when changing size of window
		void										setCuttingPlanes(float near_plane, float far_plane);
		void 										setCoordSysVisible(bool visible=true);
		void										setEyeDist(double eye_dist=0.08);
		void										setFocalDist(double focal=50.0);
		void 										setFrustumVisible(bool visible=true);
		void										setScene(Scene& s);
		void										setScene(Scene *s);
    void                    setSelectActiveColor( const Color& color );
    void                    setSelectActiveLineWidth( float width );
    void                    setSelectColor( const Color& color );
    void                    setSelectLineWidth( float width );
		virtual void 						zoom(float z);


	protected:
		float									_near_plane;
		float									_far_plane;
		float									_ratio;
		Frustum									_frustum;
		GLMatrix								_frustum_matrix;					// Frustrum matrix

		void										basisChange(
															const Vector<float,3>& x,
															const Vector<float,3>& y,
															const Vector<float,3>& z,
															const Vector<float,3>& p);

		virtual void						display();
		virtual	void						drawActiveCam();
		SceneObject*						find(unsigned int name);
		virtual void						makeGraphics();
		void										resetC(float z = 1);
		void										select(int type_id);
		virtual void						setPerspective();

		// *****************
		// Virtual functions
		// from SceneObject
		void										localDisplay();
		void										localSelect();


//	private:
		static Scene						_default_scene;
		static unsigned int						_display_list;

    Color                   _select_color;
    float                   _select_linewidth;

    Color                   _select_active_color;
    float                   _select_active_linewidth;

		Scene*									_scene;
		int											_x,_y,_w,_h;					// Viewport position and size.

		bool										_coord_sys_visible;
		bool										_frustum_visible;

		double									_focal_length;
		double									_eye_dist;
		double									_ed_fd;
		float									_angle_tan;

		bool                    _culling;
    bool                    _blend_sort;
	};

}


// Inlcude inline function implementations
#include "gmCamera.c"


#endif // __gmCAMERA_H__

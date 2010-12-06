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



/*! \file gmLight.h
 *
 *  Interface for the basic Light classes
 *	Light, PointLight and SpotLight
 *
 *  \date   2008-07-25
 */



#ifndef __gmLIGHT_H__
#define __gmLIGHT_H__


// STL include
#include <string>

// GMlib includes
#include "gmDisplayObject.h"


namespace GMlib{

	/*! \class Light gmLight.h <gmLight>
	 * \brief Pending Documentatioo
	 *
	 *	Pending Documentatioo
	 */
  class Light {
  public:
    Light();
    Light( const Color& amb , const Color& dif, const Color& spe );
    Light( const Light& );
    virtual ~Light();

    virtual void                  culling( const Frustum& );
    void                          disable();
    void                          enable();
    bool                          isCullable();
    bool                          isEnabled();
    virtual void                  lighting();
    void                          setColor(
                                    const Color& ambient = Color( 0.2f, 0.2f, 0.2f ),
                                    const Color& diffuse = Color( 1.0f, 1.0f, 1.0f ),
                                    const Color& specular= Color( 1.0f, 1.0f, 1.0f )
                                  );

    void                          setCullable( bool cullable );
    void                          setIntensity(double d,int i=0);


    const Color&                  getAmbient();
    const Color&                  getDiffuse();
    unsigned int                  getLightName();
    const Color&                  getSpecular();

  protected:
    void                          glLight( GLenum pn, const Color& co);
    void                          glLight( GLenum pn, float f );
    void                          glLight( GLenum pn, int f );
    void                          glLightDir( const Vector<float,3>& dir );
    void                          glLightPos( const Point<float,3>& pos );
    void                          glLightSun( const Vector<float,3>& pos );

    static float                  _min_light_contribution; // 1/100


  private:
    static unsigned int           _next_light;
    static Array<unsigned int>    _free_light;
    GLenum                        _light_name;

    Color                         _ambient;
    Color                         _diffuse;
    Color                         _specular;
    bool                          _cullable;


  };	// END class Light







	/*! \class PointLight gmLight.h <gmLight>
	 * \brief Pending Documentatioo
	 *
	 *	Pending Documentatioo
	 */
	class PointLight : public Light, public DisplayObject {
	public:
		PointLight();
		PointLight(	const Point<float,3>& pos);
		PointLight(
      const Color& amb,
			const Color& dif,
			const Color& spe,
			const Point<float,3>& pos
		);
		PointLight(	const PointLight& pl);
		virtual ~PointLight();

		virtual void 			culling( const Frustum& frustum );
		std::string		    getIdentity() const;
		void 							setAttenuation(float constant, float linear, float quadratic);
		void 							setAttenuation(const float att[]);

	protected:
		void 							calculateRadius(float constant, float linear, float quadratic);
		void 							lighting();

		Point3D<float>		_pos;
		Point3D<float>		_attenuation;


	private:
		Sphere<float,3>   _light_sphere;

	};	// END class PointLight








	/*! \class SpotLight gmLight.h <gmLight>
	 * \brief Pending Documentatioo
	 *
	 *	Pending Documentatioo
	 */
	class SpotLight : public PointLight {
	public:
		SpotLight();
		SpotLight(
			const Point<float,3>& pos,
			const Vector<float,3>& dir,
			Angle cut_off );
		SpotLight(
			const Color& amb,
			const Color& dif,
			const Color& spe,
			const Point<float,3>& pos,
			const Vector<float,3>& dir,
			Angle cut_off = 90);
		SpotLight( const SpotLight& pl);
		virtual ~SpotLight();

    const Angle&            getCutOff() const;
    double                  getExponent() const;
		std::string             getIdentity() const;

		virtual void            setCutOff( const Angle& cut_off);
		void                    setExponent(double exp);


	protected:
		Vector3D<float>	        _dir;
		Angle				            _cutoff;
		double				          _exp;

		void lighting();

	};	// END class SpotLight








	/*!	\class Sun gmLight.h <gmLight>
	 *	\brief Pending Documentation
	 *
	 *	Pending Documentation
	 */
	class Sun : public Light, public SceneObject {
	public:
		Sun(const Vector<float,3>& dir = Vector3D<float>(1,1,1));
		virtual ~Sun();

		std::string             getIdentity() const;
		void                    scaleDayLight( double d );
		void                    setDayLight( const Color& amb = Color( 0.1f, 0.1f, 0.1f ) );


	protected:
		void                    lighting();


	private:
		Vector<float,3>         _dir;
                Color                   _global_ambient;

		void                    _setDayLight(double d);

	}; // END class Sun

}	// END namespace GMlib



// Include inline Light class implementations
#include "gmLight_Light.c"

// Include inline implementations
#include "gmLight_PointLight.c"

// Include inline SpotLight class implementations
#include "gmLight_SpotLight.c"

// Include inline Sun class implementations
#include "gmLight_Sun.c"


#endif // __gmLIGHT_H__

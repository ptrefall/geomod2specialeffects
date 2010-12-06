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


#ifndef __gmMATERIAL_H__
#define __gmMATERIAL_H__


#include "gmOpenGL.h"
#include "gmTexture.h"
#include "gmString.h"
#include "gmArray.h"

namespace GMlib {



  class Material;
  class MaterialObject;
  class MaterialObjectList;



  /*! \class Material gmMaterial.h <gmMaterial>
   *  \brief The Material class
   *
   *  containing:
   *    ambient, diffuce and specular colors,
   *		shininess (0-100) and
   *    texture ID and
   *		source and destination blending factors
   */
  class Material {
  public:
    Material(
      const Color& amb 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      const Color& dif 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      const Color& spc 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      float shininess 		= 0.0f,
      const Texture& texture = Texture()
    );
    Material( const Texture& tex, const Material& mat = Material() );
    Material( const Material& copy );
    virtual ~Material();

    const Color&    getAmb() const;
    const Color&    getDif() const;
    const Color&    getSpc() const;
    float           getShininess() const;
    int             getTextureID() const;
    virtual void    glSet() const;
    void            glSetInverse() const;
    virtual void    glUnSet() const;
    bool            isTransparent() const;
    void            set( const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture );
    void            set( const Color& amb, const Color& dif, const Color& spc );
    void            set( const GLenum sfactor, const GLenum dfactor );
    void            set( float shininess );
    void            set( const Texture& texture );
    void            setAmb( const Color& amb );
    void            setDif( const Color& dif );
    void            setDoubleSided( bool s );
    void            setSided( GLenum s );
    void            setSpc( const Color& spc );
    void            setTransparancy( double t );

    Material&       operator =  ( const Material& m );
    bool            operator == ( const Material& m ) const;


  protected:
    Texture         _texture;
    Color           _amb;
    Color           _dif;
    Color           _spc;
    float           _shininess;


  private:

    GLenum          _source_blend_factor;
    GLenum          _destination_blend_factor;
    GLenum          _sided;


  // *****************************
    // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  public:
    template <class T_Stream>
    friend T_Stream& operator << ( T_Stream& out, const Material& m ) {

      out << m._amb       << GMseparator::Element
          << m._dif       << GMseparator::Element
          << m._spc       << GMseparator::Element
          << m._shininess << GMseparator::Element;

//      if(m._texture.isValid()) {
//
//        char *tx=Texture::findFileName(m._texname);
//        out << tx << GMseparator::Group;
//      }
//      else
//      {
//        char* no = "no-texture";
//        out << no << GMseparator::Group;
//      }

      return out;
    }

    template <class T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, Material& m ) {

      static Separator es(GMseparator::Element);
      static Separator gs(GMseparator::Group);
      char fn[255];  // think about this

      in  >> m._amb       >> es
          >> m._dif       >> es
          >> m._spc       >> es
          >> m._shininess >> es
          >> fn           >> gs;

//      if( !( fn[0] == 'n' && fn[1] == 'o' && fn[2] == '-' ) )
//      {
//        Texture tx(true);
//        m.set(tx.LoadGL(fn));
//      }
      m.set( GL_ONE, GL_ONE );
  //		delete fn;
      return in;
    }

    #endif

  }; // END class Material


  // ********************
  // Predefined Materials

  namespace GMmaterial {

    extern Material BlackPlastic;
    extern Material BlackRubber;
    extern Material Brass;
    extern Material Bronze;
    extern Material Chrome;
    extern Material Copper;
    extern Material Emerald;
    extern Material Gold;
    extern Material Jade;
    extern Material Obsidian;
    extern Material Pearl;
    extern Material Pewter;
    extern Material Plastic;
    extern Material PolishedBronze;
    extern Material PolishedCopper;
    extern Material PolishedGold;
    extern Material PolishedGreen;
    extern Material PolishedRed;
    extern Material PolishedSilver;
    extern Material Ruby;
    extern Material Sapphire;
    extern Material Silver;
    extern Material Snow;
    extern Material Turquoise;

  } // END namespace GMlib::Material







  /*! \class MaterialObject gmMaterial.h <gmMaterial>
   *  \brief The MaterialObject class
   *
   *  containing:
   *    A name and
   *	  is a Materia
   */
  class MaterialObject: public Material {
  public:
    MaterialObject(
			const Material& mat = GMmaterial::Snow,
      const char* name = "Snow"
		);

    MaterialObject(
			const Material& mat,
      std::string name
		);

    MaterialObject(	const MaterialObject& m);

    void 							deleteTexture();
    const Material&		getMaterial() const;
    const String&			getName() const;
    const char*				getNameC() const;
    bool 							is(const char* name) const;
    bool 							is(const std::string& name) const;
    bool 							is(const Material& m) const;
    void 							setMaterial(const Material& m);
    void 							setName(const std::string& name);
    void 							setName(const char* name);

    MaterialObject&		operator=(const MaterialObject& m);


	private:
    String		_name;			// Size of name is max 16 letters

  }; // END MaterialObject class








  /*! \class MaterialObjectList gmMaterial.h <gmMaterial>
   *  \brief List of materialObjects class
   *
   *  containing:
   *    List of materialObjects
   */
  class MaterialObjectList : Array<MaterialObject> {
  public:
    MaterialObjectList(bool init=true);
    MaterialObjectList(char* file_name);

    void	initPreDef();
    bool	readFromFile(char* file_name);
    bool	storeToFile(char* file_name);

  }; // END class MaterialObjectList

} // END namespace GMlib


// Include inline Material class implementations
#include "gmMaterial_Material.c"

// Include inline MaterialObject class implementations
#include "gmMaterial_MaterialObject.c"

// Inline MaterialObjectList class implementations
#include "gmMaterial_MaterialObjectList.c"


#endif // __gmMATERIAL_H__

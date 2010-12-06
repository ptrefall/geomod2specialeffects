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



/*! \file gmColor.h
 *
 *  An implementation of colors and different color operations
 *
 *  \date   2009-03-06
 */

#ifndef __gmCOLOR_H__
#define __gmCOLOR_H__


namespace GMlib {




  /*! \class Color gmColor.h <gmColor>
   *  \brief A color class
   *
   *  A color class defining a color object and "color" operations
   */
  class Color {
  public:
    Color( unsigned int n = 0 );
    Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );
    Color( int r, int g, int b, int a = 255 );
    Color( double r, double g, double b, double a = 1.0 );
    Color( const Color& copy );



    unsigned int    get() const;
    unsigned char   get( int i ) const;
    unsigned char   getAlpha() const;
    double          getAlphaC() const;
    unsigned char   getBlue() const;
    double          getBlueC() const;
    double          getClampd( int i ) const;
    unsigned char   getGreen() const;
    double          getGreenC() const;
    Color           getInterpolatedHSV( double d, Color mx ) const;
    Color           getInverse() const;
    unsigned char   getRed() const;
    double          getRedC() const;
    const unsigned char*  getRgba() const;

    void            set( unsigned int n );
    void            set( unsigned char  rgba, int i );
    void            set( double rgba, int i );
    void            set( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0 );
    void            set( double r, double g, double b, double a = 0.0 );
    void            setAlpha( unsigned char a );
    void            setAlpha( double a );
    void            setBlue( unsigned char b );
    void            setBlue( double b );
    void            setGreen( unsigned char g );
    void            setGreen( double g );
    void            setRed( unsigned char r );
    void            setRed( double r );
    void            toHSV();
    void            toRGB();


    Color&          operator *= ( double d );
    Color           operator *  ( double d ) const;
    Color&          operator /= ( double d );
    Color           operator /  ( double d ) const;
    Color&          operator += ( const Color& o );
    Color           operator +  ( const Color& o ) const;
    Color&          operator -= ( const Color& o );
    Color           operator -  ( const Color& o ) const;
    Color&          operator += ( int o );
    Color           operator +  ( int o ) const;
    Color&          operator -= ( int o );
    Color           operator -  ( int o ) const;
    Color&          operator += ( double o );
    Color           operator +  ( double o );
    Color&          operator -= ( double o );
    Color           operator -  ( double o ) const;
    bool            operator == ( const Color& co ) const;


  protected:

    union{
      unsigned int name;
      unsigned char rgba[4];
    } _color;


  public:

    friend
    Color operator * ( double d, Color o ) {

        return o *= d;
      }


    // *****************************
    // IOSTREAM overloaded operators

    #ifdef GM_STREAM

    template<typename T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, Color& v ) {

      static Separator es(GMseparator::Element);

      //unsigned char r,g,b,a;
      double r, g, b, a;

      in >> r >> es >> g >> es >> b >> es >> a;
      v.set(r, g, b, a);

      return in;
    }


    template<typename T_Stream>
    friend T_Stream& operator << ( T_Stream& out, const Color& v ) {

      out << v.getRedC()    << GMseparator::Element
          << v.getGreenC()  << GMseparator::Element
          << v.getBlueC()   << GMseparator::Element
          << v.getAlphaC();
      return out;
    }


  private:

    istream& _printIn( istream& in );
    ostream& _printOut( ostream& out ) const;

    friend
    ostream& operator << ( ostream& out, const Color& v ) {

      return v._printOut( out );
    }

    friend
    istream& operator >> ( istream& in, Color& v ) {

      return v._printIn(in);
    }

    #endif


  };  // END class Color


  // *****************
  // Predefined Colors

  namespace GMcolor {

    extern Color AliceBlue;
    extern Color AntiqueWhite;
    extern Color Aqua;
    extern Color AquaMarine;
    extern Color Azure;
    extern Color Beige;
    extern Color Bisque;
    extern Color Black;
    extern Color BlanchedAlamond;
    extern Color Blue;
    extern Color BlueViolet;
    extern Color Brown;
    extern Color BurlyWood;
    extern Color CadetBlue;
    extern Color Chartreuse;
    extern Color Chocolate;
    extern Color Coral;
    extern Color CornflowerBlue;
    extern Color Cornsilk;
    extern Color Crimson;
    extern Color Cyan;
    extern Color DarkBlue;
    extern Color DarkCyan;
    extern Color DarkGoldenRod;
    extern Color DarkGrey;
    extern Color DarkGreen;
    extern Color DarkKhaki;
    extern Color DarkMagenta;
    extern Color DarkOliveGreen;
    extern Color DarkOrange;
    extern Color DarkOrchid;
    extern Color DarkRed;
    extern Color DarkSalmon;
    extern Color DarkSeaGreen;
    extern Color DarkSlateBlue;
    extern Color DarkSlateGrey;
    extern Color DarkTurquoise;
    extern Color DarkViolet;
    extern Color DeepPink;
    extern Color DeepSkyBlue;
    extern Color DimGrey;
    extern Color DodgerBlue;
    extern Color FireBrick;
    extern Color FloralWhite;
    extern Color ForestGreen;
    extern Color Fuchsia;
    extern Color Gainsboro;
    extern Color GhostWhite;
    extern Color Gold;
    extern Color GoldenRod;
    extern Color Grey;
    extern Color Green;
    extern Color GreenYellow;
    extern Color HoneyDew;
    extern Color HotPink;
    extern Color IndianRed;
    extern Color Indigo;
    extern Color Ivory;
    extern Color Khaki;
    extern Color Lavender;
    extern Color LavenderBlush;
    extern Color LawnGreen;
    extern Color LemonChiffon;
    extern Color LightBlue;
    extern Color LightCoral;
    extern Color LightCyan;
    extern Color LightGoldenRodYellow;
    extern Color LightGrey;
    extern Color LightGreen;
    extern Color LightPink;
    extern Color LightSalmon;
    extern Color LightSeaGreen;
    extern Color LightSkyBlue;
    extern Color LightSlateGrey;
    extern Color LightSteelBlue;
    extern Color LightYellow;
    extern Color Lime;
    extern Color LimeGreen;
    extern Color Linen;
    extern Color Magenta;
    extern Color Maroon;
    extern Color MediumAquaMarine;
    extern Color MediumBlue;
    extern Color MediumOrchid;
    extern Color MediumPurple;
    extern Color MediumSeaGreen;
    extern Color MediumSlateBlue;
    extern Color MediumSpringGreen;
    extern Color MediumTurquoise;
    extern Color MediumVioletRed;
    extern Color MidnightBlue;
    extern Color MintCream;
    extern Color MistyRose;
    extern Color Moccasin;
    extern Color NavajoWhite;
    extern Color Navy;
    extern Color OldLace;
    extern Color Olive;
    extern Color OliveDrab;
    extern Color Orange;
    extern Color OrangeRed;
    extern Color Orchid;
    extern Color PaleGoldenRod;
    extern Color PaleGreen;
    extern Color PaleTurquoise;
    extern Color PaleVioletRed;
    extern Color PapayaWhip;
    extern Color PeachPuff;
    extern Color Peru;
    extern Color Pink;
    extern Color Plum;
    extern Color PowderBlue;
    extern Color Purple;
    extern Color Red;
    extern Color RosyBrown;
    extern Color RoyalBlue;
    extern Color SaddleBrown;
    extern Color Salmon;
    extern Color SandyBrown;
    extern Color SeaGreen;
    extern Color SeaShell;
    extern Color Sienna;
    extern Color Silver;
    extern Color SkyBlue;
    extern Color SlateBlue;
    extern Color SlateGrey;
    extern Color Snow;
    extern Color SpringGreen;
    extern Color SteelBlue;
    extern Color Tan;
    extern Color Teal;
    extern Color Thistle;
    extern Color Tomato;
    extern Color Turquoise;
    extern Color Violet;
    extern Color Wheat;
    extern Color White;
    extern Color WhiteSmoke;
    extern Color Yellow;
    extern Color YellowGreen;

  } // END namespace GMlib::Color


} // END namespace GMlib



// Include inline Color class function implementations
#include "gmColor.c"


#endif // __gmCOLOR_H__



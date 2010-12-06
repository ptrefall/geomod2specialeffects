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



/*! \file gmColor.cpp
 *  \brief Color class implementations
 *
 *  Implementation of the Color class.
 *  Definitions of standard colors
 *
 *  \date   2009-03-06
 */



// Header
#include "gmColor.h"


namespace GMlib {

  namespace GMcolor {

    // Predefined colors
    Color AliceBlue               ( 0xF0,  0xF8,  0xFF );
    Color AntiqueWhite            ( 0xFA,  0xEB,  0xD7 );
    Color Aqua                    ( 0x00,  0xFF,  0xFF );
    Color AquaMarine              ( 0x7F,  0xFF,  0xD4 );
    Color Azure                   ( 0xF0,  0xFF,  0xFF );
    Color Beige                   ( 0xF5,  0xF5,  0xDC );
    Color Bisque                  ( 0xFF,  0xE4,  0xC4 );
    Color Black                   ( 0x00,  0x00,  0x00 );
    Color BlanchedAlamond         ( 0xFF,  0xEB,  0xCD );
    Color Blue                    ( 0x00,  0x00,  0xFF );
    Color BlueViolet              ( 0x8A,  0x2B,  0xE2 );
    Color Brown                   ( 0xA5,  0x2A,  0x2A );
    Color BurlyWood               ( 0xDE,  0xB8,  0x87 );
    Color CadetBlue               ( 0x5F,  0x9E,  0xA0 );
    Color Chartreuse              ( 0x7F,  0xFF,  0x00 );
    Color Chocolate               ( 0xD2,  0x69,  0x1E );
    Color Coral                   ( 0xFF,  0x7F,  0x50 );
    Color CornflowerBlue          ( 0x64,  0x95,  0xED );
    Color Cornsilk                ( 0xFF,  0xF8,  0xDC );
    Color Crimson                 ( 0xDC,  0x14,  0x3C );
    Color Cyan                    ( 0x00,  0xFF,  0xFF );
    Color DarkBlue                ( 0x00,  0x00,  0x8B );
    Color DarkCyan                ( 0x00,  0x8B,  0x8B );
    Color DarkGoldenRod           ( 0xB8,  0x86,  0x0B );
    Color DarkGrey                ( 0xA9,  0xA9,  0xA9 );
    Color DarkGreen               ( 0x00,  0x64,  0x00 );
    Color DarkKhaki               ( 0xBD,  0xB7,  0x6B );
    Color DarkMagenta             ( 0x8B,  0x00,  0x8B );
    Color DarkOliveGreen          ( 0x55,  0x6B,  0x2F );
    Color DarkOrange              ( 0xFF,  0x8C,  0x00 );
    Color DarkOrchid              ( 0x99,  0x32,  0xCC );
    Color DarkRed                 ( 0x8B,  0x00,  0x00 );
    Color DarkSalmon              ( 0xE9,  0x96,  0x7A );
    Color DarkSeaGreen            ( 0x8F,  0xBC,  0x8F );
    Color DarkSlateBlue           ( 0x48,  0x3D,  0x8B );
    Color DarkSlateGrey           ( 0x2F,  0x4F,  0x4F );
    Color DarkTurquoise           ( 0x00,  0xCE,  0xD1 );
    Color DarkViolet              ( 0x94,  0x00,  0xD3 );
    Color DeepPink                ( 0xFF,  0x14,  0x93 );
    Color DeepSkyBlue             ( 0x00,  0xBF,  0xFF );
    Color DimGrey                 ( 0x69,  0x69,  0x69 );
    Color DodgerBlue              ( 0x1E,  0x90,  0xFF );
    Color FireBrick               ( 0xB2,  0x22,  0x22 );
    Color FloralWhite             ( 0xFF,  0xFA,  0xF0 );
    Color ForestGreen             ( 0x22,  0x8B,  0x22 );
    Color Fuchsia                 ( 0xFF,  0x00,  0xFF );
    Color Gainsboro               ( 0xDC,  0xDC,  0xDC );
    Color GhostWhite              ( 0xF8,  0xF8,  0xFF );
    Color Gold                    ( 0xFF,  0xD7,  0x00 );
    Color GoldenRod               ( 0xDA,  0xA5,  0x20 );
    Color Grey                    ( 0x80,  0x80,  0x80 );
    Color Green                   ( 0x00,  0xFF,  0x00 );
    Color GreenYellow             ( 0xAD,  0xFF,  0x2F );
    Color HoneyDew                ( 0xF0,  0xFF,  0xF0 );
    Color HotPink                 ( 0xFF,  0x69,  0xB4 );
    Color IndianRed               ( 0xCD,  0x5C,  0x5C );
    Color Indigo                  ( 0x4B,  0x00,  0x82 );
    Color Ivory                   ( 0xFF,  0xFF,  0xF0 );
    Color Khaki                   ( 0xF0,  0xE6,  0x8C );
    Color Lavender                ( 0xE6,  0xE6,  0xFA );
    Color LavenderBlush           ( 0xFF,  0xF0,  0xF5 );
    Color LawnGreen               ( 0x7C,  0xFC,  0x00 );
    Color LemonChiffon            ( 0xFF,  0xFA,  0xCD );
    Color LightBlue               ( 0xAD,  0xD8,  0xE6 );
    Color LightCoral              ( 0xF0,  0x80,  0x80 );
    Color LightCyan               ( 0xE0,  0xFF,  0xFF );
    Color LightGoldenRodYellow    ( 0xFA,  0xFA,  0xD2 );
    Color LightGrey               ( 0xD3,  0xD3,  0xD3 );
    Color LightGreen              ( 0x90,  0xEE,  0x90 );
    Color LightPink               ( 0xFF,  0xB6,  0xC1 );
    Color LightSalmon             ( 0xFF,  0xA0,  0x7A );
    Color LightSeaGreen           ( 0x20,  0xB2,  0xAA );
    Color LightSkyBlue            ( 0x87,  0xCE,  0xFA );
    Color LightSlateGrey          ( 0x77,  0x88,  0x99 );
    Color LightSteelBlue          ( 0xB0,  0xC4,  0xDE );
    Color LightYellow             ( 0xFF,  0xFF,  0xE0 );
    Color Lime                    ( 0x00,  0xFF,  0x00 );
    Color LimeGreen               ( 0x32,  0xCD,  0x32 );
    Color Linen                   ( 0xFA,  0xF0,  0xE6 );
    Color Magenta                 ( 0xFF,  0x00,  0xFF );
    Color Maroon                  ( 0x80,  0x00,  0x00 );
    Color MediumAquaMarine        ( 0x66,  0xCD,  0xAA );
    Color MediumBlue              ( 0x00,  0x00,  0xCD );
    Color MediumOrchid            ( 0xBA,  0x55,  0xD3 );
    Color MediumPurple            ( 0x93,  0x70,  0xD8 );
    Color MediumSeaGreen          ( 0x3C,  0xB3,  0x71 );
    Color MediumSlateBlue         ( 0x7B,  0x68,  0xEE );
    Color MediumSpringGreen       ( 0x00,  0xFA,  0x9A );
    Color MediumTurquoise         ( 0x48,  0xD1,  0xCC );
    Color MediumVioletRed         ( 0xC7,  0x15,  0x85 );
    Color MidnightBlue            ( 0x19,  0x19,  0x70 );
    Color MintCream               ( 0xF5,  0xFF,  0xFA );
    Color MistyRose               ( 0xFF,  0xE4,  0xE1 );
    Color Moccasin                ( 0xFF,  0xE4,  0xB5 );
    Color NavajoWhite             ( 0xFF,  0xDE,  0xAD );
    Color Navy                    ( 0x00,  0x00,  0x80 );
    Color OldLace                 ( 0xFD,  0xF5,  0xE6 );
    Color Olive                   ( 0x80,  0x80,  0x00 );
    Color OliveDrab               ( 0x6B,  0x8E,  0x23 );
    Color Orange                  ( 0xFF,  0xA5,  0x00 );
    Color OrangeRed               ( 0xFF,  0x45,  0x00 );
    Color Orchid                  ( 0xDA,  0x70,  0xD6 );
    Color PaleGoldenRod           ( 0xEE,  0xE8,  0xAA );
    Color PaleGreen               ( 0x98,  0xFB,  0x98 );
    Color PaleTurquoise           ( 0xAF,  0xEE,  0xEE );
    Color PaleVioletRed           ( 0xD8,  0x70,  0x93 );
    Color PapayaWhip              ( 0xFF,  0xEF,  0xD5 );
    Color PeachPuff               ( 0xFF,  0xDA,  0xB9 );
    Color Peru                    ( 0xCD,  0x85,  0x3F );
    Color Pink                    ( 0xFF,  0xC0,  0xCB );
    Color Plum                    ( 0xDD,  0xA0,  0xDD );
    Color PowderBlue              ( 0xB0,  0xE0,  0xE6 );
    Color Purple                  ( 0x80,  0x00,  0x80 );
    Color Red                     ( 0xFF,  0x00,  0x00 );
    Color RosyBrown               ( 0xBC,  0x8F,  0x8F );
    Color RoyalBlue               ( 0x41,  0x69,  0xE1 );
    Color SaddleBrown             ( 0x8B,  0x45,  0x13 );
    Color Salmon                  ( 0xFA,  0x80,  0x72 );
    Color SandyBrown              ( 0xF4,  0xA4,  0x60 );
    Color SeaGreen                ( 0x2E,  0x8B,  0x57 );
    Color SeaShell                ( 0xFF,  0xF5,  0xEE );
    Color Sienna                  ( 0xA0,  0x52,  0x2D );
    Color Silver                  ( 0xC0,  0xC0,  0xC0 );
    Color SkyBlue                 ( 0x87,  0xCE,  0xEB );
    Color SlateBlue               ( 0x6A,  0x5A,  0xCD );
    Color SlateGrey               ( 0x70,  0x80,  0x90 );
    Color Snow                    ( 0xFF,  0xFA,  0xFA );
    Color SpringGreen             ( 0x00,  0xFF,  0x7F );
    Color SteelBlue               ( 0x46,  0x82,  0xB4 );
    Color Tan                     ( 0xD2,  0xB4,  0x8C );
    Color Teal                    ( 0x00,  0x80,  0x80 );
    Color Thistle                 ( 0xD8,  0xBF,  0xD8 );
    Color Tomato                  ( 0xFF,  0x63,  0x47 );
    Color Turquoise               ( 0x40,  0xE0,  0xD0 );
    Color Violet                  ( 0xEE,  0x82,  0xEE );
    Color Wheat                   ( 0xF5,  0xDE,  0xB3 );
    Color White                   ( 0xFF,  0xFF,  0xFF );
    Color WhiteSmoke              ( 0xF5,  0xF5,  0xF5 );
    Color Yellow                  ( 0xFF,  0xFF,  0x00 );
    Color YellowGreen             ( 0x9A,  0xCD,  0x32 );
  }
}


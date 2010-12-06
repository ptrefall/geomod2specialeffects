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



/*! \file gmColor.c
 *  \brief Inline Color class implementations
 *
 *  Implementation of inline Color class functions.
 *
 *  \date   2009-03-06
 */

#include <algorithm>

namespace GMlib {


  /*! Color::Color(unsigned int n)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color::Color(unsigned int n) {

    _color.name = n;
  }


  /*! Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a ) {

    _color.rgba[0] = r;
    _color.rgba[1] = g;
    _color.rgba[2] = b;
    _color.rgba[3] = a;
  }


  /*! Color::Color(int r, int g, int b, int a )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color::Color(int r, int g, int b, int a ) {

    _color.rgba[0] = (unsigned char)r;
    _color.rgba[1] = (unsigned char)g;
    _color.rgba[2] = (unsigned char)b;
    _color.rgba[3] = (unsigned char)a;
  }


  /*! Color::Color(double r, double g, double b, double a )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color::Color( double r, double g, double b, double a ) {

    _color.rgba[0] = (unsigned char)(r*255);
    _color.rgba[1] = (unsigned char)(g*255);
    _color.rgba[2] = (unsigned char)(b*255);
    _color.rgba[3] = (unsigned char)(a*255);
  }


  /*! Color::Color(const Color& k)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color::Color(const Color& copy) {

    _color = copy._color;
  }




  /*! unsigned int Color::get() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned int Color::get() const {
    return _color.name;
  }


  /*! unsigned char Color::get(int i)const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned char Color::get(int i)const	{
    return _color.rgba[i];
  }


  /*! unsigned char Color::getAlpha()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned char Color::getAlpha()const {
    return _color.rgba[3];
  }


  /*! double Color::getAlphaC()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Color::getAlphaC()const {
    return _color.rgba[3]/255.0;
  }


  /*! unsigned char Color::getBlue()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned char Color::getBlue()const {
    return _color.rgba[2];
  }


  /*! double Color::getBlueC()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Color::getBlueC()const {
    return _color.rgba[2]/255.0;
  }


  /*! double Color::getClampd(int i)const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Color::getClampd(int i)const	{
    return _color.rgba[i]/255.0;
  }


  /*! unsigned char Color::getGreen()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned char Color::getGreen()const {
    return _color.rgba[1];
  }


  /*! double Color::getGreenC()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Color::getGreenC()const {
    return _color.rgba[1]/255.0;
  }


  /*! Color Color::getInterpolatedHSV(double d, Color mx) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::getInterpolatedHSV(double d, Color mx) const {

    Color mn = *this;
    mx.toHSV();
    mn.toHSV();
    mx = (1-d)*mn+d*mx;
    mx.toRGB();
    return mx;
  }


  /*! Color Color::getInverse() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::getInverse() const {

    return Color(255-_color.rgba[0],255-_color.rgba[1],255-_color.rgba[3]);
  }


  /*! unsigned char Color::getRed()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned char Color::getRed()const {
    return _color.rgba[0];
  }


  /*! double Color::getRedC()const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Color::getRedC()const {
    return _color.rgba[0]/255.0;
  }


  inline
  const unsigned char*  Color::getRgba() const {

    return _color.rgba;
  }


  /*! void Color::set(unsigned int n)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::set(unsigned int n) {
    _color.name = n;
  }


  /*! void Color::set(unsigned char  rgba, int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::set(unsigned char  rgba, int i)	{
    _color.rgba[i] = rgba;
  }


  /*! void Color::set(double rgba, int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::set(double rgba, int i)	{
    _color.rgba[i] = (unsigned char)(rgba*255);
  }


  /*! void Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    _color.rgba[0] = r; _color.rgba[1] = g; _color.rgba[2] = b; _color.rgba[3] = a;
  }


  /*! void Color::set(double r, double g, double b, double a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::set(double r, double g, double b, double a) {
    _color.rgba[0] = (unsigned char)(r*255); _color.rgba[1] = (unsigned char)(g*255);
    _color.rgba[2] = (unsigned char)(b*255); _color.rgba[3] = (unsigned char)(a*255);
  }


  /*! void Color::setAlpha(unsigned char a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setAlpha(unsigned char a) {
    _color.rgba[3] = a;
  }


  /*! void Color::setAlpha(double a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setAlpha(double a) {
    _color.rgba[3] = (unsigned char)(a*255);
  }


  /*! void Color::setBlue(unsigned char b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setBlue(unsigned char b) {
    _color.rgba[2] = b;
  }


  /*! void Color::setBlue(double b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setBlue(double b) {
    _color.rgba[2] = (unsigned char)(b*255);
  }


  /*! void Color::setGreen(unsigned char g)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setGreen(unsigned char g) {
    _color.rgba[1] = g;
  }


  /*! void Color::setGreen(double g)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setGreen(double g) {
    _color.rgba[1] = (unsigned char)(g*255);
  }


  /*! void Color::setRed(unsigned char r)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setRed( unsigned char r ) {

    _color.rgba[0] = r;
  }


  /*! void Color::setRed(double r)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::setRed(double r) {
    _color.rgba[0] = (unsigned char)(r*255);
  }


  /*! \brief Pending Documentation
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::toHSV() {

    double r=getRedC(),g=getGreenC(),b=getBlueC();
    double h,s,v,mx,mn;
    mx = std::max<double>( std::max<double>(r,g), b );
    mn = std::min<double>( std::min<double>(r,g), b );
    v=mx;
    if(mx > 1e-6) s = (mx-mn)/mx;
    else		  s = 0.0;
    if(s == 0.0)  h = 0.0;
    else
    {
      double rc = (mx-r)/(mx-mn);
      double gc = (mx-g)/(mx-mn);
      double bc = (mx-b)/(mx-mn);
      if(r == mx)			h = bc-gc;
      else if(g == mx)	h = rc-bc + 2.0;
      else if(b == mx)	h = gc-rc + 4.0;
      h *= 60.0;
      if(h<0.0) h += 360.0;
      h /= 360.0;			// 360 degree is skaled to 1.
    }
    setRed(h); setGreen(s); setBlue(v);
  }


  /*! void Color::toRGB()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Color::toRGB() {

    double h=getRedC(),s=getGreenC(),v=getBlueC();
    double r,g,b;
    h *= 360.0;
    if(s < 0.000001)
      r = g = b = v;
    else
    {
      if(h > 359.999999) h = 0.0;
      h /= 60.0;
      int    i = (int)h;
      double f = h - double(i);
      double p = v*(1-s);
      double q = v*(1-s*f);
      double t = v*(1-s*(1-f));
      switch(i)
      {
      case 0: r=v; g=t; b=p; break;
      case 1: r=q; g=v; b=p; break;
      case 2: r=p; g=v; b=t; break;
      case 3: r=p; g=q; b=v; break;
      case 4: r=t; g=p; b=v; break;
      case 5: r=v; g=p; b=q; break;
      default: ;
      }
    }
    setRed( r ); setGreen( g ); setBlue( b );
  }


  /*! Color& Color::operator*=(double d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator*=(double d) {

    double k;
    k = _color.rgba[0]*d; if(k > 255.0) _color.rgba[0] = 255; else _color.rgba[0] = (unsigned char)k;
    k = _color.rgba[1]*d; if(k > 255.0) _color.rgba[1] = 255; else _color.rgba[1] = (unsigned char)k;
    k = _color.rgba[2]*d; if(k > 255.0) _color.rgba[2] = 255; else _color.rgba[2] = (unsigned char)k;
    k = _color.rgba[3]*d; if(k > 255.0) _color.rgba[3] = 255; else _color.rgba[3] = (unsigned char)k;
    return * this;
  }


  /*! Color Color::operator*(double d)const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator*(double d)const {

    return d * (*this);
  }


  /*! Color& Color::operator/=(double d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator/=(double d) {

    d=1/d;
    return (*this) *= d;
  }


  /*! Color Color::operator/(double d) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator/(double d) const {

    d=1/d;
    return d * (*this);
  }


  /*! Color& Color::operator+=(const Color& o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator+=(const Color& o) {

    int k;
    k = _color.rgba[0]+o._color.rgba[0]; if(k > 255) _color.rgba[0] = 255; else _color.rgba[0] = k;
    k = _color.rgba[1]+o._color.rgba[1]; if(k > 255) _color.rgba[1] = 255; else _color.rgba[1] = k;
    k = _color.rgba[2]+o._color.rgba[2]; if(k > 255) _color.rgba[2] = 255; else _color.rgba[2] = k;
    k = _color.rgba[3]+o._color.rgba[3]; if(k > 255) _color.rgba[3] = 255; else _color.rgba[3] = k;
    return * this;
  }


  /*! Color Color::operator+(const Color& o) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator+(const Color& o) const {

    Color k= (*this);
    return k += o;
  }


  /*! Color& Color::operator-=(const Color& o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator-=(const Color& o) {

    int k;
    k = _color.rgba[0]-o._color.rgba[0]; if(k < 0) _color.rgba[0] = 0; else _color.rgba[0] = k;
    k = _color.rgba[1]-o._color.rgba[1]; if(k < 0) _color.rgba[1] = 0; else _color.rgba[1] = k;
    k = _color.rgba[2]-o._color.rgba[2]; if(k < 0) _color.rgba[2] = 0; else _color.rgba[2] = k;
    k = _color.rgba[3]-o._color.rgba[3]; if(k < 0) _color.rgba[3] = 0; else _color.rgba[3] = k;
    return * this;
  }


  /*! Color Color::operator-(const Color& o) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator-(const Color& o) const {

    Color k= (*this);
    return k -= o;
  }


  /*! Color& Color::operator+=(int o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator+=(int o) {

    int k;
    k = _color.rgba[0]+o; if(k > 255) _color.rgba[0] = 255; else _color.rgba[0] = k;
    k = _color.rgba[1]+o; if(k > 255) _color.rgba[1] = 255; else _color.rgba[1] = k;
    k = _color.rgba[2]+o; if(k > 255) _color.rgba[2] = 255; else _color.rgba[2] = k;
    k = _color.rgba[3]+o; if(k > 255) _color.rgba[3] = 255; else _color.rgba[3] = k;
    return *this;
  }


  /*! Color Color::operator+(int o) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator+(int o) const {

    Color k= (*this);
    return k += o;
  }


  /*! Color& Color::operator-=(int o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator-=(int o) {

    int k;
    k = _color.rgba[0]-o; if(k < 0) _color.rgba[0] = 0; else _color.rgba[0] = k;
    k = _color.rgba[1]-o; if(k < 0) _color.rgba[1] = 0; else _color.rgba[1] = k;
    k = _color.rgba[2]-o; if(k < 0) _color.rgba[2] = 0; else _color.rgba[2] = k;
    k = _color.rgba[3]-o; if(k < 0) _color.rgba[3] = 0; else _color.rgba[3] = k;
    return * this;
  }


  /*! Color Color::operator-(int o) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator-(int o) const {

    Color k= (*this); return k -= o;
  }


  /*! Color& Color::operator+=(double o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator+=(double o) {

    int k = int(o*255);
    return (*this) += k;
  }


  /*! Color Color::operator+(double o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator+(double o) {

    Color k= (*this); return k += o;
  }


  /*! Color& Color::operator-=(double o)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color& Color::operator-=(double o) {

    int k = int(o*255);
    return (*this) -= k;
  }


  /*! Color Color::operator-(double o) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Color Color::operator-(double o) const {

    Color k= (*this); return k -= o;
  }


  /*! bool Color::operator==(const Color& co) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Color::operator==(const Color& co) const {

    return _color.name == co._color.name;
  }


} // End namespace GMlib

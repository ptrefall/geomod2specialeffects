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



/*! \file gmDisplayObject.h
 *  \brief Pending Detailed Documentation
 *
 *  Interface to the Display Object class
 *
 *  \date   2008-07-22
 *
 *  \todo
 *  - Move variable documentation physicaly out of the header file.
 *  - Translage documentattion text for the class
 */



#ifndef __gmDISPLAYOBJECT_H__
#define __gmDISPLAYOBJECT_H__

// STL includes
#include <string>

// Local GMlib includes
#include "gmSceneObject.h"



namespace GMlib {


  /*! \class DisplayObject gmDisplayObject.h <gmDisplayObject>
   *  \brief The DisplayObject Class
   *
   *  Pending Documentation
   */
  class DisplayObject : public SceneObject {
  public:
    DisplayObject(
      const Point<float,3>&  pos = Point3D<float>(0,0,0),
      const Vector<float,3>& dir = Vector3D<float>(1,0,0),
      const Vector<float,3>& up = Vector3D<float>(0,0,1)
    );

    DisplayObject(
      const Point<float,3>&  lock_pos,
      const Point<float,3>&  pos = Point3D<float>(0,0,0),
      const Vector<float,3>& up = Vector3D<float>(0,0,1)
    );

    DisplayObject(
      SceneObject* lock_object,
      const Point<float,3>&  pos = Point3D<float>(0,0,0),
      const Vector<float,3>& up = Vector3D<float>(0,0,1)
    );

    DisplayObject(const DisplayObject& s);
    virtual ~DisplayObject();




    virtual Vector<float,3>	  getDir();
    Point<float,3>	          getLockPos();
    double				            getLockDist();
    virtual Point<float,3>	  getPos();
    virtual Vector<float,3>   getSide();
    virtual Vector<float,3>   getUp();
    bool				              isLocked();
    virtual void		          lock(SceneObject* obj);
    virtual void		          lock(const Point<float,3>& pos);
    virtual void		          lock(double d);
    virtual void              move(float d);
    virtual void              move(const Vector<float,3>& t);
    virtual void              move(char,double);
    virtual void              move(const Vector<float,2>& t);
    virtual void              roll(Angle a);
    void                      set(
                                const Point<float,3>&  pos,
                                const Vector<float,3>& dir,
                                const Vector<float,3>& up
                              );
    virtual void              tilt(Angle a);
    virtual void              turn(Angle a);
    void				              unLock();



    // *****************
    // Virtual functions
    // from SceneObject
    virtual std::string       getIdentity() const;
    virtual void              rotate(Angle a, const Vector<float,3>& rot_axel);
    virtual void              rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void              rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    virtual void              rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void              translate(const Vector<float,3>& trans_vector);
    virtual void              translateGlobal(const Vector<float,3>& trans_vector);



  protected:
    // Matrices from Scene to this
    HqMatrix<float,3>				  _matrix_scene;
    HqMatrix<float,3>				  _matrix_scene_inv;

    Point3D<float>		        _pos;
    UnitVector3D<float>	      _dir;
    UnitVector3D<float>	      _side;
    UnitVector3D<float>	      _up;

    Point3D<float>		        _lock_pos;
    SceneObject*			        _lock_object;
    bool					            _locked;

    virtual void              basisChange(
                                const Vector<float,3>& dir,
                                const Vector<float,3>& side,
                                const Vector<float,3>& up,
                                const Vector<float,3>& pos
                              );

    Point<float,3>	          getSceneLockPos();
    void				              updateOrientation(const Point<float,3>& lock_at_p);

    // *****************
    // Virtual functions
    // from SceneObject
    void			                _prepareDisplay(const HqMatrix<float,3>& m);
    void			                localSimulate(double dt);


    #ifdef GM_STREAM
    public:

      // Stream constructor
      /*! DisplayObject( T_Stream& in, int st)
       *  \brief DisplayObject Stream Constructor
       *
       *  Pending further Documentation
       *
       *  \todo
       *  - Find out why this doesn't work:
       *    DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix(), _matrix_scene_inv()
       */
      template <typename T_Stream>
  //    DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix(), _matrix_scene_inv() {
      DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix_scene_inv() {

        prIn(in);
        _side	= _up^_dir;
        _locked	= false;
        _lock_object	= 0;
        basisChange(_side, _up, _dir, _pos);
      }


      template <typename T_Stream>
      friend T_Stream& operator<<(T_Stream& out, const DisplayObject& v) {

        out << *((SceneObject*)& v);
        v.prOut(out);
        return out;
      }

      template <typename T_Stream>
      friend T_Stream& operator>>(T_Stream& in, DisplayObject& v) {

        in >> *((SceneObject*)& v);
        v.prIn(in);
        return in;
      }


    private:
      //, const DisplayObject& v)
      template <typename T_Stream>
      void prOut(T_Stream& out) const {

        out << _pos << GMseparator::Object << _dir << GMseparator::Object << _up << GMseparator::Object;
      }

      //, DisplayObject& v)
      template <typename T_Stream>
      void prIn(T_Stream& in) {

        static Separator os(GMseparator::Object);
        in >> _pos >> os >> _dir >> os >> _up >> os;
      }
    #endif

  }; // END DisplayObject class


} // END namespace GMlib

// Include inline implementations
#include "gmDisplayObject.c"

#endif // __gmDIDPLAYOBJECT_H__

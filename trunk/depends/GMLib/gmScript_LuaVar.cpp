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



/*! \file gmScript_LuaVar.cpp
 *  \brief LuaVar class implementations
 *
 *  Implementation of the LuaVar class.
 *
 *  \date   2009-09-08
 */


#include "gmScript.h"

#ifdef GM_SCRIPT_LUA


namespace GMlib {

  namespace Script {

    namespace Lua {

      LuaVar::LuaVar() : _type(GM_LUA_VAR_TYPE_NIL) {}


      LuaVar::LuaVar( bool b ) : _type( GM_LUA_VAR_TYPE_BOOL ), _var_bool( b ) {}


      LuaVar::LuaVar( int num ) : _type( GM_LUA_VAR_TYPE_NUM ), _var_num( num ) {}


      LuaVar::LuaVar( float num ) : _type( GM_LUA_VAR_TYPE_NUM ), _var_num( num ) {}


      LuaVar::LuaVar( double num ) : _type( GM_LUA_VAR_TYPE_NUM ), _var_num( num ) {}


      LuaVar::LuaVar( char* str ) : _type( GM_LUA_VAR_TYPE_STRING ), _var_str( str )  {}


      LuaVar::LuaVar( const char* str ) : _type( GM_LUA_VAR_TYPE_STRING ), _var_str( str ) {}


      LuaVar::LuaVar( luaC::lua_CFunction func ) : _type( GM_LUA_VAR_TYPE_CFUNC ), _var_func( func ) {}


      LuaVar::LuaVar( const LuaVar& copy ) {

        *this = copy;
      }


      LuaVar::~LuaVar() {}


      LuaVar& LuaVar::operator = ( const LuaVar& copy ) {

        _type       = copy._type;
        _var_bool   = copy._var_bool;
        _var_num    = copy._var_num;
        _var_str    = copy._var_str;

        return *this;
      }


      const std::string& LuaVar::getName() const {

        return _name;
      }


      void LuaVar::push( luaC::lua_State* L ) const {

        switch(_type) {
          case GM_LUA_VAR_TYPE_BOOL:
            luaC::lua_pushboolean( L, _var_bool );
            break;

          case GM_LUA_VAR_TYPE_NUM:
            luaC::lua_pushnumber( L, _var_num );
            break;

          case GM_LUA_VAR_TYPE_STRING:
            luaC::lua_pushstring( L, _var_str.c_str() );
            break;

          case GM_LUA_VAR_TYPE_CFUNC:
            luaC::lua_pushcfunction( L, _var_func );
            break;

          case GM_LUA_VAR_TYPE_NIL:
          default:
            luaC::lua_pushnil( L );
            break;



        }
      }


      void LuaVar::setName( const std::string& name ) {

        _name = name;
      }


      bool LuaVar::toBoolean() const {

         return _var_bool;
      }


      double LuaVar::toDouble() const {

        return _var_num;
      }


      float LuaVar::toFloat() const {

        return float(_var_num);
      }


      int LuaVar::toInt() const {

        return int(_var_num);
      }


      std::string LuaVar::toString() const {

        return _var_str;
      }


    } // END namespace Lua

  } // END namespace Script

} // END namespace GMlib


#endif // GM_SCRIPT_LUA

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



/*! \file gmScript_LuaScript.cpp
 *  \brief LuaScript class implementations
 *
 *  Implementation of the LuaScript class.
 *
 *  \date   2009-08-30
 */



#ifdef GM_SCRIPT_LUA


#include "gmScript.h"

namespace GMlib {

  namespace Script {

    namespace Lua {


      LuaScript::LuaScript() {

        _L = luaC::luaL_newstate();
        _valid = false;
        _errfunc = 0;
      }


      LuaScript::~LuaScript() {

        luaC::lua_close(_L);
      }


      void LuaScript::addVar( LuaVar* var ) {

        _vars += var;
      }


      void LuaScript::addVars( const ArrayT<LuaVar*>& vars ) {

        _vars += vars;
      }


      void LuaScript::clearVars() {

        _vars.clear();
      }


      void LuaScript::constructResult() {

          luaC::lua_getglobal( _L, "result" );

          // Clear existing result set.
          _result.clear();

          // Handle lua result dependent on type
          int var_type = luaC::lua_type( _L, luaC::lua_gettop(_L) );
          switch( var_type ) {

            case LUA_TBOOLEAN:  _result += new LuaVar( luaC::lua_toboolean( _L, 1 ) );  break;
            case LUA_TNUMBER:   _result += new LuaVar( luaC::lua_tonumber( _L, 1 ) );   break;
            case LUA_TSTRING:   _result += new LuaVar( luaC::lua_tostring( _L, 1 ) );   break;
            case LUA_TTABLE:    constructResult_table();    break;

            case LUA_TNIL:
            default:
              break;
          }
      }


      void LuaScript::constructResult_table() {

        luaC::lua_pushnil( _L );

        while( luaC::lua_next(_L, -2) != 0 ) {

          int var_type = luaC::lua_type( _L, -1 );

          switch( var_type ) {

            case LUA_TBOOLEAN:  _result += new LuaVar( luaC::lua_toboolean( _L, -1 ) );  break;
            case LUA_TNUMBER:   _result += new LuaVar( luaC::lua_tonumber( _L, -1 ) );   break;
            case LUA_TSTRING:   _result += new LuaVar( luaC::lua_tostring( _L, -1 ) );   break;
            case LUA_TTABLE:    constructResult_table();    break;

            case LUA_TNIL:
            default:
              break;
          }

          luaC::lua_pop(_L, 1);
        }
      }


      void LuaScript::exec() {

        load();

        if( _valid ) {

          // Push varis
          int no_vars = 0;
          for( int i = 0; i < _vars.getSize(); i++ ) {

            if( _vars[i]->getName().length() > 0 ) {

              _vars[i]->push( _L );
              luaC::lua_setglobal( _L, _vars[i]->getName().c_str() );
              no_vars++;
            }
          }

          // Call the lua script program
          _s = luaC::lua_pcall( _L, 0, LUA_MULTRET, 0 );
        }
      }


      void LuaScript::exec( const std::string& fname ) {

        load();

        if( _valid ) {

          // Execute the script
          _s = luaC::lua_pcall( _L, 0, 0, _errfunc );
          if( _s == 0 ) {

            // Set function name to be called
            luaC::lua_getglobal( _L, fname.c_str() );

            // Push the functions variables on the stack
            for( int i = 0; i < _vars.getSize(); i++ )
              _vars[i]->push( _L );

            // Call the function
            _s = luaC::lua_pcall( _L, _vars.getSize(), 1, _errfunc );

            // Set result as global value.
            luaC::lua_setglobal( _L, "result" );

            // copy back return values.
            constructResult();

            // ballance the lua stack
  //          luaC::lua_pop( _L, 1 );
          }
        }
      }


      int LuaScript::getErrfunc() const {

        return _errfunc;
      }


      std::string LuaScript::getErrors() {

        std::string err;

        if( _s == 0 )
          err = "No Error";
        else {

          err = lua_tostring( _L, -1 );
          luaC::lua_pop( _L, 1 );
        }

        return err;
      }


      const Array<LuaVar*>& LuaScript::getResult() const {

        return _result;
      }


      int LuaScript::getStatus() const {

        return _s;
      }


      void LuaScript::load() {

        // Set script to invalid
        _valid = false;

        // Load lua chunk
        switch( _load_type ) {

          case GM_LUA_LOAD_TYPE_FILE:
            _s = luaC::luaL_loadfile( _L, _prog.c_str() );
            break;

          case GM_LUA_LOAD_TYPE_STRING:
            _s = luaC::luaL_loadstring( _L, _prog.c_str() );
            break;
        }

        // Check if load was successful
        if( _s == 0 )
          _valid = true;
      }


      void LuaScript::loadProgram( const std::string& prog, GM_LUA_LOAD_TYPE type ) {

        _load_type = type;
        _prog = prog;
      }


      void LuaScript::loadStdLibs() {

        luaC::luaL_openlibs( _L );
      }

    } // END namespace Lua

  } // END namespace Script

} // END namespace GMlib


#endif // GM_SCRIPT_LUA

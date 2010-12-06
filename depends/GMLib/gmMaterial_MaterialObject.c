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



/*! \file gmMaterial_MaterialObject.c
 *  \brief Inline MaterialObject class implementations
 *
 *  Implementation of the MaterialObject class.
 *
 *  \date   2008-08-03
 */



namespace GMlib {


  /*! MaterialObject::MaterialObject(	const Material& mat, const char* name )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const Material& mat, const char* name ) : Material(mat)	{

    _name = name;
  }


  /*! MaterialObject::MaterialObject(	const Material& mat, string name )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const Material& mat, std::string name ) : Material(mat)	{

    _name = name;
  }


  /*! MaterialObject::MaterialObject(	const MaterialObject& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const MaterialObject& m) : Material(m) {

    _name = m._name;
  }


  /*! void MaterialObject::deleteTexture()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::deleteTexture() {

    this->_texture = Texture();
  }


  /*! const Material&		MaterialObject::getMaterial() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const Material&		MaterialObject::getMaterial() const {

    return *this;
  }


  /*! const GM_String&	MaterialObject::getName() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const String&	MaterialObject::getName() const {

    return _name;
  }


  /*! const char* MaterialObject::getNameC() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const char* MaterialObject::getNameC() const {

    return _name.c_str();
  }


  /*! bool MaterialObject::is(const char* name) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const char* name) const {

    return _name == name;
  }


  /*! bool MaterialObject::is(const string& name) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const std::string& name) const {

    return _name == name;
  }


  /*! bool MaterialObject::is(const Material& m) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const Material& m) const {

    return m == (Material)(*this);
  }


  /*! void MaterialObject::setMaterial(const Material& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setMaterial(const Material& m)	{

    Material::operator = ( m );
  }

  /*! void MaterialObject::setName(const string& name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setName(const std::string& name) {

    _name = name;
  }

  /*! void MaterialObject::setName(const char* name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setName(const char* name) {

    _name = name;
  }


  /*! MaterialObject& MaterialObject::operator=(const MaterialObject& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject& MaterialObject::operator=(const MaterialObject& m) {

    Material::operator = ( m );

    _name         = m._name;

    return *this;
  }

}

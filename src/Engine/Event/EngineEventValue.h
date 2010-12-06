#pragma once

#include <ClanLib/src/API/core.h>

namespace Engine
{
class Component; 
class IProperty;
class IEntity;
namespace Events
{

class EngineEventValue
{
public:
	enum Type
	{
		null,
		integer,
		uinteger,
		string,
		boolean,
		number,
		component,
		property,
		entity
	};

	EngineEventValue();
	EngineEventValue(int value);
	EngineEventValue(unsigned int value);
	EngineEventValue(float value);
	EngineEventValue(const CL_String &value);
	EngineEventValue(const CL_StringRef &value);
	EngineEventValue(const char *str);
	EngineEventValue(const wchar_t *str);
	EngineEventValue(Engine::Component *comp);
	EngineEventValue(Engine::IProperty *prop);
	EngineEventValue(Engine::IEntity *entity);
	explicit EngineEventValue(bool value);
	EngineEventValue(Type type);

	Type GetType() const;

	bool IsNull() const;
	bool IsUinteger() const;
	bool IsInteger() const;
	bool IsNumber() const;
	bool IsString() const;
	bool IsBoolean() const;
	bool IsComponent() const;
	bool IsProperty() const;
	bool IsEntity() const;
	bool IsComplex() const;

	unsigned int ToUinteger() const;
	int ToInteger() const;
	float ToNumber() const;
	CL_String ToString() const;
	bool ToBoolean() const;
	Engine::Component *ToComponent() const;
	Engine::IProperty *ToProperty() const;
	Engine::IEntity *ToEntity() const;

	inline operator unsigned int() const { return ToUinteger(); }
	inline operator int() const { return ToInteger(); }
	inline operator float() const { return ToNumber(); }
	inline operator CL_String() const { return ToString(); }
	inline operator bool() const { return ToBoolean(); }

private:
	Type type;
	union
	{
		int valueInt;
		unsigned int valueUint;
		float valueFloat;
		bool valueBool;
	};
	CL_String valueString;
	Engine::Component *valueComp;
	Engine::IProperty *valueProp;
	Engine::IEntity *valueEntity;
};

}}

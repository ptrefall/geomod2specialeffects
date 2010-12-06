#include "precomp.h"
#include "EngineEventValue.h"

using namespace Engine;
using namespace Events;

EngineEventValue::EngineEventValue()
: type(null), valueInt(0)
{
}

EngineEventValue::EngineEventValue(int value)
: type(integer), valueInt(value)
{
}

EngineEventValue::EngineEventValue(unsigned int value)
: type(uinteger), valueUint(value)
{
}

EngineEventValue::EngineEventValue(float value)
: type(number), valueFloat(value)
{
}

EngineEventValue::EngineEventValue(const CL_String &value)
: type(string), valueString(value)
{
}

EngineEventValue::EngineEventValue(const CL_StringRef &value)
: type(string), valueString(value)
{
}

EngineEventValue::EngineEventValue(const char *value)
: type(string), valueString(value)
{
}

EngineEventValue::EngineEventValue(const wchar_t *value)
: type(string), valueString(value)
{
}

EngineEventValue::EngineEventValue(Engine::Component *value)
: type(component), valueComp(value)
{
}

EngineEventValue::EngineEventValue(Engine::IProperty *value)
: type(property), valueProp(value)
{
}

EngineEventValue::EngineEventValue(Engine::IEntity *value)
: type(entity), valueEntity(value)
{
}

EngineEventValue::EngineEventValue(bool value)
: type(boolean), valueBool(value)
{
}

EngineEventValue::EngineEventValue(Type type)
: type(type), valueInt(0)
{
}

EngineEventValue::Type EngineEventValue::GetType() const
{
	return type;
}

bool EngineEventValue::IsNull() const
{
	return type == null;
}

bool EngineEventValue::IsUinteger() const
{
	return type == uinteger;
}

bool EngineEventValue::IsInteger() const
{
	return type == integer;
}

bool EngineEventValue::IsNumber() const
{
	return type == number;
}

bool EngineEventValue::IsString() const
{
	return type == string;
}

bool EngineEventValue::IsBoolean() const
{
	return type == boolean;
}

bool EngineEventValue::IsComponent() const
{
	return type == component;
}

bool EngineEventValue::IsProperty() const
{
	return type == property;
}

bool EngineEventValue::IsEntity() const
{
	return type == entity;
}

unsigned int EngineEventValue::ToUinteger() const
{
	if (IsUinteger())
		return valueUint;
	else
		throw CL_Exception("EngineEventValue is not an unsigned integer");
}

int EngineEventValue::ToInteger() const
{
	if (IsInteger())
		return valueInt;
	else
		throw CL_Exception("EngineEventValue is not an integer");
}

float EngineEventValue::ToNumber() const
{
	if (IsNumber())
		return valueFloat;
	else
		throw CL_Exception("EngineEventValue is not a floating point number");
}

CL_String EngineEventValue::ToString() const
{
	if (IsString())
		return valueString;
	else
		throw CL_Exception("EngineEventValue is not a string");
}

bool EngineEventValue::ToBoolean() const
{
	if (IsBoolean())
		return valueBool;
	else
		throw CL_Exception("EngineEventValue is not a boolean");
}

Engine::Component *EngineEventValue::ToComponent() const
{
	if(IsComponent())
		return valueComp;
	else
		throw CL_Exception("EngineEventValue is not a component");
}

Engine::IProperty *EngineEventValue::ToProperty() const
{
	if(IsProperty())
		return valueProp;
	else
		throw CL_Exception("EngineEventValue is not a property");
}

Engine::IEntity *EngineEventValue::ToEntity() const
{
	if(IsEntity())
		return valueEntity;
	else
		throw CL_Exception("EngineEventValue is not an entity");
}

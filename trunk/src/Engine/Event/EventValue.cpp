#include "precomp.h"
#include "EventValue.h"

using namespace Engine;
using namespace Events;

EventValue::EventValue()
: type(null), valueInt(0)
{
}

EventValue::EventValue(int value)
: type(integer), valueInt(value)
{
}

EventValue::EventValue(unsigned int value)
: type(uinteger), valueUint(value)
{
}

EventValue::EventValue(float value)
: type(number), valueFloat(value)
{
}

EventValue::EventValue(const CL_String &value)
: type(string), valueString(value)
{
}

EventValue::EventValue(const CL_StringRef &value)
: type(string), valueString(value)
{
}

EventValue::EventValue(const char *value)
: type(string), valueString(value)
{
}

EventValue::EventValue(const wchar_t *value)
: type(string), valueString(value)
{
}

EventValue::EventValue(Engine::Component *value)
: type(component), valueComp(value)
{
}

EventValue::EventValue(Engine::IProperty *value)
: type(property), valueProp(value)
{
}

EventValue::EventValue(Engine::IEntity *value)
: type(entity), valueEntity(value)
{
}

EventValue::EventValue(bool value)
: type(boolean), valueBool(value)
{
}

EventValue::EventValue(Type type)
: type(type), valueInt(0)
{
}

EventValue::Type EventValue::GetType() const
{
	return type;
}

bool EventValue::IsNull() const
{
	return type == null;
}

bool EventValue::IsUinteger() const
{
	return type == uinteger;
}

bool EventValue::IsInteger() const
{
	return type == integer;
}

bool EventValue::IsNumber() const
{
	return type == number;
}

bool EventValue::IsString() const
{
	return type == string;
}

bool EventValue::IsBoolean() const
{
	return type == boolean;
}

bool EventValue::IsComponent() const
{
	return type == component;
}

bool EventValue::IsProperty() const
{
	return type == property;
}

bool EventValue::IsEntity() const
{
	return type == entity;
}

unsigned int EventValue::ToUinteger() const
{
	if (IsUinteger())
		return valueUint;
	else
		throw CL_Exception("EventValue is not an unsigned integer");
}

int EventValue::ToInteger() const
{
	if (IsInteger())
		return valueInt;
	else
		throw CL_Exception("EventValue is not an integer");
}

float EventValue::ToNumber() const
{
	if (IsNumber())
		return valueFloat;
	else
		throw CL_Exception("EventValue is not a floating point number");
}

CL_String EventValue::ToString() const
{
	if (IsString())
		return valueString;
	else
		throw CL_Exception("EventValue is not a string");
}

bool EventValue::ToBoolean() const
{
	if (IsBoolean())
		return valueBool;
	else
		throw CL_Exception("EventValue is not a boolean");
}

Engine::Component *EventValue::ToComponent() const
{
	if(IsComponent())
		return valueComp;
	else
		throw CL_Exception("EventValue is not a component");
}

Engine::IProperty *EventValue::ToProperty() const
{
	if(IsProperty())
		return valueProp;
	else
		throw CL_Exception("EventValue is not a property");
}

Engine::IEntity *EventValue::ToEntity() const
{
	if(IsEntity())
		return valueEntity;
	else
		throw CL_Exception("EventValue is not an entity");
}

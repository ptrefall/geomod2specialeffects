#pragma once

namespace Engine
{
namespace Events
{

class IEvent
{
public:
	IEvent(const char *type) {}
	virtual const char *getType() const = 0;
	virtual int getArg0Type() const = 0;
	virtual int getArg1Type() const = 0;
	virtual int getArg2Type() const = 0;
	virtual int getArg3Type() const = 0;
	virtual int getArg4Type() const = 0;
};

}}

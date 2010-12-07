#pragma once

#include "IEvent.h"
#include "Type.h"

namespace Engine
{
namespace Events
{

template<class T0, class T1, class T2, class T3, class T4>
class Event : public IEvent
{
public:
	Event(const char *type, const T0 &arg0, const T1 &arg1, const T2 &arg2, const T3 &arg3, const T4 &arg4) 
		: IEvent(type), type(type), arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4) {}
	virtual const char *getType() const { return type; }
	virtual int getArg0Type() const { return Type::getType(arg0); }
	virtual int getArg1Type() const { return Type::getType(arg1); }
	virtual int getArg2Type() const { return Type::getType(arg2); }
	virtual int getArg3Type() const { return Type::getType(arg3); }
	virtual int getArg4Type() const { return Type::getType(arg4); }
	const T0 &getArg0() const { return arg0; }
	const T1 &getArg1() const { return arg1; }
	const T2 &getArg2() const { return arg2; }
	const T3 &getArg3() const { return arg3; }
	const T4 &getArg4() const { return arg4; }

protected:
	const char *type;
	const T0 &arg0;
	const T1 &arg1;
	const T2 &arg2;
	const T3 &arg3;
	const T4 &arg4;
};

}}

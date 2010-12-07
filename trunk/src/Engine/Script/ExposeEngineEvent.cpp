#include "precomp.h"
#include "ExposeEngineEvent.h"
#include "ScriptMgr.h"
#include <Core/CoreMgr.h>
#include <Entity/IEntity.h>

using namespace Engine;
using namespace LuaPlus;
using namespace Events;

ExposeEngineEvent::ExposeEngineEvent(CoreMgr *coreMgr, const Events::EngineEvent *event)
: event(event)
{
	this->coreMgr = coreMgr;
}

ExposeEngineEvent::~ExposeEngineEvent()
{
	lEvent.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

void ExposeEngineEvent::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	
	if(lEvents.IsNil())
		lEvents = globals.GetByName("Events");
	if(lEvents.IsNil())
		lEvents = globals.CreateTable("Events");

	lEvent = lEvents.CreateTable(event->getName().c_str());
	lEvent.SetString("id", event->getName().c_str());

	for(unsigned int i = 0; i < event->getArgumentCount(); i++)
	{
		Events::EngineEventValue arg = event->getArgument(i);
		exposeArg(i, arg, lEvent);
	}
}

void ExposeEngineEvent::exposeArg(unsigned int i, const Events::EngineEventValue &arg, LuaPlus::LuaObject &lEvent)
{
	if(arg.IsBoolean())
	{
	}
	else if(arg.IsInteger())
	{
	}
	else if(arg.IsNumber())
	{
	}
	else if(arg.IsUinteger())
	{
	}
	else if(arg.IsString())
	{
	}
	else if(arg.IsComponent())
	{
	}
	else if(arg.IsProperty())
	{
	}
	else if(arg.IsEntity())
	{
	}
	else if(arg.IsComplex())
	{
	}
	else if(arg.IsNull())
	{
	}
}

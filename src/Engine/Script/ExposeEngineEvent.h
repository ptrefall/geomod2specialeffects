#pragma once

#include <LuaPlus/LuaPlus.h>
#include <Event/EngineEvent.h>
#include <Event/EngineEventValue.h>

namespace Engine
{
class CoreMgr;
class ExposeEngineEvent
{
public:
	ExposeEngineEvent(CoreMgr *coreMgr, const Events::EngineEvent *event);
	~ExposeEngineEvent();

	LuaPlus::LuaObject getLEvent() const { return lEvent; }
	LuaPlus::LuaObject getLEvents() const { return lEvents; }

private:
	void init();
	void exposeArg(unsigned int i, const Events::EngineEventValue &arg, LuaPlus::LuaObject &lEvent);
	CoreMgr *coreMgr;

	const Events::EngineEvent *event;
	LuaPlus::LuaObject lEvent;
	LuaPlus::LuaObject lEvents;
};

}

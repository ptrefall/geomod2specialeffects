#pragma once

#include <LuaPlus/LuaPlus.h>
#include <vector>
#include <EventSystem/src/EngineEventContainer.h>
#include <EventSystem/src/EngineEvent.h>

namespace Engine
{
namespace Core { class CoreManager; }
namespace Script
{
class WrapIEntity;
class WrapComponent;

class WrapComponentContainer
{
public:
	WrapComponentContainer(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity);
	~WrapComponentContainer();

	int init();

	LuaPlus::LuaObject &getLComps() { return lComponents; }

private:
	void AddComponent(LuaPlus::LuaObject self, LuaPlus::LuaObject lName);

	Core::CoreManager *coreMgr;
	Script::WrapIEntity *wEntity;

	LuaPlus::LuaObject lComponents;
	std::vector<WrapComponent*> wComponents;

	void OnComponentAdded(const Engine::Events::EngineEvent &event);
	Engine::Events::EngineEventContainer engineEvents;
};

}
}

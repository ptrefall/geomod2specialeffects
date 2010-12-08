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

class WrapEntityManager
{
public:
	WrapEntityManager(Core::CoreManager *coreMgr);
	~WrapEntityManager();

	int init();

	LuaPlus::LuaObject &getLEntities() { return lEntities; }
	LuaPlus::LuaObject getLEntity(unsigned int id);
	WrapIEntity *getWEntity(unsigned int id);

private:
	LuaPlus::LuaObject CreateEntity(LuaPlus::LuaObject lType, LuaPlus::LuaObject lName);

	Core::CoreManager *coreMgr;

	LuaPlus::LuaObject lEntities;
	std::vector<WrapIEntity*> wEntities;

	void OnEntityCreated(const Engine::Events::EngineEvent &event);
	void OnEntityRemoved(const Engine::Events::EngineEvent &event);
	Engine::Events::EngineEventContainer engineEvents;
};

}
}

#pragma once

#include <LuaPlus/LuaPlus.h>
#include <vector>
#include <ClanLib/src/API/core.h>
#include <Property.h>
#include <IEntity.h>
#include <EventSystem/src/EngineEventContainer.h>
#include <EventSystem/src/EngineEvent.h>

namespace Engine
{
namespace Core { class CoreManager; }
namespace Script
{
class WrapIEntity;
class WrapIPlayer;
class WrapIProperty;
class WrapIRoom;

class WrapPropertyContainer
{
public:
	WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity);
	WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIPlayer *wPlayer);
	WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIRoom *wRoom);
	~WrapPropertyContainer();

	int init();

	LuaPlus::LuaObject &getLProps() { return lProperties; }

private:
	void AddProperty(LuaPlus::LuaObject self, LuaPlus::LuaObject name, LuaPlus::LuaObject defValue);
	LuaPlus::LuaObject HasProperty(LuaPlus::LuaObject self, LuaPlus::LuaObject name);

	void add(const CL_String &name, Entity::IProperty *prop, WrapIProperty *wProp);

	Core::CoreManager *coreMgr;
	Script::WrapIEntity *wEntity;
	Script::WrapIPlayer *wPlayer;
	Script::WrapIRoom *wRoom;

	LuaPlus::LuaObject lProperties;
	std::vector<WrapIProperty*> wProperties;

	void OnPropertyAdded(const Engine::Events::EngineEvent &event);
	Engine::Events::EngineEventContainer engineEvents;
};

}
}

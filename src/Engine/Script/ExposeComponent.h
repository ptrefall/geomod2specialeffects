#pragma once

#include <LuaPlus/LuaPlus.h>
#include <Clanlib/src/API/core.h>

namespace Engine
{
namespace Core { class CoreManager; }
namespace Entity { class Component; }
namespace Script
{
class WrapIEntity;
class WrapComponentContainer;

class WrapComponent
{
public:
	WrapComponent(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity, WrapComponentContainer *wCompContainer, Entity::Component *component);
	~WrapComponent();

	int init();

	Entity::Component *getComp() const { return component; }
	LuaPlus::LuaObject getLComp() const { return lComponent; }
	WrapIEntity *getWEntity() const { return wEntity; }

private:
	Core::CoreManager *coreMgr;
	Script::WrapComponentContainer *wCompContainer;
	Script::WrapIEntity *wEntity;

	Entity::Component *component;
	LuaPlus::LuaObject lComponent;
};

}
}

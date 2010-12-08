#include "LuaComponent.h"
#include "WrapComponent.h"
#include "WrapEntityManager.h"
#include "WrapIEvent.h"
#include "ScriptManager.h"
#include <Core/Core.h>
#include <Log/LogManager.h>
#include <ComponentContainer.h>
#include <PropertyContainer.h>
#include <EventSystem/src/Event.h>
#include <EventSystem/src/CommandHandler.h>
#include <Player/IPlayer.h>

#include <LuaPlus/LuaPlus.h>

using namespace Engine;
using namespace Component;
using namespace LuaPlus;

LuaComponent::LuaComponent(Engine::Core::CoreManager *coreMgr, Engine::Entity::IEntity *entity, const CL_String &name)
: Engine::Entity::Component(entity, name), coreMgr(coreMgr)
{
	wComp = NULL;
	hasInit = false;
	hasUpdate = false;
	hasCommand = false;
	hasEvent = false;
}

void LuaComponent::initLuaExposure(Script::WrapComponent *wComp)
{
	this->wComp = wComp;
	
	hasInit = false;
	LuaObject lInit = wComp->getLComp().GetByName("OnInit");
	if(lInit.IsFunction())
	{
		hasInit = true;
	}

	hasUpdate = false;
	LuaObject lUpdate = wComp->getLComp().GetByName("OnUpdate");
	if(lUpdate.IsFunction())
	{
		hasUpdate = true;
	}
	
	hasCommand = false;
	LuaObject lCommand = wComp->getLComp().GetByName("OnCommand");
	if(lCommand.IsFunction())
	{
		hasCommand = true;
	}
	
	hasEvent = false;
	LuaObject lEvent = wComp->getLComp().GetByName("OnEvent");
	if(lEvent.IsFunction())
	{
		hasEvent = true;
	}

	if(hasInit)
	{
		//Make sure that the entity exist in the global state's Entities table
		LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntities().GetByIndex(entity->getId());
		if(lEntity.IsNil())
		{
			CL_String err = cl_format("Entity of id %1 has not been exposed to Lua!", entity->getId());
			coreMgr->getLogMgr()->log("LuaComponent:InitLuaExposure", err, Log::L_ERROR);
			return;
		}

		coreMgr->getScriptMgr()->doString(cl_format("%1:OnInit(Entities[%2])", name, entity->getId()));
	}
}

void LuaComponent::ExecuteCommand(const CL_String &command, Engine::Player::IPlayer *player)
{
	if(hasCommand)
	{
		//Make sure that the entity exist in the global state's Entities table
		LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntities().GetByIndex(entity->getId());
		if(lEntity.IsNil())
		{
			CL_String err = cl_format("Entity of id %1 has not been exposed to Lua!", entity->getId());
			coreMgr->getLogMgr()->log("LuaComponent:ExecuteCommand", err, Log::L_ERROR);
			return;
		}

		if(player)
			coreMgr->getScriptMgr()->doString(cl_format("%1:OnCommand(Entities[%2], '%3', %4)", name, entity->getId(), command, player->getId()));
		else
			coreMgr->getScriptMgr()->doString(cl_format("%1:OnCommand(Entities[%2], '%3', nil)", name, entity->getId(), command));
	}
}

void LuaComponent::ExecuteEvent(const Engine::Events::IEvent &event, Engine::Player::IPlayer *player)
{
	if(hasEvent)
	{
		//Make sure that the entity exist in the global state's Entities table
		LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntities().GetByIndex(entity->getId());
		if(lEntity.IsNil())
		{
			CL_String err = cl_format("Entity of id %1 has not been exposed to Lua!", entity->getId());
			coreMgr->getLogMgr()->log("LuaComponent:ExecuteEvent", err, Log::L_ERROR);
			return;
		}

		Script::WrapIEvent wEvent(coreMgr, &event);
		int fail = wEvent.init();
		if(fail)
			return;

		//Make sure that the event exist in the global state's Events table
		LuaObject lEvent = wEvent.getLEvents().GetByName(event.getType());
		if(lEvent.IsNil())
		{
			CL_String err = cl_format("Event of type %1 has not been exposed to Lua!", event.getType());
			coreMgr->getLogMgr()->log("LuaComponent:ExecuteEvent", err, Log::L_ERROR);
			return;
		}

		if(player)
			coreMgr->getScriptMgr()->doString(cl_format("%1:OnEvent(Entities[%2], Events['%3'], %4)", name, entity->getId(), event.getType(), player->getId()));
		else
			coreMgr->getScriptMgr()->doString(cl_format("%1:OnEvent(Entities[%2], Events['%3'], nil)", name, entity->getId(), event.getType()));
	}
}

void LuaComponent::Update(double dt)
{
	if(hasUpdate)
	{
		//Make sure that the entity exist in the global state's Entities table
		LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntities().GetByIndex(entity->getId());
		if(lEntity.IsNil())
		{
			CL_String err = cl_format("Entity of id %1 has not been exposed to Lua!", entity->getId());
			coreMgr->getLogMgr()->log("LuaComponent:Update", err, Log::L_ERROR);
			return;
		}

		coreMgr->getScriptMgr()->doString(cl_format("%1:OnUpdate(Entities[%2], %3)", name, entity->getId(), dt));
	}
}

#include "WrapEntityManager.h"
#include "WrapIEntity.h"
#include <Core/Core.h>
#include <Core/EntityManager.h>
#include <Log/LogManager.h>
#include <EventSystem/src/IEngineEventManager.h>
#include "ScriptManager.h"
#include <IEntity.h>

using namespace Engine;
using namespace Script;
using namespace LuaPlus;

WrapEntityManager::WrapEntityManager(Core::CoreManager *coreMgr)
: engineEvents(coreMgr->getEngineEventMgr())
{
	this->coreMgr = coreMgr;
}

WrapEntityManager::~WrapEntityManager()
{
}

int WrapEntityManager::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	globals.RegisterDirect("CreateEntity", *this, &WrapEntityManager::CreateEntity);
	lEntities = globals.CreateTable("Entities");

	engineEvents.Connect("EntityCreated", this, &WrapEntityManager::OnEntityCreated);
	engineEvents.Connect("EntityRemoved", this, &WrapEntityManager::OnEntityRemoved);
	return 0;
}

LuaObject WrapEntityManager::getLEntity(unsigned int id)
{
	return lEntities.GetByIndex((int)id);
}

WrapIEntity *WrapEntityManager::getWEntity(unsigned int id)
{
	for(unsigned int i = 0; i < wEntities.size(); i++)
	{
		if(wEntities[i]->getEntity()->getId() == id)
		{
			return wEntities[i];
		}
	}
	return NULL;
}

LuaObject WrapEntityManager::CreateEntity(LuaPlus::LuaObject lType, LuaPlus::LuaObject lName)
{
	if(!lType.IsString())
	{
		CL_String type_type = lType.TypeName();
		
		CL_String msg = cl_format("Failed to create entity, because the type of type was %1 when expecting String", type_type);
		coreMgr->getLogMgr()->log("WrapEntityManager::CreateEntity", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}
	if(!lName.IsString() && !lName.IsNil())
	{
		CL_String name_type = lName.TypeName();
		
		CL_String msg = cl_format("Failed to create entity, because the type of name was %1 when expecting String or Nil", name_type);
		coreMgr->getLogMgr()->log("WrapEntityManager::CreateEntity", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	CL_String type = lType.ToString();
	CL_String name;

	Engine::Entity::IEntity *entity = NULL;
	if(lName.IsString())
	{
		name = lName.ToString();
		if(name != CL_String())
		{
			entity = coreMgr->getEntityMgr()->create(type, name);
		}
		else
		{
			entity = coreMgr->getEntityMgr()->create(type);
		}
	}
	else
	{
		entity = coreMgr->getEntityMgr()->create(type);
	}

	if(entity == NULL)
	{
		CL_String msg = cl_format("Failed to create entity %1 of type %2", name, type);
		coreMgr->getLogMgr()->log("WrapEntityManager::CreateEntity", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	WrapIEntity *wEntity = getWEntity(entity->getId());

	if(wEntity)
		return wEntity->getLEntity();
	else
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

void WrapEntityManager::OnEntityCreated(const Engine::Events::EngineEvent &event)
{
	Engine::Entity::IEntity *entity = event.getArgument(0).ToEntity();

	WrapIEntity *wEntity = new WrapIEntity(coreMgr, this, entity);
	int fail = wEntity->init();
	if(fail)
	{
		delete wEntity;
		wEntity = NULL;
		
		CL_String msg = cl_format("Failed to initialize entity wrapper for type %1", entity->getType());
		coreMgr->getLogMgr()->log("WrapEntityManager::OnEntityCreated", msg, Log::L_ERROR);
		return;
	}
	wEntities.push_back(wEntity);
}

void WrapEntityManager::OnEntityRemoved(const Engine::Events::EngineEvent &event)
{
	Engine::Entity::IEntity *entity = event.getArgument(0).ToEntity();
	for(unsigned int i = 0; i < wEntities.size(); i++)
	{
		if(wEntities[i]->getEntity()->getId() == entity->getId())
		{
			WrapIEntity *wEntity = wEntities[i];
			wEntities.erase(wEntities.begin() + i);
			delete wEntity;
			wEntity = NULL;
			break;
		}
	}
}

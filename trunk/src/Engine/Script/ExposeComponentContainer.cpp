#include "WrapComponentContainer.h"
#include "WrapComponent.h"
#include "WrapIEntity.h"
#include "ScriptManager.h"
#include <Core/Core.h>
#include <Log/LogManager.h>
#include <IEntity.h>
#include <Component.h>
#include <EventSystem/src/IEngineEventManager.h>
#include <EventSystem/src/Event.h>

using namespace Engine;
using namespace Script;
using namespace LuaPlus;

WrapComponentContainer::WrapComponentContainer(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity)
: engineEvents(coreMgr->getEngineEventMgr())
{
	this->coreMgr = coreMgr;
	this->wEntity = wEntity;
}

WrapComponentContainer::~WrapComponentContainer()
{
	for(unsigned int i = 0; i < wComponents.size(); i++)
	{
		WrapComponent *wComp = wComponents[i];
		delete wComp;
		wComp = NULL;
	}
	wComponents.clear();
	lComponents.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

int WrapComponentContainer::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	lComponents = wEntity->getLEntity().CreateTable("Components");

	{
		LuaObject lMeta = lComponents.CreateTable("MetaTable");
		lMeta.SetObject("__index", lMeta);
		lMeta.RegisterDirect("Add", *this, &WrapComponentContainer::AddComponent);
		lComponents.SetLightUserData("__object", this);
		lComponents.SetMetaTable(lMeta);
	}

	{
		LuaObject lMeta = wEntity->getLMeta();
		lMeta.RegisterDirect("AddComponent", *this, &WrapComponentContainer::AddComponent);
	}
	
	Engine::Entity::IEntity *entity = wEntity->getEntity();
	std::vector<Engine::Entity::Component*> &components = entity->GetComponents();
	std::vector<Engine::Entity::Component*>::iterator compIt = components.begin();
	for(; compIt != components.end(); ++compIt)
	{
		WrapComponent *wComp = new WrapComponent(coreMgr, wEntity, this, (*compIt));
		int fail = wComp->init();
		if(fail)
		{
			delete wComp;
			wComp = NULL;

			CL_String err = cl_format("Failed to initialize component wrapper for Component %1", (*compIt)->GetName());
			coreMgr->getLogMgr()->log("WrapComponentContainer:Init", err, Log::L_ERROR);
			continue;
		}
		wComponents.push_back(wComp);
	}

	engineEvents.Connect("ComponentAdded", this, &WrapComponentContainer::OnComponentAdded);

	return 0;
}

void WrapComponentContainer::AddComponent(LuaObject self, LuaObject lName)
{
	if(!self.IsTable())
	{
		CL_String self_type = self.TypeName();
		
		CL_String err = cl_format("Failed to add component, because the type of self was %1 when expecting Table", self_type);
		coreMgr->getLogMgr()->log("WrapComponentContainer:AddComponent", err, Log::L_ERROR);
		return;
	}

	if(!lName.IsString())
	{
		CL_String name_type = lName.TypeName();
		
		CL_String err = cl_format("Failed to add component, because the type of name was %1 when expecting String", name_type);
		coreMgr->getLogMgr()->log("WrapComponentContainer:AddComponent", err, Log::L_ERROR);
		return;
	}

	CL_String name = lName.ToString();
	
	if(wEntity == NULL)
	{
		CL_String err = cl_format("Failed to add component %1, because there is no entity!", name);
		coreMgr->getLogMgr()->log("WrapComponentContainer:AddComponent", err, Log::L_ERROR);
		return;
	}

	Entity::Component *comp = wEntity->getEntity()->AddComponent(name);
	if(comp == NULL)
	{
		CL_String err = cl_format("Failed to add component %1, because no component was returned!", name);
		coreMgr->getLogMgr()->log("WrapComponentContainer:AddComponent", err, Log::L_ERROR);
		return;
	}

	return;
}

void WrapComponentContainer::OnComponentAdded(const Engine::Events::EngineEvent &event)
{
	Engine::Entity::IEntity *entity = event.getArgument(1).ToEntity();
	if(entity->getId() != wEntity->getEntity()->getId())
		return;

	Engine::Entity::Component *comp = event.getArgument(0).ToComponent();

	WrapComponent *wComp = new WrapComponent(coreMgr, wEntity, this, comp);
	int fail = wComp->init();
	if(fail)
	{
		delete wComp;
		wComp = NULL;
		
		CL_String err = cl_format("Failed to initialize component wrapper for Component %1", comp->GetName());
		coreMgr->getLogMgr()->log("WrapComponentContainer:OnComponentAdded", err, Log::L_ERROR);
		return;
	}
	wComponents.push_back(wComp);
}

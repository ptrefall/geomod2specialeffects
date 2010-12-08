#include "WrapPropertyContainer.h"
#include "WrapIProperty.h"
#include "WrapIEntity.h"
#include "WrapIPlayer.h"
#include "WrapIRoom.h"
#include "ScriptManager.h"
#include <Core/Core.h>
#include <Log/LogManager.h>
#include <EventSystem/src/IEngineEventManager.h>
#include <IEntity.h>
#include <Player/IPlayer.h>
#include <Room/IRoom.h>
#include <EventSystem/src/Event.h>

using namespace Engine;
using namespace Script;
using namespace LuaPlus;

WrapPropertyContainer::WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity)
: engineEvents(coreMgr->getEngineEventMgr())
{
	this->coreMgr = coreMgr;
	this->wEntity = wEntity;
	this->wPlayer = NULL;
	this->wRoom = NULL;
}

WrapPropertyContainer::WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIPlayer *wPlayer)
: engineEvents(coreMgr->getEngineEventMgr())
{
	this->coreMgr = coreMgr;
	this->wPlayer = wPlayer;
	this->wEntity = NULL;
	this->wRoom = NULL;
}

WrapPropertyContainer::WrapPropertyContainer(Core::CoreManager *coreMgr, Script::WrapIRoom *wRoom)
: engineEvents(coreMgr->getEngineEventMgr())
{
	this->coreMgr = coreMgr;
	this->wRoom = wRoom;
	this->wPlayer = NULL;
	this->wEntity = NULL;
}

WrapPropertyContainer::~WrapPropertyContainer()
{
	for(unsigned int i = 0; i < wProperties.size(); i++)
	{
		WrapIProperty *wProp = wProperties[i];
		delete wProp;
		wProp = NULL;
	}
	wProperties.clear();
	lProperties.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

int WrapPropertyContainer::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	
	if(wEntity)
	{
		lProperties = wEntity->getLEntity().CreateTable("Properties");

		Engine::Entity::IEntity *entity = wEntity->getEntity();
		std::map<CL_String, Engine::Entity::IProperty*> &properties = entity->GetProperties();
		std::map<CL_String, Engine::Entity::IProperty*>::iterator propIt = properties.begin();
		for(; propIt != properties.end(); ++propIt)
		{
			WrapIProperty *wProp = new WrapIProperty(coreMgr, wEntity, this, propIt->second);
			int fail = wProp->init();
			if(fail)
			{
				delete wProp;
				wProp = NULL;

				CL_String msg = cl_format("Failed to initialize Property Wrapper for property %1", propIt->first);
				coreMgr->getLogMgr()->log("WrapPropertyContainer::Init", msg, Log::L_ERROR);
				continue;
			}
			wProperties.push_back(wProp);
		}

		LuaObject lMeta = wEntity->getLMeta();
		lMeta.RegisterDirect("AddProperty", *this, &WrapPropertyContainer::AddProperty);
		lMeta.RegisterDirect("HasProperty", *this, &WrapPropertyContainer::HasProperty);
	}
	else if(wPlayer)
	{
		lProperties = wPlayer->getLPlayer().CreateTable("Properties");

		Engine::Player::IPlayer *player = wPlayer->getPlayer();
		std::map<CL_String, Engine::Entity::IProperty*> &properties = player->GetProperties();
		std::map<CL_String, Engine::Entity::IProperty*>::iterator propIt = properties.begin();
		for(; propIt != properties.end(); ++propIt)
		{
			WrapIProperty *wProp = new WrapIProperty(coreMgr, wPlayer, this, propIt->second);
			int fail = wProp->init();
			if(fail)
			{
				delete wProp;
				wProp = NULL;

				CL_String msg = cl_format("Failed to initialize Property Wrapper for property %1", propIt->first);
				coreMgr->getLogMgr()->log("WrapPropertyContainer::Init", msg, Log::L_ERROR);
				continue;
			}
			wProperties.push_back(wProp);
		}

		LuaObject lMeta = wPlayer->getLMeta();
		lMeta.RegisterDirect("AddProperty", *this, &WrapPropertyContainer::AddProperty);
		lMeta.RegisterDirect("HasProperty", *this, &WrapPropertyContainer::HasProperty);
	}
	else if(wRoom)
	{
		lProperties = wRoom->getLRoom().CreateTable("Properties");

		Engine::Room::IRoom *room = wRoom->getRoom();
		std::map<CL_String, Engine::Entity::IProperty*> &properties = room->GetProperties();
		std::map<CL_String, Engine::Entity::IProperty*>::iterator propIt = properties.begin();
		for(; propIt != properties.end(); ++propIt)
		{
			WrapIProperty *wProp = new WrapIProperty(coreMgr, wRoom, this, propIt->second);
			int fail = wProp->init();
			if(fail)
			{
				delete wProp;
				wProp = NULL;

				CL_String msg = cl_format("Failed to initialize Property Wrapper for property %1", propIt->first);
				coreMgr->getLogMgr()->log("WrapPropertyContainer::Init", msg, Log::L_ERROR);
				continue;
			}
			wProperties.push_back(wProp);
		}

		LuaObject lMeta = wRoom->getLMeta();
		lMeta.RegisterDirect("AddProperty", *this, &WrapPropertyContainer::AddProperty);
		lMeta.RegisterDirect("HasProperty", *this, &WrapPropertyContainer::HasProperty);
	}
	
	engineEvents.Connect("PropertyAdded", this, &WrapPropertyContainer::OnPropertyAdded);

	return 0;
}

void WrapPropertyContainer::AddProperty(LuaObject self, LuaObject lName, LuaObject defValue)
{
	if(!self.IsTable())
	{
		CL_String self_type = self.TypeName();
		
		CL_String msg = cl_format("Failed to add property, because the type of self was %1 when expecting Table", self_type);
		coreMgr->getLogMgr()->log("WrapPropertyContainer::AddProperty", msg, Log::L_ERROR);
		return;
	}

	if(!lName.IsString())
	{
		CL_String name_type = lName.TypeName();
		
		CL_String msg = cl_format("Failed to add property, because the type of name was %1 when expecting String", name_type);
		coreMgr->getLogMgr()->log("WrapPropertyContainer::AddProperty", msg, Log::L_ERROR);
		return;
	}

	CL_String name = lName.ToString();
	
	Entity::IEntity *entity = NULL;
	Player::IPlayer *player = NULL;
	Room::IRoom *room = NULL;
	if(wEntity)
		entity = wEntity->getEntity();
	else if(wPlayer)
		player = wPlayer->getPlayer();
	else if(wRoom)
		room = wRoom->getRoom();

	if(defValue.IsBoolean())
	{
		bool val = defValue.GetBoolean();
		if(entity)
			entity->AddProperty<bool>(name, val);
		else if(player)
			player->AddProperty<bool>(name, val);
		else if(room)
			room->AddProperty<bool>(name, val);
	}
	else if(defValue.IsNumber())
	{
		float val = (float)defValue.ToNumber();
		if(entity)
			entity->AddProperty<float>(name, val);
		else if(player)
			player->AddProperty<float>(name, val);
		else if(room)
			room->AddProperty<float>(name, val);
	}
	else if(defValue.IsInteger())
	{
		int val = defValue.ToInteger();
		if(entity)
			entity->AddProperty<int>(name, val);
		else if(player)
			player->AddProperty<int>(name, val);
		else if(room)
			room->AddProperty<int>(name, val);
	}
	else if(defValue.IsString())
	{
		CL_String val = defValue.ToString();
		if(entity)
			entity->AddProperty<CL_String>(name, val);
		else if(player)
			player->AddProperty<CL_String>(name, val);
		else if(room)
			room->AddProperty<CL_String>(name, val);
	}
	else if(defValue.IsTable())
	{
		bool hasX = false;
		bool hasY = false;
		bool hasZ = false;
		bool hasW = false;

		LuaObject xObj = defValue.GetByName("x");
		if(xObj.IsNumber())
			hasX = true;
		
		LuaObject yObj = defValue.GetByName("y");
		if(yObj.IsNumber())
			hasY = true;
		
		LuaObject zObj = defValue.GetByName("z");
		if(zObj.IsNumber())
			hasZ = true;
		
		LuaObject wObj = defValue.GetByName("w");
		if(wObj.IsNumber())
			hasW = true;

		if(hasX && hasY && hasZ && hasW)
		{
			CL_Vec4f val = CL_Vec4f((float)xObj.ToNumber(),(float)yObj.ToNumber(),(float)zObj.ToNumber(),(float)wObj.ToNumber());
			if(entity)
				entity->AddProperty<CL_Vec4f>(name, val);
			else if(player)
				player->AddProperty<CL_Vec4f>(name, val);
			else if(room)
				room->AddProperty<CL_Vec4f>(name, val);
		}
		else if(hasX && hasY && hasZ)
		{
			CL_Vec3f val = CL_Vec3f((float)xObj.ToNumber(),(float)yObj.ToNumber(),(float)zObj.ToNumber());
			if(entity)
				entity->AddProperty<CL_Vec3f>(name, val);
			else if(player)
				player->AddProperty<CL_Vec3f>(name, val);
			else if(room)
				room->AddProperty<CL_Vec3f>(name, val);
		}
		else if(hasX && hasY)
		{
			CL_Vec2f val = CL_Vec2f((float)xObj.ToNumber(),(float)yObj.ToNumber());
			if(entity)
				entity->AddProperty<CL_Vec2f>(name, val);
			else if(player)
				player->AddProperty<CL_Vec2f>(name, val);
			else if(room)
				room->AddProperty<CL_Vec2f>(name, val);
		}
	}
	return;
}

LuaPlus::LuaObject WrapPropertyContainer::HasProperty(LuaPlus::LuaObject self, LuaPlus::LuaObject name)
{
	if(!self.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", self.TypeName());
		coreMgr->getLogMgr()->log("WrapPropertyContainer::HasProperty", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	if(!name.IsString())
	{
		CL_String msg = cl_format("Name was not a string (it's a %1)", name.TypeName());
		coreMgr->getLogMgr()->log("WrapPropertyContainer::HasProperty", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	bool retVal = false;
	if(wEntity)
		retVal = wEntity->getEntity()->HasProperty(name.ToString());
	else if(wPlayer)
		retVal = wPlayer->getPlayer()->HasProperty(name.ToString());
	else if(wRoom)
		retVal = wRoom->getRoom()->HasProperty(name.ToString());

	LuaObject lRetVal;
	lRetVal.AssignBoolean(coreMgr->getScriptMgr()->GetGlobalState()->Get(), retVal);
	return lRetVal;
}

void WrapPropertyContainer::add(const CL_String &name, Entity::IProperty *prop, WrapIProperty *wProp)
{
	if(prop == NULL)
	{
		CL_String msg = cl_format("Failed to add property %1, because no property was returned", name);
		coreMgr->getLogMgr()->log("WrapPropertyContainer::add", msg, Log::L_ERROR);
		return;
	}
	if(wEntity)
		wProp = new WrapIProperty(coreMgr, wEntity, this, prop);
	else if(wPlayer)
		wProp = new WrapIProperty(coreMgr, wPlayer, this, prop);
	else if(wRoom)
		wProp = new WrapIProperty(coreMgr, wRoom, this, prop);

	int fail = wProp->init();
	if(fail)
	{
		delete wProp;
		wProp = NULL;
		
		CL_String msg = cl_format("Failed to initialize property wrapper for property %1", prop->GetName());
		coreMgr->getLogMgr()->log("WrapPropertyContainer::add", msg, Log::L_ERROR);
		return;
	}
	wProperties.push_back(wProp);
}

void WrapPropertyContainer::OnPropertyAdded(const Engine::Events::EngineEvent &event)
{
	if(event.getArgument(1).IsEntity() && wEntity)
	{
		Engine::Entity::IEntity *entity = event.getArgument(1).ToEntity();
		if(entity->getId() != wEntity->getEntity()->getId())
			return;
	}
	else if(event.getArgument(1).IsIPlayer() && wPlayer)
	{
		Engine::Player::IPlayer *player = event.getArgument(1).ToIPlayer();
		if(player->getId() != wPlayer->getPlayer()->getId())
			return;
	}
	else if(event.getArgument(1).IsIRoom() && wRoom)
	{
		Engine::Room::IRoom *room = event.getArgument(1).ToIRoom();
		if(room->getId() != wRoom->getRoom()->getId())
			return;
	}
	else
	{
	}

	Engine::Entity::IProperty *prop = event.getArgument(0).ToProperty();
	WrapIProperty *wProp = NULL;
	add(prop->GetName(), prop, wProp);
}

#include "WrapIEntity.h"
#include "WrapEntityManager.h"
#include "WrapPropertyContainer.h"
#include "WrapComponentContainer.h"
#include "WrapIPlayer.h"
#include "WrapPlayerManager.h"
#include "WrapIRoom.h"
#include "WrapRoomManager.h"
#include "ScriptManager.h"
#include <Core/Core.h>
#include <Log/LogManager.h>
#include <IEntity.h>
#include <EventSystem/src/Event.h>
#include <Player/IPlayer.h>

using namespace Engine;
using namespace Script;
using namespace LuaPlus;

WrapIEntity::WrapIEntity(Core::CoreManager *coreMgr, WrapEntityManager *wEntityMgr, Entity::IEntity *entity)
: wPropContainer(NULL), wCompContainer(NULL)
{
	this->coreMgr = coreMgr;
	this->wEntityMgr = wEntityMgr;
	this->entity = entity;
}

WrapIEntity::~WrapIEntity()
{
	if(wPropContainer)
	{
		delete wPropContainer;
		wPropContainer = NULL;
	}
	if(wCompContainer)
	{
		delete wCompContainer;
		wCompContainer = NULL;
	}

	lEntity.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	lMeta.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

int WrapIEntity::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	unsigned int entityId = entity->getId();
	
	LuaObject &lEntities = wEntityMgr->getLEntities();
	lEntity = lEntities.CreateTable((int)entityId);
	lEntity.SetString("tableType", "IEntity");
	lEntity.SetInteger("id", (int)entityId);
	lEntity.SetString("type", entity->getType().c_str());
	lEntity.SetString("name", entity->getName().c_str());
	lEntity.SetString("name_lc", CL_StringHelp::text_to_lower(entity->getName()).c_str());
	lMeta = lEntity.CreateTable("MetaTable");
	lMeta.SetObject("__index", lMeta);

	lMeta.RegisterDirect("SendEvent", *this, &WrapIEntity::SendEvent);
	lMeta.RegisterDirect("SendCommand", *this, &WrapIEntity::SendCommand);
	lMeta.RegisterDirect("Kill", *this, &WrapIEntity::Kill);
	lMeta.RegisterDirect("HasComponent", *this, &WrapIEntity::HasComponent);
	lMeta.RegisterDirect("HasPlayer", *this, &WrapIEntity::HasPlayer);
	lMeta.RegisterDirect("GetPlayer", *this, &WrapIEntity::GetPlayer);

	lMeta.RegisterDirect("IsInARoom", *this, &WrapIEntity::IsInARoom);
	lMeta.RegisterDirect("GetRoom", *this, &WrapIEntity::GetRoom);
	lMeta.RegisterDirect("SetRoom", *this, &WrapIEntity::SetRoom);
	
	lEntity.SetLightUserData("__object", this);
	lEntity.SetMetaTable(lMeta);

	wPropContainer = new WrapPropertyContainer(coreMgr, this);
	int fail = wPropContainer->init();
	if(fail)
	{
		delete wPropContainer;
		wPropContainer = NULL;
		
		CL_String err = cl_format("Failed to initialize property container wrapper for IEntity wrapper with id: %1", entityId);
		coreMgr->getLogMgr()->log("WrapObject::init", err, Log::L_ERROR);
		return 1;
	}

	wCompContainer = new WrapComponentContainer(coreMgr, this);
	fail = wCompContainer->init();
	if(fail)
	{
		delete wCompContainer;
		wCompContainer = NULL;
		
		CL_String err = cl_format("Failed to initialize component container wrapper for IEntity wrapper with id: %1", entityId);
		coreMgr->getLogMgr()->log("WrapObject::init", err, Log::L_ERROR);
		return 1;
	}

	return 0;
}

void WrapIEntity::SendCommand(LuaObject lSelf, LuaObject lCommand)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SendCommand", msg, Log::L_ERROR);
		return;
	}

	if(!lCommand.IsString())
	{
		CL_String msg = cl_format("CommandType was not a string (it's a %1)", lCommand.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SendCommand", msg, Log::L_ERROR);
		return;
	}

	entity->ExecuteCommandOnComponents(lCommand.ToString(), NULL);
}

void WrapIEntity::SendEvent(LuaObject lSelf, LuaObject lEventType, LuaObject lEventArg)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SendEvent", msg, Log::L_ERROR);
		return;
	}

	if(!lEventType.IsString())
	{
		CL_String msg = cl_format("EventType was not a string (it's a %1)", lEventType.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SendEvent", msg, Log::L_ERROR);
		return;
	}

	if(!lEventArg.IsString() && !lEventArg.IsBoolean() && !lEventArg.IsNumber() && !lEventArg.IsTable() && !lEventArg.IsNil())
	{
		CL_String msg = cl_format("EventArg was not a string, bool, number, table or nil (it's a %1)", lEventArg.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SendEvent", msg, Log::L_ERROR);
		return;
	}

	CL_String eventType = lEventType.ToString();
	if(lEventArg.IsString())
	{
		CL_String arg = lEventArg.ToString();
		entity->ExecuteEventOnComponents(Engine::Events::Event<CL_String, Engine::Entity::IEntity*>(eventType.c_str(), arg, entity), NULL);
	}
	else if(lEventArg.IsBoolean())
	{
		bool arg = lEventArg.GetBoolean();
		entity->ExecuteEventOnComponents(Engine::Events::Event<bool, Engine::Entity::IEntity*>(eventType.c_str(), arg, entity), NULL);
	}
	else if(lEventArg.IsNumber())
	{
		float arg = lEventArg.GetFloat();
		entity->ExecuteEventOnComponents(Engine::Events::Event<float, Engine::Entity::IEntity*>(eventType.c_str(), arg, entity), NULL);
	}
	else if(lEventArg.IsTable())
	{	
		LuaObject tableType = lEventArg.GetByName("tableType");

		//If tableType is nil, then this should be a vector
		if(tableType.IsNil())
		{
			LuaObject xObj = lEventArg.GetByName("x");
			LuaObject yObj = lEventArg.GetByName("y");
			LuaObject zObj = lEventArg.GetByName("z");

			CL_Vec3f arg((float)xObj.ToNumber(), (float)yObj.ToNumber(), (float)zObj.ToNumber());
			entity->ExecuteEventOnComponents(Engine::Events::Event<CL_Vec3f, Engine::Entity::IEntity*>(eventType.c_str(), arg, entity), NULL);
		}
		else if(tableType.IsString())
		{
			CL_String type = tableType.ToString();
			if(type == "IEntity")
			{
				LuaObject lEntityId = lEventArg.GetByName("id");
				if(!lEntityId.IsInteger())
				{
					return;
				}
				unsigned int entityId = (unsigned int)lEntityId.ToInteger();
				Entity::IEntity *arg = coreMgr->getScriptMgr()->getWEntityMgr()->getWEntity(entityId)->getEntity();
				entity->ExecuteEventOnComponents(Engine::Events::Event<Engine::Entity::IEntity*, Engine::Entity::IEntity*>(eventType.c_str(), arg, entity), NULL);
			}
			else if(type == "IRoom")
			{
				//TODO: Implement for room
			}
			else if(type == "IZone")
			{
				//TODO: Implement for zone
			}
			else if(type == "Human")
			{
				//TODO: Implement for human
			}
			else if(type == "Agent")
			{
				//TODO: Implement for agent
			}
		}
	}
	else
	{
		entity->ExecuteEventOnComponents(Engine::Events::Event<Engine::Entity::IEntity*, Engine::Entity::IEntity*>(eventType.c_str(), entity, entity), NULL);
	}
}

void WrapIEntity::Kill(LuaPlus::LuaObject lSelf)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::Kill", msg, Log::L_ERROR);
		return;
	}

	CL_String msg = cl_format("Registering entity %1 of type %2 for kill!", entity->getName(), entity->getType());
	coreMgr->getLogMgr()->log("WrapIEntity::Kill", msg, Log::L_INFO);
	entity->kill();
}

LuaPlus::LuaObject WrapIEntity::HasComponent(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lName)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::HasComponent", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	if(!lName.IsString())
	{
		CL_String msg = cl_format("Name was not a string (it's a %1)", lName.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::HasComponent", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	LuaObject lHasComp;
	lHasComp.AssignBoolean(coreMgr->getScriptMgr()->GetGlobalState()->Get(), entity->HasComponent(lName.ToString()));
	return lHasComp;
}

LuaPlus::LuaObject WrapIEntity::HasPlayer(LuaPlus::LuaObject lSelf)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::HasPlayer", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	LuaObject lHasPlayer;
	lHasPlayer.AssignBoolean(coreMgr->getScriptMgr()->GetGlobalState()->Get(), entity->hasPlayer());
	return lHasPlayer;
}

LuaPlus::LuaObject WrapIEntity::GetPlayer(LuaPlus::LuaObject lSelf)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::HasPlayer", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	if(!entity->hasPlayer())
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());

	WrapIPlayer *wPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getWHuman(entity->getPlayer()->getId());
	if(wPlayer == NULL)
	{
		wPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getWAgent(entity->getPlayer()->getId());
		if(wPlayer == NULL)
		{
			return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
		}
	}

	return wPlayer->getLPlayer();
}

LuaObject WrapIEntity::IsInARoom(LuaObject lSelf)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::IsInARoom", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	LuaObject lIsInARoom;
	lIsInARoom.AssignBoolean(coreMgr->getScriptMgr()->GetGlobalState()->Get(), entity->isInARoom());
	return lIsInARoom;
}

LuaObject WrapIEntity::GetRoom(LuaObject lSelf)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::GetRoom", msg, Log::L_ERROR);
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());
	}

	if(!entity->isInARoom())
		return LuaObject(coreMgr->getScriptMgr()->GetGlobalState()->Get());

	LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(entity->getRoom()->getId()); 
	return lRoom;
}

void WrapIEntity::SetRoom(LuaObject lSelf, LuaObject lRoom)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SetRoom", msg, Log::L_ERROR);
		return;
	}

	if(!lRoom.IsTable())
	{
		CL_String msg = cl_format("Room was not a table (it's a %1)", lRoom.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SetRoom", msg, Log::L_ERROR);
		return;
	}

	LuaObject lRoomId = lRoom.GetByName("id");
	if(!lRoomId.IsInteger())
	{
		CL_String msg = cl_format("id was not an integer (it's a %1)", lRoomId.TypeName());
		coreMgr->getLogMgr()->log("WrapIEntity::SetRoom", msg, Log::L_ERROR);
		return;
	}

	Room::IRoom *room = coreMgr->getScriptMgr()->getWRoomMgr()->getWRoom((unsigned int)lRoomId.ToInteger())->getRoom();
	if(room)
		entity->setRoom(room);
}

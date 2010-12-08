#include "WrapIProperty.h"
#include "WrapIEntity.h"
#include "WrapEntityManager.h"
#include "WrapIPlayer.h"
#include "WrapPlayerManager.h"
#include "WrapIRoom.h"
#include "WrapRoomManager.h"
#include "WrapPropertyContainer.h"
#include "ScriptManager.h"
#include <Core/Core.h>
#include <Log/LogManager.h>
#include <IProperty.h>
#include <TypeSerializer.h>
#include <IEntity.h>
#include <Player/IPlayer.h>
#include <Room/IRoom.h>
#include <EventSystem/src/Event.h>

using namespace Engine;
using namespace Script;
using namespace LuaPlus;
using namespace Entity;

WrapIProperty::WrapIProperty(Core::CoreManager *coreMgr, Script::WrapIEntity *wEntity, WrapPropertyContainer *wPropContainer, Entity::IProperty *property)
{
	this->coreMgr = coreMgr;
	this->wEntity = wEntity;
	this->wPlayer = NULL;
	this->wRoom = NULL;
	this->wPropContainer = wPropContainer;
	this->property = property;
	name = property->GetName();
}

WrapIProperty::WrapIProperty(Core::CoreManager *coreMgr, Script::WrapIPlayer *wPlayer, WrapPropertyContainer *wPropContainer, Entity::IProperty *property)
{
	this->coreMgr = coreMgr;
	this->wEntity = NULL;
	this->wPlayer = wPlayer;
	this->wRoom = NULL;
	this->wPropContainer = wPropContainer;
	this->property = property;
	name = property->GetName();
}

WrapIProperty::WrapIProperty(Core::CoreManager *coreMgr, Script::WrapIRoom *wRoom, WrapPropertyContainer *wPropContainer, Entity::IProperty *property)
{
	this->coreMgr = coreMgr;
	this->wEntity = NULL;
	this->wPlayer = NULL;
	this->wRoom = wRoom;
	this->wPropContainer = wPropContainer;
	this->property = property;
	name = property->GetName();
}

WrapIProperty::~WrapIProperty()
{
	lProperty.AssignNil(coreMgr->getScriptMgr()->GetGlobalState()->Get());
}

int WrapIProperty::init()
{
	LuaObject globals = (*coreMgr->getScriptMgr()->GetGlobalState())->GetGlobals();
	
	LuaObject &lProps = wPropContainer->getLProps();
	lProperty = lProps.CreateTable(property->GetName().c_str());
	lProperty.SetString("id", property->GetName().c_str());
	
	{
		LuaObject lMeta = lProperty.CreateTable("MetaTable");
		lMeta.SetObject("__index", lMeta);

		lMeta.RegisterDirect("Get", *this, &WrapIProperty::Get);
		lMeta.RegisterDirect("Set", *this, &WrapIProperty::Set);
		lMeta.RegisterDirect("AddListener", *this, &WrapIProperty::AddListener);
		
		lProperty.SetLightUserData("__object", this);
		lProperty.SetMetaTable(lMeta);
	}

	{
		LuaObject lMeta;
		if(wEntity)
			lMeta = wEntity->getLMeta();
		else if(wPlayer)
			lMeta = wPlayer->getLMeta();
		else if(wRoom)
			lMeta = wRoom->getLMeta();

		lMeta.RegisterDirect(cl_format("Get%1", property->GetName()).c_str(), *this, &WrapIProperty::Get);
		lMeta.RegisterDirect(cl_format("Set%1", property->GetName()).c_str(), *this, &WrapIProperty::Set);
		lMeta.RegisterDirect(cl_format("Add%1Listener", property->GetName()).c_str(), *this, &WrapIProperty::AddListener);
	}

	initPropertyListener();

	return 0;
}

void WrapIProperty::initPropertyListener()
{
	if(property->GetTypeId() == TypeSerializer::TYPE_BOOL)
	{
		Property<bool> *prop = dynamic_cast<Property<bool> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedBool);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC2)
	{
		Property<CL_Vec2f> *prop = dynamic_cast<Property<CL_Vec2f> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedVec2f);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC3)
	{
		Property<CL_Vec3f> *prop = dynamic_cast<Property<CL_Vec3f> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedVec3f);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC4)
	{
		Property<CL_Vec4f> *prop = dynamic_cast<Property<CL_Vec4f> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedVec4f);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_STRING)
	{
		Property<CL_String> *prop = dynamic_cast<Property<CL_String> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedString);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_DOUBLE)
	{
		Property<double> *prop = dynamic_cast<Property<double> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedDouble);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_FLOAT)
	{
		Property<float> *prop = dynamic_cast<Property<float> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedFloat);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_INT)
	{
		Property<int> *prop = dynamic_cast<Property<int> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedInt);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_UNSIGNED_INT)
	{
		Property<unsigned int> *prop = dynamic_cast<Property<unsigned int> *>(property);
		if(prop)
			slotPropertyChanged = prop->ValueChanged().connect(this, &WrapIProperty::OnPropertyChangedUInt);
	}
}

LuaObject WrapIProperty::Get(LuaObject self)
{
	LuaObject lValue;

	if(wRoom)
	{
		std::map<CL_String, Entity::IProperty*>::iterator it = wRoom->getRoom()->GetProperties().find(property->GetName());
		if(it != wRoom->getRoom()->GetProperties().end())
		{
			if(property != it->second)
			{
				coreMgr->getLogMgr()->log("WrapIProperty::Get", "There's a bug in WrapIProperty for wRoom!", Log::L_WARN);
				property = it->second;
			}
		}
	}
	else if(wPlayer)
	{
		std::map<CL_String, Entity::IProperty*>::iterator it = wPlayer->getPlayer()->GetProperties().find(property->GetName());
		if(it != wPlayer->getPlayer()->GetProperties().end())
		{
			if(property != it->second)
			{
				coreMgr->getLogMgr()->log("WrapIProperty::Get", "There's a bug in WrapIProperty for wPlayer!", Log::L_WARN);
				property = it->second;
			}
		}
	}
	else if(wEntity)
	{
		std::map<CL_String, Entity::IProperty*>::iterator it = wEntity->getEntity()->GetProperties().find(property->GetName());
		if(it != wEntity->getEntity()->GetProperties().end())
		{
			if(property != it->second)
			{
				coreMgr->getLogMgr()->log("WrapIProperty::Get", "There's a bug in WrapIProperty for wEntity!", Log::L_WARN);
				property = it->second;
			}
		}
	}

	if(property->GetTypeId() == TypeSerializer::TYPE_BOOL)
	{
		Entity::Property<bool> *prop = static_cast<Entity::Property<bool>*>(property);
		lValue.AssignBoolean(coreMgr->getScriptMgr()->GetGlobalState()->Get(), prop->Get());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC2)
	{
		Entity::Property<CL_Vec2f> *prop = static_cast<Entity::Property<CL_Vec2f>*>(property);
		lValue.AssignNewTable(coreMgr->getScriptMgr()->GetGlobalState()->Get());
		lValue.SetNumber("x", prop->Get().x);
		lValue.SetNumber("y", prop->Get().y);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC3)
	{
		Entity::Property<CL_Vec3f> *prop = static_cast<Entity::Property<CL_Vec3f>*>(property);
		lValue.AssignNewTable(coreMgr->getScriptMgr()->GetGlobalState()->Get());
		lValue.SetNumber("x", prop->Get().x);
		lValue.SetNumber("y", prop->Get().y);
		lValue.SetNumber("z", prop->Get().z);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC4)
	{
		Entity::Property<CL_Vec4f> *prop = static_cast<Entity::Property<CL_Vec4f>*>(property);
		lValue.AssignNewTable(coreMgr->getScriptMgr()->GetGlobalState()->Get());
		lValue.SetNumber("x", prop->Get().x);
		lValue.SetNumber("y", prop->Get().y);
		lValue.SetNumber("z", prop->Get().z);
		lValue.SetNumber("w", prop->Get().w);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_STRING)
	{
		lValue.AssignString(coreMgr->getScriptMgr()->GetGlobalState()->Get(), property->ToString().c_str());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_DOUBLE)
	{
		Entity::Property<double> *prop = static_cast<Entity::Property<double>*>(property);
		lValue.AssignNumber(coreMgr->getScriptMgr()->GetGlobalState()->Get(), (float)prop->Get());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_FLOAT)
	{
		Entity::Property<float> *prop = static_cast<Entity::Property<float>*>(property);
		lValue.AssignNumber(coreMgr->getScriptMgr()->GetGlobalState()->Get(), prop->Get());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_INT)
	{
		Entity::Property<int> *prop = static_cast<Entity::Property<int>*>(property);
		lValue.AssignInteger(coreMgr->getScriptMgr()->GetGlobalState()->Get(), prop->Get());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_UNSIGNED_INT)
	{
		Entity::Property<unsigned int> *prop = static_cast<Entity::Property<unsigned int>*>(property);
		lValue.AssignInteger(coreMgr->getScriptMgr()->GetGlobalState()->Get(), (int)prop->Get());
	}

	return lValue;
}

void WrapIProperty::Set(LuaObject self, LuaObject value)
{
	if(property->GetTypeId() == TypeSerializer::TYPE_BOOL)
	{
		if(!value.IsBoolean())
			return;

		Property<bool> *prop = (Property<bool>*)property;
		prop->Set(value.GetBoolean());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC2)
	{
		if(!value.IsTable())
			return;

		Property<CL_Vec2f> *prop = (Property<CL_Vec2f>*)property;
		LuaObject xObj = value.GetByName("x");
		LuaObject yObj = value.GetByName("y");
		if(!xObj.IsNumber() || !yObj.IsNumber())
			return;

		CL_Vec2f val((float)xObj.ToNumber(), (float)yObj.ToNumber());
		prop->Set(val);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC3)
	{
		if(!value.IsTable())
			return;

		Property<CL_Vec3f> *prop = (Property<CL_Vec3f>*)property;
		LuaObject xObj = value.GetByName("x");
		LuaObject yObj = value.GetByName("y");
		LuaObject zObj = value.GetByName("z");
		if(!xObj.IsNumber() || !yObj.IsNumber() || !zObj.IsNumber())
			return;

		CL_Vec3f val((float)xObj.ToNumber(), (float)yObj.ToNumber(), (float)zObj.ToNumber());
		prop->Set(val);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_VEC4)
	{
		if(!value.IsTable())
			return;

		Property<CL_Vec4f> *prop = (Property<CL_Vec4f>*)property;
		LuaObject xObj = value.GetByName("x");
		LuaObject yObj = value.GetByName("y");
		LuaObject zObj = value.GetByName("z");
		LuaObject wObj = value.GetByName("w");
		if(!xObj.IsNumber() || !yObj.IsNumber() || !zObj.IsNumber() || !wObj.IsNumber())
			return;

		CL_Vec4f val((float)xObj.ToNumber(), (float)yObj.ToNumber(), (float)zObj.ToNumber(), (float)wObj.ToNumber());
		prop->Set(val);
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_STRING)
	{
		if(!value.IsString())
			return;

		Property<CL_String> *prop = (Property<CL_String>*)property;
		prop->Set(CL_String(value.ToString()));
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_DOUBLE)
	{
		if(!value.IsNumber())
			return;

		Property<double> *prop = (Property<double>*)property;
		prop->Set(value.ToNumber());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_FLOAT)
	{
		if(!value.IsNumber())
		{
			coreMgr->getLogMgr()->log("WrapIProperty::Set", cl_format("Property %1 is not a number, it's a %2 with value: %3", property->GetName(), value.TypeName(), value.ToString()), Log::L_WARN);
			return;
		}

		Property<float> *prop = (Property<float>*)property;
		prop->Set((float)value.ToNumber());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_INT)
	{
		if(!value.IsInteger())
			return;

		Property<int> *prop = (Property<int>*)property;
		prop->Set(value.ToInteger());
	}
	else if(property->GetTypeId() == TypeSerializer::TYPE_UNSIGNED_INT)
	{
		if(!value.IsInteger())
			return;

		Property<unsigned int> *prop = (Property<unsigned int>*)property;
		prop->Set((unsigned int)value.ToInteger());
	}
}

void WrapIProperty::AddListener(LuaPlus::LuaObject self, LuaPlus::LuaObject listener)
{
	if(!listener.IsString())
	{
		CL_String msg = cl_format("The listener has to be a string, but was a %1", listener.TypeName());
		coreMgr->getLogMgr()->log("WrapIProperty::AddListener", msg, Log::L_ERROR);
		return;
	}
	listeners.push_back(listener.ToString());
}

template<class T>
void WrapIProperty::OnPropertyChanged(const T &oldValue, const T &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Entities[%2], %3, %4)", listeners[i], id, oldValue, newValue);
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String script = cl_format("%1(Agents[%2], %3, %4)", listeners[i], id, oldValue, newValue);
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String script = cl_format("%1(Humans[%2], %3, %4)", listeners[i], id, oldValue, newValue);
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Rooms[%2], %3, %4)", listeners[i], id, oldValue, newValue);
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}

void WrapIProperty::OnPropertyChangedVec2f(const CL_Vec2f &oldValue, const CL_Vec2f &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChangedVec2f", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3}", oldValue.x, oldValue.y);
			CL_String newVal = cl_format("{x=%6, y=%7}", newValue.x, newValue.y);
			CL_String script = cl_format("%1(Entities[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String oldVal = cl_format("{x=%2, y=%3}", oldValue.x, oldValue.y);
					CL_String newVal = cl_format("{x=%6, y=%7}", newValue.x, newValue.y);
					CL_String script = cl_format("%1(Agents[%2], %3, %4)", listeners[i], id, oldVal, newVal);
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String oldVal = cl_format("{x=%2, y=%3}", oldValue.x, oldValue.y);
				CL_String newVal = cl_format("{x=%6, y=%7}", newValue.x, newValue.y);
				CL_String script = cl_format("%1(Humans[%2], %3, %4)", listeners[i], id, oldVal, newVal);
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3}", oldValue.x, oldValue.y);	
			CL_String newVal = cl_format("{x=%6, y=%7}", newValue.x, newValue.y);
			CL_String script = cl_format("%1(Rooms[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}
void WrapIProperty::OnPropertyChangedVec3f(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChangedVec3f", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3, z=%4}", oldValue.x, oldValue.y, oldValue.z);
			CL_String newVal = cl_format("{x=%6, y=%7, z=%8}", newValue.x, newValue.y, newValue.z);
			CL_String script = cl_format("%1(Entities[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String oldVal = cl_format("{x=%2, y=%3, z=%4}", oldValue.x, oldValue.y, oldValue.z);
					CL_String newVal = cl_format("{x=%6, y=%7, z=%8}", newValue.x, newValue.y, newValue.z);
					CL_String script = cl_format("%1(Agents[%2], %3, %4)", listeners[i], id, oldVal, newVal);
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String oldVal = cl_format("{x=%2, y=%3, z=%4}", oldValue.x, oldValue.y, oldValue.z);
				CL_String newVal = cl_format("{x=%6, y=%7, z=%8}", newValue.x, newValue.y, newValue.z);
				CL_String script = cl_format("%1(Humans[%2], %3, %4)", listeners[i], id, oldVal, newVal);
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3, z=%4}", oldValue.x, oldValue.y, oldValue.z);
			CL_String newVal = cl_format("{x=%6, y=%7, z=%8}", newValue.x, newValue.y, newValue.z);
			CL_String script = cl_format("%1(Rooms[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}
void WrapIProperty::OnPropertyChangedVec4f(const CL_Vec4f &oldValue, const CL_Vec4f &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChangedVec4f", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3, z=%4, w=%5}", oldValue.x, oldValue.y, oldValue.z, oldValue.w);
			CL_String newVal = cl_format("{x=%6, y=%7, z=%8, w=%9}", newValue.x, newValue.y, newValue.z, newValue.w);
			CL_String script = cl_format("%1(Entities[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String oldVal = cl_format("{x=%2, y=%3, z=%4, w=%5}", oldValue.x, oldValue.y, oldValue.z, oldValue.w);
					CL_String newVal = cl_format("{x=%6, y=%7, z=%8, w=%9}", newValue.x, newValue.y, newValue.z, newValue.w);
					CL_String script = cl_format("%1(Agents[%2], %3, %4)", listeners[i], id, oldVal, newVal);
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String oldVal = cl_format("{x=%2, y=%3, z=%4, w=%5}", oldValue.x, oldValue.y, oldValue.z, oldValue.w);
				CL_String newVal = cl_format("{x=%6, y=%7, z=%8, w=%9}", newValue.x, newValue.y, newValue.z, newValue.w);
				CL_String script = cl_format("%1(Humans[%2], %3, %4)", listeners[i], id, oldVal, newVal);
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String oldVal = cl_format("{x=%2, y=%3, z=%4, w=%5}", oldValue.x, oldValue.y, oldValue.z, oldValue.w);
			CL_String newVal = cl_format("{x=%6, y=%7, z=%8, w=%9}", newValue.x, newValue.y, newValue.z, newValue.w);
			CL_String script = cl_format("%1(Rooms[%2], %3, %4)", listeners[i], id, oldVal, newVal);
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}
void WrapIProperty::OnPropertyChangedBool(const bool &oldValue, const bool &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChangedBool", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Entities[%2], %3, %4)", listeners[i], id, CL_StringHelp::bool_to_text(oldValue), CL_StringHelp::bool_to_text(newValue));
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String script = cl_format("%1(Agents[%2], %3, %4)", listeners[i], id, CL_StringHelp::bool_to_text(oldValue), CL_StringHelp::bool_to_text(newValue));
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String script = cl_format("%1(Humans[%2], %3, %4)", listeners[i], id, CL_StringHelp::bool_to_text(oldValue), CL_StringHelp::bool_to_text(newValue));
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Rooms[%2], %3, %4)", listeners[i], id, CL_StringHelp::bool_to_text(oldValue), CL_StringHelp::bool_to_text(newValue));
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}
void WrapIProperty::OnPropertyChangedString(const CL_String &oldValue, const CL_String &newValue)
{
	for(unsigned int i = 0; i < listeners.size(); i++)
	{
		if(wEntity)
		{
			unsigned int id = 0;
			id = wEntity->getEntity()->getId();

			LuaObject lEntity = coreMgr->getScriptMgr()->getWEntityMgr()->getLEntity(id);
			if(lEntity.IsNil())
			{
				CL_String msg = cl_format("There's no entity in Entities table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChangedString", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Entities[%2], '%3', '%4')", listeners[i], id, oldValue, newValue);
			coreMgr->getScriptMgr()->doString(script);
		}
		else if(wPlayer)
		{
			unsigned int id = 0;
			id = wPlayer->getPlayer()->getId();

			LuaObject lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLHuman(id);
			if(lPlayer.IsNil())
			{
				lPlayer = coreMgr->getScriptMgr()->getWPlayerMgr()->getLAgent(id);
				if(lPlayer.IsNil())
				{
					CL_String msg = cl_format("There's no player in Humans or Agents table with id %1!", id);
					coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
					return;
				}
				else
				{
					CL_String script = cl_format("%1(Agents[%2], '%3', '%4')", listeners[i], id, oldValue, newValue);
					coreMgr->getScriptMgr()->doString(script);
				}
			}
			else
			{
				CL_String script = cl_format("%1(Humans[%2], '%3', '%4')", listeners[i], id, oldValue, newValue);
				coreMgr->getScriptMgr()->doString(script);
			}
		}
		else if(wRoom)
		{
			unsigned int id = 0;
			id = wRoom->getRoom()->getId();

			LuaObject lRoom = coreMgr->getScriptMgr()->getWRoomMgr()->getLRoom(id);
			if(lRoom.IsNil())
			{
				CL_String msg = cl_format("There's no room in Rooms table with id %1!", id);
				coreMgr->getLogMgr()->log("WrapIProperty::OnPropertyChanged", msg, Log::L_ERROR);
				return;
			}

			CL_String script = cl_format("%1(Rooms[%2], '%3', '%4')", listeners[i], id, oldValue, newValue);
			coreMgr->getScriptMgr()->doString(script);
		}
	}
}
void WrapIProperty::OnPropertyChangedDouble(const double &oldValue, const double &newValue)
{
	OnPropertyChanged<double>(oldValue, newValue);
}
void WrapIProperty::OnPropertyChangedFloat(const float &oldValue, const float &newValue)
{
	OnPropertyChanged<float>(oldValue, newValue);
}
void WrapIProperty::OnPropertyChangedInt(const int &oldValue, const int &newValue)
{
	OnPropertyChanged<int>(oldValue, newValue);
}
void WrapIProperty::OnPropertyChangedUInt(const unsigned int &oldValue, const unsigned int &newValue)
{
	OnPropertyChanged<unsigned int>(oldValue, newValue);
}

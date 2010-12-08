#pragma once

#include <Component.h>
#include <EventSystem/src/IEvent.h>
#include <IEntity.h>

namespace Engine
{
namespace Core { class CoreManager; }
namespace Player { class IPlayer; }
namespace Script { class WrapComponent; }

namespace Component
{
	class LuaComponent : public Engine::Entity::Component
	{
	public:
		virtual ~LuaComponent() {}

		virtual void Update(double dt);
		virtual void ExecuteCommand(const CL_String &command, Engine::Player::IPlayer *player);
		virtual void ExecuteEvent(const Engine::Events::IEvent &event, Engine::Player::IPlayer *player);

		static CL_String GetType() { return "Lua"; }
		static Engine::Entity::Component* Create(Engine::Core::CoreManager *coreMgr, Engine::Entity::IEntity *entity, const T_String &name) { return new LuaComponent(coreMgr, entity, name); }

		void initLuaExposure(Script::WrapComponent *wComp);

	protected:
		LuaComponent(Engine::Core::CoreManager *coreMgr, Engine::Entity::IEntity *entity, const T_String &name);

		Engine::Core::CoreManager *coreMgr;
		Script::WrapComponent *wComp;

		bool hasInit, hasUpdate, hasCommand, hasEvent;
	};
}}

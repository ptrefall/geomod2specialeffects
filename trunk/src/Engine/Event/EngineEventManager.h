#pragma once

#include "IEngineEventManager.h"
#include <map>

namespace Engine
{
namespace Events
{

class EngineEventManager : public IEngineEventManager
{
public:
	virtual CallbackClass &GetEvent(const CL_String &name);
	virtual void SendEvent(const EngineEvent &event);

private:
	std::map<CL_String, CallbackClass> eventHandlers;
};

}
}

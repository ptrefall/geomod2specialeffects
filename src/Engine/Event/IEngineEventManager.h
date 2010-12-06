#pragma once

#include "EngineEvent.h"
#include <ClanLib/src/API/core.h>

namespace Engine
{
namespace Events
{

class IEngineEventManager
{
public:
	typedef CL_Signal_v1<const EngineEvent &> CallbackClass;

	virtual CallbackClass &GetEvent(const CL_String &name) = 0;
	virtual void SendEvent(const EngineEvent &event) = 0;
};

}
}

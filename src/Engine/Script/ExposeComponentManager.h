#pragma once

#include <LuaPlus/LuaPlus.h>
#include <vector>

namespace Engine
{
namespace Core { class CoreManager; }
namespace Script
{

class WrapComponentManager
{
public:
	WrapComponentManager(Core::CoreManager *coreMgr);
	~WrapComponentManager();

	int init();

private:
	void RegisterComponent(LuaPlus::LuaObject lName);

	Core::CoreManager *coreMgr;
};

}
}

#pragma once

#include <LuaPlus/LuaLink.h>
#include <LuaPlus/LuaPlus.h>
#include <LuaPlus/LuaObject.h>

namespace Engine
{
	class CoreMgr;
	class ScriptMgr
	{
	public:
		ScriptMgr(CoreMgr *coreMgr);
		~ScriptMgr();

		LuaPlus::LuaStateOwner *GetGlobalState() { return &globalState; }

		int doFile(const CL_String &fileName);
		int doString(const CL_String &script, bool throwException = false, bool logError = true);
		CL_String getErrorOnStack();

	private:
		void init();

		void Print(LuaPlus::LuaObject text);

		LuaPlus::LuaStateOwner globalState;
		LuaPlus::LuaObject metaTable;

		CoreMgr *coreMgr;
	};
}

#pragma once

class CL_SetupCore;

namespace GMlib
{
	class GMWindow;
}

namespace Engine
{
	namespace Events { class IEventManager; }
	class GuiMgr;
	class ResMgr;
	class ScriptMgr;
	class CoreMgr
	{
	public:
		CoreMgr(const CL_String &base_path);
		~CoreMgr();

		Events::IEventManager *getEventMgr() const { return EventMgr; }
		GuiMgr *getGuiMgr() const { return guiMgr; }
		ResMgr *getResMgr() const { return resMgr; }
		ScriptMgr *getScriptMgr() const { return scriptMgr; }

	private:
		CL_SetupCore *setupCore; // Initializes clanlib core lib when CoreManager is instanciated/constructed

		void init(const CL_String &base_path);
		void run();

		Events::IEventManager *EventMgr;
		GuiMgr *guiMgr;
		ResMgr *resMgr;
		ScriptMgr *scriptMgr;
		GMlib::GMWindow *scene;
	};
}

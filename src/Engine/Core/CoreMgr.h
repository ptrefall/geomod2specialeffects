#pragma once

class CL_SetupCore;

namespace GMlib
{
	class GMWindow;
}

namespace Engine
{
	namespace Events { class IEngineEventManager; }
	class GuiMgr;
	class ResMgr;
	class ScriptMgr;
	class CoreMgr
	{
	public:
		CoreMgr(const CL_String &base_path);
		~CoreMgr();

		Events::IEngineEventManager *getEngineEventMgr() const { return engineEventMgr; }
		GuiMgr *getGuiMgr() const { return guiMgr; }
		ResMgr *getResMgr() const { return resMgr; }
		ScriptMgr *getScriptMgr() const { return scriptMgr; }

	private:
		CL_SetupCore *setupCore; // Initializes clanlib core lib when CoreManager is instanciated/constructed

		void init(const CL_String &base_path);
		void run();

		Events::IEngineEventManager *engineEventMgr;
		GuiMgr *guiMgr;
		ResMgr *resMgr;
		ScriptMgr *scriptMgr;
		GMlib::GMWindow *scene;
	};
}

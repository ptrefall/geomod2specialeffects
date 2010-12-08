#include "precomp.h"
#include "CoreMgr.h"

#include <Event/IEventManager.h>
#include <Event/EventManager.h>
#include <Gui/GuiMgr.h>
#include <Resource/ResMgr.h>
#include <Script/ScriptMgr.h>
#include <GMLib/gmWindow.h>

using namespace Engine;

CoreMgr::CoreMgr(const CL_String &base_path)
: setupCore(new CL_SetupCore()),
  EventMgr(NULL), guiMgr(NULL), resMgr(NULL), scriptMgr(NULL), scene(NULL)
{
	init(base_path);
	run();
}

CoreMgr::~CoreMgr()
{
	if(EventMgr)
	{
		delete EventMgr;
		EventMgr = NULL;
	}
	if(guiMgr)
	{
		delete guiMgr;
		guiMgr = NULL;
	}
	if(resMgr)
	{
		delete resMgr;
		resMgr = NULL;
	}
	if(scriptMgr)
	{
		delete scriptMgr;
		scriptMgr = NULL;
	}
	if(scene)
	{
		delete scene;
		scene = NULL;
	}
}

void CoreMgr::init(const CL_String &base_path)
{
	int fail = 0;

	resMgr = new ResMgr(base_path);
	guiMgr = new GuiMgr(false, 640, 480, 16, 0);
	EventMgr = new Events::EventManager();
	scriptMgr = new ScriptMgr(this);
	scene = new GMlib::GMWindow();
	scene->init();
}

void CoreMgr::run()
{
	if(!scene->toggleRun())
		throw CL_Exception("Starting up scene failed!");

	while(guiMgr->isWindowOpen())
	{
		scene->display();
		guiMgr->swapBuffers();
	}
}

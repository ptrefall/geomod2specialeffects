#include "precomp.h"
#include "CoreMgr.h"

#include <Event/IEngineEventManager.h>
#include <Event/EngineEventManager.h>
#include <Gui/GuiMgr.h>
#include <Resource/ResMgr.h>
#include <GMLib/gmWindow.h>

using namespace Engine;

CoreMgr::CoreMgr(const CL_String &base_path)
: setupCore(new CL_SetupCore()),
  engineEventMgr(NULL), guiMgr(NULL), resMgr(NULL), scene(NULL)
{
	init(base_path);
	run();
}

CoreMgr::~CoreMgr()
{
	if(engineEventMgr)
	{
		delete engineEventMgr;
		engineEventMgr = NULL;
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
	engineEventMgr = new Events::EngineEventManager();
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

#include "precomp.h"
#include "CoreMgr.h"

#include <Event/IEventManager.h>
#include <Event/EventManager.h>
#include <Gui/GuiMgr.h>
#include <Resource/ResMgr.h>
#include <Script/ScriptMgr.h>
#include <Entity/EntityManager.h>
#include <Entity/IEntity.h>
#include <GMLib/gmWindow.h>
#include <GMLib/gmDisplayObject.h>

#include <Scene/Scene.h>
#include <Resource/IResource.h>

using namespace Engine;

CoreMgr::CoreMgr(const CL_String &base_path)
: setupCore(new CL_SetupCore()),
  eventMgr(NULL), guiMgr(NULL), resMgr(NULL), scriptMgr(NULL), entityMgr(NULL), scene(NULL)
{
	init(base_path);
	run();
}

CoreMgr::~CoreMgr()
{
	if(eventMgr)
	{
		delete eventMgr;
		eventMgr = NULL;
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
	if(entityMgr)
	{
		delete entityMgr;
		entityMgr = NULL;
	}
	if(scene)
	{
		delete scene;
		scene = NULL;
	}
}

void CoreMgr::addToScene(IEntity *entity)
{
	GMlib::DisplayObject *obj = dynamic_cast<GMlib::DisplayObject *>(entity);
	if(obj)
		scene->insert(obj);
}

void CoreMgr::init(const CL_String &base_path)
{
	int fail = 0;

	resMgr = new ResMgr(this, base_path);
	IResource *cfg = resMgr->create("config.xml", "XML");

	int fullscreen = cfg->getBool("Config/GUI/Fullscreen");
	int w = cfg->getInt("Config/GUI/Width");
	int h = cfg->getInt("Config/GUI/Height");
	int d = cfg->getInt("Config/GUI/Depth");
	int vsync = cfg->getInt("Config/GUI/VSync");
	guiMgr = new GuiMgr((fullscreen > 0), w, h, d, vsync);
	eventMgr = new Events::EventManager();
	entityMgr = new EntityManager(this);
	scriptMgr = new ScriptMgr(this);
	scriptMgr->init();
	scene = new GMlib::GMWindow();
	scene->init();

	CL_String scene_script = cfg->getString("Config/Scene/Script");
	Scene::init_scene(this, scene_script);
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

#include "precomp.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "EntityReg.h"
#include "ComponentFactory.h"
#include "ComponentReg.h"

#include <Event/Event.h>
#include <Event/EventValue.h>
#include <Event/IEventManager.h>

using namespace Engine;

EntityManager::EntityManager(CoreMgr *coreMgr) 
: factory(NULL), compFactory(NULL), uIds(0), coreMgr(coreMgr)
{
	init();
}

EntityManager::~EntityManager()
{
	if(factory)
	{
		delete factory;
		factory = NULL;
	}
	if(compFactory)
	{
		delete compFactory;
		compFactory = NULL;
	}

	uIds = 0;
}

void EntityManager::init()
{
	compFactory = new ComponentFactory(coreMgr);
	ComponentReg::Register(compFactory);

	factory = new EntityFactory(coreMgr);
	EntityReg::Register(factory, coreMgr);
}

IEntity *EntityManager::create(const CL_String &type, const CL_String &name)
{
	if(factory == NULL)
		return NULL;

	CL_String n;
	if(name.empty())
		n = type;
	else
		n = name;

	IEntity *entity = factory->create(type, n);
	coreMgr->getEventMgr()->SendEvent(Events::Event("EntityCreated", Events::EventValue(entity)));

	factory->addDataAndLogic(entity, type);
	return entity;
}

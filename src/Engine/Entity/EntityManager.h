#pragma once

namespace Engine
{
class CoreMgr;
class IEntity;
class ComponentFactory;
class EntityManager
{
public:
	EntityManager(CoreMgr *coreMgr) : coreMgr(coreMgr) {}
	~EntityManager() {}

	ComponentFactory *getComponentFactory() const { return NULL; }
	IEntity *create(const CL_String &type, const CL_String &name = CL_String()) { return NULL; }

private:
	CoreMgr *coreMgr;
	ComponentFactory *compFactory;
};

}

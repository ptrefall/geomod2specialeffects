#include "precomp.h"
#include "Curve.h"

using namespace Engine;

Curve::Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), GMlib::PCurve<float>()
{
}

Curve::~Curve()
{
}

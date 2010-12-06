#pragma once

#include <Entity/IEntity.h>
#include <GMlib/gmPCurve.h>

namespace Engine
{
	class CoreMgr;
	class Curve : public IEntity, public GMlib::PCurve<float>
	{
	public:
		Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~Curve();

		virtual void eval(float t, int d, bool l=true) {}
		virtual float getStartP() { return 0.0f; }
		virtual float getEndP() { return 0.0f; }
	};
}

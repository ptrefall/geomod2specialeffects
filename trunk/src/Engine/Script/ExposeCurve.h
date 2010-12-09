#pragma once

#include <LuaPlus/LuaPlus.h>

namespace Engine
{
class CoreMgr;
class Curve;

class ExposeCurve
{
public:
	ExposeCurve(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, Curve *curve);
	~ExposeCurve();

protected:
	void init();

	void Replot(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD);

	CoreMgr *coreMgr;

	Curve *curve;
	LuaPlus::LuaObject lEntity;
	LuaPlus::LuaObject lMeta;
};

}

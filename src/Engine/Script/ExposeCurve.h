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
	void CalcBernHermMultControlPoints(LuaPlus::LuaObject lSelf);
	LuaPlus::LuaObject GetBernHermValue(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lX, LuaPlus::LuaObject lY);
	LuaPlus::LuaObject GetBernHermMultControlPointsValue(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lX, LuaPlus::LuaObject lY);

	CoreMgr *coreMgr;

	Curve *curve;
	LuaPlus::LuaObject lEntity;
	LuaPlus::LuaObject lMeta;
};

}

#pragma once

#include <LuaPlus/LuaPlus.h>

namespace Engine
{
class CoreMgr;
class ERBS;

class ExposeERBS
{
public:
	ExposeERBS(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, ERBS *curve);
	~ExposeERBS();

protected:
	void init();

	void Replot(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD);
	void SetInputCurve(	LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lCurve, LuaPlus::LuaObject lNumLocalCurves, 
						LuaPlus::LuaObject lDeg, LuaPlus::LuaObject lLocalCurveReplotNum);
	LuaPlus::LuaObject GetNumLocalCurves(LuaPlus::LuaObject lSelf);
	LuaPlus::LuaObject GetLocalCurve(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lCurveIndex);

	CoreMgr *coreMgr;

	ERBS *curve;
	LuaPlus::LuaObject lEntity;
	LuaPlus::LuaObject lMeta;
};

}

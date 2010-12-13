#pragma once

#include <LuaPlus/LuaPlus.h>

namespace Engine
{
class CoreMgr;
class Bezier;

class ExposeBezier
{
public:
	ExposeBezier(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, Bezier *curve);
	~ExposeBezier();

protected:
	void init();

	void Replot(LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD);

	CoreMgr *coreMgr;

	Bezier *curve;
	LuaPlus::LuaObject lEntity;
	LuaPlus::LuaObject lMeta;
};

}

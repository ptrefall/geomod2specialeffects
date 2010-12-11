#include "precomp.h"
#include "ExposeCurve.h"
#include "ExposeIEntity.h"
#include "ScriptMgr.h"
#include <Core/CoreMgr.h>
#include <Entities/Curve.h>

using namespace Engine;
using namespace LuaPlus;

ExposeCurve::ExposeCurve(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, Curve *curve)
{
	this->coreMgr = coreMgr;
	this->lEntity = lEntity;
	this->lMeta = lMeta;
	this->curve = curve;
	init();
}

ExposeCurve::~ExposeCurve()
{
}

void ExposeCurve::init()
{
	lMeta.RegisterDirect("Replot", *this, &ExposeCurve::Replot);
}

void ExposeCurve::Replot(LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		throw CL_Exception(msg);
	}

	if(!lM.IsInteger() && !lM.IsNumber())
	{
		CL_String msg = cl_format("M was not an integer, nor a number (it's a %1)", lM.TypeName());
		throw CL_Exception(msg);
	}

	if(!lD.IsInteger() && !lD.IsNumber() && !lD.IsNil())
	{
		CL_String msg = cl_format("D was not an integer, nor a number, nor nil (it's a %1)", lD.TypeName());
		throw CL_Exception(msg);
	}

	int m = 0;
	int d = 2;

	if(lM.IsInteger())
		m = lM.ToInteger();
	else
		m = (int)lM.GetFloat();

	if(lD.IsInteger())
		d = lD.ToInteger();
	else if(lD.IsNumber())
		d = (int)lD.GetFloat();
	curve->replot(m, d);
}

LuaObject ExposeCurve::GetBernHermValue(LuaObject lSelf, LuaObject lX, LuaObject lY)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		throw CL_Exception(msg);
	}

	if(!lX.IsInteger() && !lX.IsNumber())
	{
		CL_String msg = cl_format("X was not an integer, nor a number (it's a %1)", lX.TypeName());
		throw CL_Exception(msg);
	}

	if(!lY.IsInteger() && !lY.IsNumber())
	{
		CL_String msg = cl_format("Y was not an integer, nor a number (it's a %1)", lY.TypeName());
		throw CL_Exception(msg);
	}

	int x = -1;
	int y = -1;

	if(lX.IsInteger())
		x = lX.ToInteger();
	else
		x = (int)lX.GetFloat();

	if(lY.IsInteger())
		y = lY.ToInteger();
	else if(lY.IsNumber())
		y = (int)lY.GetFloat();

	float value = curve->getBernHermValue(x,y);
	LuaObject lValue;
	lValue.AssignNumber(coreMgr->getScriptMgr()->GetGlobalState()->Get(), value);
	return lValue;
}

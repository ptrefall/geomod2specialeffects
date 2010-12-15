#include "precomp.h"
#include "ExposeERBS.h"
#include "ExposeIEntity.h"
#include "ExposeEntityManager.h"
#include "ScriptMgr.h"
#include <Core/CoreMgr.h>
#include <Entities/ERBS.h>
#include <Entities/Bezier.h>

using namespace Engine;
using namespace LuaPlus;

ExposeERBS::ExposeERBS(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, ERBS *curve)
{
	this->coreMgr = coreMgr;
	this->lEntity = lEntity;
	this->lMeta = lMeta;
	this->curve = curve;
	init();
}

ExposeERBS::~ExposeERBS()
{
}

void ExposeERBS::init()
{
	lMeta.RegisterDirect("Replot", *this, &ExposeERBS::Replot);
	lMeta.RegisterDirect("SetInputCurve", *this, &ExposeERBS::SetInputCurve);
}

void ExposeERBS::Replot(LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD)
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

void ExposeERBS::SetInputCurve(	LuaPlus::LuaObject lSelf, LuaPlus::LuaObject lCurve, LuaPlus::LuaObject lNumLocalCurves, 
							   LuaPlus::LuaObject lDeg, LuaPlus::LuaObject lLocalCurveReplotNum)
{
	if(!lSelf.IsTable())
	{
		CL_String msg = cl_format("Self was not a table (it's a %1)", lSelf.TypeName());
		throw CL_Exception(msg);
	}

	if(!lCurve.IsTable())
	{
		CL_String msg = cl_format("Curve was not a table (it's a %1)", lCurve.TypeName());
		throw CL_Exception(msg);
	}

	if(!lNumLocalCurves.IsInteger() && !lNumLocalCurves.IsNumber())
	{
		CL_String msg = cl_format("NumLocalCurves was not an integer, nor a number (it's a %1)", lNumLocalCurves.TypeName());
		throw CL_Exception(msg);
	}

	if(!lDeg.IsInteger() && !lDeg.IsNumber())
	{
		CL_String msg = cl_format("Deg was not an integer, nor a number (it's a %1)", lDeg.TypeName());
		throw CL_Exception(msg);
	}

	if(!lLocalCurveReplotNum.IsInteger() && !lLocalCurveReplotNum.IsNumber())
	{
		CL_String msg = cl_format("LocalCurveReplotNum was not an integer, nor a number (it's a %1)", lLocalCurveReplotNum.TypeName());
		throw CL_Exception(msg);
	}

	LuaObject lCurveId = lCurve.GetByName("id");
	if(!lCurveId.IsInteger())
	{
		CL_String msg = cl_format("CurveId was not an integer, (it's a %1)", lCurveId.TypeName());
		throw CL_Exception(msg);
	}

	int curveId = lCurveId.ToInteger();
	ExposeIEntity *exposedCurve = coreMgr->getScriptMgr()->getExposedEntityMgr()->getExposedEntity(curveId);
	if(exposedCurve == NULL || (!exposedCurve->isBezier() && !exposedCurve->isCurve()))
	{
		CL_String msg = cl_format("Entity was not a bezier nor a curve type!");
		throw CL_Exception(msg);
	}

	PCurve *inpCurve = inpCurve = dynamic_cast<PCurve*>(exposedCurve->getEntity());
	if(inpCurve == NULL)
	{
		CL_String msg = cl_format("InpCurve was NULL, wrong type of Entity!");
		throw CL_Exception(msg);
	}

	int numLocalCurves = 0;
	if(lNumLocalCurves.IsInteger())
		numLocalCurves = lNumLocalCurves.ToInteger();
	else
		numLocalCurves = (int)lNumLocalCurves.GetFloat();

	int deg = 0;
	if(lDeg.IsInteger())
		deg = lDeg.ToInteger();
	else
		deg = (int)lDeg.GetFloat();

	int localCurveReplotNum = 0;
	if(lLocalCurveReplotNum.IsInteger())
		localCurveReplotNum = lLocalCurveReplotNum.ToInteger();
	else
		localCurveReplotNum = (int)lLocalCurveReplotNum.GetFloat();

	curve->setInputCurve(inpCurve, numLocalCurves, deg, localCurveReplotNum);
}

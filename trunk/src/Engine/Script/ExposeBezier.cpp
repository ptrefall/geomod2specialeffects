#include "precomp.h"
#include "ExposeBezier.h"
#include "ExposeIEntity.h"
#include "ScriptMgr.h"
#include <Core/CoreMgr.h>
#include <Entities/Bezier.h>

using namespace Engine;
using namespace LuaPlus;

ExposeBezier::ExposeBezier(CoreMgr *coreMgr, LuaPlus::LuaObject &lEntity, LuaPlus::LuaObject &lMeta, Bezier *curve)
{
	this->coreMgr = coreMgr;
	this->lEntity = lEntity;
	this->lMeta = lMeta;
	this->curve = curve;
	init();
}

ExposeBezier::~ExposeBezier()
{
}

void ExposeBezier::init()
{
	lMeta.RegisterDirect("Replot", *this, &ExposeBezier::Replot);
}

void ExposeBezier::Replot(LuaObject lSelf, LuaPlus::LuaObject lM, LuaPlus::LuaObject lD)
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

#include "precomp.h"
#include "Curve.h"
#include <Event/EngineEvent.h>
#include <Event/EngineEventValue.h>

using namespace Engine;

Curve::Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), GMlib::PCurve<float>()
{
	closed = this->AddProperty<bool>("Closed", false);
	param_start = this->AddProperty<float>("ParamStart", 0.0f);
	param_end = this->AddProperty<float>("ParamEnd", 0.0f);
	resultSet_dim = this->AddProperty<int>("ResultSetDim", 0);
	derivation_method = this->AddProperty<int>("DerivationMethod", 0);
	resultSet = this->AddProperty<CL_Vec4f>("ResultSet", CL_Vec4f(0.0f, 0.0f, 0.0f, 0.0f));

	slotResultSetDimChanged = resultSet_dim.ValueChanged().connect(this, &Curve::OnResultSetDimChanged);
	slotDerivationMethodChanged = derivation_method.ValueChanged().connect(this, &Curve::OnDerivationMethodChanged);
	slotResultSetChanged = resultSet.ValueChanged().connect(this, &Curve::OnResultSetChanged);
}

Curve::~Curve()
{
}

void Curve::eval(float t, int d, bool l)
{
	this->ExecuteEventOnComponents(Events::EngineEvent("Eval", Events::EngineEventValue(t), Events::EngineEventValue(d), Events::EngineEventValue(l)));
}

void Curve::OnResultSetDimChanged(const int &oldValue, const int &newValue)
{
	this->_p.setDim( newValue );
}

void Curve::OnDerivationMethodChanged(const int &oldValue, const int &newValue)
{
	if((GMlib::GM_DERIVATION_METHOD)newValue > GMlib::GM_DERIVATION_DD)
		return;

	this->_dm = (GMlib::GM_DERIVATION_METHOD)newValue;
}

void Curve::OnResultSetChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue)
{
	this->_p[(int)newValue.x][0] = newValue.y;
	this->_p[(int)newValue.x][1] = newValue.z;
	this->_p[(int)newValue.x][2] = newValue.w;
}

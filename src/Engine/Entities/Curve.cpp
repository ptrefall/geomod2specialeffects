#include "precomp.h"
#include "Curve.h"
#include <Event/Event.h>
#include <Event/EventValue.h>

using namespace Engine;

Curve::Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), PCurve(coreMgr), _p(NULL)
{
	//Parametric curve properties
	identity = this->AddProperty<CL_String>("Identity", "Curve");
	closed = this->AddProperty<bool>("Closed", false);
	param_start = this->AddProperty<float>("ParamStart", 0.0f);
	param_end = this->AddProperty<float>("ParamEnd", 0.0f);
	size = this->AddProperty<int>("Size", 1);
	resultSet_dim = this->AddProperty<int>("ResultSetDim", 0);
	derivation_method = this->AddProperty<int>("DerivationMethod", 0);
	resultSet = this->AddProperty<CL_Vec4f>("ResultSet", CL_Vec4f(0.0f, 0.0f, 0.0f, 0.0f));

	//SceneObject properties
	position = this->AddProperty<CL_Vec3f>("Position", CL_Vec3f(0.0f, 0.0f, 0.0f));

	//Parametric curve property callbacks
	slotSizeChanged = size.ValueChanged().connect(this, &Curve::OnSizeChanged);
	slotResultSetDimChanged = resultSet_dim.ValueChanged().connect(this, &Curve::OnResultSetDimChanged);
	slotDerivationMethodChanged = derivation_method.ValueChanged().connect(this, &Curve::OnDerivationMethodChanged);
	slotResultSetChanged = resultSet.ValueChanged().connect(this, &Curve::OnResultSetChanged);

	//SceneObject property callbacks
	slotPositionChanged = position.ValueChanged().connect(this, &Curve::OnPositionChanged);
}

Curve::~Curve()
{
}

void Curve::handle(WorkData *data)
{
	PCurveEvalData *evalData = static_cast<PCurveEvalData*>(data);
	eval(evalData->p, evalData->t, evalData->d, evalData->l);
}

void Curve::eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l)
{
	this->_p = &_p;
	this->ExecuteEventOnComponents(Events::Event("Eval", Events::EventValue(t), Events::EventValue(d), Events::EventValue(l)));
}

/////////////////////////////////////////
// PARAMETRIC CURVE PROPERTY CALLBACKS
/////////////////////////////////////////
void Curve::OnSizeChanged(const int &oldValue, const int &newValue)
{
	this->_no_sam = size;
}

void Curve::OnResultSetDimChanged(const int &oldValue, const int &newValue)
{
	if(_p == NULL)
		return;

	(*_p).setDim( newValue );
}

void Curve::OnDerivationMethodChanged(const int &oldValue, const int &newValue)
{
	if((GMlib::GM_DERIVATION_METHOD)newValue > GMlib::GM_DERIVATION_DD)
		return;

	this->_dm = (GMlib::GM_DERIVATION_METHOD)newValue;
}

void Curve::OnResultSetChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue)
{
	if(_p == NULL)
		return;

	(*_p)[(int)newValue.x][0] = newValue.y;
	(*_p)[(int)newValue.x][1] = newValue.z;
	(*_p)[(int)newValue.x][2] = newValue.w;
}

/////////////////////////////////////
// SCENE OBJECT PROPERTY CALLBACKS
/////////////////////////////////////
void Curve::OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	GMlib::Vector3D<float> translation;
	translation[0] = newValue.x - oldValue.x;
	translation[1] = newValue.y - oldValue.y;
	translation[2] = newValue.z - oldValue.z;
	this->translate(translation);
}

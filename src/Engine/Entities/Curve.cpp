#include "precomp.h"
#include "Curve.h"
#include <Event/Event.h>
#include <Event/EventValue.h>

using namespace Engine;

Curve::Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), 
  GMlib::PCurve<float>()
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

	//Bezier properties
	controlPoint = this->AddProperty<CL_Vec3f>("ControlPoint", CL_Vec3f(0.0f, 0.0f, 0.0f));
	numControlPoints = this->AddProperty<int>("NumControlPoints", 0);
	bernHermDim = this->AddProperty<CL_Vec2f>("BernHermDim", CL_Vec2f(0.0f, 0.0f));
	bernHermIndex = this->AddProperty<CL_Vec3f>("BernHermMatIndex", CL_Vec3f(0.0f, 0.0f, 0.0f));

	//SceneObject properties
	position = this->AddProperty<CL_Vec3f>("Position", CL_Vec3f(0.0f, 0.0f, 0.0f));

	//Parametric curve property callbacks
	slotSizeChanged = size.ValueChanged().connect(this, &Curve::OnSizeChanged);
	slotResultSetDimChanged = resultSet_dim.ValueChanged().connect(this, &Curve::OnResultSetDimChanged);
	slotDerivationMethodChanged = derivation_method.ValueChanged().connect(this, &Curve::OnDerivationMethodChanged);
	slotResultSetChanged = resultSet.ValueChanged().connect(this, &Curve::OnResultSetChanged);
	
	//Bezier property callbacks
	slotControlPointChanged = controlPoint.ValueChanged().connect(this, &Curve::OnControlPointChanged);
	slotBernHermDimChanged = bernHermDim.ValueChanged().connect(this, &Curve::OnBernHermDimChanged);
	slotBernHermIndexChanged = bernHermIndex.ValueChanged().connect(this, &Curve::OnBernHermIndexChanged);

	//SceneObject property callbacks
	slotPositionChanged = position.ValueChanged().connect(this, &Curve::OnPositionChanged);
}

Curve::~Curve()
{
}

void Curve::eval(float t, int d, bool l)
{
	this->ExecuteEventOnComponents(Events::Event("Eval", Events::EventValue(t), Events::EventValue(d), Events::EventValue(l)));
}

float Curve::getBernHermValue(int x, int y)
{
	if(x > bernHermMat.getDim1()-1 || x < 0 || y > bernHermMat.getDim2()-1 || y < 0)
		return 0.0f;

	return bernHermMat[x][y];
}

void Curve::calcBernHermMultControlPoints()
{
	bernHermMatMultControlPoints = bernHermMat * controlPoints;
}

float Curve::getBernHermMultControlPoints(int x, int y)
{
	return bernHermMatMultControlPoints[x][y];
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

//////////////////////////////////
// BEZIER PROPERTY CALLBACKS
//////////////////////////////////
void Curve::OnControlPointChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	controlPoints.putFirst(GMlib::Vector3D<float>(newValue.x, newValue.y, newValue.z));
	numControlPoints = numControlPoints.Get() + 1;
}

void Curve::OnBernHermDimChanged(const CL_Vec2f &oldValue, const CL_Vec2f &newValue)
{
	bernHermMat.setDim((int)newValue.x, (int)newValue.y);
}

void Curve::OnBernHermIndexChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	if(newValue.x > bernHermMat.getDim1()-1 || newValue.x < 0 || newValue.y > bernHermMat.getDim2()-1 || newValue.y < 0)
		return;

	bernHermMat[(int)newValue.x][(int)newValue.y] = newValue.z;
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

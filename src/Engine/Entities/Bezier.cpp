#include "precomp.h"
#include "Bezier.h"
#include <Event/Event.h>
#include <Event/EventValue.h>
#include <WorkThread/WorkProduction.h>

using namespace Engine;

Bezier::Bezier(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), PCurve(coreMgr)
{
	//Parametric curve properties
	identity = this->AddProperty<CL_String>("Identity", "Bezier");
	closed = this->AddProperty<bool>("Closed", false);
	param_start = this->AddProperty<float>("ParamStart", 0.0f);
	param_end = this->AddProperty<float>("ParamEnd", 0.0f);
	size = this->AddProperty<int>("Size", 1);
	resultSet_dim = this->AddProperty<int>("ResultSetDim", 0);
	derivation_method = this->AddProperty<int>("DerivationMethod", 0);
	resultSet = this->AddProperty<CL_Vec4f>("ResultSet", CL_Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
	mtReplot = this->AddProperty<int>("MultiThreadedReplot", 0);

	//Bezier properties
	controlPoint = this->AddProperty<CL_Vec3f>("ControlPoint", CL_Vec3f(0.0f, 0.0f, 0.0f));

	//SceneObject properties
	position = this->AddProperty<CL_Vec3f>("Position", CL_Vec3f(0.0f, 0.0f, 0.0f));
	rotation = this->AddProperty<CL_Vec4f>("Rotation", CL_Vec4f(0.0f, 0.0f, 0.0f, 0.0f));

	//Parametric curve property callbacks
	slotSizeChanged = size.ValueChanged().connect(this, &Bezier::OnSizeChanged);
	slotDerivationMethodChanged = derivation_method.ValueChanged().connect(this, &Bezier::OnDerivationMethodChanged);
	slotMTReplotChanged = mtReplot.ValueChanged().connect(this, &Bezier::OnMTReplotChanged);
	
	//Bezier property callbacks
	slotControlPointChanged = controlPoint.ValueChanged().connect(this, &Bezier::OnControlPointChanged);

	//SceneObject property callbacks
	slotPositionChanged = position.ValueChanged().connect(this, &Bezier::OnPositionChanged);
	slotRotationChanged = rotation.ValueChanged().connect(this, &Bezier::OnRotationChanged);
}

Bezier::~Bezier()
{
}

void Bezier::optionalInit(GMlib::DVector<GMlib::Vector<float,3>> pt, float t1, float t2, float t3)
{
	GMlib::DMatrix<float> bernHermMat;
	calcBernHerm(bernHermMat, (t2-t1)/(t3-t1), pt.getDim()-1, 1.0f/(t3-t1));
	bernHermMat.invert();

	controlPoints = bernHermMat * pt;

	for(int i = 0; i < controlPoints.getDim(); i++)
		controlPoints[i] -= pt(0);
	this->translate(pt(0));
}

void Bezier::handle(WorkData *data)
{
	PCurveEvalData *evalData = static_cast<PCurveEvalData*>(data);
	eval(evalData->p, evalData->t, evalData->d, evalData->l);
}

void Bezier::eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l)
{
	_p.setDim(resultSet_dim.Get()+1);
	
	GMlib::DMatrix<float> bernHermMat;
	calcBernHerm(bernHermMat, t, controlPoints.getDim()-1, 1.0f);
	
	GMlib::DVector<GMlib::Vector<float,3> > pt = bernHermMat * controlPoints;
	
	_p[0][0] = pt[0][0];
	_p[0][1] = pt[0][1];
	_p[0][2] = pt[0][2];
	
	if(_dm == GMlib::GM_DERIVATION_EXPLICIT)
	{
		if(d > 0)
		{
			_p[1][0] = pt[1][0];
			_p[1][1] = pt[1][1];
			_p[1][2] = pt[1][2];
		}
		
		if(d > 1) 
		{
			_p[2][0] = pt[2][0];
			_p[2][1] = pt[2][1];
			_p[2][2] = pt[2][2];
		}
		
		if(d > 2) 
		{
			_p[3][0] = pt[3][0];
			_p[3][1] = pt[3][1];
			_p[3][2] = pt[3][2];
		}
	}
}

void Bezier::calcBernHerm(GMlib::DMatrix<float> &bernHermMat, float t, int d, float size)
{
	bernHermMat.setDim(d+1, d+1);
	
	bernHermMat[d-1][0] = 1.0f - t;
	bernHermMat[d-1][1] = t;

	for(int i = d - 2; i >= 0; i--)
	{
		bernHermMat[i][0] = (1.0f-t)*bernHermMat[i+1][0];
		for(int j = 1; j < d-i; j++)
		{
			bernHermMat[i][j] = (t*bernHermMat[i+1][j-1] + (1.0f-t)*bernHermMat[i+1][j]);
		}
		bernHermMat[i][d-i] = t*bernHermMat[i+1][d-i-1];
	}
	bernHermMat[d][0] = -size;
	bernHermMat[d][1] = size;

	for(int k = 2; k <= d; k++)
	{
		float s = k * size;
		for(int i = d; i > d-k; i--)
		{
			bernHermMat[i][k] = s*bernHermMat[i][k-1];
			for(int j = k-1; j > 0; j--)
			{
				bernHermMat[i][j] = s*(bernHermMat[i][j-1] - bernHermMat[i][j]);
			}
			bernHermMat[i][0] = -s*bernHermMat[i][0];
		}
	}

}

/////////////////////////////////////////
// PARAMETRIC CURVE PROPERTY CALLBACKS
/////////////////////////////////////////
void Bezier::OnSizeChanged(const int &oldValue, const int &newValue)
{
	this->_no_sam = size;
}

void Bezier::OnDerivationMethodChanged(const int &oldValue, const int &newValue)
{
	if((GMlib::GM_DERIVATION_METHOD)newValue > GMlib::GM_DERIVATION_DD)
		return;

	this->_dm = (GMlib::GM_DERIVATION_METHOD)newValue;
}

void Bezier::OnMTReplotChanged(const int &oldValue, const int &newValue)
{
	this->setMultiThreadedReplotting((newValue > 0));
}

//////////////////////////////////
// BEZIER PROPERTY CALLBACKS
//////////////////////////////////
void Bezier::OnControlPointChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	controlPoints.putFirst(GMlib::Vector3D<float>(newValue.x, newValue.y, newValue.z));
}

/////////////////////////////////////
// SCENE OBJECT PROPERTY CALLBACKS
/////////////////////////////////////
void Bezier::OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	GMlib::Vector3D<float> translation;
	translation[0] = newValue.x - oldValue.x;
	translation[1] = newValue.y - oldValue.y;
	translation[2] = newValue.z - oldValue.z;
	this->translate(translation);
}

void Bezier::OnRotationChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue)
{
	this->rotate(GMlib::Angle(newValue.x), GMlib::Vector3D<float>(newValue.y, newValue.z, newValue.w));
}

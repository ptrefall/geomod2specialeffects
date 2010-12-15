#include "precomp.h"
#include "ERBS.h"
#include "Bezier.h"
#include <Entity/EntityManager.h>
#include <Event/Event.h>
#include <Event/EventValue.h>
#include <WorkThread/WorkProduction.h>
#include <GMlib/gmColor.h>
#include <Core/CoreMgr.h>

using namespace Engine;

ERBS::ERBS(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory)
: IEntity(id, type, name, coreMgr, factory), PCurve(coreMgr)
{
	//Parametric curve properties
	identity = this->AddProperty<CL_String>("Identity", "ERBS");
	closed = this->AddProperty<bool>("Closed", false);
	param_start = this->AddProperty<float>("ParamStart", 0.0f);
	param_end = this->AddProperty<float>("ParamEnd", 0.0f);
	size = this->AddProperty<int>("Size", 1);
	resultSet_dim = this->AddProperty<int>("ResultSetDim", 0);
	derivation_method = this->AddProperty<int>("DerivationMethod", 0);
	resultSet = this->AddProperty<CL_Vec4f>("ResultSet", CL_Vec4f(0.0f, 0.0f, 0.0f, 0.0f));
	mtReplot = this->AddProperty<int>("MultiThreadedReplot", 0);

	//ERBS properties
	knotInit = this->AddProperty<CL_Vec2f>("KnotInit", CL_Vec2f(0.0f, 0.0f));

	//SceneObject properties
	position = this->AddProperty<CL_Vec3f>("Position", CL_Vec3f(0.0f, 0.0f, 0.0f));

	//Parametric curve property callbacks
	slotSizeChanged = size.ValueChanged().connect(this, &ERBS::OnSizeChanged);
	slotDerivationMethodChanged = derivation_method.ValueChanged().connect(this, &ERBS::OnDerivationMethodChanged);
	slotMTReplotChanged = mtReplot.ValueChanged().connect(this, &ERBS::OnMTReplotChanged);
	
	//ERBS property callbacks
	slotKnotInitChanged = knotInit.ValueChanged().connect(this, &ERBS::OnKnotInitChanged);

	//SceneObject property callbacks
	slotPositionChanged = position.ValueChanged().connect(this, &ERBS::OnPositionChanged);
}

ERBS::~ERBS()
{
}

void ERBS::setInputCurve(PCurve *inpCurve, int numLocalCurves, int deg, int localCurveReplotNum)
{
	ERBSEval.set(inpCurve->getParStart(), (inpCurve->getParEnd() - inpCurve->getParStart()) / numLocalCurves-1);
	closed = inpCurve->isClosed(); 

	if (closed.Get())
		numLocalCurves++;

	localCurves.setDim(numLocalCurves);

	knots.setDim(numLocalCurves+2);
	knots[1]= inpCurve->getParStart();
	knots[numLocalCurves] = inpCurve->getParEnd();
	
	float delta = (knots[numLocalCurves]-knots[1])/(numLocalCurves-1);
	for(int i = 0; i < numLocalCurves; i++) 
		knots[i+1] = knots[1]+i*delta;

	knots[0] = knots[1];
	knots[numLocalCurves+1] = knots[numLocalCurves];
	if(closed.Get())
	{
		knots[0] -= knots[numLocalCurves]-knots[numLocalCurves-1];
		knots[numLocalCurves+1] += knots[2]-knots[1];
	}

	for ( int i = 1; i < numLocalCurves; i++ )
	{
		Bezier *localCurve = static_cast<Bezier*>(IEntity::coreMgr->getEntityMgr()->create("BezierCurve"));
		localCurve->optionalInit(inpCurve->evaluateParent(knots[i], deg), knots[i-1], knots[i], knots[i+1]);
		localCurves[i-1] = localCurve;
		localCurve->setColor( GMlib::GMcolor::Blue );
		localCurve->replot(localCurveReplotNum);  
	}

	if(closed.Get())
		localCurves[numLocalCurves-1] = localCurves[0];
	else 
	{
		Bezier *localCurve = static_cast<Bezier*>(IEntity::coreMgr->getEntityMgr()->create("BezierCurve"));
		localCurve->optionalInit(inpCurve->evaluateParent(knots[numLocalCurves], deg), knots[numLocalCurves-1], knots[numLocalCurves], knots[numLocalCurves+1]);
		localCurve->setColor( GMlib::GMcolor::Blue );
		localCurve->replot(localCurveReplotNum); 
		localCurves[numLocalCurves-1] = localCurve;
	}
}

void ERBS::handle(WorkData *data)
{
	PCurveEvalData *evalData = static_cast<PCurveEvalData*>(data);
	eval(evalData->p, evalData->t, evalData->d, evalData->l);
}

void ERBS::eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l)
{
	int idx;
	for(idx = 1; idx < knots.getDim(); idx++)
	{
		if( t < knots[idx+1] )
			break;
	}

	GMlib::DVector<GMlib::Vector<float,3>> c0 = localCurves[idx-1]->evaluateParent((t-knots[idx-1]) / (knots[idx+1] - knots[idx-1]), d);

	// if t matches the knotvector precisely, return value at first local curve
	if(std::fabs(t - knots[idx]) < 1e-5)
	{
		_p = c0;
		return;
	}

	// Evaluate second local curve piece
	//T secondInterval = _knots[idx+2] - _knots[idx];
	//T secondT =  (t-_knots[idx+2]) / secondInterval; // get a T in [0,1] for the bezier curve
	GMlib::DVector<GMlib::Vector<float,3>> c1 = localCurves[idx]->evaluateParent((t-knots[idx])/ (knots[idx+2]-knots[idx]), d);

	// Calc ERBS Basis
	GMlib::DVector<float> basisCoeffs;
	basisCoeffs.setDim(d+1);
	ERBSEval.set(knots[idx], knots[idx+1] - knots[idx]);
	basisCoeffs[0] = 1 - ERBSEval.operator()(t);  // (*_evaluator)(t)
	basisCoeffs[1] = - ERBSEval.getDer1();
	basisCoeffs[2] = - ERBSEval.getDer2();

	// Calculate pascals triangle numbers and then compute the sample position data
	c0 -= c1;

	GMlib::DVector<float> a(d);
	for( int i = 0; i <= d; i++ )
	{
		// Compute the pascal triangle numbers
		a[i] = 1;
		for( int j = i-1; j > 0; j-- )
		{
			a[j] += a[j-1];
		}

		// Compute the sample position data
		for( int j = 0; j <= i; j++ )
		{
			c1[i] += (a[j] * basisCoeffs[j]) * c0[i-j];
		}
	}
	_p = c1;
}

/////////////////////////////////////////
// PARAMETRIC CURVE PROPERTY CALLBACKS
/////////////////////////////////////////
void ERBS::OnSizeChanged(const int &oldValue, const int &newValue)
{
	this->_no_sam = size;
}

void ERBS::OnDerivationMethodChanged(const int &oldValue, const int &newValue)
{
	if((GMlib::GM_DERIVATION_METHOD)newValue > GMlib::GM_DERIVATION_DD)
		return;

	this->_dm = (GMlib::GM_DERIVATION_METHOD)newValue;
}

void ERBS::OnMTReplotChanged(const int &oldValue, const int &newValue)
{
	this->setMultiThreadedReplotting((newValue > 0));
}

//////////////////////////////////
// ERBS PROPERTY CALLBACKS
//////////////////////////////////
void ERBS::OnKnotInitChanged(const CL_Vec2f &oldValue, const CL_Vec2f &newValue)
{
	float st = newValue.x;
    float dt = (newValue.y - newValue.x) / (localCurves.getDim()-1);
    float kvd = localCurves.getDim() + 2;
    if(closed.Get()) 
		kvd--;

    knots.setDim(kvd);

    for(int i = 0; i < kvd - 2; i++)
		knots[i+1] = st + i * dt;

    if(closed.Get()) 
	{
		knots[0] = knots[1] - (knots[kvd-2] - knots[kvd-3]);
		knots[kvd-1] = knots[kvd-2] + (knots[2] - knots[1] );
    }
    else 
	{
		knots[0] = knots[1];
		knots[kvd-1] = knots[kvd-2];
    }

	param_start = knots[1];
	param_end = knots[knots.getDim()-2];
}

/////////////////////////////////////
// SCENE OBJECT PROPERTY CALLBACKS
/////////////////////////////////////
void ERBS::OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue)
{
	GMlib::Vector3D<float> translation;
	translation[0] = newValue.x - oldValue.x;
	translation[1] = newValue.y - oldValue.y;
	translation[2] = newValue.z - oldValue.z;
	this->translate(translation);
}

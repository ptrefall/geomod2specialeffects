#pragma once

#include <Entity/IEntity.h>
#include <Parametric/PCurve.h>
#include <GMlib/gmDMatrix.h>
#include <GMlib/gmDVector.h>
#include <GMlib/gmERBSEvaluator.h>

namespace Engine
{
	class Bezier;
	class CoreMgr;
	class ERBS : public IEntity, public PCurve
	{
	public:
		ERBS(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~ERBS();

		static CL_String GetStaticSpecialType() { return "ERBS"; }
		static IEntity* Create(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory) { return new ERBS(id, type, name, coreMgr, factory); }
		virtual CL_String getSpecialType() const { return GetStaticSpecialType(); }

		virtual std::string getIdentity() const { return identity.Get().c_str(); }
		virtual bool isClosed() const { return closed.Get(); }

		virtual void handle(WorkData *data);

		void setInputCurve(PCurve *inpCurve, int numLocalCurves, int deg, int localCurveReplotNum);

		int getNumLocalCurves() const { return localCurves.getDim(); }
		Bezier *getLocalCurve(int index) { return localCurves[index]; }

	protected:
		virtual void eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l=true);
		virtual float getStartP() { return param_start.Get(); }
		virtual float getEndP() { return param_end.Get(); }

	private:

		//ERBS member variables
		GMlib::DVector<Bezier*> localCurves;
		GMlib::DVector<float> knots;
		GMlib::ERBSEvaluator<float> ERBSEval;

		//Parametric curve properties
		Property<CL_String> identity;
		Property<bool> closed;
		Property<float> param_start;
		Property<float> param_end;
		Property<int> size;
		Property<int> resultSet_dim;
		Property<int> derivation_method;
		Property<CL_Vec4f> resultSet;
		Property<int> mtReplot;

		//ERBS curve properties
		Property<CL_Vec2f> knotInit;
		Property<bool> showLocalCurves;
		Property<int> replotValue;

		//SceneObject properties
		Property<CL_Vec3f> position;
		Property<CL_Vec4f> rotation;

		CL_Slot slotSizeChanged;
		void OnSizeChanged(const int &oldValue, const int &newValue);

		CL_Slot slotDerivationMethodChanged;
		void OnDerivationMethodChanged(const int &oldValue, const int &newValue);

		CL_Slot slotKnotInitChanged;
		void OnKnotInitChanged(const CL_Vec2f &oldValue, const CL_Vec2f &newValue);

		CL_Slot slotPositionChanged;
		void OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);

		CL_Slot slotRotationChanged;
		void OnRotationChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue);

		CL_Slot slotMTReplotChanged;
		void OnMTReplotChanged(const int &oldValue, const int &newValue);

		CL_Slot slotShowLocalCurvesChanged;
		void OnShowLocalCurvesChanged(const bool &oldValue, const bool &newValue);
	};
}

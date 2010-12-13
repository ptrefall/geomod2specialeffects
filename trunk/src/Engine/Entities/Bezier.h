#pragma once

#include <Entity/IEntity.h>
#include <Parametric/PCurve.h>
#include <GMlib/gmDMatrix.h>
#include <GMlib/gmDVector.h>

namespace Engine
{
	class CoreMgr;
	class Bezier : public IEntity, public PCurve
	{
	public:
		Bezier(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~Bezier();

		static CL_String GetStaticSpecialType() { return "Bezier"; }
		static IEntity* Create(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory) { return new Bezier(id, type, name, coreMgr, factory); }
		virtual CL_String getSpecialType() const { return GetStaticSpecialType(); }

		virtual std::string getIdentity() const { return identity.Get().c_str(); }
		virtual bool isClosed() const { return closed.Get(); }

		void calcBernHerm(GMlib::DMatrix<float> &bernHermMat, float t, int d, float size);

	protected:
		virtual void eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l=true);
		virtual float getStartP() { return param_start.Get(); }
		virtual float getEndP() { return param_end.Get(); }

	private:

		//Bezier member variables
		GMlib::DVector<GMlib::Vector<float, 3>> controlPoints;
		GMlib::DVector<GMlib::Vector<float, 3>> bernHermMatMultControlPoints;

		//Parametric curve properties
		Property<CL_String> identity;
		Property<bool> closed;
		Property<float> param_start;
		Property<float> param_end;
		Property<int> size;
		Property<int> resultSet_dim;
		Property<int> derivation_method;
		Property<CL_Vec4f> resultSet;

		//Bezier curve properties
		Property<CL_Vec3f> controlPoint; //Change this to add another controlPoint

		//SceneObject properties
		Property<CL_Vec3f> position;

		CL_Slot slotSizeChanged;
		void OnSizeChanged(const int &oldValue, const int &newValue);

		CL_Slot slotDerivationMethodChanged;
		void OnDerivationMethodChanged(const int &oldValue, const int &newValue);

		CL_Slot slotControlPointChanged;
		void OnControlPointChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);

		CL_Slot slotPositionChanged;
		void OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);
	};
}

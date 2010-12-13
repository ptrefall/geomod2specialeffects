#pragma once

#include <Entity/IEntity.h>
#include <GMlib/gmPCurve.h>
#include <GMlib/gmDMatrix.h>
#include <GMlib/gmDVector.h>

namespace Engine
{
	class CoreMgr;
	class Curve : public IEntity, public GMlib::PCurve<float>
	{
	public:
		Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~Curve();

		static CL_String GetStaticSpecialType() { return "Curve"; }
		static IEntity* Create(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory) { return new Curve(id, type, name, coreMgr, factory); }
		virtual CL_String getSpecialType() const { return GetStaticSpecialType(); }

		virtual std::string getIdentity() const { return identity.Get().c_str(); }
		virtual bool isClosed() const { return closed.Get(); }

		float getBernHermValue(int x, int y);
		void calcBernHermMultControlPoints();
		float getBernHermMultControlPoints(int x, int y);

	protected:
		virtual void eval(float t, int d, bool l=true);
		virtual float getStartP() { return param_start.Get(); }
		virtual float getEndP() { return param_end.Get(); }

	private:

		//Bezier member variables
		GMlib::DMatrix<float> bernHermMat;
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
		Property<int> numControlPoints; //Holds number of control points
		Property<CL_Vec2f> bernHermDim; //Dimension of the Bernstein-Hermite polynomials
		Property<CL_Vec3f> bernHermIndex; //Set value of a bernHerm index via this property

		//SceneObject properties
		Property<CL_Vec3f> position;

		CL_Slot slotSizeChanged;
		void OnSizeChanged(const int &oldValue, const int &newValue);

		CL_Slot slotResultSetDimChanged;
		void OnResultSetDimChanged(const int &oldValue, const int &newValue);

		CL_Slot slotDerivationMethodChanged;
		void OnDerivationMethodChanged(const int &oldValue, const int &newValue);

		CL_Slot slotResultSetChanged;
		void OnResultSetChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue);

		CL_Slot slotControlPointChanged;
		void OnControlPointChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);

		CL_Slot slotBernHermDimChanged;
		void OnBernHermDimChanged(const CL_Vec2f &oldValue, const CL_Vec2f &newValue);

		CL_Slot slotBernHermIndexChanged;
		void OnBernHermIndexChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);

		CL_Slot slotPositionChanged;
		void OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);
	};
}

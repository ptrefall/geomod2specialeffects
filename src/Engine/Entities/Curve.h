#pragma once

#include <Entity/IEntity.h>
#include <GMlib/gmPCurve.h>

namespace Engine
{
	class CoreMgr;
	class Curve : public IEntity, public GMlib::PCurve<float>
	{
	public:
		Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~Curve();

		static CL_String GetSpecialType() { return "Curve"; }
		static IEntity* Create(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory) { return new Curve(id, type, name, coreMgr, factory); }

		virtual void eval(float t, int d, bool l=true);
		virtual float getStartP() { return param_start.Get(); }
		virtual float getEndP() { return param_end.Get(); }

	private:
		Property<bool> closed;
		Property<float> param_start;
		Property<float> param_end;
		Property<int> resultSet_dim;
		Property<int> derivation_method;
		Property<CL_Vec4f> resultSet;

		CL_Slot slotResultSetDimChanged;
		void OnResultSetDimChanged(const int &oldValue, const int &newValue);

		CL_Slot slotDerivationMethodChanged;
		void OnDerivationMethodChanged(const int &oldValue, const int &newValue);

		CL_Slot slotResultSetChanged;
		void OnResultSetChanged(const CL_Vec4f &oldValue, const CL_Vec4f &newValue);
	};
}

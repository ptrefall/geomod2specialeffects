#pragma once

#include <Entity/IEntity.h>
#include <Parametric/PCurve.h>
#include <GMlib/gmDMatrix.h>
#include <GMlib/gmDVector.h>

namespace Engine
{
	class CoreMgr;
	class Curve : public IEntity, public PCurve
	{
	public:
		Curve(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory);
		virtual ~Curve();

		static CL_String GetStaticSpecialType() { return "Curve"; }
		static IEntity* Create(unsigned int id, const CL_String &type, const CL_String &name, CoreMgr *coreMgr, ComponentFactory &factory) { return new Curve(id, type, name, coreMgr, factory); }
		virtual CL_String getSpecialType() const { return GetStaticSpecialType(); }

		virtual std::string getIdentity() const { return identity.Get().c_str(); }
		virtual bool isClosed() const { return closed.Get(); }

		virtual void handle(WorkData *data);

	protected:
		virtual void eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l=true);
		virtual float getStartP() { return param_start.Get(); }
		virtual float getEndP() { return param_end.Get(); }

	private:
		GMlib::DVector< GMlib::Vector<float, 3> > *_p;

		//Parametric curve properties
		Property<CL_String> identity;
		Property<bool> closed;
		Property<float> param_start;
		Property<float> param_end;
		Property<int> size;
		Property<int> resultSet_dim;
		Property<int> derivation_method;
		Property<CL_Vec4f> resultSet;

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

		CL_Slot slotPositionChanged;
		void OnPositionChanged(const CL_Vec3f &oldValue, const CL_Vec3f &newValue);
	};
}

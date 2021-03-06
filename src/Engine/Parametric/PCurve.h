#pragma once

#include <GMLib/gmArray.h>
#include <GMLib/gmParametrics.h>
#include <GMLib/gmDVector.h>
#include <GMLib/gmPCurveVisualizer.h>

#include <WorkThread/WorkData.h>
#include <WorkThread/WorkDoneData.h>
#include <WorkThread/WorkProducer.h>

#ifdef _MSC_VER
	#include <intrin.h>
	#ifndef compiler_barrier
		#define compiler_barrier() _ReadWriteBarrier()
	#endif
#else
	#ifndef compiler_barrier
		#define compiler_barrier()  __asm__ __volatile__("" : : : "memory")
	#endif
#endif

namespace Engine 
{
class CoreMgr;

class PCurveEvalData : public WorkData
{
public:
	WorkProducer *producer;
	unsigned int index;
	GMlib::DVector< GMlib::Vector<float, 3> > &p;
	float t;
	int d;
	bool l;
	CL_InterlockedVariable handled;
	PCurveEvalData(WorkProducer *producer, unsigned int index, GMlib::DVector< GMlib::Vector<float, 3> > &p, float t, int d, bool l)
		: producer(producer), index(index), p(p), t(t), d(d), l(l) { compiler_barrier(); handled.set(0); }

	virtual void handle() 
	{ 
		{ 
			compiler_barrier(); 
			handled.increment(); 
		} 
		if(handled.get() == 1)
		{ 
			producer->handle(this); 
		}
	}

	virtual bool isHandled() { compiler_barrier(); return (handled.get() > 0); }
};

class PCurveEvalDoneData : public WorkDoneData
{
public:
	WorkProducer *producer;
	GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > > *p;
	int m;
	int d;
	float start;
	float end;
	PCurveEvalDoneData(WorkProducer *producer, GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > > *p, int m, int d, float start, float end)
		: producer(producer), p(p), m(m), d(d), start(start), end(end) {}

	virtual void handle() { producer->finished(this); }
};

class PCurve : public GMlib::Parametrics<float,1>, public WorkProducer
{
public:
	PCurve(CoreMgr *coreMgr, int s = 20 );
	~PCurve();

	void setMultiThreadedReplotting(bool mt) { multithreaded_replotting = mt; }

	void enableDefaultVisualizer( bool enable = true );
	GMlib::DVector<GMlib::Vector<float,3>> evaluate( float t, int d );
	GMlib::DVector<GMlib::Vector<float,3>> &evaluateGlobal( float t, int d );
	GMlib::DVector<GMlib::Vector<float,3>> &evaluateParent( float t, int d );
	
	float getCurvature( float t );
	float getCurveLength( float a = 0, float b = -1 );
	
	int getDerivatives() const;
	GMlib::Vector<float,3> getDer1( float t );
	GMlib::Vector<float,3> getDer2( float t );
	
	std::string getIdentity() const;
	
	float getLineWidth() const;
	
	virtual float getLocalMapping( float t, float ts, float ti, float te );
	
	float getParDelta();
	float getParEnd();
	float getParStart();
	
	float getRadius( float t );
	int getSamples() const;
	float getSpeed( float t );
	
	void insertVisualizer( GMlib::Visualizer* visualizer );
	void removeVisualizer( GMlib::Visualizer* visualizer );

	virtual bool isClosed() const;
	virtual void preSample( int m, int d, float s =0.0f, float e = 0.0f );
	virtual void replot( int m = 0, int d = 2 );

	void postReplot(int m = 0, int d = 2 );
	
	void genResampleWork(int m, int d, float start, float end);
	void postResampleWorkDone(int m, int d, float start, float end);
	
	//virtual void resample( GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p, int m, int d, float start, float end );
	
	void setDomain( float start, float end );
	void setDomainScale( float sc );
	void setDomainTrans( float tr );
	
	void setLineWidth( float width = 1.0f );
	
	void setNoDer( int d );
	
	virtual void setSurroundingSphere();
	
	void toggleDefaultVisualizer();

	GMlib::Point<float,3> operator()( float t );

	virtual void finished(WorkDoneData *data);

protected:
	GMlib::Array<GMlib::PCurveVisualizer<float>*> _pcurve_visualizers;
	GMlib::PCurveVisualizer<float> *_default_visualizer;

	GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > > *p;

	bool multithreaded_replotting;

	int _no_sam;      // Number of samples for single sampling
	int _no_der;      // Number of derivatives
	float _line_width;


	GMlib::DVector< GMlib::Vector<float,2>> _sam_p;       // Sampling partition (start/stop)
	GMlib::DVector< int> _no_sam_p;    // Number of samples for each partition
	int _defalt_d;    // used by operator() for number of derivative to evaluate.


	// The result of the previous evaluation
	//GMlib::DVector<GMlib::Vector<float,3>> _p;           // Position and belonging derivatives
	float _t;           // The parameter value used for last evaluation
	int _d;           // Number of derivatives computed last time

	// Shift of parameter.
	float _tr;          // translate
	float _sc;          // scale

	virtual void eval(GMlib::DVector< GMlib::Vector<float, 3> >& _p, float t, int d, bool l = true ) = 0;
	virtual float getEndP() = 0;
	virtual float getStartP() = 0;
	float shift( float t );

private:
	void _eval(GMlib::DVector< GMlib::Vector<float, 3> >& p, float t, int d );
	void _evalDerDD( int d, float du ) const;
	float _integral(float a, float b, double eps) { return 1.0f; }
	CoreMgr *coreMgr;
};

}

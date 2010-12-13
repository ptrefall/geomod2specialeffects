#include "precomp.h"
#include "PCurve.h"
#include <Core/CoreMgr.h>
#include <WorkThread/WorkThreadMgr.h>

using namespace Engine;

PCurve::PCurve(CoreMgr *coreMgr, int s ) 
: coreMgr(coreMgr)
{
	_no_sam           = s;
	_no_der           = 1;
	_d                = -1;
	_tr               = 0.0f;
	_sc               = 1.0f;

	setNoDer(2);

	this->_lighted    = false;
	_line_width       = 1.0f;

	_default_visualizer = new GMlib::PCurveVisualizer<float>();
	enableDefaultVisualizer( true );
}

PCurve::~PCurve() 
{
	enableDefaultVisualizer( false );
	delete _default_visualizer;
}

void PCurve::_eval( GMlib::DVector< GMlib::Vector<float, 3> >& p, float t, int d ) 
{
	if( !(d <=_d &&  t ==_t) ) 
	{
		_t = t; _d = d;
		eval( p, shift(t), d );
	}
}

void PCurve::_evalDerDD( GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > > & p, int d, float du ) const 
{
	float one_over_du = 1.0f / du;
	float one_over_2du = 1.0f / ( 2.0f * du );

	int u, i, k;

	for( u = 1; u < d; u++ ) 
	{
		for( i = 1; i < p.getDim() - 1; i++ ) 
		{
			for( k = 0; k < 3; k++ )
				p[i][u][k] = p[i+1][u-1][k] - p[i-1][u-1][k];

			p[i][u] *= one_over_2du;
		}
	}

	if( isClosed() ) 
	{
		for( u = 1; u < d; u++ ) 
		{
			for( k = 0; k < 3; k++ )
				p[0][u][k] = p[p.getDim()-1][u][k] = p[1][u-1][k] - p[p.getDim() - 2][u-1][k];

			p[0][u] = p[p.getDim()-1][u] *= one_over_2du;
		}
	}
	else 
	{
		for( u = 1; u < d; u++ ) 
		{
			for( k = 0; k < 3; k++ ) 
			{
				p[0][u][k] = p[1][u-1][k] - p[0][u-1][k];
				p[p.getDim()-1][u][k] = p[p.getDim()-1][u-1][k] - p[p.getDim()-2][u-1][k];
			}
			p[0][u] *= one_over_du;
			p[p.getDim()-1][u] *= one_over_du;
		}
	}
}

void PCurve::enableDefaultVisualizer( bool enable ) 
{
if( !enable )
	removeVisualizer( _default_visualizer );
else
	insertVisualizer( _default_visualizer );
}

GMlib::DVector<GMlib::Vector<float,3> > PCurve::evaluate( float t, int d ) 
{
	GMlib::DVector< GMlib::Vector<float, 3> > p;
	_eval(p, t,d);
	return p;
}

GMlib::DVector<GMlib::Vector<float,3> >& PCurve::evaluateGlobal( float t, int d ) 
{
	static GMlib::DVector< GMlib::Vector<float,3> > p;
	p.setDim(d+1);
	_eval(p,t,d);

	p[0] = this->_present*((GMlib::Point<float,3>)p[0]);

	for( int i = 1; i <= d; i++ )
		p[i] = this->_present * (GMlib::Vector<float,3>)p[i];

	return p;
}

GMlib::DVector<GMlib::Vector<float,3> >& PCurve::evaluateParent( float t, int d ) 
{
	static GMlib::DVector< GMlib::Vector<float,3> > p;
	p.setDim(d+1);
	_eval(p, t,d);

	p[0] = this->_matrix*((GMlib::Point<float,3>)p[0]);

	for( int i = 1; i <= d; i++ )
		p[i] = this->_matrix * (GMlib::Vector<float,3>)p[i];

	return p;
}

float PCurve::getCurvature( float t ) 
{
	GMlib::DVector< GMlib::Vector<float,3> > p;
	_eval(p, t, 2 );
	GMlib::Vector<float,3> d1 = p[1];
	float a1= d1.getLength();

	if( a1 < float(1.0e-5) )
		return 0.0f;

	d1 /= a1;

	GMlib::Vector<float,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

	return d2.getLength();
}

float PCurve::getCurveLength( float a , float b ) 
{
	if(b<a)	
	{
		a = getParStart();
		b = getParEnd();
	}

	return _integral( a, b, 1e-10 );
}

int PCurve::getDerivatives() const 
{
	return _no_der;
}

GMlib::Vector<float,3> PCurve::getDer1( float t ) 
{
	GMlib::DVector< GMlib::Vector<float, 3> > p;
	eval(p, t, 1 );
	return p[1];
}

GMlib::Vector<float,3> PCurve::getDer2(float t ) 
{
	GMlib::DVector< GMlib::Vector<float, 3> > p;
	_eval(p,t,2);
	return p[2];
}

std::string PCurve::getIdentity() const 
{
	return "PCurve";
}

float PCurve::getLineWidth() const 
{
	return _line_width;
}

float PCurve::getLocalMapping( float t, float /*ts*/, float /*ti*/, float /*te*/ ) 
{
	return t;
}

float PCurve::getParDelta()
{
	return _sc*( getEndP() - getStartP() );
}

float PCurve::getParEnd() 
{
	return getParStart() + getParDelta();
}

float PCurve::getParStart()
{
	return getStartP() + _tr;
}

float PCurve::getRadius( float t ) 
{
	return 1.0f / getCurvature( t );
}

int PCurve::getSamples() const
{
	return _no_sam;
}

float PCurve::getSpeed( float t )
{
	return getDer1( t ).getLength();
}

void PCurve::insertVisualizer( GMlib::Visualizer* visualizer ) 
{
	GMlib::PCurveVisualizer<float> *visu = dynamic_cast<GMlib::PCurveVisualizer<float>*>( visualizer );
	if( !visu )
		return;

	if( _pcurve_visualizers.exist( visu ) )
		return;

	_pcurve_visualizers += visu;

	GMlib::SceneObject::insertVisualizer( visualizer );
}

bool PCurve::isClosed() const
{
	return false;
}

void PCurve::preSample( int /*m*/, int /*d*/, float /*s*/, float /*e*/ ) 
{
}


////////////////////////////////////
////
//// REWRITTEN TO MULTITHREADING
////
////////////////////////////////////
void PCurve::replot( int m, int d ) 
{
	// Correct sample domain
	if( m < 2 )
		m = _no_sam;
	else
		_no_sam = m;

	// Correct derivatives
	if( d < 1 )
		d = _no_der;
	else
		_no_der = d;

	// pre-sampel / pre evaluate data for a given parametric curve, if wanted/needed
	preSample( m, 1, getStartP(), getEndP() );

	// Resample
	GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > > p;
	
	/////////////////////////////////
	// MULTITHREADING EDIT!
	/////////////////////////////////
	
	//resample( p, m, 1, getStartP(), getEndP() );

	genResampleWork(p, m, 1, getStartP(), getEndP());

	/*// Set The Surrounding Sphere
	setSurroundingSphere( p );

	// Replot Visaulizers
	for( int i = 0; i < this->_pcurve_visualizers.getSize(); i++ )
		this->_pcurve_visualizers[i]->replot( p, m, d );*/
}

void PCurve::postReplot(GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p, int m, int d)
{
	// Set The Surrounding Sphere
	setSurroundingSphere( p );

	// Replot Visaulizers
	for( int i = 0; i < this->_pcurve_visualizers.getSize(); i++ )
		this->_pcurve_visualizers[i]->replot( p, m, d );
}

/////////////////////////////////////
// CHECKS MULTITHREADED WORK STATUS
/////////////////////////////////////
void PCurve::finished(WorkDoneData *data)
{
	PCurveEvalDoneData *evalData = static_cast<PCurveEvalDoneData*>(data);
	postResampleWorkDone(evalData->p, evalData->m, evalData->d, evalData->start, evalData->end);
	postReplot(evalData->p, evalData->m, evalData->d);
}

void PCurve::removeVisualizer( GMlib::Visualizer* visualizer ) 
{
	GMlib::PCurveVisualizer<float> *visu = dynamic_cast<GMlib::PCurveVisualizer<float>*>( visualizer );
	if( visu )
		_pcurve_visualizers.remove( visu );

	GMlib::SceneObject::removeVisualizer( visu );
}

////////////////////////////////////
////
//// REWRITTEN TO MULTITHREADING
////
////////////////////////////////////
void PCurve::genResampleWork(GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p, int m, int d, float start, float end)
{
	float du = (end-start)/(m-1);
	p.setDim(m);

	//Generate jobs for worker threads here instead
	//of calling eval directly in a linear fassion...
	std::vector<WorkData*> work_group;
	for( int i = 0; i < m - 1; i++ ) 
	{
		PCurveEvalData *evalData = new PCurveEvalData(p[i], start + i * d, d, true);
		work_group.push_back(evalData);

		//eval(p[i], start + i * du, d, true);
		//p[i] = _p;
	}
	PCurveEvalData *evalData = new PCurveEvalData(p[m-1], end, d, true);
	work_group.push_back(evalData);

	PCurveEvalDoneData *evalDoneData = new PCurveEvalDoneData(p, m,d, start,end);
	coreMgr->getWorkThreadMgr()->addWorkGroup(this, work_group, evalDoneData);
	//eval( end, d, true );
	//p[m-1] = _p;
}

void PCurve::postResampleWorkDone(GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p, int m, int d, float start, float end)
{
	switch( this->_dm ) 
	{
	case GMlib::GM_DERIVATION_EXPLICIT:
		// Do nothing, evaluator algorithms for explicite calculation of derivatives
		// should be defined in the eval( ... ) function enclosed by
		// if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
		break;

	case GMlib::GM_DERIVATION_DD:
	default:
			float du = (end-start)/(m-1);
			_evalDerDD( p, d, du );
		break;
	};
}

/*void PCurve::resample( GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p, int m, int d, float start, float end )
{
	float du = (end-start)/(m-1);
	p.setDim(m);

	//Generate jobs for worker threads here instead
	//of calling eval directly in a linear fassion...
	for( int i = 0; i < m - 1; i++ ) 
	{
		eval( start + i * du, d, true);
		p[i] = _p;
	}
	eval( end, d, true );
	p[m-1] = _p;


	switch( this->_dm ) 
	{
	case GMlib::GM_DERIVATION_EXPLICIT:
		// Do nothing, evaluator algorithms for explicite calculation of derivatives
		// should be defined in the eval( ... ) function enclosed by
		// if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
		break;

	case GMlib::GM_DERIVATION_DD:
	default:
			_evalDerDD( p, d, du );
		break;
	};
}*/

void PCurve::setDomain(float start, float end) 
{
	_sc = ( end - start );
	_tr= getStartP() + start;
}

void PCurve::setDomainScale( float sc )
{
	_sc = sc;
}

void PCurve::setDomainTrans( float tr ) 
{
	_tr = tr;
}

void PCurve::setLineWidth( float width )
{
	_line_width = width;
}

void PCurve::setNoDer( int d )
{
	_defalt_d = d;
}

void PCurve::setSurroundingSphere( const GMlib::DVector< GMlib::DVector< GMlib::Vector<float, 3> > >& p )
{
	GMlib::Sphere<float,3>  s;
	s.resetPos( GMlib::Point<float,3>( p(0)(0) ) );
	s += GMlib::Point<float,3>( p(p.getDim() - 1)(0) );
	for( int i = p.getDim() - 2; i > 0; i-- )
	s += GMlib::Point<float,3>( p(i)(0) );
	GMlib::Parametrics<float,1>::setSurroundingSphere(s);
}

float PCurve::shift( float t )
{
	return _tr + _sc * ( t - getStartP() );
}

void PCurve::toggleDefaultVisualizer() 
{
	if( !_pcurve_visualizers.exist( _default_visualizer ) )
		enableDefaultVisualizer( true );
	else
		enableDefaultVisualizer( false );
}

GMlib::Point<float,3> PCurve::operator()( float t )
{
	GMlib::DVector< GMlib::Vector<float, 3> > p;
	eval(p, t, _defalt_d );
	return ( GMlib::Point<float,3> ) p[0];
}

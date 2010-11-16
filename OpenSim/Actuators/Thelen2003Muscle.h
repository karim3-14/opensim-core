#ifndef __Thelen2003Muscle_h__
#define __Thelen2003Muscle_h__

// Thelen2003Muscle.h
/*
 * Copyright (c)  2006, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


// INCLUDE
#include "osimActuatorsDLL.h"
#include <OpenSim/Common/PropertyDbl.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/ArrayPtrs.h>
#include <OpenSim/Common/ScaleSet.h>
#include <OpenSim/Common/Function.h>
#include <OpenSim/Simulation/Model/Muscle.h>

#ifdef SWIG
	#ifdef OSIMACTUATORS_API
		#undef OSIMACTUATORS_API
		#define OSIMACTUATORS_API
	#endif
#endif

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
 * A class implementing a SIMM muscle.
 *
 * @author Peter Loan
 * @version 1.0
 */
class OSIMACTUATORS_API Thelen2003Muscle : public Muscle  
{

//=============================================================================
// DATA
//=============================================================================
protected:
	/** Maximum isometric force that the fibers can generate */
	PropertyDbl _maxIsometricForceProp;
	double &_maxIsometricForce;

	/** Optimal length of the muscle fibers */
	PropertyDbl _optimalFiberLengthProp;
	double &_optimalFiberLength;

	/** Resting length of the tendon */
	PropertyDbl _tendonSlackLengthProp;
	double &_tendonSlackLength;

	/** Angle between tendon and fibers at optimal fiber length */
	PropertyDbl _pennationAngleProp;
	double &_pennationAngle;

	/** Activation time constant */  
	PropertyDbl _activationTimeConstantProp;
	double &_activationTimeConstant;

	/** Deactivation time constant */
	PropertyDbl _deactivationTimeConstantProp;
	double &_deactivationTimeConstant;

	/** Max contraction velocity full activation in fiber lengths per second */
	PropertyDbl _vmaxProp;
	double &_vmax;

	/** Max contraction velocity at low activation */
	PropertyDbl _vmax0Prop;
	double &_vmax0;

	/** Tendon strain due to maximum isometric muscle force */
	PropertyDbl _fmaxTendonStrainProp;
	double &_fmaxTendonStrain;

	/** Passive muscle strain due to maximum isometric muscle force */
	PropertyDbl _fmaxMuscleStrainProp;
	double &_fmaxMuscleStrain;

	/** Shape factor for Gaussian active muscle force-length relationship */
	PropertyDbl _kShapeActiveProp;
	double &_kShapeActive;

	/** Exponential shape factor for passive force-length relationship */
	PropertyDbl _kShapePassiveProp;
	double &_kShapePassive;

	/** Passive damping included in the force-velocity relationship */
	PropertyDbl _dampingProp;
	double &_damping;

	/** Force-velocity shape factor */
	PropertyDbl _afProp;
	double &_af;

	/** Maximum normalized lengthening force */
	PropertyDbl _flenProp;
	double &_flen;

protected:
	static const int STATE_ACTIVATION;
	static const int STATE_FIBER_LENGTH;
//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	Thelen2003Muscle();
	Thelen2003Muscle(const std::string &aName,double aMaxIsometricForce,double aOptimalFiberLength,double aTendonSlackLength,double aPennationAngle);
	Thelen2003Muscle(const Thelen2003Muscle &aMuscle);
	virtual ~Thelen2003Muscle();
	virtual Object* copy() const;

#ifndef SWIG
	Thelen2003Muscle& operator=(const Thelen2003Muscle &aMuscle);
#endif
    void copyData(const Thelen2003Muscle &aMuscle);
	virtual void copyPropertyValues(Actuator& aActuator);
#ifndef SWIG

#endif

	//--------------------------------------------------------------------------
	// GET
	//--------------------------------------------------------------------------
	// Properties
	virtual double getMaxIsometricForce() const { return _maxIsometricForce; }
	virtual double getOptimalFiberLength() const { return _optimalFiberLength; }
	virtual double getTendonSlackLength() const { return _tendonSlackLength; }
	virtual double getPennationAngleAtOptimalFiberLength() const { return _pennationAngle; }
	virtual double getActivationTimeConstant() const { return _activationTimeConstant; }
	virtual double getDeactivationTimeConstant() const { return _deactivationTimeConstant; }
	virtual double getVmax() const { return _vmax; }
	virtual double getVmax0() const { return _vmax0; }
	virtual double getFmaxTendonStrain() const { return _fmaxTendonStrain; }
	virtual double getFmaxMuscleStrain() const { return _fmaxMuscleStrain; }
	virtual double getKshapeActive() const { return _kShapeActive; }
	virtual double getKshapePassive() const { return _kShapePassive; }
	virtual double getDamping() const { return _damping; }
	virtual double getAf() const { return _af; }
	virtual double getFlen() const { return _flen; }
	virtual bool setActivationTimeConstant(double aActivationTimeConstant);
	virtual bool setDeactivationTimeConstant(double aDeactivationTimeConstant);
	virtual bool setMaxIsometricForce(double aMaxIsometricForce);
	virtual bool setOptimalFiberLength(double aOptimalFiberLength);
	virtual bool setTendonSlackLength(double aTendonSlackLength);
	virtual bool setPennationAngle(double aPennationAngle);
	virtual bool setVmax(double aVmax);
	virtual bool setVmax0(double aVmax0);
	virtual bool setFmaxTendonStrain(double aFmaxTendonStrain);
	virtual bool setFmaxMuscleStrain(double aFmaxMuscleStrain);
	virtual bool setKshapeActive(double aKShapeActive);
	virtual bool setKshapePassive(double aKshapePassive);
	virtual bool setDamping(double aDamping);
	virtual bool setAf(double aAf);
	virtual bool setFlen(double aFlen);

	// Computed quantities
#ifndef SWIG
	virtual double getPennationAngle(const SimTK::State& s) const;
	virtual double getNormalizedFiberLength(const SimTK::State& s) const;
	virtual double getPassiveFiberForce(const SimTK::State& s) const;
	virtual double getStress(const SimTK::State& s) const;
	virtual double getActivation(const SimTK::State& s) const { return getStateVariable(s, STATE_ACTIVATION); }
	virtual void setActivation(SimTK::State& s, double activation) const { setStateVariable(s, STATE_ACTIVATION, activation); }
	virtual double getActivationDeriv(const SimTK::State& s) const { return getStateVariableDeriv(s, STATE_ACTIVATION); }
	virtual void setActivationDeriv(const SimTK::State& s, double activationDeriv) const { setStateVariableDeriv(s, STATE_ACTIVATION, activationDeriv); }
	virtual double getFiberLength(const SimTK::State& s) const { return getStateVariable(s, STATE_FIBER_LENGTH); }
	virtual void setFiberLength(SimTK::State& s, double fiberLength) const { setStateVariable(s, STATE_FIBER_LENGTH, fiberLength); }
	virtual double getFiberLengthDeriv(const SimTK::State& s) const { return getStateVariableDeriv(s, STATE_FIBER_LENGTH); }
	virtual void setFiberLengthDeriv(const SimTK::State& s, double fiberLengthDeriv) const { setStateVariableDeriv(s, STATE_FIBER_LENGTH, fiberLengthDeriv); }
    virtual void setPassiveForce(const SimTK::State& s, double aForce) const;
    virtual double getPassiveForce( const SimTK::State& s) const;
	 virtual void setTendonForce(const SimTK::State& s, double aForce) const;
	 virtual double getTendonForce(const SimTK::State& s) const;



	//--------------------------------------------------------------------------
	// FORCE-LENGTH-VELOCITY PROPERTIES
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// COMPUTATIONS
	//--------------------------------------------------------------------------
	virtual void computeEquilibrium(SimTK::State& s ) const;
	virtual double computeActuation(const SimTK::State& s) const;
	double calcTendonForce(const SimTK::State& s, double aNormTendonLength) const;
	double calcPassiveForce(const SimTK::State& s, double aNormFiberLength) const;
	double calcActiveForce(const SimTK::State& s, double aNormFiberLength) const;
	double calcFiberVelocity(const SimTK::State& s, double aActivation, double aActiveForce, double aVelocityDependentForce) const;
	virtual double computeIsometricForce(SimTK::State& s, double activation) const;
	virtual double computeIsokineticForceAssumingInfinitelyStiffTendon(SimTK::State& s, double aActivation);

	//--------------------------------------------------------------------------
	// SCALE
	//--------------------------------------------------------------------------
	virtual void postScale(const SimTK::State& s, const ScaleSet& aScaleSet);
	virtual void scale(const SimTK::State& s, const ScaleSet& aScaleSet);

#endif
	virtual int getStateVariableYIndex(int index) const;

	OPENSIM_DECLARE_DERIVED(Thelen2003Muscle, Actuator);

protected:
	// Model Component Interface
	virtual void setup(Model& aModel);
	virtual void createSystem(SimTK::MultibodySystem& system) const;
	virtual SimTK::Vector computeStateVariableDerivatives(const SimTK::State &s) const;

private:
	void setNull();
	void setupProperties();
//=============================================================================
};	// END of class Thelen2003Muscle
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __Thelen2003Muscle_h__



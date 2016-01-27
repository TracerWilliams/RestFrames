/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   DecayGenFrame.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2015 Jan
///
//   This file is part of RestFrames.
//
//   RestFrames is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
// 
//   RestFrames is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// 
//   You should have received a copy of the GNU General Public License
//   along with RestFrames. If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////

#ifndef DecayGenFrame_HH
#define DecayGenFrame_HH

#include "RestFrames/DecayFrame.hh"
#include "RestFrames/GeneratorFrame.hh"

using namespace std;

namespace RestFrames {

  class ResonanceGenFrame;

  ///////////////////////////////////////////////
  // DecayGenFrame class
  ///////////////////////////////////////////////
  class DecayGenFrame : public DecayFrame<GeneratorFrame> {
  public:
    DecayGenFrame(const string& sname, const string& stitle);
    virtual ~DecayGenFrame();

    virtual void SetMass(double val);
    virtual double GetMass() const;

    // For two-body decays
    virtual void SetCosDecayAngle(double val);
    virtual void SetDeltaPhiDecayPlane(double val);

  protected:
    double m_Mass;

    double m_CosDecayAngle;
    double m_DeltaPhiDecayPlane;

    vector<int> m_VarMassChildren;
    vector<double> m_InterMassFracMCMC;

    virtual bool IsSoundBody() const;

    virtual void ResetFrame();
    virtual bool GenerateFrame();
   
    void GenerateTwoBodyRecursive(const vector<double>& M_parent, 
				  const vector<double>& M_child,
				  const TVector3& axis_par, 
				  const TVector3& axis_perp,
				  vector<TLorentzVector>& P_child);

    virtual bool InitializeGenAnalysis();

    virtual bool IterateMCMC();
    virtual double GetProbMCMC(double mass) const;

  private:
    void Init();

  };

  int DoubleMax(const void *a, const void *b);

}

#endif

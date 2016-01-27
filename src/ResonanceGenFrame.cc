/////////////////////////////////////////////////////////////////////////
//   RestFrames: particle physics event analysis library
//   --------------------------------------------------------------------
//   Copyright (c) 2014-2015, Christopher Rogan
/////////////////////////////////////////////////////////////////////////
///
///  \file   ResonanceGenFrame.cc
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

#include <stdlib.h>
#include "RestFrames/ResonanceGenFrame.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // ResonanceGenFrame class
  ///////////////////////////////////////////////

  ResonanceGenFrame::ResonanceGenFrame(const string& sname, const string& stitle)
    : DecayGenFrame(sname,stitle)
  {
    Init();
  }

  ResonanceGenFrame::ResonanceGenFrame()
    : DecayGenFrame("Empty","Empty")
  {
    Init();
  }
  
  ResonanceGenFrame::~ResonanceGenFrame(){ }

  void ResonanceGenFrame::Init(){
    m_PoleMass = 0.;
    m_Width = 0.;
  }

  ResonanceGenFrame& ResonanceGenFrame::Empty(){
    return ResonanceGenFrame::m_Empty;
  }

  void ResonanceGenFrame::SetMass(double val){
    if(val < 0.){
      m_Log << LogWarning;
      m_Log << "Unable to set mass to negative value ";
      m_Log << val << ". Setting to zero." << m_End;
      m_PoleMass = 0.;
    } else {
      m_PoleMass = val;
    }
  }

  void ResonanceGenFrame::SetMassMCMC(double val){
    if(val < 0.){
      m_Log << LogWarning;
      m_Log << "Unable to set mass to negative value ";
      m_Log << val << ". Setting to zero." << m_End;
      m_Mass = 0.;
    } else {
      m_Mass = val;
    }
  }

  void ResonanceGenFrame::SetWidth(double val){
    SetMind(false);
    
    if(val < 0.){
      m_Log << LogWarning;
      m_Log << "Unable to set width to negative value ";
      m_Log << val << ". Setting to zero." << m_End;
      m_Width = 0.;
      SetVariableMassMCMC(false);
    } else {
      m_Width = val;
      SetVariableMassMCMC(true);
    }
  }


  double ResonanceGenFrame::GetPoleMass() const {
    return m_PoleMass;
  }

  double ResonanceGenFrame::GetWidth() const {
    return m_Width;
  }

  double ResonanceGenFrame::GetProbMCMC(double mass) const {
    if(mass < 0) return 0.;
    
    double den = (mass*mass-m_PoleMass*m_PoleMass)*(mass*mass-m_PoleMass*m_PoleMass)
      + mass*mass*mass*mass*m_Width*m_Width/m_PoleMass/m_PoleMass;

    if(den > 0.)
      return DecayGenFrame::GetProbMCMC(mass)*mass*mass/den;
    else
      return 0.;
  }

  double ResonanceGenFrame::GenerateMassMCMC(double max) const {
    double min = 0.;
    int N = GetNChildren();
    for(int i = 0; i < N; i++)
      min += GetChildFrame(i).GetMass();

    if((max < min) && (max < 0))
      return 0.;

    if(m_Width <= 0.)
      return 0.;
    
    if(min <= 0)
      min = 0.;
    
    double M2 = m_PoleMass*m_PoleMass;
    double MW = m_PoleMass*m_Width;
    double Imin = atan((min*min-M2)/MW);
    double Imax;
    if(max <= 0) 
      Imax = TMath::Pi()/2.;
    else 
      Imax = atan((max*max-M2)/MW);
    
    return sqrt(M2 + MW*tan(Imin+GetRandom()*(Imax-Imin)));
  }

  double ResonanceGenFrame::GetGenerateProbMCMC(double mass) const {
    double den = mass*mass-m_PoleMass*m_PoleMass;
    den *= den;
    den += m_PoleMass*m_PoleMass*m_Width*m_Width;
    if(den > 0)
      return 1./den;
    else
      return 0.;
  }

  ResonanceGenFrame ResonanceGenFrame::m_Empty;
}

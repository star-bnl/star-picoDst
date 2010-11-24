#ifndef StPicoTrack_hh
#define StPicoTrack_hh

class StMuTrack;
class StPicoDst;

#include "TObject.h"
#include "StThreeVectorF.hh"
#include "TVector2.h"
#include <stdio.h>
#include <math.h>

class StPicoTrack : public TObject {
 public:
  StPicoTrack();
  ~StPicoTrack();
  StPicoTrack(StMuTrack *, StMuTrack *, float, int, double,
              int, int, float*, float*, int*);
  void    Clear(const Option_t *opt="");
  virtual void Print(Option_t* option = "") const;  ///< Print track info
            
  Int_t   id() const             { return (Int_t)mId; }
  Float_t chi2() const           { return (Float_t)mChi2/1000.; }
  Float_t chi2prob() const       { return (Float_t)mChi2Prob/1000.;}
  StThreeVectorF gMom() const    { return mGMomentum; }
  StThreeVectorF pMom() const    { return mPMomentum; }
  StThreeVectorF origin() const  { return mOrigin; }
  Int_t   flowFlag() const       { return (Int_t)mFlowFlag; }
  TVector2 Qi() const            { return TVector2(mQXi, mQYi); }
  Float_t dca() const            { return (Float_t)mGDca/1000.; }
  Short_t charge() const         { return (mNHitsFit>0) ? +1 : -1; }
  Int_t   nHitsFit() const       { return (mNHitsFit>0) ? (Int_t)mNHitsFit : (Int_t)(-1*mNHitsFit); }
  Int_t   nHitsMax() const       { return (Int_t)mNHitsMax; }
  Int_t   nHitsDedx() const      { return (Int_t)mNHitsDedx; }
  Float_t dEdx() const           { return (Float_t)mDedx/1000.; }
  Float_t nSigmaPion() const     { return (Float_t)mNSigmaPion/100.; }
  Float_t nSigmaKaon() const     { return (Float_t)mNSigmaKaon/100.; }
  Float_t nSigmaProton() const   { return (Float_t)mNSigmaProton/100.; }
  Float_t nSigmaElectron() const { return (Float_t)mNSigmaElectron/100.; }

  Int_t   btofCellId() const     { return (Int_t)mBTofCellId; }
  Float_t btof() const           { return mBTof; }
  Float_t btofBeta() const       { return mBTofBeta; }
  StThreeVectorF btofHisPos() const { return mBTofHitPos; }  

  Int_t   bemcId() const         { return (Int_t)mBEMCId; }
  Int_t   adc0() const           { return (Int_t)mBTOWADC0; }
  Float_t e0() const             { return (Float_t)mBTOWE0/1000.; }
  Float_t e3() const             { return (Float_t)mBTOWE3/1000.; }
  Float_t e() const              { return (Float_t)mBTOWE/1000.; }
  Float_t zDist() const          { return (Float_t)mBEMCDistZ/100.; }
  Float_t phiDist() const        { return (Float_t)mBEMCDistPhi/10000.; }
  Int_t   nEta() const           { return (Int_t)mBSMDNEta; }
  Int_t   nPhi() const           { return (Int_t)mBSMDNPhi; }  

 protected:
  UShort_t mId;               // track Id
  UShort_t mChi2;             // chi2*1000
  UShort_t mChi2Prob;         // chi2prob*1000
  StThreeVectorF mGMomentum;  // Global momentum
  StThreeVectorF mPMomentum;  // primary momentum, (0.,0.,0.) if none
  UChar_t  mFlowFlag;         // 1 - tpc EP, 2 - ftpc EP, 0 - none
  Float_t  mQXi;              //
  Float_t  mQYi;              // Q-vector for this track
  StThreeVectorF mOrigin;     // global helix origin
  UShort_t mGDca;             // global dca*1000
  UShort_t mDedx;             // dEdx*1000
  Char_t   mNHitsFit;         // q*nHitsFit
  UChar_t  mNHitsMax;         //
  UChar_t  mNHitsDedx;        //
  Short_t  mNSigmaPion;       // nsigmaPi * 100
  Short_t  mNSigmaKaon;       //
  Short_t  mNSigmaProton;     //
  Short_t  mNSigmaElectron;   //
  
  Short_t  mBTofCellId;       // (tray-1)*192+(module-1)*6+(cell-1): -1 - no match
  Float_t  mBTof;             // time-Of-Flight
  Float_t  mBTofBeta;         // beta
  StThreeVectorF mBTofHitPos; // projected hit position

  Short_t  mBEMCId;           // emc point id
  UShort_t mBTOWADC0;         // adc0
  UShort_t mBTOWE0;           // E0*1000
  UShort_t mBTOWE3;           // E*1000 sum E of 3 highest tower in 3x3
  UShort_t mBTOWE;            // EMC point E*1000 
  Short_t  mBEMCDistZ;        // z*100
  Short_t  mBEMCDistPhi;      // phi*10000
  UChar_t  mBSMDNEta;         // # of hits in eta
  UChar_t  mBSMDNPhi;         // # of hits in phi

  friend class StPicoDst;

  ClassDef(StPicoTrack, 1)
};

#endif

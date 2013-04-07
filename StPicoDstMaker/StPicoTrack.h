#ifndef StPicoTrack_hh
#define StPicoTrack_hh

class StMuTrack;
class StPicoDst;

#include "TObject.h"
#include "StThreeVectorF.hh"
#include "TVector2.h"
#include <stdio.h>
#include <math.h>

// Macro to control EMC variables
#define EMCON 1

class StPicoTrack : public TObject {
 public:
  StPicoTrack();
  ~StPicoTrack();
  StPicoTrack(StMuTrack *, StMuTrack *, float, int, double,
              int, int, float*, float*, int*, int*);
  void    Clear(const Option_t *opt="");
  virtual void Print(const Char_t *option = "") const;  ///< Print track info
            
  Int_t   id() const             { return (Int_t)mId; }
  Float_t chi2() const           { return (Float_t)mChi2/1000.; }
  Float_t chi2prob() const       { return (Float_t)mChi2Prob/1000.;}
  StThreeVectorF gMom() const    { return mGMomentum; }
  StThreeVectorF pMom() const    { return mPMomentum; }
  StThreeVectorF origin() const  { return StThreeVectorF(mOriginX/100.,mOriginY/100.,mOriginZ/100.); }
  Int_t   flowFlag() const       { return (Int_t)mFlowFlag; }
//  TVector2 Qi() const            { return TVector2(mQXi, mQYi); }
  TVector2 Qi() const            { return TVector2(-9999., -9999.); }
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
  Int_t   btofMatchFlag() const  { return (Int_t)mBTofMatchFlag; }
  Float_t btof() const           { return (Float_t)mBTof/1000.; }
  Float_t btofBeta() const       { return (Float_t)mBTofBeta/20000.; }
  Float_t btofYLocal() const     { return (Float_t)mBTofYLocal/1000.; }
  Float_t btofZLocal() const     { return (Float_t)mBTofZLocal/1000.; }  
  StThreeVectorF btofHisPos() const { return StThreeVectorF(mBTofHitPosX/100., mBTofHitPosY/100., mBTofHitPosZ/100.); }  

#if EMCON == 1
  Int_t   bemcId() const         { return (Int_t)mBEMCId; }
  Int_t   adc0() const           { return (Int_t)mBTOWADC0; }
  Float_t e0() const             { return (Float_t)mBTOWE0/1000.; }
  Float_t e() const              { return (Float_t)mBTOWE/1000.; }
  Float_t zDist() const          { return (Float_t)mBEMCDistZ/100.; }
  Float_t phiDist() const        { return (Float_t)mBEMCDistPhi/10000.; }
  Int_t   nEta() const           { return (Int_t)mBSMDNEta; }
  Int_t   nPhi() const           { return (Int_t)mBSMDNPhi; }  

  Int_t   btowId() const         { return (Int_t)mBTOWId; }
  Int_t   btowId2() const        { return (Int_t)mBTOWId23/10; }
  Int_t   btowId3() const        { return (Int_t)mBTOWId23%10; }
  Float_t e1() const             { return (Float_t)mBTOWE1/1000.; }
  Float_t e2() const             { return (Float_t)mBTOWE2/1000.; }
  Float_t e3() const             { return (Float_t)mBTOWE3/1000.; }
  Float_t etaTowDist() const     { return (Float_t)mBTOWDistEta/10000.; }
  Float_t phiTowDist() const     { return (Float_t)mBTOWDistPhi/10000.; }
#else
  Int_t   bemcId() const         { return -9999; }
  Int_t   adc0() const           { return -9999; }
  Float_t e0() const             { return -9999.; }
  Float_t e() const              { return -9999.; }
  Float_t zDist() const          { return -9999.; }
  Float_t phiDist() const        { return -9999.; }
  Int_t   nEta() const           { return -9999; }
  Int_t   nPhi() const           { return -9999; }

  Int_t   btowId() const         { return -9999; }
  Int_t   btowId2() const        { return -9999; }
  Int_t   btowId3() const        { return -9999; }
  Float_t e1() const             { return -9999.; }
  Float_t e2() const             { return -9999.; }
  Float_t e3() const             { return -9999.; }
  Float_t etaTowDist() const     { return -9999.; }
  Float_t phiTowDist() const     { return -9999.; }
#endif

 protected:
  UShort_t mId;               // track Id
  UShort_t mChi2;             // chi2*1000
  UShort_t mChi2Prob;         // chi2prob*1000
  StThreeVectorF mGMomentum;  // Global momentum
  StThreeVectorF mPMomentum;  // primary momentum, (0.,0.,0.) if none
  UChar_t  mFlowFlag;         // 1 - tpc EP, 2 - ftpc EP, 0 - none
//  Float_t  mQXi;              //
//  Float_t  mQYi;              // Q-vector for this track
  Short_t  mOriginX;          // global helix origin X * 100
  Short_t  mOriginY;          // global helix origin Y * 100 
  Short_t  mOriginZ;          // global helix origin Z * 100 
  UShort_t mGDca;             // global dca*1000
  UShort_t mDedx;             // dEdx*1000
  Char_t   mNHitsFit;         // q*nHitsFit
  UChar_t  mNHitsMax;         // nHitsMax
  UChar_t  mNHitsDedx;        // nHitsDedx
  Short_t  mNSigmaPion;       // nsigmaPi * 100
  Short_t  mNSigmaKaon;       // nsigmaK * 100
  Short_t  mNSigmaProton;     // nsigmaP * 100
  Short_t  mNSigmaElectron;   // nsigmaE * 100

  // BTOF variables  
  Short_t  mBTofCellId;       // (tray-1)*192+(module-1)*6+(cell-1): -1 - no match
  UChar_t  mBTofMatchFlag;    // 0 - no match, 1 - one-to-one, 2 - one-to-multiple
  UShort_t mBTof;             // time-Of-Flight * 1000 in ns
  UShort_t mBTofBeta;         // beta * 20000
  Short_t  mBTofYLocal;       // ylocal * 1000
  Short_t  mBTofZLocal;       // zlocal * 1000
  Short_t  mBTofHitPosX;      // projected hit position X * 100
  Short_t  mBTofHitPosY;      // projected hit position Y * 100
  Short_t  mBTofHitPosZ;      // projected hit position Z * 100

#if EMCON == 1
  // these variables are extracted from the standard BEMC cluster algorithm
  Short_t  mBEMCId;           // index in bemcPoint array
  Short_t  mBTOWADC0;         // adc0 higest adc in the cluster
  Short_t  mBTOWE0;           // E0*1000 highest tower in the cluster
  Short_t  mBTOWE;            // EMC point E*1000 
  Short_t  mBEMCDistZ;        // z*100
  Short_t  mBEMCDistPhi;      // phi*10000
  UChar_t  mBSMDNEta;         // # of hits in eta
  UChar_t  mBSMDNPhi;         // # of hits in phi

  // these variables are purely from single tower or nearby towers  
  Short_t  mBTOWId;           // projected tower Id 1-4800
  Char_t   mBTOWId23;         // emc 2nd and 3rd closest tower local id  ( 2nd X 10 + 3rd), each id 0-8
  Short_t  mBTOWE1;           // E1*1000 matched (closest) tower E
  Short_t  mBTOWE2;           // E2*1000 2nd closest tower E
  Short_t  mBTOWE3;           // E3*1000 3rd closest tower E
  Short_t  mBTOWDistEta;      // eta*10000 distance between track and matched tower center
  Short_t  mBTOWDistPhi;      // phi*10000 distance between track and matched tower center
#endif

  friend class StPicoDst;

  ClassDef(StPicoTrack, 1)
};

#endif

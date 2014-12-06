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
  StPicoTrack(StMuTrack *, StMuTrack *, float, int, double);
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
  
  // pid traits
  void    setEmcPidTraitsIndex(Int_t index)  { mEmcPidTraitsIndex = (Short_t)index;  }
  Int_t   emcPidTraitsIndex() const          { return (Int_t)mEmcPidTraitsIndex;     }

  void    setBTofPidTraitsIndex(Int_t index) { mBTofPidTraitsIndex = (Short_t)index; }
  Int_t   bTofPidTraitsIndex() const         { return (Int_t)mBTofPidTraitsIndex;    }

  void    setMtdPidTraitsIndex(Int_t index)  { mMtdPidTraitsIndex = (Short_t)index;  }
  Int_t   mtdPidTraitsIndex() const          { return (Int_t)mMtdPidTraitsIndex;     }

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
  UChar_t  mNHitsMapHFT;      // the hit map in all HFT layers

  // pidTraits
  Short_t  mEmcPidTraitsIndex;  // index of the EMC  pidTratis in the event
  Short_t  mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
  Short_t  mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event

  friend class StPicoDst;

  ClassDef(StPicoTrack, 1)
};

#endif

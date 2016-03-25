#ifndef StPicoTrack_h
#define StPicoTrack_h

#include <cmath>

#include "TObject.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StEvent/StDcaGeometry.h"
#include "StarClassLibrary/PhysicalConstants.h"

class StMuTrack;
class StPicoDst;
class StDcaGeometry;


// Macro to control EMC variables
#define EMCON 1

class StPicoTrack : public TObject {
 public:
  StPicoTrack();
  StPicoTrack(StMuTrack const* globalTrack, StMuTrack const* primaryTrack, double magField, StDcaGeometry const*);
  virtual ~StPicoTrack() {}

  // This class doesn't allocate any data on the heap so the default copy ctor
  // and assignment operators are sufficient. The compiler will generate them
  // by default for this class because the destructor is explicitely defined.
  // But please note that this auto-generation feature is deprecated, i.e.
  // it might disappear from future compiler implementations.
  // Explicitely requesting the defaults as done below is the way to go, however
  // it currently doesn't work with STAR version of rootcint which is needed for
  // ROOT I/O on this object.
  //StPicoTrack(StPicoTrack const&) = default;
  //StPicoTrack& operator=(StPicoTrack const&) = default;

  virtual void Print(const Char_t* option = "") const;  ///< Print track info

  Int_t   id() const;
  Float_t chi2() const;
  Float_t gPt() const;
  Float_t gPtot() const;
  StThreeVectorF const& pMom() const;
  StThreeVectorF gMom(StThreeVectorF const& pVtx, float B) const;
  Short_t charge() const;
  Int_t   nHitsFit() const;
  Int_t   nHitsMax() const;
  Int_t   nHitsDedx() const;
  Int_t   nHitsMapHFT() const;
  Float_t dEdx() const;
  Float_t nSigmaPion() const;
  Float_t nSigmaKaon() const;
  Float_t nSigmaProton() const;
  Float_t nSigmaElectron() const;

  UInt_t  map0() const;
  UInt_t  map1() const;

  const Float_t* params() const;
  const Float_t* errMatrix() const;

  StDcaGeometry dcaGeometry() const;
  StPhysicalHelixD helix() const;
  bool isHFTTrack() const;

  // MTD pid traits
  void setEmcPidTraitsIndex(Int_t index);
  void setBTofPidTraitsIndex(Int_t index);
  void setMtdPidTraitsIndex(Int_t index);

  Int_t emcPidTraitsIndex() const;
  Int_t bTofPidTraitsIndex() const;
  Int_t mtdPidTraitsIndex() const;

 protected:
  UShort_t mId;               // track Id
  UShort_t mChi2;             // chi2*1000
  StThreeVectorF mPMomentum;  // primary momentum, (0.,0.,0.) if none
  UShort_t mDedx;             // dEdx*1000
  Char_t   mNHitsFit;         // q*nHitsFit - TPC
  Char_t   mNHitsMax;         // nHitsMax - TPC
  UChar_t  mNHitsDedx;        // nHitsDedx - TPC
  Short_t  mNSigmaPion;       // nsigmaPi * 100
  Short_t  mNSigmaKaon;       // nsigmaK * 100
  Short_t  mNSigmaProton;     // nsigmaP * 100
  Short_t  mNSigmaElectron;   // nsigmaE * 100
  UInt_t   mMap0;             // TopologyMap data0
  UInt_t   mMap1;             // TopologyMap data1

  // a copy of the StMuTrack::dcaGeometry() parameters
  Float_t  mPar[6];
  Float_t  mErrMatrix[15];
  // pidTraits
  Short_t  mEmcPidTraitsIndex;  // index of the EMC  pidTratis in the event
  Short_t  mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
  Short_t  mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event

  ClassDef(StPicoTrack, 1)
};

inline void StPicoTrack::setEmcPidTraitsIndex(Int_t index)  { mEmcPidTraitsIndex = (Short_t)index;  }
inline void StPicoTrack::setBTofPidTraitsIndex(Int_t index) { mBTofPidTraitsIndex = (Short_t)index; }
inline void StPicoTrack::setMtdPidTraitsIndex(Int_t index)  { mMtdPidTraitsIndex = (Short_t)index;  }

inline Int_t   StPicoTrack::id() const                 { return (Int_t)mId; }
inline Float_t StPicoTrack::chi2() const               { return (Float_t)mChi2/1000.; }
inline Float_t StPicoTrack::gPt() const   { return 1./fabs(mPar[3]); }
inline Float_t StPicoTrack::gPtot() const { return gPt()*sqrt(1+mPar[4]*mPar[4]); }
inline StThreeVectorF const& StPicoTrack::pMom() const { return mPMomentum; }
inline Short_t StPicoTrack::charge() const         { return (mNHitsFit>0) ? +1 : -1; }
inline Int_t   StPicoTrack::nHitsFit() const       { return (mNHitsFit>0) ? (Int_t)mNHitsFit : (Int_t)(-1*mNHitsFit); }
inline Int_t   StPicoTrack::nHitsMax() const       { return (Int_t)mNHitsMax; }
inline Int_t   StPicoTrack::nHitsDedx() const      { return (Int_t)mNHitsDedx; }
inline Int_t   StPicoTrack::nHitsMapHFT() const    { return (Int_t)(mMap0 >> 1 & 0x7F); }
inline Float_t StPicoTrack::dEdx() const           { return (Float_t)mDedx/1000.; }
inline Float_t StPicoTrack::nSigmaPion() const     { return (Float_t)mNSigmaPion/100.; }
inline Float_t StPicoTrack::nSigmaKaon() const     { return (Float_t)mNSigmaKaon/100.; }
inline Float_t StPicoTrack::nSigmaProton() const   { return (Float_t)mNSigmaProton/100.; }
inline Float_t StPicoTrack::nSigmaElectron() const { return (Float_t)mNSigmaElectron/100.; }
inline UInt_t  StPicoTrack::map0() const { return (UInt_t)mMap0; }
inline UInt_t  StPicoTrack::map1() const { return (UInt_t)mMap1; }
inline const Float_t* StPicoTrack::params() const     { return mPar; }
inline const Float_t* StPicoTrack::errMatrix() const  { return mErrMatrix; }
inline StPhysicalHelixD StPicoTrack::helix() const { return dcaGeometry().helix(); }
inline bool StPicoTrack::isHFTTrack() const            { return (nHitsMapHFT()>>0 & 0x1) && (nHitsMapHFT()>>1 & 0x3) && (nHitsMapHFT()>>3 & 0x3); }
inline Int_t   StPicoTrack::emcPidTraitsIndex() const  { return (Int_t)mEmcPidTraitsIndex; }
inline Int_t   StPicoTrack::bTofPidTraitsIndex() const { return (Int_t)mBTofPidTraitsIndex; }
inline Int_t   StPicoTrack::mtdPidTraitsIndex() const  { return (Int_t)mMtdPidTraitsIndex; }

inline StDcaGeometry StPicoTrack::dcaGeometry() const
{
  StDcaGeometry a;
  a.set(mPar, mErrMatrix);
  return a;
}

/// Return the global momentum at the dca point to the pVtx (usually it is the primary vertex.   B - magnetic field from PicoEvent::bField()
inline StThreeVectorF StPicoTrack::gMom(StThreeVectorF const& pVtx, float B) const
{
  StPhysicalHelixD gHelix = helix();
  return gHelix.momentumAt(gHelix.pathLength(pVtx), B*kilogauss);
}
#endif

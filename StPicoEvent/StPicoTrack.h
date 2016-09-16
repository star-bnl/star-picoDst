#ifndef StPicoTrack_h
#define StPicoTrack_h

#include <cmath>

#include "TObject.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StPhysicalHelixD.hh"
#include "StarClassLibrary/SystemOfUnits.h"
#include "StEvent/StDcaGeometry.h"

class StMuTrack;
class StDcaGeometry;

class StPicoTrack : public TObject
{
public:
  StPicoTrack();
  StPicoTrack(StMuTrack const* globalTrack, StMuTrack const* primaryTrack, double magField, StThreeVectorD const& pVtx, StDcaGeometry const& dcaG);
  virtual ~StPicoTrack() {}

  virtual void Print(Char_t const* option = "") const;  ///< Print track info

  Int_t   id() const;
  Float_t chi2() const;
  Float_t gPt() const;
  Float_t gPtot() const;
  StThreeVectorF const& pMom() const;
  StThreeVectorF const& gMom() const;
  StThreeVectorF gMom(StThreeVectorF const& pVtx, float B) const;
  StThreeVectorF const& origin() const;
  StThreeVectorF const& dca() const;
  Short_t charge() const;
  Int_t   nHitsFit() const;
  Int_t   nHitsMax() const;
  Int_t   nHitsDedx() const;
  UInt_t  hftHitsMap() const;
  Float_t dEdx() const;
  Float_t nSigmaPion() const;
  Float_t nSigmaKaon() const;
  Float_t nSigmaProton() const;
  Float_t nSigmaElectron() const;

  UInt_t  topologyMap(unsigned int) const;

  StPhysicalHelixD helix(float B) const;
  bool isPxl1() const;
  bool isPxl2() const;
  bool isIst() const;
  bool isSst() const;
  bool isHft() const;
  bool isHFTTrack() const;

  /** Checks whether this track is associated with a primary vertex. */
  bool isPrimary() const;

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
  StThreeVectorF mGMomentum;  // global momentum at dca to primary vertex
  StThreeVectorF mOrigin;     // origin at dca to primary vertex
  Float_t  mDedx;             // dEdx in nominal STAR units: GeV/cm
  Char_t   mNHitsFit;         // q*nHitsFit - TPC
  Char_t   mNHitsMax;         // nHitsMax - TPC
  UChar_t  mNHitsDedx;        // nHitsDedx - TPC
  Char_t   mCharge;
  Short_t  mNSigmaPion;       // nsigmaPi * 100
  Short_t  mNSigmaKaon;       // nsigmaK * 100
  Short_t  mNSigmaProton;     // nsigmaP * 100
  Short_t  mNSigmaElectron;   // nsigmaE * 100
  UInt_t   mTopologyMap[2];   // Toplogy Map data0 and data1. See StEvent/StTrackTopologyMap.cxx

  // pidTraits
  Short_t  mEmcPidTraitsIndex;  // index of the EMC  pidTratis in the event
  Short_t  mBTofPidTraitsIndex; // index of the BTOF pidTratis in the event
  Short_t  mMtdPidTraitsIndex;  // index of the MTD  pidTratis in the event

  ClassDef(StPicoTrack, 1)
};

inline void StPicoTrack::setEmcPidTraitsIndex(Int_t index) { mEmcPidTraitsIndex = (Short_t)index; }
inline void StPicoTrack::setBTofPidTraitsIndex(Int_t index) { mBTofPidTraitsIndex = (Short_t)index; }
inline void StPicoTrack::setMtdPidTraitsIndex(Int_t index) { mMtdPidTraitsIndex = (Short_t)index; }
inline Int_t   StPicoTrack::id() const { return mId; }
inline Float_t StPicoTrack::chi2() const { return mChi2 / 1000.f; }
inline Float_t StPicoTrack::gPt() const { return mGMomentum.perp(); }
inline Float_t StPicoTrack::gPtot() const { return mGMomentum.mag(); }
inline StThreeVectorF const& StPicoTrack::pMom() const { return mPMomentum; }
inline StThreeVectorF const& StPicoTrack::gMom() const { return mGMomentum; }
inline StThreeVectorF const& StPicoTrack::origin() const { return mOrigin; }
inline StThreeVectorF const& StPicoTrack::dca() const { return mOrigin; }
inline Short_t StPicoTrack::charge() const { return static_cast<Short_t>(mCharge); }
inline Int_t   StPicoTrack::nHitsFit() const { return (mNHitsFit > 0) ? (Int_t)mNHitsFit : (Int_t)(-1 * mNHitsFit); }
inline Int_t   StPicoTrack::nHitsMax() const { return mNHitsMax; }
inline Int_t   StPicoTrack::nHitsDedx() const { return mNHitsDedx; }
inline UInt_t  StPicoTrack::hftHitsMap() const { return topologyMap(0) >> 1 & 0x7F; }
inline Float_t StPicoTrack::dEdx() const { return mDedx;}
inline Float_t StPicoTrack::nSigmaPion() const { return mNSigmaPion / 100.f; }
inline Float_t StPicoTrack::nSigmaKaon() const { return mNSigmaKaon / 100.f; }
inline Float_t StPicoTrack::nSigmaProton() const { return mNSigmaProton / 100.f; }
inline Float_t StPicoTrack::nSigmaElectron() const { return mNSigmaElectron / 100.f; }
inline UInt_t  StPicoTrack::topologyMap(unsigned int idx) const { return mTopologyMap[idx]; }
inline Int_t   StPicoTrack::emcPidTraitsIndex() const { return mEmcPidTraitsIndex; }
inline Int_t   StPicoTrack::bTofPidTraitsIndex() const { return mBTofPidTraitsIndex; }
inline Int_t   StPicoTrack::mtdPidTraitsIndex() const { return mMtdPidTraitsIndex; }
inline bool    StPicoTrack::isPxl1() const { return hftHitsMap() >> 0 & 0x1; }
inline bool    StPicoTrack::isPxl2() const { return hftHitsMap() >> 1 & 0x3; }
inline bool    StPicoTrack::isIst()  const { return hftHitsMap() >> 3 & 0x3; }
inline bool    StPicoTrack::isSst()  const { return hftHitsMap() >> 5 & 0x3; }
inline bool    StPicoTrack::isHft() const { return isPxl1() && isPxl2() && (isIst() || isSst()); }
inline bool StPicoTrack::isHFTTrack() const { return isHft(); }

/**
 * The default "primary" momentum is (0, 0, 0) but it is expected to have
 * a non-zero length when the track is associated with a primary vertex.
 */
inline bool StPicoTrack::isPrimary() const
{
  return mPMomentum.magnitude() > 0;
}

/// Return the global momentum at the dca point to the pVtx (usually it is the primary vertex.   B - magnetic field from PicoEvent::bField()
inline StThreeVectorF StPicoTrack::gMom(StThreeVectorF const& pVtx, float const B) const
{
  StPhysicalHelixD gHelix = helix(B);
  return gHelix.momentumAt(gHelix.pathLength(pVtx), B * kilogauss);
}

inline StPhysicalHelixD StPicoTrack::helix(float const B) const
{
  return StPhysicalHelixD(mGMomentum, mOrigin, B * kilogauss, static_cast<float>(charge()));
}
#endif

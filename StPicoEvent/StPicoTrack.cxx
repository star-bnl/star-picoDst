#include <limits>

#include "TMath.h"

#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoTrack.h"


//----------------------------------------------------------------------------------
StPicoTrack::StPicoTrack() : TObject(),
  mId(0),
  mChi2(std::numeric_limits<unsigned short>::max()),
  mPMomentum(0., 0., 0.), mGMomentum(0., 0., 0.), mOrigin(0., 0., 0.), 
  mDedx(0.), /* mDnDx(0.), mDnDxError(0.), */
  mNHitsFit(0), mNHitsMax(0), mNHitsDedx(0),
  mNSigmaPion(std::numeric_limits<short>::max()),
  mNSigmaKaon(std::numeric_limits<short>::max()),
  mNSigmaProton(std::numeric_limits<short>::max()),
  mNSigmaElectron(std::numeric_limits<short>::max()),
  mTopologyMap{}, mBEmcPidTraitsIndex(-1), mBTofPidTraitsIndex(-1), mMtdPidTraitsIndex(-1)
{
}

//----------------------------------------------------------------------------------
void StPicoTrack::Print(Char_t const* option) const
{
  LOG_INFO << "id: " << id()
           << " chi2: " << chi2() << "\n"
           << "pMom: " << pMom()
           << " nHitsFit: " << nHitsFit()
           << " nHitsdEdx: " << nHitsDedx() << "\n"
           << "nSigma pi/K/p/e: " << nSigmaPion()   << "/" << nSigmaKaon() << "/"
           << nSigmaProton() << "/" << nSigmaElectron()
           << endm;
}

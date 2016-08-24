#include <limits>

#include "TMath.h"

#include "StPicoEvent/StPicoTrack.h"
#include "St_base/StMessMgr.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"


//----------------------------------------------------------------------------------
StPicoTrack::StPicoTrack() : TObject(), mId(0), mChi2(std::numeric_limits<unsigned short>::max()),
  mPMomentum(0., 0., 0.), mGMomentum(0., 0., 0.), mOrigin(0., 0., 0.),
  mDedx(0), mNHitsFit(0), mNHitsMax(0), mNHitsDedx(0), mNSigmaPion(std::numeric_limits<short>::max()), mNSigmaKaon(std::numeric_limits<short>::max()),
  mNSigmaProton(std::numeric_limits<short>::max()), mNSigmaElectron(std::numeric_limits<short>::max()),
  mMap0(0), mMap1(0), mEmcPidTraitsIndex(-1), mBTofPidTraitsIndex(-1), mMtdPidTraitsIndex(-1)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
// t - the global track.  p - the associated primary track from the first primary vertex
/////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------
StPicoTrack::StPicoTrack(StMuTrack const* const t, StMuTrack const* const p, double const B, StThreeVectorD const& pVtx, StDcaGeometry const& dcaG)
  : StPicoTrack()
{
  if (!t || t->type() != global || (p && (p->type() != primary || p->id() != t->id())))
  {
    LOG_WARN << " Bad StPicoTrack constructor ...... Check!" << endm;
  }
  else
  {
    mId        = (UShort_t)t->id();
    mChi2      = (t->chi2() * 1000. > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)(TMath::Nint(t->chi2() * 1000.));
    if (p)
    {
      mPMomentum = p->p();
    }

    StPhysicalHelixD gHelix = dcaG.helix();
    gHelix.moveOrigin(gHelix.pathLength(pVtx));
    mGMomentum = gHelix.momentum(B * kilogauss);
    mOrigin = gHelix.origin();

    int q      = t->charge();
    mDedx      = (t->dEdx() * 1e6 * 1000. > std::numeric_limits<unsigned short>::max()) ? 0 : (UShort_t)(TMath::Nint(t->dEdx() * 1e6 * 1000.));
    int flag = t->flag();
    if (flag / 100 < 7) // TPC tracks
    {
      mNHitsFit  = (Char_t)(t->nHitsFit(kTpcId) * q);
      mNHitsMax  = (UChar_t)(t->nHitsPoss(kTpcId));
    }
    else     // FTPC tracks
    {
      if (t->helix().momentum(B * kilogauss).pseudoRapidity() > 0.)
      {
        mNHitsFit  = (Char_t)(t->nHitsFit(kFtpcWestId) * q);
        mNHitsMax  = (UChar_t)(t->nHitsPoss(kFtpcWestId));
      }
      else
      {
        mNHitsFit  = (Char_t)(t->nHitsFit(kFtpcEastId) * q);
        mNHitsMax  = (UChar_t)(t->nHitsPoss(kFtpcEastId));
      }
    }
    mNHitsDedx = (Char_t)(t->nHitsDedx());
    mNSigmaPion     = (fabs(t->nSigmaPion() * 100.)     > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(t->nSigmaPion() * 100.));
    mNSigmaKaon     = (fabs(t->nSigmaKaon() * 100.)     > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(t->nSigmaKaon() * 100.));
    mNSigmaProton   = (fabs(t->nSigmaProton() * 100.)   > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(t->nSigmaProton() * 100.));
    mNSigmaElectron = (fabs(t->nSigmaElectron() * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(t->nSigmaElectron() * 100.));

    mMap0 = (UInt_t)(t->topologyMap().data(0));
    mMap1 = (UInt_t)(t->topologyMap().data(1));
  }
}


StPicoTrack::StPicoTrack(UShort_t id, UShort_t chi2,
   const StThreeVectorF& pMomentum, const StThreeVectorF& gMomentum, const StThreeVectorF& origin,
   UShort_t dedx, Char_t nHitsFit, Char_t nHitsMax, UChar_t nHitsDedx,
   Short_t nSigmaPion, Short_t nSigmaKaon, Short_t nSigmaProton, Short_t nSigmaElectron,
   UInt_t map0, UInt_t map1) : TObject(),
  mId(id),
  mChi2(chi2),
  mPMomentum(pMomentum),
  mGMomentum(gMomentum),
  mOrigin(origin),
  mDedx(dedx),
  mNHitsFit(nHitsFit),
  mNHitsMax(nHitsMax),
  mNHitsDedx(nHitsDedx),
  mNSigmaPion(nSigmaPion),
  mNSigmaKaon(nSigmaKaon),
  mNSigmaProton(nSigmaProton),
  mNSigmaElectron(nSigmaElectron),
  mMap0(map0), mMap1(map1),
  mEmcPidTraitsIndex(-1), mBTofPidTraitsIndex(-1), mMtdPidTraitsIndex(-1)
{}


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

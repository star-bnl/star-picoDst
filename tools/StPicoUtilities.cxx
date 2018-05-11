#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoMtdHit.h"
#include "StPicoEvent/StPicoMtdPidTraits.h"
#include "StPicoEvent/StPicoMtdTrigger.h"
#include "StPicoEvent/StPicoTrack.h"


//class StThreeVectorD;
class StDcaGeometry;
class StMuDst;
class StMuMtdHit;
class StMuMtdPidTraits;
class StMuTrack;



StPicoEvent::StPicoEvent(StMuDst const& muDst)
{ }


StPicoTrack::StPicoTrack(StMuTrack const* const gTrk, StMuTrack const* const pTrk,
  double const B, StThreeVectorD const& pVtx, StDcaGeometry const& dcaG)
{ }


StPicoMtdPidTraits::StPicoMtdPidTraits(const StMuMtdHit*  hit,
                                       const StMuMtdPidTraits* trait,
                                       const Int_t index)
{ }


StPicoMtdTrigger::StPicoMtdTrigger(const StMuDst& muDst, const int QTtoModule[8][8],
                                   const int QTSlewBinEdge[8][16][8],
				   const int QTSlewCorr[8][16][8])
{ }


StPicoBTofPidTraits::StPicoBTofPidTraits(const StMuTrack* gTrack,
    const StMuTrack* pTrack,
    const Int_t idx2PicoTrack)
{ }


StPicoMtdHit::StPicoMtdHit(StMuMtdHit const* hit)
{ }

#include "TClonesArray.h"

#include "StEvent/StTriggerData.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"

#include "StPicoDstMaker/StPicoBbcFiller.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoBbcHit.h"
#include "StPicoEvent/StPicoCommon.h"

using namespace StarPicoDst;


StBeamDirection beam_direction(DetectorSide ew)
{
  return ew == DetectorSide::East ? StBeamDirection::east : StBeamDirection::west;
}


void StPicoBbcFiller::fill(const StMuDst& muDst)
{
  TClonesArray *hitCollection = mPicoDst.picoArray(StPicoArrays::BbcHit);

  StMuEvent *event = muDst.event();
  StTriggerData *trg = const_cast<StTriggerData *>(event->triggerData());

  // Loop over BBC tiles
  for (DetectorSide ew : detectorSides)
  {
    for (int pmtId = 1; pmtId <= 17; pmtId++)
    {
      int ADC = trg->bbcADC(beam_direction(ew), pmtId);
      if (ADC <= 0) continue;
      int TDC = trg->bbcTDC5bit(beam_direction(ew), pmtId);
      int TAC = trg->bbcTDC(beam_direction(ew), pmtId); // yes I know the method says "TDC" but it's the TAC

      int counter = hitCollection->GetEntries();
      new((*hitCollection)[counter]) StPicoBbcHit(pmtId, ew, ADC, TAC, TDC, true, true);
    }
  }
}

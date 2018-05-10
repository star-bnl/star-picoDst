#include "TClonesArray.h"

#include "StEvent/StTriggerData.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"

#include "StPicoDstMaker/StPicoEpdFiller.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEpdHit.h"



void StPicoEpdFiller::fill(const StMuDst& muDst)
{
  TClonesArray *hitCollection = mPicoDst.picoArray(StPicoArrays::EpdHit);

  for (unsigned int i = 0; i < muDst.numberOfEpdHit(); i++)
  {
    StMuEpdHit* aHit = muDst.epdHit(i);

    int counter = hitCollection->GetEntries();
    new( (*hitCollection)[counter] ) StPicoEpdHit(aHit->id(), aHit->qtData(), aHit->nMIP());
  }
}

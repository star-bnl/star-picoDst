#include "TClonesArray.h"

#include "StEvent/StTriggerData.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"

#include "StPicoDstMaker/StPicoBbcFiller.h"
#include "StPicoDstMaker/StPicoDst.h"
#include "StPicoEvent/StPicoBbcTile.h"


StBeamDirection eastwestdir(int ew)
{
  if (ew == 0) return east;

  return west;
};

StPicoBbcFiller::StPicoBbcFiller(StPicoDst& picoDst, int year) :
  mPicoDst(picoDst)
{
}


void StPicoBbcFiller::Fill(const StMuDst& muDst)
{
  TClonesArray *mTileCollection = mPicoDst.picoArray(StPicoArrays::BbcTile);

  StMuEvent *Event = muDst.event();
  StTriggerData *trg = const_cast<StTriggerData *>(Event->triggerData());

  Short_t ADC, TDC, TAC, ID;
  Short_t ntiles = 0;
  Bool_t HasTAC;
  // BBC tiles

  for (Int_t ew = 0; ew < 2; ew++) {
    Short_t sign = ew = 0 ? -1 : +1;

    for (Int_t pmt = 0; pmt < 24; pmt++) {
      ADC = trg->bbcADC(eastwestdir(ew), pmt + 1, 0);
      TAC = trg->bbcTDC(eastwestdir(ew), pmt + 1, 0); // yes I know the method says "TDC" but it's the TAC
      TDC = trg->bbcTDC5bit(eastwestdir(ew), pmt + 1);
      ID = sign * (pmt + 1);
      HasTAC = kTRUE;
      new((*mTileCollection)[ntiles++]) StPicoBbcTile(ID, ADC, TAC, TDC, HasTAC);
    }
  }

}

#include "St_base/StMessMgr.h"
#include "StPicoEvent/StPicoBbcTile.h"

StPicoBbcTile::StPicoBbcTile() : mId(0), mQTdata(0)
{
  /* no-op */
}


StPicoBbcTile::StPicoBbcTile(int ID, int ADC, int TAC, int TDC, bool hasTAC) :
  mId(ID),
  mQTdata( (ADC & 0x0FFF) | (TAC & 0x0FFF) << 12 | (TDC & 0x001F) << 24 | hasTAC << 29 )
{
}


void StPicoBbcTile::setQTdata(Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC)
{
  ULong_t uADC = ADC;
  ULong_t uTDC = TDC;
  ULong_t uTAC = TAC;
  mQTdata = (uADC & 0xFFF) + ((uTAC & 0xFFF) << 12) + ((uTDC & 0x1F) << 24) + (hasTAC ? (1 << 29) : 0);
}

void StPicoBbcTile::Print(const Char_t *option) const
{

  /*  --- this below does not compile so I am skipping it.
      Dmitri, could you put it in?  I guess I am missing
      an include.  I must be missing an include file somewhere
      since even 'endm' is unrecognized when I say 'cons'
  LOG_INFO << " Id = " << mId
     << " ADC = " << this->ADC()
     << " TAC = " << this->TAC()
     << " TDC = " << this->TDC()
     << " - This tile "
     << hasTAC()?"has TAC":"does not have TAC"
     << endm;
  */
}

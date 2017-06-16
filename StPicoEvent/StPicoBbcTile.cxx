#include "St_base/StMessMgr.h"
#include "StPicoEvent/StPicoBbcTile.h"

StPicoBbcTile::StPicoBbcTile() : mId(0), mQTdata(0)
{
  /* no-op */
}

StPicoBbcTile::StPicoBbcTile(Short_t ID, Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC)
{
  mId = ID;
  this->setQTdata(ADC, TAC, TDC, hasTAC);

  /*
    if (ADC!=0) cout << "--------------";
    cout << "Tile being created with ID=" << mId
    << " ADC=" << ADC << " TDC=" << TDC << " TAC=" << TAC << endl;
    cout << "Ampersand gives " << (ADC&0xFFF) << endl;
    cout << "shifing one gives " << (ADC&0xFFF)<<1 << endl;
    cout << "My method says ADC is " << this->adc() << " TDC is " << this->tdc() << " TAC is " << this->tac() << endl;
    cout << "mQTdata is " << mQTdata << endl;
  */
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

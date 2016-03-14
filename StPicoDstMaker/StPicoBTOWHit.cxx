#include <limits>

#include "TMath.h"
#include "St_base/StMessMgr.h"
#include "StPicoBTOWHit.h"

ClassImp(StPicoBTOWHit)

//----------------------------------------------------------------------------------
StPicoBTOWHit::StPicoBTOWHit(): mId(0), mAdc(0), mE(0)
{
}

//----------------------------------------------------------------------------------
StPicoBTOWHit::StPicoBTOWHit(int id, int adc, float e): StPicoBTOWHit()
{
  if(id  <0 || adc <0) return;

  mId   = (id  > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)id;
  mAdc  = (adc > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)adc;
  mE    = (e*1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(e*1000.));
}

//----------------------------------------------------------------------------------
StPicoBTOWHit::~StPicoBTOWHit()
{ /* noop */ }

//----------------------------------------------------------------------------------
void StPicoBTOWHit::Print(const Char_t *option) const {
  LOG_INFO << " Id = " << id() << " Adc = " << adc() << " Energy = " << energy() << endm;
}

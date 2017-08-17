#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoMtdTrigger.h"


//----------------------------------------------------------------------------------
StPicoMtdTrigger::StPicoMtdTrigger():
  mVpdTacSum(0), mTHUBtime{},
  mQTtacSum{}, mMT101Tac{}, mMT101Id{}, mTF201TriggerBit(0),
  mShouldHaveRejectEvent(-1)
{
}


//----------------------------------------------------------------------------------
StPicoMtdTrigger::~StPicoMtdTrigger()
{
}
//----------------------------------------------------------------------------------
void StPicoMtdTrigger::getMaximumQTtac(const Int_t qt, Int_t& pos1, Int_t& pos2)
{
  pos1 = 0;
  pos2 = 0;

  if (qt < 1 || qt > kNQTboard)
  {
    LOG_ERROR << "Wrong qt board number: " << qt << endm;
    return;
  }

  UShort_t max1 = 0, max2 = 0;
  for (Int_t i = 0; i < 8; i++)
  {
    if (max1 < mQTtacSum[qt - 1][i])
    {
      max2 = max1;
      pos2 = pos1;
      max1 = mQTtacSum[qt - 1][i];
      pos1 = i + 1;
    }
    else if (max2 < mQTtacSum[qt - 1][i])
    {
      max2 = mQTtacSum[qt - 1][i];
      pos2 = i + 1;
    }
  }
}

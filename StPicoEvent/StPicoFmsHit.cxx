/***************************************************************************
 *
 * $Id: StPicoFmsHit.h, v0.01 $
 * Author: Peifeng Liu, Stony Brook University, pliuphys@gmail.com
 *
 ***************************************************************************/

#include "StPicoFmsHit.h"
#include "StFmsDbMaker/StFmsDbMaker.h"
StFmsDbMaker* StPicoFmsHit::fmsDbMaker=0;
bool StPicoFmsHit::noFmsDbMaker=0;

void StPicoFmsHit::Print(const Char_t* option) const
{
  LOG_INFO<<"DetectorId = "<<detectorId()
          <<"Channel = "   <<channel()
          <<"ADC = "       <<adc()
          <<endm;
}

StThreeVectorF StPicoFmsHit::starXYZ() const
{
  loadFmsDbMaker();
  if(!fmsDbMaker)
    return StThreeVectorF{};

  const auto c=channel();
  const auto d=detectorId();

  return fmsDbMaker->getStarXYZ(d,c);
}

Float_t StPicoFmsHit::energy() const
{
  loadFmsDbMaker();
  if(!fmsDbMaker)
    return 0.0;

  const auto c=channel();
  const auto d=detectorId();

  return fmsDbMaker->getGain(d,c)*fmsDbMaker->getGainCorrection(d,c)*mAdc;
}

void StPicoFmsHit::loadFmsDbMaker()
{
  if(noFmsDbMaker)
    return;

  if(fmsDbMaker)
    return;

  fmsDbMaker=static_cast<StFmsDbMaker*>(StMaker::GetChain()->GetMaker("fmsDb"));

  if(fmsDbMaker)
    LOG_INFO<<"StPicoFmsHit::loadFmsDbMaker(): found fmsDb"<<endm;
  else{
    LOG_ERROR<<"StPicoFmsHit::loadFmsDbMaker(): failed to get fmsDb!"<<endm;
    noFmsDbMaker=true;
  }
}

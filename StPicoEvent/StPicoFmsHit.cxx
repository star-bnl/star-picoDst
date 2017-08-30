#include <iostream>

#include "StPicoEvent/StPicoFmsHit.h"


/**
 * \author: Peifeng Liu, Stony Brook University, pliuphys@gmail.com
 */
StPicoFmsHit::StPicoFmsHit() : TObject(), mChannelDetectorId(0), mAdc(0)
{
}


StPicoFmsHit::StPicoFmsHit(int detectorId, int channelId, int adc) :
  TObject(),
  mChannelDetectorId(32*channelId + detectorId),
  mAdc(adc)
{
}


void StPicoFmsHit::Print(const Char_t *option) const
{
  std::cout << " FMS hit -"
            << " detectorId: " << detectorId()
            << " channel: " << channel()
            << " ADC: " << adc()
            << "\n";
}

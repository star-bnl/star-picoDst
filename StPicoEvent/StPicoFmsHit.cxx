

/**
 * \author: Peifeng Liu, Stony Brook University, pliuphys@gmail.com
 */

#include "StPicoFmsHit.h"

void StPicoFmsHit::Print(const Char_t *option) const
{
  LOG_INFO << "DetectorId = " << detectorId()
           << "Channel = "   << channel()
           << "ADC = "       << adc()
           << endm;
}

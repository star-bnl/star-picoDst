/***************************************************************************
 *
 * $Id: StPicoFmsHit.h, v0.01 $
 * Author: Peifeng Liu, Stony Brook University, pliuphys@gmail.com
 *
 ***************************************************************************/

#ifndef StPicoFmsHit_hh
#define StPicoFmsHit_hh

#include "TObject.h"

#include "StarClassLibrary/StThreeVectorF.hh"


class StPicoFmsHit:public TObject{
 public:
  StPicoFmsHit()
  {
    set(0,0,0);
  }

  StPicoFmsHit(UShort_t detectorId, UShort_t channel, UShort_t adc)
  {
    set(detectorId,channel,adc);
  }

  virtual ~StPicoFmsHit(){}

  void Print(const Char_t* option="") const;

  void set(UShort_t detectorId, UShort_t channel, UShort_t adc)
  {
    encodeDetectorIdChannel(detectorId,channel);
    mAdc=adc;
  }

  void encodeDetectorIdChannel(UShort_t detectorId, UShort_t channel)
  {
    mChannelDetectorId=32*channel+detectorId;
  }

  UShort_t detectorId() const
  {
    return mChannelDetectorId%32;
  }
  UShort_t channel() const
  {
    return mChannelDetectorId/32;
  }
  UShort_t adc() const
  {
    return mAdc;
  }

 private:
  UShort_t mChannelDetectorId;//32*channel+detectorId. Allow channel 0-2047, detectorId 0-31.
  UShort_t mAdc;

  ClassDef(StPicoFmsHit,1)
};

#endif

#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoBTofPidTraits.h"


//----------------------------------------------------------------------------------
StPicoBTofPidTraits::StPicoBTofPidTraits() :
  mTrackIndex(-1),
  mBTofCellId(-1), mBTofMatchFlag(-1),
  mBTof(0), mBTofBeta(0),
  mBTofYLocal(-999), mBTofZLocal(-999),
  mBTofHitPosX(-999), mBTofHitPosY(-999), mBTofHitPosZ(-999)
{
  // constructor
}


//----------------------------------------------------------------------------------
StPicoBTofPidTraits::~StPicoBTofPidTraits()
{
  // destructor
}

//----------------------------------------------------------------------------------
void StPicoBTofPidTraits::Print(const Char_t* option) const
{
  LOG_INFO << " Matched track index = " << mTrackIndex << endm;
  LOG_INFO << " BTOF cellId = " << btofCellId() << " tof = " << btof() << " beta = " << btofBeta() << endm;
  LOG_INFO << " BTOF match = " << btofMatchFlag() << " yLocal/zLocal " << btofYLocal() << " " << btofZLocal() << endm;
}

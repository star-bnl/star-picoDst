#include <limits>

#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoMtdPidTraits.h"


//----------------------------------------------------------------------------------
StPicoMtdPidTraits::StPicoMtdPidTraits() : TObject(),
  mTrackIndex(-1), mMtdHitIndex(-1), mMatchFlag(-1),
  mDeltaY(-999.), mDeltaZ(-999.), mDeltaTimeOfFlight(-999.), mBeta(-999.), mMtdHitChan(-1)
{
  // constructor
}

//----------------------------------------------------------------------------------
StPicoMtdPidTraits::~StPicoMtdPidTraits()
{
  // dummy destructor
}
//----------------------------------------------------------------------------------
void StPicoMtdPidTraits::Print(const Char_t* option) const
{
  LOG_INFO << "Matched hit: backleg =  " << backleg()
           << ", module  = " << module()
           << ", cell    = " << cell()
           << endm;
  LOG_INFO << "Matched track index = " << mTrackIndex << endm;
  LOG_INFO << "(DeltaY, DeltaZ, DeltaTOF, beta) = ("
           << mDeltaY << ", "
           << mDeltaZ << ", "
           << mDeltaTimeOfFlight << ", "
           << mBeta << ")" << endm;
}

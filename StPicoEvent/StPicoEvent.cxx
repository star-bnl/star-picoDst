#include <algorithm>
#include <limits>
#include "StPicoEvent/StPicoEvent.h"


StPicoEvent::StPicoEvent():
  mRunId(0), mEventId(0), mFillId(0), mBField(0), mTime(0),
  mPrimaryVertex{ -999., -999., -999.}, mPrimaryVertexError{ -999., -999., -999},
  mRanking(-999), mNBEMCMatch(0), mNBTOFMatch(0),
  mTriggerIds{},
  mRefMultFtpcEast(0), mRefMultFtpcWest(0),
  mRefMultNeg(0), mRefMultPos(0),
  mRefMult2NegEast(0), mRefMult2PosEast(0), mRefMult2NegWest(0), mRefMult2PosWest(0),
  mRefMult3NegEast(0), mRefMult3PosEast(0), mRefMult3NegWest(0), mRefMult3PosWest(0),
  mRefMult4NegEast(0), mRefMult4PosEast(0), mRefMult4NegWest(0), mRefMult4PosWest(0),
  mRefMultHalfNegEast(0), mRefMultHalfPosEast(0), mRefMultHalfNegWest(0), mRefMultHalfPosWest(0),
  mGRefMult(0), mNumberOfGlobalTracks(0), mbTofTrayMultiplicity(0), mNHitsHFT{},
  mNVpdHitsEast(0), mNVpdHitsWest(0), mNTofT0(0), mVzVpd(-999.),
  mZDCx(0), mBBCx(0), mBackgroundRate(0), mBbcBlueBackgroundRate(0), mBbcYellowBackgroundRate(0),
  mBbcEastRate(0), mBbcWestRate(0), mZdcEastRate(0), mZdcWestRate(0),
  mZdcSumAdcEast(0), mZdcSumAdcWest(0),
  mZdcSmdEastHorizontal{}, mZdcSmdEastVertical{}, mZdcSmdWestHorizontal{}, mZdcSmdWestVertical{},
  mBbcAdcEast{}, mBbcAdcWest{},
  mHighTowerThreshold{}, mJetPatchThreshold{}
{}


StPicoEvent::~StPicoEvent()
{ }

int StPicoEvent::year() const
{
  return mRunId / 1000000 - 1 + 2000;
}

int StPicoEvent::day() const
{
  return (mRunId % 1000000) / 1000;
}

bool StPicoEvent::isTrigger(unsigned int id) const
{
  return std::find(mTriggerIds.begin(), mTriggerIds.end(), id) != mTriggerIds.end();
}

#include <algorithm>
#include <limits>
#include "StEvent/StEventTypes.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StEvent/StBTofHeader.h"
#include "St_base/StMessMgr.h"
#include "StPicoUtilities.h"
#include "StPicoEvent.h"

ClassImp(StPicoEvent)

StPicoEvent::StPicoEvent():
 mRunId(0), mEventId(0), mFillId(0), mBField(0),
 mPrimaryVertex{-999.,-999.,-999.}, mPrimaryVertexError{-999.,-999.,-999},
 mRanking(-999), mNBEMCMatch(0), mNBTOFMatch(0),
 mTriggerIds{},
 mRefMultFtpcEast(0), mRefMultFtpcWest(0),
 mRefMultNeg(0), mRefMultPos(0),
 mRefMult2NegEast(0), mRefMult2PosEast(0), mRefMult2NegWest(0), mRefMult2PosWest(0),
 mRefMultHalfNegEast(0), mRefMultHalfPosEast(0), mRefMultHalfNegWest(0), mRefMultHalfPosWest(0),
 mGRefMult(0), mNumberOfGlobalTracks(0), mbTofTrayMultiplicity(0), mNHitsHFT{},
 mNVpdHitsEast(0), mNVpdHitsWest(0), mNT0(0), mVzVpd(std::numeric_limits<short>::max()),
 mZDCx(0), mBBCx(0), mBackgroundRate(0), mBbcBlueBackgroundRate(0), mBbcYellowBackgroundRate(0),
 mBbcEastRate(0), mBbcWestRate(0), mZdcEastRate(0), mZdcWestRate(0),
 mZdcSumAdcEast(0), mZdcSumAdcWest(0),
 mZdcSmdEastHorizontal{}, mZdcSmdEastVertical{}, mZdcSmdWestHorizontal{}, mZdcSmdWestVertical{},
 mBbcAdcEast{}, mBbcAdcWest{},
 mHT_Th{}
{}

StPicoEvent::StPicoEvent(const StMuDst& muDst) : StPicoEvent()
{
  StMuEvent* ev = muDst.event() ;

  mRunId = ev->runNumber();
  mEventId = ev->eventNumber();
  mFillId = ev->runInfo().beamFillNumber(blue);
  mBField=ev->magneticField();

  mPrimaryVertex = ev->primaryVertexPosition();
  mPrimaryVertexError = ev->primaryVertexErrors();
  if( mPrimaryVertex.x()==mPrimaryVertex.y() && mPrimaryVertex.y()==mPrimaryVertex.z() )
  {
    mPrimaryVertex.set(-999.,-999.,-999.);
    mPrimaryVertexError.set(0.,0.,0);
  }

  if(StMuPrimaryVertex* pv = muDst.primaryVertex())
  {
    mRanking = pv->ranking();
    mNBEMCMatch = pv->nBEMCMatch();
    mNBTOFMatch = pv->nBTOFMatch();
  }

  mTriggerIds = ev->triggerIdCollection().nominal().triggerIds();

  mRefMultFtpcEast = (UShort_t)(ev->refMultFtpcEast());
  mRefMultFtpcWest = (UShort_t)(ev->refMultFtpcWest());
  mRefMultNeg = (UShort_t)(ev->refMultNeg());
  mRefMultPos = (UShort_t)(ev->refMultPos());
  mRefMult2NegEast = (UShort_t)StPicoUtilities::refMult2(0, 0, muDst);
  mRefMult2PosEast = (UShort_t)StPicoUtilities::refMult2(1, 0, muDst);
  mRefMult2NegWest = (UShort_t)StPicoUtilities::refMult2(0, 1, muDst);
  mRefMult2PosWest = (UShort_t)StPicoUtilities::refMult2(1, 1, muDst);
  mRefMultHalfNegEast = (UShort_t)StPicoUtilities::refMultHalf(0, 0, muDst);
  mRefMultHalfPosEast = (UShort_t)StPicoUtilities::refMultHalf(1, 0, muDst);
  mRefMultHalfNegWest = (UShort_t)StPicoUtilities::refMultHalf(0, 1, muDst);
  mRefMultHalfPosWest = (UShort_t)StPicoUtilities::refMultHalf(1, 1, muDst);

  mGRefMult = (UShort_t)ev->grefmult();
  mNumberOfGlobalTracks = muDst.numberOfGlobalTracks();
  mbTofTrayMultiplicity = ev->btofTrayMultiplicity() ;
  mNHitsHFT[0] = (UShort_t)ev->numberOfPxlInnerHits();
  mNHitsHFT[1] = (UShort_t)ev->numberOfPxlOuterHits();
  mNHitsHFT[2] = (UShort_t)ev->numberOfIstHits();
  mNHitsHFT[3] = (UShort_t)ev->numberOfSsdHits();

  if(StBTofHeader* header = muDst.btofHeader())
  {
    mNVpdHitsEast = (UChar_t)(header->numberOfVpdHits(east));
    mNVpdHitsWest = (UChar_t)(header->numberOfVpdHits(west));
    mNT0 = (UShort_t)(header->nTzero());
    mVzVpd = (fabs(header->vpdVz()*100.)>std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(header->vpdVz()*100.));
  }

  mZDCx = (UInt_t)ev->runInfo().zdcCoincidenceRate();
  mBBCx = (UInt_t)ev->runInfo().bbcCoincidenceRate();
  mBackgroundRate = ev->runInfo().backgroundRate();
  mBbcBlueBackgroundRate = ev->runInfo().bbcBlueBackgroundRate();
  mBbcYellowBackgroundRate = ev->runInfo().bbcYellowBackgroundRate();
  mBbcEastRate = ev->runInfo().bbcEastRate();
  mBbcWestRate = ev->runInfo().bbcWestRate();
  mZdcEastRate = ev->runInfo().zdcEastRate();
  mZdcWestRate = ev->runInfo().zdcWestRate();

  StZdcTriggerDetector& ZDC = ev->zdcTriggerDetector();
  mZdcSumAdcEast = (UShort_t)ZDC.adcSum(east);
  mZdcSumAdcWest = (UShort_t)ZDC.adcSum(west);
  for (int strip=1;strip<9;++strip)
  {
    if (ZDC.zdcSmd(east,1,strip))
      mZdcSmdEastHorizontal[strip-1] = (UShort_t)ZDC.zdcSmd(east,1,strip);
    if (ZDC.zdcSmd(east,0,strip))
      mZdcSmdEastVertical[strip-1] = (UShort_t)ZDC.zdcSmd(east,0,strip);
    if (ZDC.zdcSmd(west,1,strip))
      mZdcSmdWestHorizontal[strip-1] = (UShort_t)ZDC.zdcSmd(west,1,strip);
    if (ZDC.zdcSmd(west,0,strip))
      mZdcSmdWestVertical[strip-1] = (UShort_t)ZDC.zdcSmd(west,0,strip);
  }

  StBbcTriggerDetector bbc = ev->bbcTriggerDetector() ;
  for(UInt_t i=0;i<bbc.numberOfPMTs();++i)
  {
    const UInt_t eastWest = (i<24) ? 0 : 1 ; // East:0-23, West:24-47
    const UInt_t pmtId    = i%24 ;           // pmtId:0-23

    if( eastWest == 0 ) mBbcAdcEast[pmtId] = bbc.adc(i) ;
    else                mBbcAdcWest[pmtId] = bbc.adc(i) ;
  }
}

StPicoEvent::~StPicoEvent()
{ }

int StPicoEvent::year() const
{
  return mRunId/1000000 - 1 + 2000;
}

int StPicoEvent::day() const
{
  return (mRunId%1000000)/1000;
}

bool StPicoEvent::isTrigger(unsigned int id) const
{
  return std::find(mTriggerIds.begin(), mTriggerIds.end(), id) != mTriggerIds.end();
}

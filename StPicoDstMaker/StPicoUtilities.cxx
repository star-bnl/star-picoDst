#include <bitset>
#include <limits>

#include "StPicoDstMaker/StPicoUtilities.h"

#include "St_base/StMessMgr.h"
#include "StarClassLibrary/StPhysicalHelixD.hh"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StEvent/StEventTypes.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StDcaGeometry.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuMtdHeader.h"
#include "StMuDSTMaker/COMMON/StMuMtdHit.h"
#include "StMuDSTMaker/COMMON/StMuMtdPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

#include "StPicoEvent/StPicoBTofPidTraits.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StPicoEvent/StPicoMtdHit.h"
#include "StPicoEvent/StPicoMtdPidTraits.h"
#include "StPicoEvent/StPicoMtdTrigger.h"
#include "StPicoEvent/StPicoTrack.h"



namespace StPicoUtilities
{

/**
 * Return the global momentum at the dca point to the pVtx (usually it is the
 * primary vertex.
 *
 * param[in]   B   magnetic field from PicoEvent::bField()
 */
StThreeVectorF trackMomentumAt(const StPicoTrack& picoTrack, StThreeVectorF const& pVtx, float const B)
{
  StPhysicalHelixD helix = makePhysicalHelix(picoTrack, B);
  return helix.momentumAt(helix.pathLength(pVtx), B * 1e-14);
}


/**
 * Expects magnetic field in kiloGauss'es
 */
StPhysicalHelixD makePhysicalHelix(const StPicoTrack& picoTrack, float const B)
{
  // StPhysicalHelixD expects magnetic field in GeV*s/cm^2
  // 1 kiloGauss = 10^-14 GeV*s/cm^2
  return StPhysicalHelixD(picoTrack.gMom(), picoTrack.origin(), B * 1e-14, static_cast<float>(picoTrack.charge()));
}

}



StPicoEvent::StPicoEvent(StMuDst const& muDst) : StPicoEvent()
{
  StMuEvent* ev = muDst.event() ;

  mRunId = ev->runNumber();
  mEventId = ev->eventNumber();
  mFillId = ev->runInfo().beamFillNumber(blue);
  mBField = ev->magneticField();

  mTime=ev->eventInfo().time();

  mPrimaryVertex = ev->primaryVertexPosition();
  mPrimaryVertexError = ev->primaryVertexErrors();

  if (StMuPrimaryVertex* pv = muDst.primaryVertex())
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

  {
    using namespace StPicoUtilities;
    auto custom_refMult = StPicoUtilities::calculateRefMult(muDst);
    mRefMult2NegEast = custom_refMult[RefMult2NegEast];
    mRefMult2PosEast = custom_refMult[RefMult2PosEast];
    mRefMult2NegWest = custom_refMult[RefMult2NegWest];
    mRefMult2PosWest = custom_refMult[RefMult2PosWest];
    mRefMult3NegEast = custom_refMult[RefMult3NegEast];
    mRefMult3PosEast = custom_refMult[RefMult3PosEast];
    mRefMult3NegWest = custom_refMult[RefMult3NegWest];
    mRefMult3PosWest = custom_refMult[RefMult3PosWest];
    mRefMult4NegEast = custom_refMult[RefMult4NegEast];
    mRefMult4PosEast = custom_refMult[RefMult4PosEast];
    mRefMult4NegWest = custom_refMult[RefMult4NegWest];
    mRefMult4PosWest = custom_refMult[RefMult4PosWest];
    mRefMultHalfNegEast = custom_refMult[RefMultHalfNegEast];
    mRefMultHalfPosEast = custom_refMult[RefMultHalfPosEast];
    mRefMultHalfNegWest = custom_refMult[RefMultHalfNegWest];
    mRefMultHalfPosWest = custom_refMult[RefMultHalfPosWest];
  }

  mGRefMult = (UShort_t)ev->grefmult();
  mNumberOfGlobalTracks = muDst.numberOfGlobalTracks();
  mbTofTrayMultiplicity = ev->btofTrayMultiplicity() ;
  mNHitsHFT[0] = (UShort_t)ev->numberOfPxlInnerHits();
  mNHitsHFT[1] = (UShort_t)ev->numberOfPxlOuterHits();
  mNHitsHFT[2] = (UShort_t)ev->numberOfIstHits();
  mNHitsHFT[3] = (UShort_t)ev->numberOfSsdHits();

  if (StBTofHeader* header = muDst.btofHeader())
  {
    mNVpdHitsEast = (UChar_t)(header->numberOfVpdHits(east));
    mNVpdHitsWest = (UChar_t)(header->numberOfVpdHits(west));
    mNTofT0 = (UShort_t)(header->nTzero());
    mVzVpd = header->vpdVz();
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
  for (int strip = 1; strip < 9; ++strip)
  {
    if (ZDC.zdcSmd(east, 1, strip))
      mZdcSmdEastHorizontal[strip - 1] = (UShort_t)ZDC.zdcSmd(east, 1, strip);
    if (ZDC.zdcSmd(east, 0, strip))
      mZdcSmdEastVertical[strip - 1] = (UShort_t)ZDC.zdcSmd(east, 0, strip);
    if (ZDC.zdcSmd(west, 1, strip))
      mZdcSmdWestHorizontal[strip - 1] = (UShort_t)ZDC.zdcSmd(west, 1, strip);
    if (ZDC.zdcSmd(west, 0, strip))
      mZdcSmdWestVertical[strip - 1] = (UShort_t)ZDC.zdcSmd(west, 0, strip);
  }

  StBbcTriggerDetector bbc = ev->bbcTriggerDetector() ;
  for (UInt_t i = 0; i < bbc.numberOfPMTs(); ++i)
  {
    UInt_t const eastWest = (i < 24) ? 0 : 1 ; // East:0-23, West:24-47
    UInt_t const pmtId    = i % 24 ;         // pmtId:0-23

    if (eastWest == 0) mBbcAdcEast[pmtId] = bbc.adc(i) ;
    else               mBbcAdcWest[pmtId] = bbc.adc(i) ;
  }
}



StPicoTrack::StPicoTrack(StMuTrack const* const gTrk, StMuTrack const* const pTrk, double const B, StThreeVectorD const& pVtx, StDcaGeometry const& dcaG)
  : StPicoTrack()
{
  if (!gTrk || gTrk->type() != global || (pTrk && (pTrk->type() != primary || pTrk->id() != gTrk->id())))
  {
    LOG_WARN << "Invalid arguments passed to StPicoTrack constructor. Object is default initialized" << endm;

    return;
  }

  mId   = (UShort_t)gTrk->id();
  mChi2 = (gTrk->chi2() * 1000. > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)(TMath::Nint(gTrk->chi2() * 1000.));

  if (pTrk)
  {
    mPMomentum = pTrk->p();
  }

  /// Calculate global momentum and position at point of DCA to the pVtx
  StPhysicalHelixD gHelix = dcaG.helix();
  gHelix.moveOrigin(gHelix.pathLength(pVtx));
  mGMomentum = gHelix.momentum(B * 1e-14);
  mOrigin = gHelix.origin();

  mDedx      = gTrk->dEdx() * 1.e6;
  //mDnDx      = gTrk->probPidTraits().dNdxFit();
  //mDnDxError = gTrk->probPidTraits().dNdxErrorFit();

  int flag = gTrk->flag();
  if (flag / 100 < 7) // TPC tracks
  {
    mNHitsFit  = (Char_t)(gTrk->nHitsFit(kTpcId) * gTrk->charge());
    mNHitsMax  = (UChar_t)(gTrk->nHitsPoss(kTpcId));
  }
  else     // FTPC tracks
  {
    if (gTrk->helix().momentum(B * 1e-14).pseudoRapidity() > 0.)
    {
      mNHitsFit  = (Char_t)(gTrk->nHitsFit(kFtpcWestId) * gTrk->charge());
      mNHitsMax  = (UChar_t)(gTrk->nHitsPoss(kFtpcWestId));
    }
    else
    {
      mNHitsFit  = (Char_t)(gTrk->nHitsFit(kFtpcEastId) * gTrk->charge());
      mNHitsMax  = (UChar_t)(gTrk->nHitsPoss(kFtpcEastId));
    }
  }
  mNHitsDedx = (UChar_t)(gTrk->nHitsDedx());
  mNSigmaPion     = (fabs(gTrk->nSigmaPion() * 100.)     > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrk->nSigmaPion() * 100.));
  mNSigmaKaon     = (fabs(gTrk->nSigmaKaon() * 100.)     > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrk->nSigmaKaon() * 100.));
  mNSigmaProton   = (fabs(gTrk->nSigmaProton() * 100.)   > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrk->nSigmaProton() * 100.));
  mNSigmaElectron = (fabs(gTrk->nSigmaElectron() * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrk->nSigmaElectron() * 100.));

  mTopologyMap[0] = (UInt_t)(gTrk->topologyMap().data(0));
  mTopologyMap[1] = (UInt_t)(gTrk->topologyMap().data(1));
}



StPicoMtdPidTraits::StPicoMtdPidTraits(const StMuMtdHit*  hit,
                                       const StMuMtdPidTraits* trait,
                                       const Int_t index):
  mTrackIndex((Short_t)index),
  mMtdHitIndex(-1),
  mMatchFlag((Char_t) trait->matchFlag()),
  mDeltaY(trait->deltaY()),
  mDeltaZ(trait->deltaZ()),
  mDeltaTimeOfFlight(trait->timeOfFlight() - trait->expTimeOfFlight()),
  mBeta((trait->pathLength() / trait->expTimeOfFlight()) / 29.9792458 ), // c_light in cm/s
  mMtdHitChan(-1)
{
  Int_t gchan = (hit->backleg() - 1) * 60 + (hit->module() - 1) * 12 + hit->cell();
  mMtdHitChan = (gchan > std::numeric_limits<short>::max()) ? -1 : (Short_t) gchan;
}



StPicoMtdTrigger::StPicoMtdTrigger(const StMuDst& muDst, const int QTtoModule[8][8],
                                   const int QTSlewBinEdge[8][16][8], const int QTSlewCorr[8][16][8]): StPicoMtdTrigger()
{
  // Header information
  StMuMtdHeader* muMtdHeader = muDst.mtdHeader();
  if (muMtdHeader)
  {
    mTHUBtime[0] = 25 * (muMtdHeader->triggerTime(1) & 0xfff);
    mTHUBtime[1] = 25 * (muMtdHeader->triggerTime(2) & 0xfff);
    mShouldHaveRejectEvent = (Char_t)(muMtdHeader->shouldHaveRejectEvent());
  }

  // RHIC year
  const int runnumber = muDst.event()->runNumber();
  int year = runnumber / 1e6 + 1999;
  // Oct. 1st (approx. 273rd day) is the start of a new running year
  if ((runnumber % 1000000) / 1000 >= 273) year += 1;

  // Trigger data
  UShort_t mtd_qt_tac_min = 100;
  if (runnumber >= 16045067) mtd_qt_tac_min = 80;
  if (runnumber >= 18070005) mtd_qt_tac_min = 200; // change due to new boards
  UShort_t mtd_qt_tac_diff_range_abs = 600;
  if (year == 2015) mtd_qt_tac_diff_range_abs = 1023;

  StTriggerData* trigger = const_cast<StTriggerData*>(muDst.event()->triggerData());
  if (trigger)
  {
    // VPD tac sum
    mVpdTacSum = trigger->vpdEarliestTDCHighThr(east) + trigger->vpdEarliestTDCHighThr(west);

    // QT information
    UShort_t mtdQTadc[kNQTboard][16];
    UShort_t mtdQTtac[kNQTboard][16];
    memset(mtdQTadc, 0, sizeof(mtdQTadc));
    memset(mtdQTtac, 0, sizeof(mtdQTtac));

    for (Int_t i = 0; i < 32; i++)
    {
      Int_t type = (i / 4) % 2;
      if(year<=2015) {
        if (type == 1) {
          mtdQTtac[0][i - i / 4 * 2 - 2] = trigger->mtdAtAddress(i, 0);
          mtdQTtac[1][i - i / 4 * 2 - 2] = trigger->mtdgemAtAddress(i, 0);
          mtdQTtac[2][i - i / 4 * 2 - 2] = trigger->mtd3AtAddress(i, 0);
          mtdQTtac[3][i - i / 4 * 2 - 2] = trigger->mtd4AtAddress(i, 0);
        }
        else
        {
          mtdQTadc[0][i - i / 4 * 2] = trigger->mtdAtAddress(i, 0);
          mtdQTadc[1][i - i / 4 * 2] = trigger->mtdgemAtAddress(i, 0);
          mtdQTadc[2][i - i / 4 * 2] = trigger->mtd3AtAddress(i, 0);
          mtdQTadc[3][i - i / 4 * 2] = trigger->mtd4AtAddress(i, 0);
        }
      }
      else {
        for (int im = 0; im < kNQTboard; im++) {
	  if (year != 2016 && im>=4) continue;
          if (type == 0) mtdQTadc[im][i - i / 4 * 2] = trigger->mtdQtAtCh(im + 1, i, 0);
          else        mtdQTtac[im][i - i / 4 * 2 - 2] = trigger->mtdQtAtCh(im + 1, i, 0);
        }
      }
    }

    Int_t j[2], a[2];
    for (Int_t im = 0; im < kNQTboard; im++)
    {
      for (int i = 0; i < 8; i++)
      {
        if (year == 2016 && i % 2 == 0) // moniter channel only used for Run16
        {
          mQTtacSum[im][i] = 0;
          continue;
        }

        // Apply slewing correction
        for (int k = 0; k < 2; k++)
        {
          j[k] = mtdQTtac[im][i * 2 + k];
          a[k] = mtdQTadc[im][i * 2 + k];

          int slew_bin = -1;
          if (a[k] > 0 && a[k] <= QTSlewBinEdge[im][i * 2 + k][0]) slew_bin = 0;
          else
          {
            for (int l = 1; l < 8; l++)
            {
              if (a[k] > QTSlewBinEdge[im][i * 2 + k][l - 1] && a[k] <= QTSlewBinEdge[im][i * 2 + k][l])
              {
                slew_bin = l;
                break;
              }
            }
          }
          if (slew_bin >= 0)
            j[k] += QTSlewCorr[im][i * 2 + k][slew_bin];
        }

        if (j[0] <= mtd_qt_tac_min || j[0] >= mtd_qt_tac_max ||
            j[1] <= mtd_qt_tac_min || j[1] >= mtd_qt_tac_max ||
            TMath::Abs(j[0] - j[1]) >= mtd_qt_tac_diff_range_abs) // no "equal" in online algorithm
        {
          mQTtacSum[im][i] = 0;
          continue;
        }

        // Apply position correction
        int module = QTtoModule[im][i];
        if(module<0)
        {
          mQTtacSum[im][i] = 0;
          continue;
        }
        mQTtacSum[im][i] = UShort_t( j[0] + j[1] + abs(module-3)*1./8 * (j[0]-j[1]) );
      }
    }

    // MT101
    for (Int_t i = 0; i < kNQTboard; i++)
    {
      int idx = 0;
      if(year==2016) idx = i / 2 * 3 + i % 2 * 16;
      else           idx = i * 3;
      mMT101Tac[i][0] = (trigger->mtdDsmAtCh(idx, 0)) + ((trigger->mtdDsmAtCh(idx + 1, 0) & 0x3) << 8);
      mMT101Id[i][0]  = (trigger->mtdDsmAtCh(idx + 1, 0) & 0xc) >> 2;
      mMT101Tac[i][1] = (trigger->mtdDsmAtCh(idx + 1, 0) >> 4) + ((trigger->mtdDsmAtCh(idx + 2, 0) & 0x3f) << 4);
      mMT101Id[i][1]  = (trigger->mtdDsmAtCh(idx + 2, 0) & 0xc0) >> 6;
    }

    // TF201
    UInt_t decision = trigger->dsmTF201Ch(0);
    UInt_t decision2 = 0;
    if (year == 2016) decision2 = trigger->dsmTF201Ch(6);
    mTF201TriggerBit = 0;

    for (Int_t i = 0; i < 4; i++)
    {
      for (Int_t j = 0; j < 2; j++)
      {
        if (year == 2016)
        {
          int qt = i * 2;
          mTF201TriggerBit |= ((decision >> (i * 2 + j + 4)) & 0x1) << (qt * 2 + j);
          qt = i * 2 + 1;
          mTF201TriggerBit |= ((decision2 >> (i * 2 + j + 4)) & 0x1) << (qt * 2 + j);
        }
        else
        {
          int qt = i;
          mTF201TriggerBit |= ((decision >> (i * 2 + j + 4)) & 0x1) << (qt * 2 + j);
        }
      }
    }

    LOG_DEBUG << "input1 = " << (std::bitset<16>) decision << "\n"
              << "input2 = " << (std::bitset<16>) decision2 << "\n"
              << "output = " << (std::bitset<16>) mTF201TriggerBit
              << endm;
  }
}



StPicoBTofPidTraits::StPicoBTofPidTraits(const StMuTrack* gTrack,
    const StMuTrack* pTrack,
    const Int_t idx2PicoTrack): StPicoBTofPidTraits()
{
  mTrackIndex = (idx2PicoTrack > std::numeric_limits<short>::max()) ? -1 : (Short_t)idx2PicoTrack;

  StMuBTofHit* btofHit = (StMuBTofHit*)gTrack->tofHit();
  Int_t tray         = btofHit->tray();
  Int_t module       = btofHit->module();
  Int_t cell         = btofHit->cell();
  Float_t tof        = gTrack->btofPidTraits().timeOfFlight();
  Float_t beta       = (pTrack) ? pTrack->btofPidTraits().beta() : -999.;
  StThreeVectorF pos = gTrack->btofPidTraits().position();

  mBTofCellId  = (Short_t)((tray - 1) * 192 + (module - 1) * 6 + (cell - 1));
  mBTofMatchFlag = (UChar_t)(gTrack->btofPidTraits().matchFlag());
  if (tof < 0)
  {
    mBTof = 0;
  }
  else
  {
    mBTof = (tof * 1000. > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)(TMath::Nint(tof * 1000.));
  }
  if (beta < 0)
  {
    mBTofBeta = 0;
  }
  else
  {
    mBTofBeta = (beta * 20000. > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)(TMath::Nint(beta * 20000.));
  }
  mBTofHitPosX = (fabs(pos.x() * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(pos.x() * 100.));
  mBTofHitPosY = (fabs(pos.y() * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(pos.y() * 100.));
  mBTofHitPosZ = (fabs(pos.z() * 100.) > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(pos.z() * 100.));
  mBTofYLocal  = (fabs(gTrack->btofPidTraits().yLocal()) * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrack->btofPidTraits().yLocal() * 1000.));
  mBTofZLocal  = (fabs(gTrack->btofPidTraits().zLocal()) * 1000. > std::numeric_limits<short>::max()) ? std::numeric_limits<short>::max() : (Short_t)(TMath::Nint(gTrack->btofPidTraits().zLocal() * 1000.));
}



StPicoMtdHit::StPicoMtdHit(StMuMtdHit const* hit): StPicoMtdHit()
{
  Int_t gchan = (hit->backleg() - 1) * 60 + (hit->module() - 1) * 12 + hit->cell();

  if (gchan < std::numeric_limits<short>::max())
  {
    mgChannel = (Short_t)gchan;
  }
  else
  {
    mgChannel = -1;
    LOG_INFO << "Weird cell: backleg = " << hit->backleg()
             << ", module = " << hit->module()
             << ", cell = " << hit->cell()
             << endm;
  }

  mLeadingEdgeTime  = (pair<Float_t, Float_t>)hit->leadingEdgeTime();
  mTrailingEdgeTime = (pair<Float_t, Float_t>)hit->trailingEdgeTime();
}

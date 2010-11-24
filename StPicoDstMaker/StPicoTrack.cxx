#include "StPicoTrack.h"
#include "StPicoCut.h"
#include "StPicoConstants.h"
#include "StPicoDstMaker.h"
#include "TVector2.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"

ClassImp(StPicoTrack)

//----------------------------------------------------------------------------------
StPicoTrack::StPicoTrack()
{
  Clear();
}

/////////////////////////////////////////////////////////////////////////////////////////
// t - the global track.  p - the associated primary track from the first primary vertex
/////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------
StPicoTrack::StPicoTrack(StMuTrack* t, StMuTrack* p, float phi_weight, int flowFlag, double B,
                         int id, int adc0, float* e, float* dist, int* nhit)
{
  Clear();
  if(!t || t->type()!=global || (p && ( p->type()!=primary || p->id()!=t->id() ) ) ) {
    LOG_WARN << " Bad StPicoTrack constructor ...... Check!" << endm;
  } else {
  mId        = (UShort_t)t->id();
  mChi2      = (t->chi2()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(t->chi2()*1000.));
  mGMomentum = t->helix().momentum(B*kilogauss);
  if(p) {
    mPMomentum = p->p();
    mChi2Prob  = (p->chi2prob()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(p->chi2prob()*1000.));
  }
  else{
    mPMomentum.set(0.,0.,0.);
    mChi2Prob = Pico::USHORTMAX ;
  }
  mOrigin    = t->helix().origin();
  int q      = t->charge();
  mGDca      = (t->dcaGlobal().mag()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(t->dcaGlobal().mag()*1000.));
  mDedx      = (t->dEdx()*1e6*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(t->dEdx()*1e6*1000.));
  int flag = t->flag();
  if(flag/100<7) { // TPC tracks
    mNHitsFit  = (UChar_t)(t->nHitsFit(kTpcId)*q);
    mNHitsMax  = (Char_t)(t->nHitsPoss(kTpcId));
  } else { // FTPC tracks
    if(mGMomentum.pseudoRapidity()>0.) {
      mNHitsFit  = (UChar_t)(t->nHitsFit(kFtpcWestId)*q);
      mNHitsMax  = (Char_t)(t->nHitsPoss(kFtpcWestId));
    } else {
      mNHitsFit  = (UChar_t)(t->nHitsFit(kFtpcEastId)*q);
      mNHitsMax  = (Char_t)(t->nHitsPoss(kFtpcEastId));
    }
  }
  mNHitsDedx = (Char_t)(t->nHitsDedx());
  mNSigmaPion     = (fabs(t->nSigmaPion()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(t->nSigmaPion()*100.));
  mNSigmaKaon     = (fabs(t->nSigmaKaon()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(t->nSigmaKaon()*100.));
  mNSigmaProton   = (fabs(t->nSigmaProton()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(t->nSigmaProton()*100.));
  mNSigmaElectron = (fabs(t->nSigmaElectron()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(t->nSigmaElectron()*100.));

  // Flow analysis
  mFlowFlag = (UChar_t)(flowFlag);
  if(mFlowFlag==others) {
    mQXi = 0.;
    mQYi = 0.;
  } else {
    float pt = mPMomentum.perp();
    float pt_weight = (pt<2.) ? pt : 2.;
    mQXi = pt_weight * phi_weight * TMath::Cos(2.*mPMomentum.phi());
    mQYi = pt_weight * phi_weight * TMath::Sin(2.*mPMomentum.phi());
    if(mQXi > 10. || mQYi > 10.) {
      LOG_WARN << " WARN!!! something is wrong with this Qi " << mQXi << " " << mQYi << " flag=" << flowFlag << " phi_weight=" << phi_weight << " pt=" << pt << endm;
    }
  }

  // TOF
  StMuBTofHit *btofHit = (StMuBTofHit *)t->tofHit();
  if(btofHit) {
    int tray = btofHit->tray(); int module = btofHit->module(); int cell = btofHit->cell();
    mBTofCellId = (Short_t)((tray-1)*192+(module-1)*6+(cell-1));
    mBTof       = t->btofPidTraits().timeOfFlight();
    mBTofBeta   = (p) ? p->btofPidTraits().beta() : -999.;
    mBTofHitPos = t->btofPidTraits().position();
  }

  // EMC - filled in a separated function
  mBEMCId       = (id>Pico::SHORTMAX) ? -1 : (Short_t)id;
  mBTOWADC0     = (adc0>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)adc0;
  mBTOWE0       = (e[0]*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(e[0]*1000.));
  mBTOWE3       = (e[1]*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(e[1]*1000.));
  mBTOWE        = (e[2]*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(floor(e[2]*1000.));
  mBEMCDistZ    = (fabs(dist[0]*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(dist[0]*100.));
  mBEMCDistPhi  = (fabs(dist[1]*10000.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(floor(dist[1]*10000.));
  mBSMDNEta     = (nhit[0]>Pico::UCHARMAX) ? Pico::UCHARMAX : (UChar_t)(floor(nhit[0]));
  mBSMDNPhi     = (nhit[1]>Pico::UCHARMAX) ? Pico::UCHARMAX : (UChar_t)(floor(nhit[1]));
  }// end if
}

//----------------------------------------------------------------------------------
StPicoTrack::~StPicoTrack()
{ /* noop */ }

//----------------------------------------------------------------------------------
void StPicoTrack::Clear(const Option_t* opt)
{
  mId = 0;
  mChi2 = Pico::USHORTMAX;
  mChi2Prob = Pico::USHORTMAX;
  mGMomentum.set(0.,0.,0.);
  mPMomentum.set(0.,0.,0.);
  mFlowFlag = 0;
  mQXi = 0.;
  mQYi = 0.;
  mOrigin.set(0.,0.,0.);
  mGDca = Pico::USHORTMAX;
  mDedx = 0;
  mNHitsFit = 0;
  mNHitsMax = 0;
  mNHitsDedx = 0;
  mNSigmaPion = Pico::SHORTMAX;
  mNSigmaKaon = Pico::SHORTMAX;
  mNSigmaProton = Pico::SHORTMAX;
  mNSigmaElectron = Pico::SHORTMAX;

  mBTofCellId = -1;
  mBTof = -999.;
  mBTofBeta = -999.;
  mBTofHitPos.set(0.,0.,0.);

  mBEMCId       = -1;
  mBTOWADC0     = 0;
  mBTOWE0       = 0;
  mBTOWE3       = 0;
  mBTOWE        = 0;
  mBEMCDistZ    = Pico::SHORTMAX;
  mBEMCDistPhi  = Pico::SHORTMAX;
  mBSMDNEta = 0;
  mBSMDNPhi = 0;
}
//----------------------------------------------------------------------------------
void StPicoTrack::Print(Option_t *option) const {
/*
  LOG_INFO << "id=" << id() << " flowflag=" << flowFlag() << " chi2=" << chi2() << " dca=" << dca() << endm;
  LOG_INFO << "gMom=" << gMom() << endm;
  LOG_INFO << "pMom=" << pMom() << endm;
  LOG_INFO << "Origin=" << origin() << endm;
  LOG_INFO << "Q vector=" << mQXi << " " << mQYi << endm;
  LOG_INFO << " nHitsFit = " << nHitsFit() << " nHitsdEdx = " << nHitsDedx() << endm;
  LOG_INFO << " nSigma Pi/K/P/E = " << nSigmaPion() << "/" << nSigmaKaon() << "/" << nSigmaProton() << "/" << nSigmaElectron() << endm;
  LOG_INFO << " BTOF cellId = " << btofCellId() << " tof = " << btof() << " beta = " << btofBeta() << endm;
*/
  LOG_INFO << " BEMC Id = " << id() << "BTOW ADC0 = " << adc0() << " energy0 = " << e0() << " e = " << e() << endm;
  LOG_INFO << " BEMC distz = " << zDist() << " distphi = " << phiDist() << endm;
  LOG_INFO << " BSMD nEta/nPhi = " << nEta() << "/" << nPhi() << endm;
}

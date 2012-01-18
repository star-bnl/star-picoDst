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
                         int id, int adc0, float* e, float* dist, int* nhit, int* ntow)
{
  Clear();
  if(!t || t->type()!=global || (p && ( p->type()!=primary || p->id()!=t->id() ) ) ) {
    LOG_WARN << " Bad StPicoTrack constructor ...... Check!" << endm;
  } else {
  mId        = (UShort_t)t->id();
  mChi2      = (t->chi2()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(t->chi2()*1000.));
  mGMomentum = t->helix().momentum(B*kilogauss);
  if(p) {
    mPMomentum = p->p();
    mChi2Prob  = (p->chi2prob()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(p->chi2prob()*1000.));
  } else {
    mPMomentum.set(0.,0.,0.);
    mChi2Prob = Pico::USHORTMAX ;
  }
  StThreeVectorF o = t->helix().origin();
  mOriginX   = (fabs(o.x()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(o.x()*100.));
  mOriginY   = (fabs(o.y()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(o.y()*100.));
  mOriginZ   = (fabs(o.z()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(o.z()*100.));
  int q      = t->charge();
  mGDca      = (t->dcaGlobal().mag()*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(t->dcaGlobal().mag()*1000.));
  mDedx      = (t->dEdx()*1e6*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(t->dEdx()*1e6*1000.));
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
  mNSigmaPion     = (fabs(t->nSigmaPion()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->nSigmaPion()*100.));
  mNSigmaKaon     = (fabs(t->nSigmaKaon()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->nSigmaKaon()*100.));
  mNSigmaProton   = (fabs(t->nSigmaProton()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->nSigmaProton()*100.));
  mNSigmaElectron = (fabs(t->nSigmaElectron()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->nSigmaElectron()*100.));

  // Flow analysis
  mFlowFlag = (UChar_t)(flowFlag);

#if 0
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
#endif

  // TOF
  StMuBTofHit *btofHit = (StMuBTofHit *)t->tofHit();
  if(btofHit) {
    int tray = btofHit->tray(); int module = btofHit->module(); int cell = btofHit->cell();
    float tof = t->btofPidTraits().timeOfFlight();
    float beta = (p) ? p->btofPidTraits().beta() : -999.;
    StThreeVectorF pos = t->btofPidTraits().position();
    mBTofCellId  = (Short_t)((tray-1)*192+(module-1)*6+(cell-1));
    mBTofMatchFlag = (UChar_t)(t->btofPidTraits().matchFlag());
    if(tof<0) { mBTof = 0; }
    else { mBTof = (tof*1000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(tof*1000.)); }
    if(beta<0) { mBTofBeta = 0; }
    else { mBTofBeta = (beta*20000.>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)(TMath::Nint(beta*20000.)); }
    mBTofHitPosX = (fabs(pos.x()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(pos.x()*100.));
    mBTofHitPosY = (fabs(pos.y()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(pos.y()*100.)); 
    mBTofHitPosZ = (fabs(pos.z()*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(pos.z()*100.)); 
    mBTofYLocal  = (fabs(t->btofPidTraits().yLocal())*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->btofPidTraits().yLocal()*1000.));
    mBTofZLocal  = (fabs(t->btofPidTraits().zLocal())*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(t->btofPidTraits().zLocal()*1000.));
  }

#if EMCON == 1
  // EMC - filled in a separated function
  mBEMCId       = (id>Pico::SHORTMAX) ? -1 : (Short_t)id;
  mBTOWADC0     = (adc0>Pico::USHORTMAX) ? Pico::USHORTMAX : (UShort_t)adc0;
  mBTOWE0       = (e[0]*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(e[0]*1000.));
  mBTOWE        = (e[1]*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(e[1]*1000.));
  mBEMCDistZ    = (fabs(dist[0]*100.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(dist[0]*100.));
  mBEMCDistPhi  = (fabs(dist[1]*10000.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(dist[1]*10000.));
  mBSMDNEta     = (nhit[0]>Pico::UCHARMAX) ? Pico::UCHARMAX : (UChar_t)(nhit[0]);
  mBSMDNPhi     = (nhit[1]>Pico::UCHARMAX) ? Pico::UCHARMAX : (UChar_t)(nhit[1]);

  mBTOWId       = (ntow[0]<=0 || ntow[0]>4800) ? -1 : (Short_t)ntow[0];
  mBTOWId23     = (ntow[1]<0 || ntow[1]>=9 || ntow[2]<0 || ntow[2]>=9) ? -1 : (Char_t)(ntow[1]*10+ntow[2]);
  mBTOWE1       = (e[2]*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(e[2]*1000.));
  mBTOWE2       = (e[3]*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(e[3]*1000.));
  mBTOWE3       = (e[4]*1000.>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(e[4]*1000.));
  mBTOWDistEta  = (fabs(dist[2]*10000.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(dist[2]*10000.));
  mBTOWDistPhi  = (fabs(dist[3]*10000.)>Pico::SHORTMAX) ? Pico::SHORTMAX : (Short_t)(TMath::Nint(dist[3]*10000.));
#endif

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
//  mQXi = 0.;
//  mQYi = 0.;
  mOriginX = 0;
  mOriginY = 0;
  mOriginZ = 0;
  mGDca = Pico::USHORTMAX;
  mDedx = 0;
  mNHitsFit  = 0;
  mNHitsMax  = 0;
  mNHitsDedx = 0;
  mNSigmaPion     = Pico::SHORTMAX;
  mNSigmaKaon     = Pico::SHORTMAX;
  mNSigmaProton   = Pico::SHORTMAX;
  mNSigmaElectron = Pico::SHORTMAX;

  mBTofCellId  = -1;
  mBTofMatchFlag = 0;
  mBTof        = 0;
  mBTofBeta    = 0;
  mBTofYLocal  = Pico::SHORTMAX;
  mBTofZLocal  = Pico::SHORTMAX;
  mBTofHitPosX = 0;
  mBTofHitPosY = 0;
  mBTofHitPosZ = 0;

#if EMCON == 1
  mBEMCId       = -1;
  mBTOWADC0     = 0;
  mBTOWE0       = -1*Pico::SHORTMAX;
  mBTOWE        = -1*Pico::SHORTMAX;
  mBEMCDistZ    = Pico::SHORTMAX;
  mBEMCDistPhi  = Pico::SHORTMAX;
  mBSMDNEta = 0;
  mBSMDNPhi = 0;

  mBTOWId       = -1;
  mBTOWId23	= -1;
  mBTOWE1       = -1*Pico::SHORTMAX;
  mBTOWE2       = -1*Pico::SHORTMAX;
  mBTOWE3       = -1*Pico::SHORTMAX;
  mBTOWDistEta  = Pico::SHORTMAX;
  mBTOWDistPhi  = Pico::SHORTMAX;
#endif
}
//----------------------------------------------------------------------------------
void StPicoTrack::Print(const Char_t *option) const {
  if(strcmp(option,"tpc")==0 || strcmp(option,"")==0) {
    LOG_INFO << "id=" << id() << " flowflag=" << flowFlag() << " chi2=" << chi2() << " dca=" << dca() << endm;
    LOG_INFO << "gMom=" << gMom() << endm;
    LOG_INFO << "pMom=" << pMom() << endm;
    LOG_INFO << "Origin=" << origin() << endm;
//    LOG_INFO << "Q vector=" << mQXi << " " << mQYi << endm;
    LOG_INFO << " nHitsFit = " << nHitsFit() << " nHitsdEdx = " << nHitsDedx() << endm;
    LOG_INFO << " nSigma Pi/K/P/E = " << nSigmaPion() << "/" << nSigmaKaon() << "/" << nSigmaProton() << "/" << nSigmaElectron() << endm;
  }
  if(strcmp(option,"tof")==0 || strcmp(option,"")==0) {
    LOG_INFO << " BTOF cellId = " << btofCellId() << " tof = " << btof() << " beta = " << btofBeta() << endm;
    LOG_INFO << " BTOF match = " << btofMatchFlag() << " yLocal/zLocal " << btofYLocal() << " " << btofZLocal() << endm;
  }
  if(strcmp(option,"emc")==0 || strcmp(option,"")==0) {
    LOG_INFO << " BEMC Id = " << bemcId() << " BTOW ADC0 = " << adc0() << " energy0 = " << e0() << " e = " << e() << endm;
    LOG_INFO << " BEMC distz = " << zDist() << " distphi = " << phiDist() << endm;
    LOG_INFO << " BSMD nEta/nPhi = " << nEta() << "/" << nPhi() << endm;
    LOG_INFO << " BTOW Id = " << btowId() << " tower Id 2/3 = " << btowId2() << " " << btowId3() << endm;
    LOG_INFO << " BTOW energy = " << e1() << " " << e2() << " " << e3() << endm;
    LOG_INFO << " BTOW position to center = " << etaTowDist() << " " << phiTowDist() << endm;
  }
}

#include "StEvent/StEnumerations.h"
#include "StPicoCut.h"
#include "StPicoTrack.h"
#include "StPicoConstants.h"
#include "St_base/StMessMgr.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

ClassImp(StPicoCut)

//----------------------------------------------------------------------------------
StPicoCut::StPicoCut() {}

//----------------------------------------------------------------------------------
StPicoCut::~StPicoCut() {}

//----------------------------------------------------------------------------------
bool StPicoCut::passEvent( StMuEvent *ev )
{
  if(!ev){
    LOG_INFO << "StPicoCut::passEvent  No StMuEvent" << endm;
    return kFALSE;
  }
//  StThreeVectorF pVertex = ev->eventSummary().primaryVertexPosition();
  StThreeVectorF pVertex = ev->primaryVertexPosition();
  if(fabs(pVertex.x())<1.e-5 && fabs(pVertex.y())<1.e-5 && fabs(pVertex.z())<1.e-5){
   LOG_INFO << "StPicoCut::passEvent  bad vertices (x,y,z) = ("
            << pVertex.x() << ","
            << pVertex.y() << ","
            << pVertex.z() << ")"
            << endm;
    return kFALSE;
  }
  if(fabs(pVertex.z())>Pico::mVzMax){
    LOG_INFO << "StPicoCut::passEvent  z-vertex out of range, vz  (evtSum)=" << pVertex.z() << " (direct)=" << ev->primaryVertexPosition().z() << endm;
    return kFALSE;
  }

  const Float_t vx = pVertex.x() ;
  const Float_t vy = pVertex.y() ;
  if(sqrt(vx*vx+vy*vy)>Pico::mVrMax){
    LOG_INFO << "StPicoCut::passEvent  vr-vertex out of range, vr = " << sqrt(vx*vx+vy*vy)
      << ",  vx = " << vx
      << ",  vy = " << vy
      << endm;
    return kFALSE ;
  }

  if(ev->refMult()<Pico::mRefMultMin) {
    LOG_INFO << "StPicoCut::passEvent refMult out of range, refMult = " << ev->refMult() << endm;
    return kFALSE;
  }

  return kTRUE;
}

//----------------------------------------------------------------------------------
bool StPicoCut::passTrack( StMuTrack *t )
{
  if(!t) return kFALSE;
  if(t->type()!=global) return kFALSE;
  if(t->flag()<0||t->flag()>1000) {
    return kFALSE;
  }
  if(t->p().perp()<Pico::mPtMin) return kFALSE;
  if(t->dcaGlobal().mag()>Pico::mGDcaMax) return kFALSE;
  if(t->flag()/100<7) {  // TPC tracks
    if( t->nHitsFit(kTpcId) < Pico::mNHitsFitMin ) return kFALSE;
    if( (1.0*t->nHitsFit(kTpcId))/(1.0*t->nHitsPoss(kTpcId)) < Pico::mRatioMin ) return kFALSE;
  } else { // FTPC tracks
    float eta = t->p().pseudoRapidity();
    int nHitsFitFtpc = 0;
    int nHitsMaxFtpc = 0;
    if(eta>0) {
      nHitsFitFtpc = t->nHitsFit(kFtpcWestId);
      nHitsMaxFtpc = t->nHitsPoss(kFtpcWestId);
    } else {
      nHitsFitFtpc = t->nHitsFit(kFtpcEastId);
      nHitsMaxFtpc = t->nHitsPoss(kFtpcEastId);
    }
    float ratioFtpc  = (1.*nHitsFitFtpc)/(1.*nHitsMaxFtpc);
    if( ratioFtpc < Pico::mRatioMin ) return kFALSE;
  }

  return kTRUE;
}

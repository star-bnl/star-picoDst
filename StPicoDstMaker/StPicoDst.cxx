#include <map>
#include "StPicoDst.h"
#include "StPicoEvent.h"
#include "StPicoTrack.h"
#include "StPicoV0.h"
#include "StPicoTrigger.h"
#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoDstMaker.h"

TClonesArray** StPicoDst::picoArrays       = 0;
TClonesArray** StPicoDst::picoV0Arrays     = 0;

//-----------------------------------------------------------------------
StPicoDst::StPicoDst() {
  /* no-op */
}
//-----------------------------------------------------------------------
void StPicoDst::unset() {
    picoArrays   = 0;
    picoV0Arrays = 0;
}
//-----------------------------------------------------------------------
void StPicoDst::set(StPicoDstMaker* maker) {
  if (!maker) { LOG_WARN << "No PicoDstMaker!" << endm; return;}
  picoArrays   = maker->mPicoArrays;
  picoV0Arrays = maker->mPicoV0Arrays;
}
//-----------------------------------------------------------------------
void StPicoDst::set(TClonesArray** thePicoArrays,
                    TClonesArray** thePicoV0Arrays)
{
  picoArrays    = thePicoArrays;
  picoV0Arrays  = thePicoV0Arrays;
}
//-----------------------------------------------------------------------
void StPicoDst::Print(Option_t *option) const {
  LOG_INFO << endm;
  LOG_INFO << "=========== event header =============" << endm << endm;
  LOG_INFO << " fill/run/event Id = " << event()->fillId() << "/" << event()->runId() << "/" << event()->eventId() << endm;
  LOG_INFO << " vertex = " << event()->primaryVertex() << endm;
  LOG_INFO << " triggerWord = " << event()->triggerWord() << " refMult = " << event()->refMult() << " refMultFtpc = " << event()->refMultFtpc() << endm;
  LOG_INFO << " nVpdHits e/w = " << event()->nVpdHitsEast() << "/" << event()->nVpdHitsWest() << " nT0 = " << event()->nT0() << " vzVpd = " << event()->vzVpd() << endm;
  LOG_INFO << " Q vector = " << event()->Q().X() << " " << event()->Q().Y()  << endm;
  LOG_INFO << "=====================================" << endm << endm;
}
//-----------------------------------------------------------------------
void StPicoDst::printTracks()  {
  if (numberOfTracks() == 0) {
    LOG_INFO << "No tracks found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ track list ( " << numberOfTracks() << " entries )" << endm << endm;
  for (UInt_t i_trk = 0; i_trk < numberOfTracks(); i_trk++) {
    LOG_INFO << "+++ track " << i_trk << endm;
    track(i_trk)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printTriggers()  {
  if (numberOfTriggers() == 0) {
    LOG_INFO << "No triggers found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ trigger list ( " << numberOfTriggers() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfTriggers(); i_t++) {
    LOG_INFO << "+++ trigger " << i_t << endm;
    trigger(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printBTOWHits()  {
  if (numberOfBTOWHits() == 0) {
    LOG_INFO << "No BTOWHit found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ BTOWHit list ( " << numberOfBTOWHits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfBTOWHits(); i_t++) {
    LOG_INFO << "+++ btowHit " << i_t << endm;
    btowHit(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printBTofHits()  {
  if (numberOfBTofHits() == 0) {
    LOG_INFO << "No BTofHit found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ BTof list ( " << numberOfBTofHits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfBTofHits(); i_t++) {
    LOG_INFO << "+++ btofHit " << i_t << endm;
    btofHit(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printKs()  {      
  if (numberOfKs() == 0) {      
    LOG_INFO << "No Kshort found!" << endm;   
    return;    
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ kshort list ( " << numberOfKs() << " entries )" << endm << endm;
  for (UInt_t i_trk = 0; i_trk < numberOfKs(); i_trk++) {      
    LOG_INFO << "+++ ks " << i_trk << endm;   
    ks(i_trk)->Print();                       
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printLambda()  {
  if (numberOfLambda() == 0) {
    LOG_INFO << "No Lambdat found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ lambda list ( " << numberOfLambda() << " entries )" << endm << endm;
  for (UInt_t i_trk = 0; i_trk < numberOfLambda(); i_trk++) {      
    LOG_INFO << "+++ Lambda " << i_trk << endm;
    lambda(i_trk)->Print();   
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printLbar()  {
  if (numberOfLbar() == 0) {
    LOG_INFO << "No Lbar found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ lambdabar list ( " << numberOfLbar() << " entries )" << endm << endm;
  for (UInt_t i_trk = 0; i_trk < numberOfLbar(); i_trk++) {      
    LOG_INFO << "+++ Lbar " << i_trk << endm;
    lbar(i_trk)->Print();   
    LOG_INFO << endm;
  }
}

ClassImp(StPicoDst)

#include <map>
#include "StPicoDst.h"
#include "StPicoEvent.h"
#include "StPicoTrack.h"
#include "StPicoEmcTrigger.h"
#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoMtdHit.h"
#include "StPicoEmcPidTraits.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoDstMaker.h"

TClonesArray** StPicoDst::picoArrays       = 0;

//-----------------------------------------------------------------------
StPicoDst::StPicoDst() {
  /* no-op */
}
//-----------------------------------------------------------------------
void StPicoDst::unset() {
    picoArrays   = 0;
}
//-----------------------------------------------------------------------
void StPicoDst::set(StPicoDstMaker* maker) {
  if (!maker) { LOG_WARN << "No PicoDstMaker!" << endm; return;}
  picoArrays   = maker->mPicoArrays;
}
//-----------------------------------------------------------------------
void StPicoDst::set(TClonesArray** thePicoArrays)
{
  picoArrays    = thePicoArrays;
}
//-----------------------------------------------------------------------
void StPicoDst::Print(Option_t *option) const {
  LOG_INFO << endm;
  LOG_INFO << "=========== event header =============" << endm << endm;
  LOG_INFO << " fill/run/event Id = " << event()->fillId() << "/" << event()->runId() << "/" << event()->eventId() << endm;
  LOG_INFO << " vertex = " << event()->primaryVertex() << endm;
  LOG_INFO << " refMult = " << event()->refMult() << " refMultFtpc = " << event()->refMultFtpc() << endm;
  LOG_INFO << " nVpdHits e/w = " << event()->nVpdHitsEast() << "/" << event()->nVpdHitsWest() << " nT0 = " << event()->nT0() << " vzVpd = " << event()->vzVpd() << endm;
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

  LOG_INFO << "=== EMC triggers ===" << endm;

  if (numberOfEmcTriggers() == 0) {
    LOG_INFO << "No triggers found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ trigger list ( " << numberOfEmcTriggers() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfEmcTriggers(); i_t++) {
    LOG_INFO << "+++ trigger " << i_t << endm;
    emcTrigger(i_t)->Print();
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
void StPicoDst::printMtdHits()  {
  if (numberOfMtdHits() == 0) {
    LOG_INFO << "No MtdHit found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ Mtd list ( " << numberOfMtdHits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfMtdHits(); i_t++) {
    LOG_INFO << "+++ mtdHit " << i_t << endm;
    mtdHit(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printEmcPidTraits()  {
  if (numberOfEmcPidTraits() == 0) {
    LOG_INFO << "No Emc pidTraits found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ Emc pidTraits list ( " << numberOfEmcPidTraits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfEmcPidTraits(); i_t++) {
    LOG_INFO << "+++ EmcPidTraits " << i_t << endm;
    emcPidTraits(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printBTofPidTraits()  {
  if (numberOfBTofPidTraits() == 0) {
    LOG_INFO << "No BTof pidTraits found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ BTof pidTraits list ( " << numberOfBTofPidTraits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfBTofPidTraits(); i_t++) {
    LOG_INFO << "+++ EmcPidTraits " << i_t << endm;
    btofPidTraits(i_t)->Print();
    LOG_INFO << endm;
  }
}
//-----------------------------------------------------------------------
void StPicoDst::printMtdPidTraits()  {
  if (numberOfMtdPidTraits() == 0) {
    LOG_INFO << "No Mtd pidTraits found!" << endm;
    return;
  }
  LOG_INFO << endm;
  LOG_INFO << "+++++++++ Mtd pidTraits list ( " << numberOfMtdPidTraits() << " entries )" << endm << endm;
  for (UInt_t i_t = 0; i_t < numberOfMtdPidTraits(); i_t++) {
    LOG_INFO << "+++ mtdPidTraits " << i_t << endm;
    mtdPidTraits(i_t)->Print();
    LOG_INFO << endm;
  }
}

ClassImp(StPicoDst)

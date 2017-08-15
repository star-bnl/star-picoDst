#ifndef StPicoDst_h
#define StPicoDst_h

#include "TClonesArray.h"
#include "StPicoEvent/StPicoArrays.h"

class StPicoEvent;
class StPicoTrack;
class StPicoEmcTrigger;
class StPicoMtdTrigger;
class StPicoBTowHit;
class StPicoBTofHit;
class StPicoMtdHit;
class StPicoBbcHit;
class StPicoEpdHit;
class StPicoFmsHit;
class StPicoBEmcPidTraits;
class StPicoBTofPidTraits;
class StPicoMtdPidTraits;


class StPicoDst
{
public:
  StPicoDst();
  ~StPicoDst() {}

  /// set the pointers to the TClonesArrays
  void set(TClonesArray**);
  /// resets the pointers to the TClonesArrays to 0
  void unset();

  /// returns pointer to the n-th TClonesArray
  TClonesArray* picoArray(int type) { return picoArrays[type]; }

  /// returns pointer to current StPicoEvent (class holding the event wise information)
  StPicoEvent* event() { return (StPicoEvent*)picoArrays[StPicoArrays::Event]->UncheckedAt(0); }
  const StPicoEvent* event() const { return (const StPicoEvent*)picoArrays[StPicoArrays::Event]->UncheckedAt(0); }

  /// return pointer to i-th track
  StPicoTrack* track(int i) { return (StPicoTrack*)picoArrays[StPicoArrays::Track]->UncheckedAt(i); }
  /// return pointer to i-th trigger data
  StPicoEmcTrigger* emcTrigger(int i) { return (StPicoEmcTrigger*)picoArrays[StPicoArrays::EmcTrigger]->UncheckedAt(i); }
  StPicoMtdTrigger* mtdTrigger(int i) { return (StPicoMtdTrigger*)picoArrays[StPicoArrays::MtdTrigger]->UncheckedAt(i); }

  /// return pointer to i-th btow hit
  StPicoBTowHit* btowHit(int i) { return (StPicoBTowHit*)picoArrays[StPicoArrays::BTowHit]->UncheckedAt(i); }
  /// return pointer to i-th btof hit
  StPicoBTofHit* btofHit(int i) { return (StPicoBTofHit*)picoArrays[StPicoArrays::BTofHit]->UncheckedAt(i); }
  /// return pointer to i-th mtd hit
  StPicoMtdHit*  mtdHit(int i) { return (StPicoMtdHit*)picoArrays[StPicoArrays::MtdHit]->UncheckedAt(i); }
  /// return pointer to i-th bbc hit
  StPicoBbcHit* bbcHit(int i) {return (StPicoBbcHit*)picoArrays[StPicoArrays::BbcHit]->UncheckedAt(i); }
  /// return pointer to i-th epd hit
  StPicoEpdHit* epdHit(int i) {return (StPicoEpdHit*)picoArrays[StPicoArrays::EpdHit]->UncheckedAt(i); }
  /// return pointer to i-th fms hit
  StPicoFmsHit*  fmsHit(int i) { return (StPicoFmsHit*)picoArrays[StPicoArrays::FmsHit]->UncheckedAt(i); }

  /// return pointer to i-th emc pidTraits
  StPicoBEmcPidTraits* bemcPidTraits(int i) { return (StPicoBEmcPidTraits*)picoArrays[StPicoArrays::BEmcPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th btof pidTraits
  StPicoBTofPidTraits* btofPidTraits(int i) { return (StPicoBTofPidTraits*)picoArrays[StPicoArrays::BTofPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th mtd pidTraits
  StPicoMtdPidTraits* mtdPidTraits(int i) { return (StPicoMtdPidTraits*)picoArrays[StPicoArrays::MtdPidTraits]->UncheckedAt(i); }

  unsigned int numberOfTracks() { return picoArrays[StPicoArrays::Track]->GetEntries(); }
  unsigned int numberOfEmcTriggers() { return picoArrays[StPicoArrays::EmcTrigger]->GetEntries(); }
  unsigned int numberOfMtdTriggers() { return picoArrays[StPicoArrays::MtdTrigger]->GetEntries(); }
  unsigned int numberOfBTOWHits() { return picoArrays[StPicoArrays::BTowHit]->GetEntries(); }
  unsigned int numberOfBTofHits() { return picoArrays[StPicoArrays::BTofHit]->GetEntries(); }
  unsigned int numberOfMtdHits() { return picoArrays[StPicoArrays::MtdHit]->GetEntries(); }
  unsigned int numberOfFmsHits() { return picoArrays[StPicoArrays::FmsHit]->GetEntries(); }
  unsigned int numberOfBEmcPidTraits() { return picoArrays[StPicoArrays::BEmcPidTraits] ->GetEntries(); }
  unsigned int numberOfBTofPidTraits() { return picoArrays[StPicoArrays::BTofPidTraits]->GetEntries(); }
  unsigned int numberOfMtdPidTraits() { return picoArrays[StPicoArrays::MtdPidTraits] ->GetEntries(); }

  void print() const; ///< Print basic event info
  void printTracks();
  void printTriggers();
  void printBTOWHits();
  void printBTofHits();
  void printMtdHits();
  void printFmsHits();
  void printBEmcPidTraits();
  void printBTofPidTraits();
  void printMtdPidTraits();

private:

  /// array of TClonesArrays
  TClonesArray** picoArrays;

};

#endif

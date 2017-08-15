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
  TClonesArray* picoArray(int type) { return mPicoArrays[type]; }

  /// returns pointer to current StPicoEvent (class holding the event wise information)
  StPicoEvent* event() { return (StPicoEvent*)mPicoArrays[StPicoArrays::Event]->UncheckedAt(0); }
  const StPicoEvent* event() const { return (const StPicoEvent*)mPicoArrays[StPicoArrays::Event]->UncheckedAt(0); }

  /// return pointer to i-th track
  StPicoTrack* track(int i) { return (StPicoTrack*)mPicoArrays[StPicoArrays::Track]->UncheckedAt(i); }
  /// return pointer to i-th trigger data
  StPicoEmcTrigger* emcTrigger(int i) { return (StPicoEmcTrigger*)mPicoArrays[StPicoArrays::EmcTrigger]->UncheckedAt(i); }
  StPicoMtdTrigger* mtdTrigger(int i) { return (StPicoMtdTrigger*)mPicoArrays[StPicoArrays::MtdTrigger]->UncheckedAt(i); }

  /// return pointer to i-th btow hit
  StPicoBTowHit* btowHit(int i) { return (StPicoBTowHit*)mPicoArrays[StPicoArrays::BTowHit]->UncheckedAt(i); }
  /// return pointer to i-th btof hit
  StPicoBTofHit* btofHit(int i) { return (StPicoBTofHit*)mPicoArrays[StPicoArrays::BTofHit]->UncheckedAt(i); }
  /// return pointer to i-th mtd hit
  StPicoMtdHit*  mtdHit(int i) { return (StPicoMtdHit*)mPicoArrays[StPicoArrays::MtdHit]->UncheckedAt(i); }
  /// return pointer to i-th bbc hit
  StPicoBbcHit* bbcHit(int i) {return (StPicoBbcHit*)mPicoArrays[StPicoArrays::BbcHit]->UncheckedAt(i); }
  /// return pointer to i-th epd hit
  StPicoEpdHit* epdHit(int i) {return (StPicoEpdHit*)mPicoArrays[StPicoArrays::EpdHit]->UncheckedAt(i); }
  /// return pointer to i-th fms hit
  StPicoFmsHit*  fmsHit(int i) { return (StPicoFmsHit*)mPicoArrays[StPicoArrays::FmsHit]->UncheckedAt(i); }

  /// return pointer to i-th emc pidTraits
  StPicoBEmcPidTraits* bemcPidTraits(int i) { return (StPicoBEmcPidTraits*)mPicoArrays[StPicoArrays::BEmcPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th btof pidTraits
  StPicoBTofPidTraits* btofPidTraits(int i) { return (StPicoBTofPidTraits*)mPicoArrays[StPicoArrays::BTofPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th mtd pidTraits
  StPicoMtdPidTraits* mtdPidTraits(int i) { return (StPicoMtdPidTraits*)mPicoArrays[StPicoArrays::MtdPidTraits]->UncheckedAt(i); }

  unsigned int numberOfTracks() { return mPicoArrays[StPicoArrays::Track]->GetEntries(); }
  unsigned int numberOfEmcTriggers() { return mPicoArrays[StPicoArrays::EmcTrigger]->GetEntries(); }
  unsigned int numberOfMtdTriggers() { return mPicoArrays[StPicoArrays::MtdTrigger]->GetEntries(); }
  unsigned int numberOfBTOWHits() { return mPicoArrays[StPicoArrays::BTowHit]->GetEntries(); }
  unsigned int numberOfBTofHits() { return mPicoArrays[StPicoArrays::BTofHit]->GetEntries(); }
  unsigned int numberOfMtdHits() { return mPicoArrays[StPicoArrays::MtdHit]->GetEntries(); }
  unsigned int numberOfFmsHits() { return mPicoArrays[StPicoArrays::FmsHit]->GetEntries(); }
  unsigned int numberOfBEmcPidTraits() { return mPicoArrays[StPicoArrays::BEmcPidTraits] ->GetEntries(); }
  unsigned int numberOfBTofPidTraits() { return mPicoArrays[StPicoArrays::BTofPidTraits]->GetEntries(); }
  unsigned int numberOfMtdPidTraits() { return mPicoArrays[StPicoArrays::MtdPidTraits] ->GetEntries(); }

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
  TClonesArray** mPicoArrays;

};

#endif

#ifndef StPicoDst_h
#define StPicoDst_h


class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class StPicoEmcTrigger;
class StPicoMtdTrigger;
class StPicoBTOWHit;
class StPicoBTofHit;
class StPicoMtdHit;
class StPicoEmcPidTraits;
class StPicoBTofPidTraits;
class StPicoMtdPidTraits;

#include "TClonesArray.h"
#include "StPicoDstMaker/StPicoArrays.h"

class StPicoDst
{
public:
  StPicoDst() {}
  ~StPicoDst() {}

  /// set the pointers to the TClonesArrays
  static void set(TClonesArray**);
  /// resets the pointers to the TClonesArrays to 0
  static void unset();

protected:
  /// array of TClonesArrays
  static TClonesArray** picoArrays;

  static TObject* getPicoObject(StPicoArrayType arrayType, unsigned int idx);
  static unsigned int numberOfEntries(StPicoArrayType arrayType);

public:
  /// returns pointer to the n-th TClonesArray
  static TClonesArray* picoArray(StPicoArrayType type) { return picoArrays[static_cast<unsigned int>(type)]; }

  /// returns pointer to current StPicoEvent (class holding the event wise information)
  static StPicoEvent* event() { return (StPicoEvent*)getPicoObject(StPicoArrayType::Event, 0); }
  /// return pointer to i-th track
  static StPicoTrack* track(int i) { return (StPicoTrack*)getPicoObject(StPicoArrayType::Track, i); }
  /// return pointer to i-th trigger data
  static StPicoEmcTrigger* emcTrigger(int i) { return (StPicoEmcTrigger*)getPicoObject(StPicoArrayType::EmcTrigger, i); }
  static StPicoMtdTrigger* mtdTrigger(int i) { return (StPicoMtdTrigger*)getPicoObject(StPicoArrayType::MtdTrigger, i); }

  /// return pointer to i-th btow hit
  static StPicoBTOWHit* btowHit(int i) { return (StPicoBTOWHit*)getPicoObject(StPicoArrayType::BTOWHit, i); }
  /// return pointer to i-th btof hit
  static StPicoBTofHit* btofHit(int i) { return (StPicoBTofHit*)getPicoObject(StPicoArrayType::BTofHit, i); }
  /// return pointer to i-th mtd hit
  static StPicoMtdHit*  mtdHit(int i) { return (StPicoMtdHit*)getPicoObject(StPicoArrayType::MtdHit, i); }

  /// return pointer to i-th emc pidTraits
  static StPicoEmcPidTraits* emcPidTraits(int i) { return (StPicoEmcPidTraits*)getPicoObject(StPicoArrayType::EmcPidTraits, i); }
  /// return pointer to i-th btof pidTraits
  static StPicoBTofPidTraits* btofPidTraits(int i) { return (StPicoBTofPidTraits*)getPicoObject(StPicoArrayType::BTofPidTraits, i); }
  /// return pointer to i-th mtd pidTraits
  static StPicoMtdPidTraits* mtdPidTraits(int i) { return (StPicoMtdPidTraits*)getPicoObject(StPicoArrayType::MtdPidTraits, i); }

  static unsigned int numberOfEvents() { return numberOfEntries(StPicoArrayType::Event); }
  static unsigned int numberOfTracks() { return numberOfEntries(StPicoArrayType::Track); }
  static unsigned int numberOfEmcTriggers() { return numberOfEntries(StPicoArrayType::EmcTrigger); }
  static unsigned int numberOfMtdTriggers() { return numberOfEntries(StPicoArrayType::MtdTrigger); }
  static unsigned int numberOfBTOWHits() { return numberOfEntries(StPicoArrayType::BTOWHit); }
  static unsigned int numberOfBTofHits() { return numberOfEntries(StPicoArrayType::BTofHit); }
  static unsigned int numberOfMtdHits() { return numberOfEntries(StPicoArrayType::MtdHit); }
  static unsigned int numberOfEmcPidTraits() { return numberOfEntries(StPicoArrayType::EmcPidTraits); }
  static unsigned int numberOfBTofPidTraits() { return numberOfEntries(StPicoArrayType::BTofPidTraits); }
  static unsigned int numberOfMtdPidTraits() { return numberOfEntries(StPicoArrayType::MtdPidTraits); }

  void print() const; ///< Print basic event info
  static void printTracks();
  static void printTriggers();
  static void printBTOWHits();
  static void printBTofHits();
  static void printMtdHits();
  static void printEmcPidTraits();
  static void printBTofPidTraits();
  static void printMtdPidTraits();
};

inline TObject* StPicoDst::getPicoObject(StPicoArrayType arrayType, unsigned int const idx)
{
  return picoArrays[static_cast<unsigned int>(arrayType)]->UncheckedAt(idx);
}

inline unsigned int StPicoDst::numberOfEntries(StPicoArrayType arrayType)
{
  return picoArrays[static_cast<unsigned int>(arrayType)]->GetEntries();
}

#endif

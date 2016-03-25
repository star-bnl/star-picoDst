#ifndef StPicoMtdPidTraits_h
#define StPicoMtdPidTraits_h

#include "TObject.h"
class StMuMtdPidTraits;
class StMuMtdHit;

class StPicoMtdPidTraits : public TObject
{
 public:
  StPicoMtdPidTraits();
  StPicoMtdPidTraits(const StMuMtdHit *, const StMuMtdPidTraits*, const Int_t index);
  virtual ~StPicoMtdPidTraits();
  virtual void Print(const Char_t *option = "") const;

  // Matching information
  Int_t    trackIndex()        const;
  Int_t    backleg()           const;
  Int_t    module()            const;
  Int_t    cell()              const;
  Int_t    matchFlag()         const;
  Float_t  deltaY()            const;
  Float_t  deltaZ()            const;
  Float_t  deltaTimeOfFlight() const;
  Float_t  beta()              const;

  // Setting functions
  void    setTrackIndex(Int_t index);
  void    setMatchFlag(Char_t flag);
  void    setDeltaY(Float_t dy);
  void    setDeltaZ(Float_t dz);
  void    setDeltaTimeOfFlight(Float_t t);
  void    setBeta(Float_t beta);

private:
  Short_t   mTrackIndex;            // Index to the associated track in the event
  Char_t    mMatchFlag;             // Matching flag indicating multiple matches
  Float_t   mDeltaY;                // DeltaY between matched track-hit pair
  Float_t   mDeltaZ;                // DeltaZ between matched track-hit pair
  Float_t   mDeltaTimeOfFlight;     // Difference between measured and expected time-of-flight
  Float_t   mBeta;                  // Beta of matched tracks
  Short_t   mMtdHitChan;            // (backleg-1) * 60 + (module-1) * 12 + cell

  ClassDef(StPicoMtdPidTraits,1)
};
inline Int_t    StPicoMtdPidTraits::trackIndex()        const { return (Int_t)mTrackIndex;             }
inline Int_t    StPicoMtdPidTraits::backleg()           const { return (Int_t)mMtdHitChan/60 + 1;      }
inline Int_t    StPicoMtdPidTraits::module()            const { return ((Int_t)mMtdHitChan%60)/12 + 1; }
inline Int_t    StPicoMtdPidTraits::cell()              const { return (Int_t)mMtdHitChan%12;          }
inline Int_t    StPicoMtdPidTraits::matchFlag()         const { return (Int_t)mMatchFlag;              }
inline Float_t  StPicoMtdPidTraits::deltaY()            const { return mDeltaY;                        }
inline Float_t  StPicoMtdPidTraits::deltaZ()            const { return mDeltaZ;                        }
inline Float_t  StPicoMtdPidTraits::deltaTimeOfFlight() const { return mDeltaTimeOfFlight;             }
inline Float_t  StPicoMtdPidTraits::beta()              const { return mBeta;                          }
inline void    StPicoMtdPidTraits::setTrackIndex(Int_t index)      { mTrackIndex = (Short_t) index; }
inline void    StPicoMtdPidTraits::setMatchFlag(Char_t flag)       { mMatchFlag = flag;             }
inline void    StPicoMtdPidTraits::setDeltaY(Float_t dy)           { mDeltaY = dy;                  }
inline void    StPicoMtdPidTraits::setDeltaZ(Float_t dz)           { mDeltaZ = dz;                  }
inline void    StPicoMtdPidTraits::setDeltaTimeOfFlight(Float_t t) { mDeltaTimeOfFlight = t;        }
inline void    StPicoMtdPidTraits::setBeta(Float_t beta)           { mBeta = beta;                  }
#endif

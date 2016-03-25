#ifndef StPicoEmcPidTraits_h
#define StPicoEmcPidTraits_h

#include "TObject.h"

class StPicoEmcPidTraits: public TObject {
 public:
  StPicoEmcPidTraits();
  StPicoEmcPidTraits(Int_t index, Int_t id, Int_t adc0, Float_t const* e, Float_t const* dist, Int_t const* nhit, Int_t const* ntow);
  virtual ~StPicoEmcPidTraits();
  virtual void Print(const Char_t *option = "") const;

  Int_t   bemcId() const;
  Int_t   adc0() const;
  Float_t e0() const;
  Float_t e() const;
  Float_t zDist() const;
  Float_t phiDist() const;
  Int_t   nEta() const;
  Int_t   nPhi() const;

  Int_t   btowId() const;
  Int_t   btowId2() const;
  Int_t   btowId3() const;
  Float_t e1() const;
  Float_t e2() const;
  Float_t e3() const;
  Float_t etaTowDist() const;
  Float_t phiTowDist() const;


 private:
  Short_t  mTrackIndex;       // Index to the associated track in the event

  // these variables are extracted from the standard BEMC cluster algorithm
  Short_t  mBEMCId;           // index in bemcPoint array
  Short_t  mBTOWADC0;         // adc0 higest adc in the cluster
  Short_t  mBTOWE0;           // E0*1000 highest tower in the cluster
  Short_t  mBTOWE;            // EMC point E*1000
  Short_t  mBEMCDistZ;        // z*100
  Short_t  mBEMCDistPhi;      // phi*10000
  UChar_t  mBSMDNEta;         // # of hits in eta
  UChar_t  mBSMDNPhi;         // # of hits in phi

  // these variables are purely from single tower or nearby towers
  Short_t  mBTOWId;           // projected tower Id 1-4800
  Char_t   mBTOWId23;         // emc 2nd and 3rd closest tower local id  ( 2nd X 10 + 3rd), each id 0-8
  Short_t  mBTOWE1;           // E1*1000 matched (closest) tower E
  Short_t  mBTOWE2;           // E2*1000 2nd closest tower E
  Short_t  mBTOWE3;           // E3*1000 3rd closest tower E
  Short_t  mBTOWDistEta;      // eta*10000 distance between track and matched tower center
  Short_t  mBTOWDistPhi;      // phi*10000 distance between track and matched tower center

  ClassDef(StPicoEmcPidTraits,1);
};
inline Int_t   StPicoEmcPidTraits::bemcId() const         { return (Int_t)mBEMCId;                 }
inline Int_t   StPicoEmcPidTraits::adc0() const           { return (Int_t)mBTOWADC0;               }
inline Float_t StPicoEmcPidTraits::e0() const             { return (Float_t)mBTOWE0/1000.;         }
inline Float_t StPicoEmcPidTraits::e() const              { return (Float_t)mBTOWE/1000.;          }
inline Float_t StPicoEmcPidTraits::zDist() const          { return (Float_t)mBEMCDistZ/100.;       }
inline Float_t StPicoEmcPidTraits::phiDist() const        { return (Float_t)mBEMCDistPhi/10000.;   }
inline Int_t   StPicoEmcPidTraits::nEta() const           { return (Int_t)mBSMDNEta;               }
inline Int_t   StPicoEmcPidTraits::nPhi() const           { return (Int_t)mBSMDNPhi;               }

inline Int_t   StPicoEmcPidTraits::btowId() const         { return (Int_t)mBTOWId;                 }
inline Int_t   StPicoEmcPidTraits::btowId2() const        { return (Int_t)mBTOWId23/10;            }
inline Int_t   StPicoEmcPidTraits::btowId3() const        { return (Int_t)mBTOWId23%10;            }
inline Float_t StPicoEmcPidTraits::e1() const             { return (Float_t)mBTOWE1/1000.;         }
inline Float_t StPicoEmcPidTraits::e2() const             { return (Float_t)mBTOWE2/1000.;         }
inline Float_t StPicoEmcPidTraits::e3() const             { return (Float_t)mBTOWE3/1000.;         }
inline Float_t StPicoEmcPidTraits::etaTowDist() const     { return (Float_t)mBTOWDistEta/10000.;   }
inline Float_t StPicoEmcPidTraits::phiTowDist() const     { return (Float_t)mBTOWDistPhi/10000.;   }
#endif

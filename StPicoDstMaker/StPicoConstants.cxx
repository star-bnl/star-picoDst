#include "StPicoConstants.h"

ClassImp(Pico)

   Float_t Pico::mVzMax = 100;
   Float_t Pico::mVrMax =   2;
   Int_t Pico::mRefMultMin = 0;                    // >=

  // track selection
   Float_t Pico::mPtMin = 0.1;
   Int_t   Pico::mNHitsFitMin = 15;               // >=
   Float_t Pico::mRatioMin = 0.;
   Float_t Pico::mGDcaMax = 10.;

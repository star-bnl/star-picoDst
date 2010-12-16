#include "StPicoConstants.h"
#include "TMath.h"

ClassImp(Pico)

   Float_t Pico::mMass[nPar] = {0.13957, 0.49368, 0.93827, 0.000511};
   Float_t Pico::mMassV0[nV0] = {0.49765, 1.11568};

   UShort_t Pico::USHORTMAX = 65535;
   Short_t  Pico::SHORTMAX  = 32767;
   UChar_t  Pico::UCHARMAX  = 255;
   Char_t   Pico::CHARMAX   = 127;

   Int_t Pico::mCent_Year10_200GeV[nCen] ={10,21,41,72,118,182,266,375,441}; // Run10 very preliminary
//   Int_t Pico::mCent_Year10_200GeV[nCen] ={14,30,56,94,146,217,312,431,510}; // Run4
   Int_t Pico::mCent_Year10_39GeV[nCen] ={7,15,28,50,81,125,185,265,316}; // Run10 39 GeV

  // event selectioin
   Int_t Pico::mTriggerId[nTrigger] = {280001,280002};
   Float_t Pico::mVzMax = 40;
   Int_t Pico::mRefMultMin = 8;                    // >=

  // track selection
   Float_t Pico::mPtMin = 0.1;
   Int_t   Pico::mNHitsFitMin = 15;               // >=
   Float_t Pico::mRatioMin = 0.52;

   Float_t Pico::mPtTpcFlowMax = 2.0;
   Float_t Pico::mPtTpcFlowMin = 0.15;
   Float_t Pico::mDcaTpcFlowMax = 2.0;
   Float_t Pico::mEtaTpcFlowMax = 1.0;
   Int_t Pico::mNHitsTpcFlowMin = 15;              // >=
   Float_t Pico::mPtFtpcFlowMax = 2.0;
   Float_t Pico::mPtFtpcFlowMin = 0.1;
   Float_t Pico::mDcaFtpcFlowMax = 2.0;
   Float_t Pico::mEtaFtpcFlowMin = 2.5;
   Float_t Pico::mEtaFtpcFlowMax = 4.0;
   Int_t Pico::mNHitsFtpcFlowMin = 5;              // >=

  // V0 cuts
   Float_t Pico::mV0DaughterNHitsFitMin     = 15;         // >= : TPC tracks
   Float_t Pico::mV0DaughterNSigmaPionMax   = 3.0;
   Float_t Pico::mV0DaughterNSigmaKaonMax   = 0.0;
   Float_t Pico::mV0DaughterNSigmaProtonMax = 3.0;
   Float_t Pico::mV0DcaDaughtersMax         = 0.85;

   Float_t Pico::mV0DaughterDca2VertexPtMax = 1.0;
  // Kshort
   Float_t Pico::mV0KsNSigmaPionMax     = 3.0;
   Float_t Pico::mV0KsPionDca2VertexMin = 0.75;
   Float_t Pico::mV0KsDca2VertexMax     = 2.0;
   Float_t Pico::mV0KsDecayLengthMin    = 2.0;
   Float_t Pico::mV0KsDecayLengthMax    = 300.;
   Float_t Pico::mV0KsMassWindowMax     = 0.1;
  // Lambda
   Float_t Pico::mV0LambdaNSigmaPionMax       = 3.0;
   Float_t Pico::mV0LambdaNSigmaProtonMax     = 3.0;
   Float_t Pico::mV0LambdaPionDca2VertexMin   = 1.0;
   Float_t Pico::mV0LambdaProtonDca2VertexMin = 0.4;
   Float_t Pico::mV0LambdaDca2VertexMax       = 5.0;
   Float_t Pico::mV0LambdaDecayLengthMin      = 2.0;
   Float_t Pico::mV0LambdaDecayLengthMax      = 300.;
   Float_t Pico::mV0LambdaMassWindowMax       = 0.1;

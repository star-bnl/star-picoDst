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
   Int_t Pico::mCent_Year10_11_5GeV[nCen] ={7,14,26,44,70,105,153,184,221}; // Run10 11.5 GeV
   Int_t Pico::mCent_Year10_7_7GeV[nCen] ={6,12,22,37,58,87,128,154,185}; // Run10 7.7 GeV
   Int_t Pico::mCent_Year11_19_6GeV[nCen] = {8,16,28,47,75,111,161,227,268}; // Run11 19.6 GeV
   Int_t Pico::mCent_Year11_27GeV[nCen] = {8,16,28,47,75,111,161,227,268}; // Run11 27 GeV (Copy from 19.6)
   Int_t Pico::mCent_Year11_200GeV[nCen] = {10,21,41,72,118,182,266,375,441}; // Run11 200 GeV (Copy from Run10 200 GeV)

  // event selectioin
//   Int_t Pico::mTriggerId[nTrigger] = {
//     290001,290004,  // mb
//     290003,         // mb-slow-bbc
//     290501,         // ht-11
//     290053, 290054, // vpd-tac
//     290002,         // vpd-tac-slow
//     290070,         // tof-150-fast
//     290060          // tof-150-slow
//   }; // 7.7
//   Int_t Pico::mTriggerId[nTrigger] = {310004,310014}; // 11.5
//   Int_t Pico::mTriggerId[nTrigger] = {280001,280002,280501}; // 39
//   Int_t Pico::mTriggerId[nTrigger] = {260001,260011,260021,260031}; // 200
//   Int_t Pico::mTriggerId[nTrigger] = {
//     340001, 340011, 340021,   // mb1-fast
//     340002, 340012, 340022,   // mb2-slow
//     340500,                   // ht-11
//     340300,                   // tof-200-fast
//     340301,                   // tof-250-slow
//     340068,                   // bbc-large-tof-fast
//     340069                    // bbc-large-tof-slow
//   }; // 19.6 GeV
//   Int_t Pico::mTriggerId[nTrigger] = {
//     360001, // mb1-fast
//     360002, // mb2-slow
//     360500, // ht-11
//     360300, // tof-550-fast
//     360301  // tof-550-slow
////     360031, // zdc-mon-tac
////     360051, // vpd-mon-tac
////     360053, // bbc-small-mon-narrow
////     360054, // bbc-small-mon-wide (equivalent to bbc-small-mon-narrow with prescale ??)
////     360080, // bbc-small-tof-mon-wide
////     360081  // bbc-small-tof-mon-narrow
//   }; // 27 GeV (Run11)
//   Int_t Pico::mTriggerId[nTrigger] = {
//       350001, // vpd-zdc-mb
//       350011, // vpd-zdc-mb
//       350003, // vpd-zdc-mb-protected
//       350013, // vpd-zdc-mb-protected
//       350023, // vpd-zdc-mb-protected
//       350033, // vpd-zdc-mb-protected
//       350043  // vpd-zdc-mb-protected
//   }; // 200 GeV (Run11)
   Int_t Pico::mTriggerId[nTrigger] = {
       370011, // vpdmb-nobsmd
       370001, // vpdmb
       370022, // bbcmb
       370501, // bht0-vpdmb
       370511, // bht1-vpdmb
       370531, // bht2
       370542, // bht0-bbcmb-tof0
       370546, // bht1-bbcmb-tof0
       370522, // bht2-bbcmb
       370601, // jp0
       370611, // jp1
       370621, // jp2
       370641, // ajp
       370301, // bbcmb-tof0
       370361, // tofmult3-vpd
       370341  // tofmult4
   }; // pp200 GeV (Run12)
   Float_t Pico::mVzMax = 100;
   Float_t Pico::mVrMax =   2;
   Int_t Pico::mRefMultMin = 0;                    // >=

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

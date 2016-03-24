#include "StPicoConstants.h"
#include "TMath.h"

ClassImp(Pico)

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

   Float_t Pico::mVzMax = 100;
   Float_t Pico::mVrMax =   2;
   Int_t Pico::mRefMultMin = 0;                    // >=

  // track selection
   Float_t Pico::mPtMin = 0.1;
   Int_t   Pico::mNHitsFitMin = 15;               // >=
   Float_t Pico::mRatioMin = 0.;
   Float_t Pico::mGDcaMax = 10.;

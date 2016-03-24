#ifndef StPicoConstants_h
#define StPicoConstants_h
#include "Rtypes.h"

  enum {
     nTrk     = 50000,
     nCen     = 9,
  };


class Pico {
public:

  static UShort_t USHORTMAX;// = 65535;
  static Short_t  SHORTMAX;//  = 32767;
  static UChar_t  UCHARMAX;//  = 255;
  static Char_t   CHARMAX;//   = 127;
  
  static Int_t mCent_Year10_200GeV[nCen];// ={14,30,56,94,146,217,312,431,510};
  static Int_t mCent_Year10_39GeV[nCen];// ={8,16,29,51,82,126,186,266,317};
  static Int_t mCent_Year10_11_5GeV[nCen];
  static Int_t mCent_Year10_7_7GeV[nCen];
  static Int_t mCent_Year11_19_6GeV[nCen];
  static Int_t mCent_Year11_27GeV[nCen];
  static Int_t mCent_Year11_200GeV[nCen];
    
  // event selectioin
  static Int_t mTriggerId[nTrigger];// = {280001,280002};
  static Int_t mTriggerIdMtd[nTriggerMtd];// added for Run14+ st_mtd stream data
  static Float_t mVzMax;// = 40;
  static Float_t mVrMax;// = 2;
  static Int_t mRefMultMin;// = 8;                    // >=
  
  // track selection
  static Float_t mPtMin;// = 0.1;
  static Int_t mNHitsFitMin;// = 15;                 // >=
  static Float_t mRatioMin;// = 0; //0.52;  -> removed for Run14 AuAu200GeV
  static Float_t mGDcaMax;// = 10.;

  ClassDef(Pico, 1)
};              
#endif

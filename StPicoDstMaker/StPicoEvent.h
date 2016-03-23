#ifndef StPicoEvent_h
#define StPicoEvent_h

class StMuDst;
class TClonesArray;
class StMuPrimaryVertex;
class StPicoDst;
class StPicoDstMaker;
class StBTofHeader;
#include "StarClassLibrary/StThreeVectorF.hh"
#include "TVector2.h"

class StPicoEvent : public TObject {
public:
  StPicoEvent();
  virtual ~StPicoEvent();
  StPicoEvent(const StMuDst& muDst);
  
  Int_t    runId() const;
  Int_t    eventId() const;
  Int_t    fillId() const;
  Float_t  bField() const;
  StThreeVectorF const & primaryVertex() const;
  StThreeVectorF const & primaryVertexError() const;
  Int_t    triggerWord() const;
  Int_t    triggerWordMtd() const;
  Int_t    refMultPos() const;
  Int_t    refMultNeg() const;
  Int_t    refMultFtpcEast() const;
  Int_t    refMultFtpcWest() const;
  Int_t    refMult() const;
  Int_t    refMultFtpc() const;
  Int_t    refMult2PosEast() const;
  Int_t    refMult2NegEast() const;
  Int_t    refMult2PosWest() const;
  Int_t    refMult2NegWest() const;
  Int_t    refMultHalfPosEast() const;
  Int_t    refMultHalfNegEast() const;
  Int_t    refMultHalfPosWest() const;
  Int_t    refMultHalfNegWest() const;
  Int_t    refMult2East() const;
  Int_t    refMult2West() const;
  Int_t    refMult2() const;
  Int_t    refMultHalfEast() const;
  Int_t    refMultHalfWest() const;
  Int_t    grefMult() const;
  Int_t    numberOfPxlInnerHits() const;
  Int_t    numberOfPxlOuterHits() const;
  Int_t    numberOfIstHits() const;
  Int_t    numberOfSsdHits() const;
        
  Int_t    nVpdHitsEast() const;
  Int_t    nVpdHitsWest() const;
  Int_t    nT0() const;
  Float_t  vzVpd() const;
  
  Float_t  ZDCx() const;
  Float_t  BBCx() const;
  Float_t  Vpd(int i) const;
  Float_t  ZdcSumAdcEast() const;
  Float_t  ZdcSumAdcWest() const;
  Float_t  ZdcSmdEastHorizontal(int i) const;
  Float_t  ZdcSmdEastVertical(int i) const;
  Float_t  ZdcSmdWestHorizontal(int i) const;
  Float_t  ZdcSmdWestVertical(int i) const;

  Float_t backgroundRate() const;
  Float_t bbcBlueBackgroundRate() const;
  Float_t bbcYellowBackgroundRate() const;
  Float_t bbcEastRate() const;
  Float_t bbcWestRate() const;
  Float_t zdcEastRate() const;
  Float_t zdcWestRate() const;
  
  Float_t spaceCharge() const;

  UShort_t btofTrayMultiplicity() const;
  UShort_t numberOfGlobalTracks() const;

  Float_t ranking() const;
  UShort_t nBEMCMatch() const;
  UShort_t nBTOFMatch() const;
  
  UShort_t bbcAdcEast(const Int_t i) const;
  UShort_t bbcAdcWest(const Int_t i) const;

  Int_t   ht_th(const Int_t i) const;
  Int_t   jp_th(const Int_t i) const;
  
// other user's functions
  int      year() const;
  int      day() const;
  float    energy() const;
  bool     isMinBias() const;
  bool     isMBSlow() const;
  bool     isCentral() const;
  bool     isHT() const;    
  bool     isHT11() const; 
  bool     isHT15() const; 
  bool     isHT18() const;
  bool     isMtdTrig() const;
  bool     isDiMuon() const;
  bool     isDiMuonHFT() const;
  bool     isSingleMuon() const;
  bool     isEMuon() const;

// set functions for trigger thresholds
  void     setHT_Th(const Int_t i, const Int_t th);
  void     setJP_Th(const Int_t i, const Int_t th);
      
protected: //these are written out
  Int_t          mRunId;           // run number
  Int_t          mEventId;         // event number
  UShort_t       mFillId;          // fill number
  Float_t        mBField;          // B field in kilogauss
  StThreeVectorF mPrimaryVertex;   // primary Vertex (1st)
  StThreeVectorF mSecondVertex;    // second Vertex position (for study)
  StThreeVectorF mPrimaryVertexError; // vertex error
  UInt_t         mTriggerWord;     // self-defined trigger word - see code for details
  UInt_t         mTriggerWordMtd;  // Added in Run14, st_mtd trigger
  UShort_t       mRefMultFtpcEast; // FTPC refMult east
  UShort_t       mRefMultFtpcWest; // FTPC refMult west
  UShort_t       mRefMultNeg;      // TPC refMult neg
  UShort_t       mRefMultPos;      // TPC refMult pos
  UShort_t       mRefMult2NegEast; // TPC refMult2 neg (-1<eta<-0.5)
  UShort_t       mRefMult2PosEast; // TPC refMult2 pos (-1<eta<-0.5)
  UShort_t       mRefMult2NegWest; // TPC refMult2 neg (0.5<eta<1.0)
  UShort_t       mRefMult2PosWest; // TPC refMult2 pos (0.5<eta<1.0)
  UShort_t       mRefMultHalfNegEast ;// TPC refMultHalf neg (eta<0)
  UShort_t       mRefMultHalfPosEast ;// TPC refMultHalf pos (eta<0)
  UShort_t       mRefMultHalfNegWest ;// TPC refMultHalf neg (eta>0)
  UShort_t       mRefMultHalfPosWest ;// TPC refMultHalf pos (eta>0)
  UShort_t       mGRefMult;
  UShort_t       mNHitsHFT[4];
  
  UChar_t        mNVpdHitsEast;    // Vpd Hits east;
  UChar_t        mNVpdHitsWest;    // vpd hits west;
  UShort_t       mNT0;             // number of T0 particles in BTOF self calibration
  Short_t        mVzVpd;           // VzVpd*100.

  UInt_t        mZDCx;           // zdcX
  UInt_t        mBBCx;
  Float_t mBackgroundRate;
  Float_t mBbcBlueBackgroundRate;
  Float_t mBbcYellowBackgroundRate;
  Float_t mBbcEastRate;
  Float_t mBbcWestRate;
  Float_t mZdcEastRate;
  Float_t mZdcWestRate;
  //Nov.10, 2008, Na
  UShort_t mVpd[64];
  UShort_t mZdcSumAdcEast;
  UShort_t mZdcSumAdcWest;
  UShort_t mZdcSmdEastHorizontal[8];
  UShort_t mZdcSmdEastVertical[8];
  UShort_t mZdcSmdWestHorizontal[8];
  UShort_t mZdcSmdWestVertical[8];
  Float_t mSpaceCharge;

  UShort_t mbTofTrayMultiplicity ; // BTOF tray multiplicity
  UShort_t mNumberOfGlobalTracks ; // # of global tracks

  // From StMuPrimaryVertex
  Float_t mRanking ;
  UShort_t mNBEMCMatch ;
  UShort_t mNBTOFMatch ;

  // BBC ADC for q-vectors (Hiroshi)
  UShort_t mBbcAdcEast[24] ; /// BBC East ADC: 0-23
  UShort_t mBbcAdcWest[24] ; /// BBC West ADC: 24-47

  // Online HT/JP thresholds
  UChar_t mHT_Th[4];
  UChar_t mJP_Th[4];
    
  friend class StPicoDst;
  friend class StPicoDstMaker;
    
  ClassDef(StPicoEvent,1)
};
inline Int_t    StPicoEvent::eventId() const          { return mEventId; }
inline Int_t    StPicoEvent::fillId() const           { return (Int_t)mFillId; }
inline Float_t  StPicoEvent::bField() const           { return mBField; }
inline StThreeVectorF const & StPicoEvent::primaryVertex() const { return mPrimaryVertex; }
inline StThreeVectorF const & StPicoEvent::primaryVertexError() const { return mPrimaryVertexError; }
inline Int_t    StPicoEvent::triggerWord() const      { return mTriggerWord; }
inline Int_t    StPicoEvent::triggerWordMtd() const   { return mTriggerWordMtd; }
inline Int_t    StPicoEvent::refMultPos() const       { return (Int_t)mRefMultPos; }
inline Int_t    StPicoEvent::refMultNeg() const       { return (Int_t)mRefMultNeg; }
inline Int_t    StPicoEvent::refMultFtpcEast() const  { return (Int_t)mRefMultFtpcEast; }
inline Int_t    StPicoEvent::refMultFtpcWest() const  { return (Int_t)mRefMultFtpcWest; }
inline Int_t    StPicoEvent::refMult() const          { return (Int_t)(mRefMultPos+mRefMultNeg); }
inline Int_t    StPicoEvent::refMultFtpc() const      { return (Int_t)(mRefMultFtpcEast+mRefMultFtpcWest); }
inline Int_t    StPicoEvent::refMult2PosEast() const      { return (Int_t)mRefMult2PosEast; }
inline Int_t    StPicoEvent::refMult2NegEast() const      { return (Int_t)mRefMult2NegEast; }
inline Int_t    StPicoEvent::refMult2PosWest() const      { return (Int_t)mRefMult2PosWest; }
inline Int_t    StPicoEvent::refMult2NegWest() const      { return (Int_t)mRefMult2NegWest; }
inline Int_t    StPicoEvent::refMultHalfPosEast() const { return (Int_t)mRefMultHalfPosEast; }
inline Int_t    StPicoEvent::refMultHalfNegEast() const { return (Int_t)mRefMultHalfNegEast; }
inline Int_t    StPicoEvent::refMultHalfPosWest() const { return (Int_t)mRefMultHalfPosWest; }
inline Int_t    StPicoEvent::refMultHalfNegWest() const { return (Int_t)mRefMultHalfNegWest; }
inline Int_t    StPicoEvent::refMult2East() const       { return (Int_t)(mRefMult2PosEast+mRefMult2NegEast); }
inline Int_t    StPicoEvent::refMult2West() const       { return (Int_t)(mRefMult2PosWest+mRefMult2NegWest); }
inline Int_t    StPicoEvent::refMult2() const           { return (Int_t)(mRefMult2PosEast+mRefMult2NegEast+mRefMult2PosWest+mRefMult2NegWest); }
inline Int_t    StPicoEvent::refMultHalfEast() const    { return (Int_t)(mRefMultHalfPosEast+mRefMultHalfNegEast); }
inline Int_t    StPicoEvent::refMultHalfWest() const    { return (Int_t)(mRefMultHalfPosWest+mRefMultHalfNegWest); }
inline Int_t    StPicoEvent::grefMult() const           { return (Int_t)(mGRefMult); }
inline Int_t    StPicoEvent::numberOfPxlInnerHits() const { return (Int_t)(mNHitsHFT[0]); }
inline Int_t    StPicoEvent::numberOfPxlOuterHits() const { return (Int_t)(mNHitsHFT[1]); }
inline Int_t    StPicoEvent::numberOfIstHits() const      { return (Int_t)(mNHitsHFT[2]); }
inline Int_t    StPicoEvent::numberOfSsdHits() const      { return (Int_t)(mNHitsHFT[3]); }

inline Int_t    StPicoEvent::nVpdHitsEast() const     { return (Int_t)mNVpdHitsEast; }
inline Int_t    StPicoEvent::nVpdHitsWest() const     { return (Int_t)mNVpdHitsWest; } 
inline Int_t    StPicoEvent::nT0() const              { return (Int_t)mNT0; }
inline Float_t  StPicoEvent::vzVpd() const            { return (Float_t)mVzVpd/100.; }

inline Float_t  StPicoEvent::ZDCx() const             { return (Float_t)mZDCx; }
inline Float_t  StPicoEvent::BBCx() const             { return (Float_t)mBBCx; }
inline Float_t  StPicoEvent::Vpd(int i) const         { return (Float_t)mVpd[i]; }
inline Float_t  StPicoEvent::ZdcSumAdcEast() const    { return (Float_t)mZdcSumAdcEast; }
inline Float_t  StPicoEvent::ZdcSumAdcWest() const    { return (Float_t)mZdcSumAdcWest; }
inline Float_t  StPicoEvent::ZdcSmdEastHorizontal(int i) const { return (Float_t)mZdcSmdEastHorizontal[i]; }
inline Float_t  StPicoEvent::ZdcSmdEastVertical(int i) const   { return (Float_t)mZdcSmdEastVertical[i]; }
inline Float_t  StPicoEvent::ZdcSmdWestHorizontal(int i) const { return (Float_t)mZdcSmdWestHorizontal[i]; }
inline Float_t  StPicoEvent::ZdcSmdWestVertical(int i) const   { return (Float_t)mZdcSmdWestVertical[i]; }

inline Float_t StPicoEvent::backgroundRate() const             { return mBackgroundRate; }
inline Float_t StPicoEvent::bbcBlueBackgroundRate() const      { return mBbcBlueBackgroundRate; }
inline Float_t StPicoEvent::bbcYellowBackgroundRate() const    { return mBbcYellowBackgroundRate; }
inline Float_t StPicoEvent::bbcEastRate() const { return mBbcEastRate; }
inline Float_t StPicoEvent::bbcWestRate() const { return mBbcWestRate; }  
inline Float_t StPicoEvent::zdcEastRate() const { return mZdcEastRate; }
inline Float_t StPicoEvent::zdcWestRate() const { return mZdcWestRate; }

inline Float_t StPicoEvent::spaceCharge() const { return mSpaceCharge; }

inline UShort_t StPicoEvent::btofTrayMultiplicity() const { return mbTofTrayMultiplicity ; }
inline UShort_t StPicoEvent::numberOfGlobalTracks() const { return mNumberOfGlobalTracks ; }

inline Float_t  StPicoEvent::ranking() const { return mRanking ; }
inline UShort_t StPicoEvent::nBEMCMatch() const { return mNBEMCMatch ; }
inline UShort_t StPicoEvent::nBTOFMatch() const { return mNBTOFMatch ; }

inline UShort_t StPicoEvent::bbcAdcEast(const Int_t i) const { return mBbcAdcEast[i]; }
inline UShort_t StPicoEvent::bbcAdcWest(const Int_t i) const { return mBbcAdcWest[i]; }

inline Int_t   StPicoEvent::ht_th(const Int_t i) const { return mHT_Th[i]; }
inline Int_t   StPicoEvent::jp_th(const Int_t i) const { return mJP_Th[i]; }

inline void StPicoEvent::setHT_Th(const Int_t i, const Int_t th) { mHT_Th[i] = (UChar_t)th; }
inline void StPicoEvent::setJP_Th(const Int_t i, const Int_t th) { mJP_Th[i] = (UChar_t)th; }  
#endif

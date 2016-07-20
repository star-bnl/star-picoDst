#ifndef StPicoMtdTrigger_h
#define StPicoMtdTrigger_h

class StMuDst;
#include "TObject.h"

class StPicoMtdTrigger : public TObject {
 public:
  StPicoMtdTrigger();
  StPicoMtdTrigger(const StMuDst& muDst);
  virtual ~StPicoMtdTrigger();

  // VPD tag sum
  UShort_t   getVpdTacSum();

  // THUB
  UInt_t     getTHUBtime(const Int_t thub);

  // qt: 1-4, pos: 1-8
  UShort_t   getQTtacSum(const Int_t qt, const Int_t pos);
  UShort_t   getMT101Tac(const Int_t qt, const Int_t index);
  UShort_t   getMT101Id(const Int_t qt, const Int_t index);
  UChar_t    getTF201TriggerBit();

  void       getMaximumQTtac(const Int_t qt, Int_t& pos1, Int_t& pos2);
  Char_t     shouldHaveRejectEvent();

 protected:
  static const UShort_t mtd_qt_tac_max = 4095;
  static const UShort_t mtd_qt_tac_min = 100;
  static const UShort_t mtd_qt_tac_diff_range_abs = 600;


 private:
  UShort_t      mVpdTacSum;      // VPD tac sum
  UInt_t        mTHUBtime[2];    // trigger time from THUB (backleg 1-15 uses THUB2, 16-30 uses THUB1)
  UShort_t      mQTtacSum[4][8]; // tacSum in 4 QT boards
  UShort_t      mMT101Tac[4][2]; // two largest tacSum from each QT board
  UChar_t       mMT101Id[4][2];  // id of largest tacSum -> position
  UChar_t       mTF201TriggerBit; // final trigger bit to TCU
  Char_t        mShouldHaveRejectEvent; // indication of event status in filtering
                                        // 0 - events not triggered by di-muon
                                        // 1 - events should have been rejected 
                                        // if only triggered by di-muon
                                        // 2 - events pass filtering cuts

  ClassDef(StPicoMtdTrigger,1);
};
inline UShort_t StPicoMtdTrigger::getVpdTacSum()                                 { return mVpdTacSum;             }
inline UInt_t   StPicoMtdTrigger::getTHUBtime(const Int_t thub)                  { return mTHUBtime[thub-1];      }
inline UShort_t StPicoMtdTrigger::getQTtacSum(const Int_t qt, const Int_t pos)   { return mQTtacSum[qt-1][pos-1]; }
inline UShort_t StPicoMtdTrigger::getMT101Tac(const Int_t qt, const Int_t index) { return mMT101Tac[qt-1][index]; }
inline UShort_t StPicoMtdTrigger::getMT101Id(const Int_t qt, const Int_t index)  { return mMT101Id[qt-1][index];  }
inline UChar_t  StPicoMtdTrigger::getTF201TriggerBit()                           { return mTF201TriggerBit;       }
inline Char_t   StPicoMtdTrigger::shouldHaveRejectEvent()                        { return mShouldHaveRejectEvent; }
#endif

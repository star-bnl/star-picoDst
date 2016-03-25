#ifndef StPicoEmcTrigger_h
#define StPicoEmcTrigger_h

#include "TObject.h"

class StPicoEmcTrigger : public TObject {
 public:
  StPicoEmcTrigger();
  StPicoEmcTrigger(int flag, int id, int adc);
  virtual ~StPicoEmcTrigger();

  virtual void Print(const Char_t *option = "") const;  ///< Print trigger info

  Int_t   flag() const;
  Int_t   id() const;
  Int_t   adc() const;

 protected:
  UChar_t mFlag;   // 0x1: ht0, 0x2: ht1, 0x4: ht2; 0x8: ht3
  UShort_t mId;    // soft id.  bjp: 1-18, ht: 1-4800
  UShort_t mAdc;   // adc

  ClassDef(StPicoEmcTrigger, 1)
};
inline Int_t StPicoEmcTrigger::flag() const           { return (Int_t)mFlag; }
inline Int_t StPicoEmcTrigger::id() const             { return (Int_t)mId; }
inline Int_t StPicoEmcTrigger::adc() const            { return (Int_t)mAdc; }
#endif

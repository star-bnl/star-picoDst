#ifndef StPicoTrigger_hh
#define StPicoTrigger_hh

class StPicoDst;

#include "TObject.h"
#include "stdio.h"

class StPicoTrigger : public TObject {
 public:
  StPicoTrigger();
  ~StPicoTrigger();
  StPicoTrigger(int, int, int);
  void    Clear(const Option_t *opt="");
  virtual void Print(const Char_t *option = "") const;  ///< Print trigger info
 
  Int_t   flag() const           { return (Int_t)mFlag; }
  Int_t   id() const             { return (Int_t)mId; }
  Int_t   adc() const            { return (Int_t)mAdc; }

 protected:
  UChar_t mFlag;   // 0x1: ht0, 0x2: ht1, 0x4: ht2; 0x8: ht3
  UShort_t mId;    // soft id.  bjp: 1-18, ht: 1-4800
  UShort_t mAdc;   // adc
  

  friend class StPicoDst;

  ClassDef(StPicoTrigger, 1)
};

#endif

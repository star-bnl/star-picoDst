#ifndef StPicoMtdHit_h
#define StPicoMtdHit_h

class PicoDst;
class StMuMtdHit;
#include "TObject.h"

using namespace std;

class StPicoMtdHit : public TObject {
 public:
  StPicoMtdHit();
  StPicoMtdHit(const StMuMtdHit* hit);
  ~StPicoMtdHit();

  virtual void Print(const Char_t *option = "") const; 

  void  setTriggerFlag(Int_t const flag);
  Int_t  gChannel()    const;
  Int_t  backleg()     const;
  Int_t  module()      const;
  Int_t  cell()        const;
  Int_t  triggerFlag() const;
  
  pair<Float_t,Float_t> leadingEdgeTime()  const;
  pair<Float_t,Float_t> trailingEdgeTime() const;
  pair<Float_t,Float_t> tot() const;
  
 protected:
  Short_t mgChannel; // mgChannel = (backleg-1) * 60 + (module-1) * 12 + cell
  UChar_t mTriggerFlag; // # of hits in the corresponding trigger unit that fired the trigger
  pair<Float_t,Float_t>  mLeadingEdgeTime;
  pair<Float_t,Float_t>  mTrailingEdgeTime;
	
  ClassDef(StPicoMtdHit,1)
};
inline void StPicoMtdHit::setTriggerFlag(Int_t const flag) { mTriggerFlag = (UChar_t)flag;}
inline Int_t StPicoMtdHit::gChannel()    const { return (Int_t)mgChannel;             }
inline Int_t StPicoMtdHit::backleg()     const { return (Int_t)mgChannel/60 + 1;      }
inline Int_t StPicoMtdHit::module()      const { return ((Int_t)mgChannel%60)/12 + 1; }
inline Int_t StPicoMtdHit::cell()        const { return (Int_t)mgChannel%12;          }
inline Int_t StPicoMtdHit::triggerFlag() const { return (Int_t) mTriggerFlag;         }
inline pair<Float_t,Float_t> StPicoMtdHit::leadingEdgeTime()  const { return mLeadingEdgeTime;  }
inline pair<Float_t,Float_t> StPicoMtdHit::trailingEdgeTime() const { return mTrailingEdgeTime; }
inline pair<Float_t,Float_t> StPicoMtdHit::tot() const
{ return pair<Float_t,Float_t>(mTrailingEdgeTime.first - mLeadingEdgeTime.first, mTrailingEdgeTime.second - mLeadingEdgeTime.second); }
#endif

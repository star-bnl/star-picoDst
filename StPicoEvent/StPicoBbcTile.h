/*
   BBC tile class for STAR picoDst
   Total size of this object is 6 bytes

   If all BBC inner tiles are saved, this makes 2*16*6 = 192 bytes
   Usually outer BBC tiles will not be saved, but if they are then this makes 384 bytes

   - Mike Lisa 20 May 2017
*/
#ifndef StPicoBbcTile_h
#define StPicoBbcTile_h

#include "TObject.h"

class StPicoBbcTile : public TObject
{
public:

  StPicoBbcTile();
  StPicoBbcTile(Short_t ID, Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC);

  virtual void Print(const Char_t *option = "") const;

  void setId(Short_t ID);
  void setQTdata(Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC);

  Bool_t hasTAC() const;
  Short_t adc() const;
  Short_t tac() const;
  Short_t tdc() const;
  Bool_t isEast() const;
  Short_t id() const;

  Short_t pmtNumber() const;  // 1...32

protected:
  // mId:
  // * for BBC: Phototube #
  // * sign for both, +/- = West/East
  Short_t mId;
  ULong_t mQTdata; // bits 0-11 are ADC;  bits 12-23 are TAC;  bits 24-28 are TDC;  bit 29 is noTAC flag

  ClassDef(StPicoBbcTile, 1)
};

inline void StPicoBbcTile::setId(Short_t ID) {mId = ID;}

inline Bool_t  StPicoBbcTile::isEast() const {return (mId < 0);}
inline Short_t StPicoBbcTile::id() const {return mId;}

inline Short_t StPicoBbcTile::pmtNumber() const {return abs(mId) < 100 ? abs(100) : -999;}

inline Short_t StPicoBbcTile::adc() const {Short_t x = (mQTdata & 0x0FFF); return x;}
inline Short_t StPicoBbcTile::tac() const {Short_t x = ((mQTdata >> 12) & 0x0FFF); return x;}
inline Short_t StPicoBbcTile::tdc() const {Short_t x = ((mQTdata >> 24) & 0x001F); return x;}
inline Bool_t  StPicoBbcTile::hasTAC() const {return ((mQTdata >> 29 & 0x1) != 0);}

#endif

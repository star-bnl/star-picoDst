/*
   EPD and BBC tile class for STAR picoDst
   Total size of this object is 6 bytes

   If all BBC inner tiles are saved, this makes 2*16*6 = 192 bytes
   Usually outer BBC tiles will not be saved, but if they are then this makes 384 bytes

   If all EPD tiles are saved, this makes 2*12*31*6 = 4.4 kB
   1/8 install in 2017:  if all EPD tiles are saved, this makes 1*3*31*6 = 558 bytes
   * in 2017, we will save all EPD tiles.  After 2017, we will not.
   - Mike Lisa 20 May 2017
*/
#ifndef StPicoBbcEpdTile_h
#define StPicoBbcEpdTile_h

#include "TObject.h"

class StPicoBbcEpdTile : public TObject
{
public:

  StPicoBbcEpdTile();
  StPicoBbcEpdTile(Short_t ID, Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC);
  virtual ~StPicoBbcEpdTile();

  virtual void Print(const Char_t *option = "") const;

  void setId(Short_t ID);
  void setQTdata(Short_t ADC, Short_t TAC, Short_t TDC, Bool_t hasTAC);

  Bool_t hasTAC() const;
  Short_t adc() const;
  Short_t tac() const;
  Short_t tdc() const;
  Bool_t isBbc() const;
  Bool_t isEpd() const;
  Bool_t isEast() const;
  Short_t id() const;

  Short_t BbcPmtNumber() const;  // 1...32
  Short_t EpdPP() const;         // 1...12
  Short_t EpdTT() const;         // 1...31

protected:
  // mId:
  // * for EPD: 100*PP+TT
  // * for BBC: Phototube #
  // * sign for both, +/- = West/East
  // PP, TT, Phototube indices start at 1, not zero.
  Short_t mId;
  ULong_t mQTdata; // bits 0-11 are ADC;  bits 12-23 are TAC;  bits 24-28 are TDC;  bit 29 is noTAC flag

  ClassDef(StPicoBbcEpdTile, 1)
};

inline void StPicoBbcEpdTile::setId(Short_t ID) {mId = ID;}

inline Bool_t  StPicoBbcEpdTile::isEast() const {return (mId < 0);}
inline Bool_t  StPicoBbcEpdTile::isBbc() const {return (abs(mId) < 100);}
inline Bool_t  StPicoBbcEpdTile::isEpd() const {return (abs(mId) > 100);}
inline Short_t StPicoBbcEpdTile::id() const {return mId;}

inline Short_t StPicoBbcEpdTile::BbcPmtNumber() const {return abs(mId) < 100 ? abs(100) : -999;}
inline Short_t StPicoBbcEpdTile::EpdPP() const {return abs(mId) > 100 ? abs(mId / 100) : -999;}
inline Short_t StPicoBbcEpdTile::EpdTT() const {return abs(mId) > 100 ? abs(mId % 100) : -999;}

inline Short_t StPicoBbcEpdTile::adc() const {Short_t x = (mQTdata & 0x0FFF); return x;}
inline Short_t StPicoBbcEpdTile::tac() const {Short_t x = ((mQTdata >> 12) & 0x0FFF); return x;}
inline Short_t StPicoBbcEpdTile::tdc() const {Short_t x = ((mQTdata >> 24) & 0x001F); return x;}
inline Bool_t  StPicoBbcEpdTile::hasTAC() const {return ((mQTdata >> 29 & 0x1) != 0);}

#endif

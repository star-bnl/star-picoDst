/*
   EPD tile class for STAR picoDst
   Total size of this object is 6 bytes

   If all BBC inner tiles are saved, this makes 2*16*6 = 192 bytes
   Usually outer BBC tiles will not be saved, but if they are then this makes 384 bytes

   If all EPD tiles are saved, this makes 2*12*31*6 = 4.4 kB
   1/8 install in 2017:  if all EPD tiles are saved, this makes 1*3*31*6 = 558 bytes
   * in 2017, we will save all EPD tiles.  After 2017, we will not.
   - Mike Lisa 20 May 2017
*/
#ifndef StPicoEpdTile_h
#define StPicoEpdTile_h

#include "TObject.h"

class StPicoEpdTile : public TObject
{
public:

  StPicoEpdTile();
  StPicoEpdTile(int PP, int TT, int EW, int ADC, int TAC, int TDC, bool hasTAC);

  virtual void Print(const Char_t *option = "") const;

  Bool_t hasTAC() const;
  Short_t adc() const;
  Short_t tac() const;
  Short_t tdc() const;
  Bool_t isEast() const;

  Short_t PP() const;         // 1...12
  Short_t TT() const;         // 1...31

protected:
  // mId:
  // * for EPD: 100*PP+TT
  // * sign: +/- = West/East
  // PP, TT, Phototube indices start at 1, not zero.
  Short_t mId;
  ULong_t mQTdata; // bits 0-11 are ADC;  bits 12-23 are TAC;  bits 24-28 are TDC;  bit 29 is noTAC flag

  ClassDef(StPicoEpdTile, 1)
};

inline Bool_t  StPicoEpdTile::isEast() const {return (mId < 0);}

inline Short_t StPicoEpdTile::PP() const {return abs(mId) > 100 ? abs(mId / 100) : -999;}
inline Short_t StPicoEpdTile::TT() const {return abs(mId) > 100 ? abs(mId % 100) : -999;}

inline Short_t StPicoEpdTile::adc() const {Short_t x = (mQTdata & 0x0FFF); return x;}
inline Short_t StPicoEpdTile::tac() const {Short_t x = ((mQTdata >> 12) & 0x0FFF); return x;}
inline Short_t StPicoEpdTile::tdc() const {Short_t x = ((mQTdata >> 24) & 0x001F); return x;}
inline Bool_t  StPicoEpdTile::hasTAC() const {return ((mQTdata >> 29 & 0x1) != 0);}

#endif

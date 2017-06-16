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

  bool hasTAC() const;
  int  adc() const;
  int  tac() const;
  int  tdc() const;
  bool isEast() const;

  int PP() const;         // 1...12
  int TT() const;         // 1...31

protected:
  // mId:
  // * for EPD: 100*PP+TT
  // * sign: +/- = West/East
  // PP, TT, Phototube indices start at 1, not zero.
  Short_t mId;
  ULong_t mQTdata; // bits 0-11 are ADC;  bits 12-23 are TAC;  bits 24-28 are TDC;  bit 29 is noTAC flag

  ClassDef(StPicoEpdTile, 1)
};

inline bool StPicoEpdTile::isEast() const {return (mId < 0);}

inline int  StPicoEpdTile::PP() const { return mId / 100; }
inline int  StPicoEpdTile::TT() const { return mId % 100; }

inline int  StPicoEpdTile::adc() const { return mQTdata & 0x0FFF; }
inline int  StPicoEpdTile::tac() const { return (mQTdata >> 12) & 0x0FFF; }
inline int  StPicoEpdTile::tdc() const { return (mQTdata >> 24) & 0x001F; }
inline bool StPicoEpdTile::hasTAC() const { return (mQTdata >> 29) & 0x1; }

#endif

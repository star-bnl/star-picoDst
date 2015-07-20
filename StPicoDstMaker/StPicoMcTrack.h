#ifndef StPicoMcTrack_hh
#define StPicoMcTrack_hh

#include <cmath>

class StMuMcTrack;
class StPicoDst;
class StMcTrack;
//class StTrack;
class StGlobalTrack;
#include "TObject.h"
#include "StThreeVectorF.hh"
#include "TVector2.h"
#include <stdio.h>
#include <math.h>

class StPicoMcTrack : public TObject {
 public:
  //Constructor, copu cosntructo & destructor
  StPicoMcTrack();
  ~StPicoMcTrack() {;}
  StPicoMcTrack(StPicoMcTrack *);
  StPicoMcTrack(StMcTrack *, const StGlobalTrack *);
  // -- Getter functions for mc track
  Int_t mcId() const;
  Int_t GePid() const;
  Int_t parentId() const;
  Int_t assoId() const;
  Int_t hitsPxl1() const;
  Int_t hitsPxl2() const;
  Int_t hitsIst() const;
  Int_t hitsSst() const;
  Int_t hitsTpc() const;
  Int_t Pxl1Truth() const;
  Int_t Pxl2Truth() const;
  Int_t IstTruth() const;
  Int_t SsdTruth() const;
  float pseudorapidity() const;
  StThreeVectorF const & Mom() const;
  StThreeVectorF const & Origin() const;
  // -- 
 protected: 
  UShort_t mMcId;
  Short_t mGePid;
  UShort_t mParentId;
  UShort_t mAssoId;
  UShort_t nHitsPxl1, nHitsPxl2, nHitsIst, nHitsSst;
  UShort_t nHitsTpc, nHitsTpcCommon;
  UShort_t mTruthBit;
  float mEta;
  StThreeVectorF mMcMomentum;
  StThreeVectorF mOrigin;
  friend class StPicoDst;

  ClassDef(StPicoMcTrack, 1)
};
inline Int_t StPicoMcTrack:: mcId() const              { return (Int_t) mMcId; }
inline Int_t StPicoMcTrack:: GePid() const             { return (Int_t) mGePid; }
inline Int_t StPicoMcTrack:: parentId() const          { return (Int_t) mParentId; }
inline Int_t StPicoMcTrack:: assoId() const           { return (Int_t)mAssoId; }
inline Int_t StPicoMcTrack:: hitsPxl1() const          {return (Int_t)nHitsPxl1; }
inline Int_t StPicoMcTrack:: hitsPxl2() const          {return (Int_t)nHitsPxl2; }
inline Int_t StPicoMcTrack:: hitsIst() const          {return (Int_t)nHitsIst; }
inline Int_t StPicoMcTrack:: hitsSst() const          {return (Int_t)nHitsSst; }
inline Int_t StPicoMcTrack:: hitsTpc() const          {return (Int_t)nHitsTpc; }
inline Int_t StPicoMcTrack:: Pxl1Truth() const         {return (Int_t) mTruthBit & 1; }
inline Int_t StPicoMcTrack:: Pxl2Truth() const         {return (Int_t) mTruthBit & (1<<1); }
inline Int_t StPicoMcTrack:: IstTruth() const         {return (Int_t) mTruthBit & (1<<2); }
inline Int_t StPicoMcTrack:: SsdTruth() const         {return (Int_t) mTruthBit & (1<<3); }
inline float StPicoMcTrack:: pseudorapidity() const { return mEta; } 
inline StThreeVectorF const & StPicoMcTrack::Mom() const    { return mMcMomentum; }
inline StThreeVectorF const & StPicoMcTrack::Origin() const { return mOrigin; }

#endif

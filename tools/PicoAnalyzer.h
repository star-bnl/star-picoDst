#ifndef PicoAnalyzer__
#define PicoAnalyzer__

#include "TObject.h"

class TTree;
class TBranch;
class TLeaf;
class TClonesArray;
class StPicoEvent;
class TH1D;
class TH2D;
class TProfile;
class TProfile2D;
class TNtuple;
class TFile;
class StEpdGeom;
class StBbcGeom;
class TRandom3;


class PicoAnalyzer : public TObject {
 public:
  PicoAnalyzer();
  ~PicoAnalyzer();

  void SetPicoDst(TTree*);
  short Init();
  short Make(int iEvent);
  short Finish();

 private:

  void ReadLeaves();   // explictly reads the relevant leaves, from the StPicoEvent object

  int FindCent(int RefMult);   // utility class just giving centrality bin.  Copied directly from Isaac 1 May 2018

  double GetBbcPmtPhi(short PmtId);
  int nEvents;

  StEpdGeom* mEpdGeom;
  StBbcGeom* mBbcGeom;

  double mNmipQtB;  // ADC value of MIP peak on rings 6-16 (read out thru QT32Bs)
  double mNmipQtC;  // ADC value of MIP peak on rings 1-5  (read out thru QT32Cs)

  double mnMipThreshold;  // low-signal threshold, to cut out noise basically.

  // the tree, branches and leaves
  TTree* mPicoDst;
  TBranch* mEpdBranch;
  TBranch* mBbcBranch;
  TBranch* mEventBranch;

  // dealing directly with the TLeaf objects is the only way I can get access to the info in the StPicoEvent object
  // a little clumsy but it has its "elegance," I suppose.  And it's pretty fast
  TLeaf* mRefMultNegLeaf;
  TLeaf* mRefMultPosLeaf;
  TLeaf* mVxLeaf;
  TLeaf* mVyLeaf;
  TLeaf* mVzLeaf;
  TLeaf* mRunIdLeaf;
  TLeaf* mVzVpdLeaf;

  // the data objects
  TClonesArray* mEpdHits;
  TClonesArray* mBbcHits;
  int mRefMult;
  double mPrimVertPos[3];         // primary vertex position (x,y,z)
  int mRunId;
  double mVzVpd;


  // 1D histograms
  TH1D* mHisto1D[40];            // miscellaneous 1D histograms
  TH1D* mNmipDists[2][12][31];   // nMIP distributions for all tiles
  TH1D* mRefMultHist[9];         // convenient to have refMult distributions for the 9 centrality bins

  // 2D histograms
  TH2D* mHisto2D[40];           // miscellaneous 2D histograms
  TH2D* mEpdEwPsi[3][3];        // [order n-1][correction level].
  TH2D* mBbcEwPsi[3][3];        // [order n-1][correction level].

  TH2D* mEpdEwPsi_midCentral[3][3];        // [order n-1][correction level].  Just to focus on 10-40%, for example
  TH2D* mBbcEwPsi_midCentral[3][3];        // [order n-1][correction level].  Just to focus on 10-40%, for example

  TH2D* mWestXY[16];    // shows locations of EPD hits when ONLY one inner BBC tile fires on West side
  TH2D* mEastXY[16];    // shows locations of EPD hits when ONLY one inner BBC tile fires on East side


  // profiles
  TProfile* mEpdAveCos[3][3];  // [order n-1][correction level].
  TProfile* mBbcAveCos[3][3];  // [order n-1][correction level].

  //  these are shift correction factors that we MAKE now
  TProfile2D* mEpdShiftOutput_sin[2][3];    // [ew][order-1]
  TProfile2D* mEpdShiftOutput_cos[2][3];    // [ew][order-1]
  TProfile2D* mBbcShiftOutput_sin[2][3];    // [ew][order-1]
  TProfile2D* mBbcShiftOutput_cos[2][3];    // [ew][order-1]

  //  these are shift correction factors that we made before, and USE now
  TProfile2D* mEpdShiftInput_sin[2][3];    // [ew][order-1]
  TProfile2D* mEpdShiftInput_cos[2][3];    // [ew][order-1]
  TProfile2D* mBbcShiftInput_sin[2][3];    // [ew][order-1]
  TProfile2D* mBbcShiftInput_cos[2][3];    // [ew][order-1]


  // ntuples
  TNtuple* mQ1vectorNtuple;      // Q1 vectors ring-by-ring. For offline weight optimization
  TNtuple* mQ2vectorNtuple;      // Q2 vectors ring-by-ring. For offline weight optimization


  // TFiles (to store histograms and data)
  TFile* mHistoFile;
  TFile* mQ1NtupleFile;
  TFile* mQ2NtupleFile;
  TFile* mCorrectionInputFile;
  TFile* mCorrectionOutputFile;

  TRandom3* mRan;


//  StPicoEvent* mPicoEvent;  // too bad, can't read this due to bloody StThreeVectorF




};


#endif

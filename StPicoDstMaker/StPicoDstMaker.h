#ifndef StPicoDstMaker_h
#define StPicoDstMaker_h

#include <vector>
#include <utility>

#include "TClonesArray.h"

#include "StChain/StMaker.h"
#include "StPicoDstMaker/StPicoEnumerations.h"
#include "StPicoDstMaker/StPicoArrays.h"

class TFile;
class TTree;
class StMuDst;
class StMuTrack;
class StEmcCollection;
class StEmcPosition;
class StEmcGeom;
class StEmcRawHit;
class StPicoDst;
class StPicoEvent;



class StPicoDstMaker : public StMaker
{
public:
  StPicoDstMaker(char const* name = "PicoDst");
  StPicoDstMaker(int mode, char const* fileName = "", char const* name = "PicoDst");
  virtual ~StPicoDstMaker();

  virtual Int_t Init();
  virtual Int_t InitRun(Int_t const runnumber);
  virtual Int_t Make();
  virtual void  Clear(Option_t* option = "");
  virtual Int_t Finish();

  void printArrays();
  void SetStatus(char const* arrType, int status);

  void setRunNumber(Int_t);
  void setProdMode(Int_t);
  void setEmcMode(bool const mode = true); // 0:No EMC, 1:EMC On
  /// Returns null pointer if no StPicoDst
  StPicoDst* picoDst();
  /// In read mode, returns pointer to the chain of .picoDst.root files
  TChain* chain();
  /// Returns pointer to the current TTree, the top level io structure
  TTree* tree();

  /// Sets the split level for the file and all branches. Please refer to the ROOT manual (http://root.cern.ch) for more info
  void setSplit(int = 99);
  /// Sets the buffer size for all branches.
  void setBufferSize(int = 65536 * 4);
  /// Sets the compression level for the file and all branches. 0 means no compression, 9 is the higher compression level.
  void setCompression(int comp = 9);

  void setVtxMode(int);

protected:

  void streamerOff();

  void openWrite();
  void write();
  void closeWrite();
  Int_t openRead();
  void  read();
  void setBranchAddresses();
  void closeRead();
  void setBranchAddresses(TChain*);

  void buildEmcIndex();
  void initEmc();
  void finishEmc();

  Bool_t initMtd(Int_t const runnumber);

  void clearArrays();
  void createArrays();

  Int_t MakeRead();
  Int_t MakeWrite();

  void fillTracks();
  void fillEvent();
  void fillEmcTrigger();
  void fillMtdTrigger();
  void fillBTOWHits();
  void fillBTofHits();
  void fillMtdHits();

  bool getBEMC(StMuTrack* , int*, int*, float*, float*, int*, int*);
  bool selectVertex();

  enum ioMode {ioRead, ioWrite};
  // production modes for different data sets
  enum prodMode {minbias, central, ht, minbias2};

  StMuDst*   mMuDst;
  StEmcCollection* mEmcCollection;
  StEmcPosition*   mEmcPosition;
  StEmcGeom*       mEmcGeom[4];
  StEmcRawHit*     mEmcIndex[4800];
  StPicoDst* mPicoDst;
  Float_t    mBField;

  Int_t      mIoMode;         //! I/O mode:  0: - read,   1: - write
  Int_t      mProdMode;       //! prod mode: 0: - mb, 1: - central, 2: - ht, 3: - mb2, mb with phi weight and q-vector calculation, 4: - save only electron or muon candidates
  bool       mEmcMode;        //! EMC ON(=1)/OFF(=0)
  Int_t      mVtxMode;

  TString   mInputFileName;        //! *.list - MuDst or picoDst
  TString   mOutputFileName;       //! FileName
  TFile*    mOutputFile;
  Int_t     mRunNumber;

  TChain*   mChain;
  TTree*    mTTree;

  int mEventCounter;
  int mSplit;
  int mCompression;
  int mBufferSize;

  // MTD map from backleg to QT
  Int_t  mModuleToQT[30][5];        // Map from module to QT board index
  Int_t  mModuleToQTPos[30][5];     // Map from module to the position on QA board
  Int_t  mQTtoModule[8][8];         // Map from QT board to module
  Int_t  mQTSlewBinEdge[8][16][8];  // Bin Edge for QT slewing correction
  Int_t  mQTSlewCorr[8][16][8];     // QT Slewing correction

  TClonesArray*   mPicoArrays[__NALLPICOARRAYS__];
  char            mStatusArrays[__NALLPICOARRAYS__];

  ClassDef(StPicoDstMaker, 0)
};

inline StPicoDst* StPicoDstMaker::picoDst() { return mPicoDst; }
inline TChain* StPicoDstMaker::chain() { return mChain; }
inline TTree* StPicoDstMaker::tree() { return mTTree; }
inline void StPicoDstMaker::setSplit(int split) { mSplit = split; }
inline void StPicoDstMaker::setCompression(int comp) { mCompression = comp; }
inline void StPicoDstMaker::setBufferSize(int buf) { mBufferSize = buf; }
inline void StPicoDstMaker::setRunNumber(int run) { mRunNumber = run; }
inline void StPicoDstMaker::setProdMode(int val) { mProdMode = val; }
inline void StPicoDstMaker::setEmcMode(bool const mode) { mEmcMode = mode; }
inline void StPicoDstMaker::setVtxMode(int const vtxMode) { mVtxMode = vtxMode; }
#endif

#ifndef StPicoDstMaker_h
#define StPicoDstMaker_h
#include "StChain/StMaker.h"
#include "TClonesArray.h"
class TFile;
class TTree;
class StFile;
class StMuDst;
class StMuEvent;
class StMuTrack;
class StBTofHeader;
class StEmcCollection;
class StEmcPosition;
class StEmcGeom;
class StBemcTables;
class StPicoDst;
class StPicoEvent;
class StPicoTrack;
class StPicoEmcTrigger;
class StPicoBTOWHit;
class StPicoBTofHit;
class StPicoCut;

#include "StPicoConstants.h"
#include "StPicoArrays.h"
#include "StEvent/StEmcRawHit.h"
#include <vector>
#include <utility>
#include <string>

#if !defined(ST_NO_NAMESPACES)
using namespace std;
#endif

class StPicoDstMaker : public StMaker {
 public:
   StPicoDstMaker(const char *name="PicoDst");
   StPicoDstMaker(int mode, const char* fileName="", const char* name="PicoDst");
   virtual ~StPicoDstMaker();

   virtual Int_t Init();
   virtual Int_t Make();
   virtual void  Clear(Option_t *option="");
   virtual Int_t Finish();

   void printArrays();
   void SetStatus(const char *arrType,int status);

   void setRunNumber(Int_t);
   void setProdMode(Int_t);
   void setEmcMode(const Int_t mode=1); // 0:No EMC, 1:EMC On
   /// Returns null pointer if no StPicoDst
   StPicoDst *picoDst();
   /// In read mode, returns pointer to the chain of .picoDst.root files
   TChain* chain();
   /// Returns pointer to the current TTree, the top level io structure
   TTree* tree();

   /// Sets the split level for the file and all branches. Please refer to the ROOT manual (http://root.cern.ch) for more info
   void setSplit(int=99);
   /// Sets the buffer size for all branches.
   void setBufferSize(int=65536*4);
   /// Sets the compression level for the file and all branches. 0 means no compression, 9 is the higher compression level.
   void setCompression(int comp=9);

 protected:
 #define saveDelete(t) { delete t; t=0;}

   void streamerOff();

   void openWrite();
   void write();
   void closeWrite();
   Int_t openRead();
   void  read();
   void setBranchAddresses();
   void closeRead();
   void setBranchAddresses(TChain*);
   void clearIndices();

   void buildEmcIndex();
   void initEmc();
   void finishEmc();

   Bool_t initMtd();

   void assignArrays();
   void clearArrays();
   void zeroArrays();
   void createArrays();
   TClonesArray* clonesArray(TClonesArray*& p, const char* type, int size, int& counter);

   Int_t MakeRead();
   Int_t MakeWrite();

   void fillTracks();
   void fillEvent();
   void fillEmcTrigger();
   void fillMtdTrigger();
   void fillBTOWHits();
   void fillBTofHits();
   void fillMtdHits();

   bool getBEMC(StMuTrack *, int*, int*, float*, float*, int*, int*);

   enum ioMode {ioRead, ioWrite};
   // production modes for different data sets
   enum prodMode {minbias, central, ht, minbias2};

   StMuDst*   mMuDst;
   StMuEvent* mMuEvent;
   StBTofHeader*    mBTofHeader;
   StEmcCollection* mEmcCollection;
   StEmcPosition*   mEmcPosition;
   StEmcGeom*       mEmcGeom[4];
   StEmcRawHit*     mEmcIndex[4800];
   StPicoDst* mPicoDst;
   StPicoCut* mPicoCut;
   Float_t    mBField;

   Int_t      mIoMode;         //! I/O mode:  0: - read,   1: - write
   Int_t      mProdMode;       //! prod mode: 0: - mb, 1: - central, 2: - ht, 3: - mb2, mb with phi weight and q-vector calculation, 4: - save only electron or muon candidates
   Int_t      mEmcMode;        //! EMC ON(=1)/OFF(=0)

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

   Int_t mIndex2Primary[nTrk];
   Int_t mMap2Track[nTrk];

   // MTD map from backleg to QT
  Int_t  mModuleToQT[30][5];     // Map from module to QT board index
  Int_t  mModuleToQTPos[30][5];  // Map from module to the position on QA board

   //
   friend class StPicoDst;

   TClonesArray*   mPicoAllArrays[__NALLPICOARRAYS__];
   TClonesArray**  mPicoArrays;
   char            mStatusArrays[__NALLPICOARRAYS__];

   ClassDef(StPicoDstMaker,1)
};

inline StPicoDst* StPicoDstMaker::picoDst() { return mPicoDst; }
inline TChain* StPicoDstMaker::chain() { return mChain; }
inline TTree* StPicoDstMaker::tree() { return mTTree; }
inline void StPicoDstMaker::setSplit(int split) { mSplit = split;}
inline void StPicoDstMaker::setCompression(int comp) { mCompression = comp;}
inline void StPicoDstMaker::setBufferSize(int buf) { mBufferSize = buf; }
inline void StPicoDstMaker::setRunNumber(int run) { mRunNumber = run; }
inline void StPicoDstMaker::setProdMode(int val) { mProdMode = val; }
inline void StPicoDstMaker::setEmcMode(const Int_t mode) { mEmcMode = mode; }
#endif

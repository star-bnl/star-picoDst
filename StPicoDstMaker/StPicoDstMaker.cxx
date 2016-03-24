#include <bitset>
#include "TRegexp.h"
#include "StChain/StChain.h"
#include "StPicoDstMaker.h"
#include "StPicoDst.h"
#include "StPicoEvent.h"
#include "StPicoTrack.h"
#include "StPicoEmcTrigger.h"
#include "StPicoMtdTrigger.h"
#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoMtdHit.h"
#include "StPicoEmcPidTraits.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoArrays.h"
#include "StPicoCut.h"
#include "StPicoConstants.h"
#include "StarRoot/THack.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TBranch.h"
#include "TRandom3.h"
#include "TRandom.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuBTofHit.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "StEvent/StBTofHeader.h"

#include "StMuDSTMaker/COMMON/StMuMtdHit.h"
#include "StMuDSTMaker/COMMON/StMuMtdPidTraits.h"
#include "tables/St_mtdModuleToQTmap_Table.h"

#include "StMuDSTMaker/COMMON/StMuEmcCollection.h"
#include "StMuDSTMaker/COMMON/StMuEmcPoint.h"
#include "StEmcUtil/projection/StEmcPosition.h"
//StEmc
#include "StEvent/StEmcCollection.h"
#include "StEvent/StEmcCluster.h"
#include "StEvent/StEmcDetector.h"
#include "StEvent/StEmcModule.h"
#include "StEvent/StEmcClusterCollection.h"
#include "StEvent/StEmcPoint.h"
#include "StEvent/StEmcRawHit.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEmcRawMaker/defines.h"
#include "StEmcRawMaker/StBemcRaw.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StEmcRawMaker/StEmcRawMaker.h"
#include "StEmcRawMaker/defines.h"
#include "StTriggerUtilities/StTriggerSimuMaker.h"
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"
#include "StTriggerUtilities/Eemc/StEemcTriggerSimu.h"
#include "StTriggerUtilities/Emc/StEmcTriggerSimu.h"
#include "StEvent/StTriggerData.h"
#include "StEvent/StDcaGeometry.h"

ClassImp(StPicoDstMaker)

#if !(ST_NO_NAMESPACES)
  using namespace units;
#endif

// Set maximum file size to 1.9 GB (Root has a 2GB limit)
#define MAXFILESIZE 1900000000

//-----------------------------------------------------------------------
StPicoDstMaker::StPicoDstMaker(const char* name) : StMaker(name),
  mMuDst(0), mMuEvent(0), mBTofHeader(0), mEmcCollection(0), mIoMode(0), mProdMode(0),
  mEmcMode(1),
  mOutputFile(0),
  mChain(0), mTTree(0), mSplit(99), mCompression(9), mBufferSize(65536*4)
{
  assignArrays();
  streamerOff();
  zeroArrays();
  createArrays();
  mPicoDst = new StPicoDst();
  mPicoCut = new StPicoCut();

  mInputFileName="";
  mOutputFileName="";
  mEventCounter=0;

  memset(mEmcIndex, 0, sizeof(mEmcIndex));

  memset(mModuleToQT,-1,sizeof(mModuleToQT));
  memset(mModuleToQTPos,-1,sizeof(mModuleToQTPos));
}
//-----------------------------------------------------------------------
StPicoDstMaker::StPicoDstMaker(int mode, const char* fileName, const char* name) : StMaker(name),
  mMuDst(0), mMuEvent(0), mBTofHeader(0), mEmcCollection(0), mIoMode(mode), mProdMode(0),
  mEmcMode(1),
  mOutputFile(0),
  mChain(0), mTTree(0), mSplit(99), mCompression(9), mBufferSize(65536*4)
{
  assignArrays();
  streamerOff();
  zeroArrays();
  createArrays();
  mPicoDst = new StPicoDst();
  mPicoCut = new StPicoCut();

  if(mIoMode==ioWrite) {
    TString inputDirFile = fileName;  // input is actually the full name including path
    Int_t index = inputDirFile.Index("st_");
    mInputFileName="";
    for(int i=index;i<(int)inputDirFile.Length();i++) {
      mInputFileName.Append(inputDirFile(i));
    }
    mOutputFileName=mInputFileName;
    mOutputFileName.ReplaceAll("MuDst.root","picoDst.root");
  }
  if(mIoMode==ioRead) {
    mInputFileName = fileName;
  }
  mEventCounter=0;

  memset(mEmcIndex, 0, sizeof(mEmcIndex));

  memset(mModuleToQT,-1,sizeof(mModuleToQT));
  memset(mModuleToQTPos,-1,sizeof(mModuleToQTPos));
}
//-----------------------------------------------------------------------
StPicoDstMaker::~StPicoDstMaker() {
//  if (mIoMode== ioWrite ) closeWrite();
//  if (mIoMode== ioRead ) closeRead();
  saveDelete(mChain);
}
//-----------------------------------------------------------------------
void StPicoDstMaker::clearIndices() {
  for(size_t i=0;i<nTrk;i++) mIndex2Primary[i] = -1;
  for(size_t i=0;i<nTrk;i++) mMap2Track[i] = -1;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::assignArrays()
{
  mPicoArrays     = mPicoAllArrays + 0;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::clearArrays()
{
  for ( int i=0; i<__NALLPICOARRAYS__; i++) {
    mPicoAllArrays[i]->Clear();
    StPicoArrays::picoArrayCounters[i] = 0;
  }
}
//-----------------------------------------------------------------------
void StPicoDstMaker::zeroArrays()
{
  memset(mPicoAllArrays, 0, sizeof(void*)*__NALLPICOARRAYS__);
  memset(mStatusArrays, (char)1, sizeof(mStatusArrays)); // defaul all ON
}
//-----------------------------------------------------------------------
void StPicoDstMaker::SetStatus(const char *arrType, int status)
{
  static const char *specNames[] = {"EventAll",0};
  static const int specIndex[] = { 0, -1};

  if (strncmp(arrType,"St",2)==0) arrType+=2;  //Ignore first "St"
  for (int i=0;specNames[i];i++) {
    if (strcmp(arrType,specNames[i])) continue;
    char *sta=mStatusArrays+specIndex[i];
    int   num=specIndex[i+1]-specIndex[i];
    memset(sta,status,num);
    LOG_INFO << "StPicoDstMaker::SetStatus " << status << " to " << specNames[i] << endm;
    if (mIoMode==ioRead)
      setBranchAddresses(mChain);
    return;
  }

  TRegexp re(arrType,1);
  for (int i=0;i<__NALLARRAYS__;i++) {
    Ssiz_t len;
    if (re.Index(StPicoArrays::picoArrayNames[i],&len) < 0)   continue;
    LOG_INFO << "StPicoDstMaker::SetStatus " << status << " to " << StPicoArrays::picoArrayNames[i] << endm;
    mStatusArrays[i]=status;
  }
  if (mIoMode==ioRead)
    setBranchAddresses(mChain);
}
//-----------------------------------------------------------------------
void StPicoDstMaker::setBranchAddresses(TChain* chain) {
  if(!chain) return;
  chain->SetBranchStatus("*",0);
  TString ts;
  for ( int i=0; i<__NALLPICOARRAYS__; i++) {
    if (mStatusArrays[i]==0) continue;
    const char *bname=StPicoArrays::picoArrayNames[i];
    TBranch *tb = chain->GetBranch(bname);
    if(!tb) {
      LOG_WARN << "setBranchAddress: Branch name " << bname << " does not exist!" << endm;
      continue;
    }
    ts = bname; ts += "*";
    chain->SetBranchStatus(ts,1);
    chain->SetBranchAddress(bname,mPicoAllArrays+i);
    assert(tb->GetAddress()==(char*)(mPicoAllArrays+i));
  }
  mTTree = mChain->GetTree();
}
//-----------------------------------------------------------------------
void  StPicoDstMaker::streamerOff() {
  StPicoEvent::Class()->IgnoreTObjectStreamer();
  StPicoTrack::Class()->IgnoreTObjectStreamer();
}
//-----------------------------------------------------------------------
void StPicoDstMaker::createArrays() {
  for ( int i=0; i<__NALLPICOARRAYS__; i++) {
    clonesArray(mPicoAllArrays[i],StPicoArrays::picoArrayTypes[i],StPicoArrays::picoArraySizes[i],StPicoArrays::picoArrayCounters[i]);
  }
  mPicoDst->set(this);
}
//-----------------------------------------------------------------------
TClonesArray* StPicoDstMaker::clonesArray(TClonesArray*& p, const char* type, int size, int& counter) {
  if(p) return p;
  p = new TClonesArray(type, size);
  counter=0;
  return p;
}

//-----------------------------------------------------------------------
Int_t StPicoDstMaker::Init(){
  if (mIoMode == ioRead) {
    openRead();     // if read
  } else if (mIoMode == ioWrite) {
    openWrite();
    if(!initMtd()) {
      LOG_ERROR << " MTD initialization error!!! " << endm;
      return kStErr;
    }
    if(mEmcMode) initEmc();
  }
  return kStOK;
}

//-----------------------------------------------------------------------
Bool_t StPicoDstMaker::initMtd()
{
  // initialize MTD maps
  memset(mModuleToQT,-1,sizeof(mModuleToQT));
  memset(mModuleToQTPos,-1,sizeof(mModuleToQTPos));

  // obtain maps from DB
  LOG_INFO << "Retrieving mtdModuleToQTmap table from database ..." << endm;
  TDataSet *dataset = GetDataBase("Geometry/mtd/mtdModuleToQTmap");
  St_mtdModuleToQTmap *mtdModuleToQTmap = static_cast<St_mtdModuleToQTmap*>(dataset->Find("mtdModuleToQTmap"));
  if(!mtdModuleToQTmap)
    {
      LOG_ERROR << "No mtdModuleToQTmap table found in database" << endm;
      return kStErr;
    }
  mtdModuleToQTmap_st *mtdModuleToQTtable = static_cast<mtdModuleToQTmap_st*>(mtdModuleToQTmap->GetTable());

  for(Int_t i=0; i<30; i++)
    {
      for(Int_t j=0; j<5; j++)
	{
	  Int_t index = i*5 + j;
	  Int_t qt = mtdModuleToQTtable->qtBoardId[index];
	  Int_t channel = mtdModuleToQTtable->qtChannelId[index];
	  mModuleToQT[i][j]    = qt;
	  if(channel<0)
	    {
	      mModuleToQTPos[i][j] = channel;
	    }
	  else
	    {
	      if(channel%8==1) mModuleToQTPos[i][j] = 1 + channel/8 * 2;
	      else             mModuleToQTPos[i][j] = 2 + channel/8 * 2;
	    }
	}
    }

  return kTRUE;
}

//-----------------------------------------------------------------------
Int_t StPicoDstMaker::Finish(){
  if (mIoMode == ioRead) {
    closeRead();
  } else if (mIoMode == ioWrite) {
    closeWrite();
    if(mEmcMode) finishEmc();
  }
  return kStOK;
}
//-----------------------------------------------------------------------
Int_t StPicoDstMaker::openRead() {
  if(!mChain) mChain = new TChain("PicoDst");
  string dirFile = mInputFileName.Data();
  if (dirFile.find(".list")!=string::npos)  {
    ifstream inputStream(dirFile.c_str());
    if(!(inputStream.good())) {
      LOG_ERROR << "ERROR: Cannot open list file " << dirFile << endm;
    }
    char line[512];
    int nFile=0;
    string ltest;
    while (inputStream.good()) {
      inputStream.getline(line,512);
      string aFile = line;
      if (inputStream.good() && aFile.find(".picoDst.root")!=string::npos) {

        TFile ftmp(line);
        if(!ftmp.IsZombie() && ftmp.GetNkeys()) {
          LOG_INFO << " Read in picoDst file " << line << endm;
          mChain->Add(line);
          nFile++;
        }
      }
    }
    LOG_INFO << " Total " << nFile << " files have been read in. " << endm;
  } else if (dirFile.find(".picoDst.root")!=string::npos)  {
    mChain->Add(dirFile.c_str());
  } else {
    LOG_WARN << " No good input file to read ... " << endm;
  }
  if(mChain) {
    setBranchAddresses(mChain);
    mPicoDst->set(this);
  }
  return kStOK;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::openWrite() {

  mOutputFile = new TFile(mOutputFileName.Data(),"RECREATE");
  LOG_INFO << " Output file: " << mOutputFileName.Data() << " created." << endm;
  mOutputFile->SetCompressionLevel(mCompression);
  TBranch* branch;
  int bufsize = mBufferSize;
  if (mSplit) bufsize /= 4;
  mTTree = new TTree("PicoDst","StPicoDst",mSplit);
  mTTree->SetMaxTreeSize(MAXFILESIZE);
  mTTree->SetAutoSave(1000000);
  for ( int i=0; i<__NALLPICOARRAYS__; i++) {
    if (mStatusArrays[i]==0) {
      cout << " Branch " << StPicoArrays::picoArrayNames[i] << " status is OFF! " << endl;
      continue;
    }
    branch = mTTree->Branch(StPicoArrays::picoArrayNames[i],&mPicoAllArrays[i],bufsize,mSplit);
  }
}
//-----------------------------------------------------------------------
void StPicoDstMaker::initEmc() {
  mEmcPosition = new StEmcPosition();
  for(int i=0;i<4;i++) {
    mEmcGeom[i] = StEmcGeom::getEmcGeom(detname[i].Data());
  }
}
//-----------------------------------------------------------------------
void StPicoDstMaker::buildEmcIndex() {
  StEmcDetector *mEmcDet = mMuDst->emcCollection()->detector(kBarrelEmcTowerId);
  memset(mEmcIndex, 0, sizeof(mEmcIndex));

  if(!mEmcDet) return;
  for (size_t iMod=1; iMod<=mEmcDet->numberOfModules(); ++iMod) {
    StSPtrVecEmcRawHit& modHits = mEmcDet->module(iMod)->hits();
    for (size_t iHit=0; iHit<modHits.size(); ++iHit) {
      StEmcRawHit* rawHit = modHits[iHit];
      if(!rawHit) continue;
      unsigned int softId = rawHit->softId(1);
      if (mEmcGeom[0]->checkId(softId)==0) { // OK
        mEmcIndex[softId-1] = rawHit;
      }

    }
  }
}
//-----------------------------------------------------------------------
void StPicoDstMaker::finishEmc() {
  if(mEmcPosition) delete mEmcPosition;
  for(int i=0;i<4;i++) {
    mEmcGeom[i] = 0;
  }
  //mEmcDet = 0;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::Clear(const char *){
  if (mIoMode==ioRead)
    return;
  clearArrays();
}
//_____________________________________________________________________________
void StPicoDstMaker::closeRead() {
  if (mChain) mChain->Delete();
  mChain = 0;
}
//_____________________________________________________________________________
void StPicoDstMaker::closeWrite() {
  if(mIoMode==ioWrite) {
    if(mOutputFile) {
      mOutputFile->Write();
      mOutputFile->Close();
    }
  }
}
//-----------------------------------------------------------------------
int StPicoDstMaker::Make(){
  int returnStarCode = kStOK;
  if (mIoMode == ioWrite){
    returnStarCode = MakeWrite();
  }
  else if (mIoMode == ioRead) returnStarCode = MakeRead();
  return returnStarCode;
}
//-----------------------------------------------------------------------
Int_t StPicoDstMaker::MakeRead() {
  if (!mChain) {
    LOG_WARN << " No input files ... ! EXIT" << endm;
    return kStWarn;
  }
  mChain->GetEntry(mEventCounter++);
  mPicoDst->set(this);
  return kStOK;
}
//-----------------------------------------------------------------------
Int_t StPicoDstMaker::MakeWrite() {
  StMuDstMaker *muDstMaker = (StMuDstMaker*)GetMaker("MuDst");
  if(!muDstMaker) {
    LOG_WARN << " No MuDstMaker " << endm; return kStWarn;
  }
  mMuDst = muDstMaker->muDst();
  if(!mMuDst) {
    LOG_WARN << " No MuDst " << endm; return kStWarn;
  }

  mMuEvent = mMuDst->event();
  if(!mMuEvent) {
    LOG_WARN << " No MuEvent " << endm; return kStWarn;
  }
  mBTofHeader = mMuDst->btofHeader();

  //////////////////////////////////////
  // select the right vertex using VPD
  /////////////////////////////////////
  Float_t vzVpd = -999;
  if(mBTofHeader) vzVpd = mBTofHeader->vpdVz();
  for(unsigned int i=0;i<mMuDst->numberOfPrimaryVertices();i++) {
    StMuPrimaryVertex *vtx = mMuDst->primaryVertex(i);
    if(!vtx) continue;
    Float_t vz = vtx->position().z();
    if(fabs(vzVpd)<100 && fabs(vzVpd-vz)<3.) {
      mMuDst->setVertexIndex(i);
      break;
    }
  }
  /////////////////////////////////////

  if(mEmcMode){
    mEmcCollection = mMuDst->emcCollection();
    if(mEmcCollection) buildEmcIndex();
  }

  clearIndices();

  Int_t refMult = mMuEvent->refMult();
  mBField = mMuEvent->magneticField();

  StThreeVectorF pVtx(0.,0.,0.);
  if(mMuDst->primaryVertex()) pVtx = mMuDst->primaryVertex()->position();

  LOG_DEBUG << " eventId = " << mMuEvent->eventId() << " refMult = " << refMult << " vtx = " << pVtx << endm;

  if(mPicoCut->passEvent(mMuEvent)) {  // keep all events in pp collisions to monitor triggers

    fillTracks();

    fillEvent();

    fillEmcTrigger();
    fillMtdTrigger();   // This must be called before fillMtdHits()
    fillBTOWHits();
    //fillBTofHits();
    fillMtdHits();

    if(Debug()) mPicoDst->printTracks();

    mTTree->Fill(); THack::IsTreeWritable(mTTree);

  }
  else
    {
      fillEvent();
      mTTree->Fill(); THack::IsTreeWritable(mTTree);
    }

  return kStOK;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::fillTracks() {
  Int_t nPrimarys = mMuDst->numberOfPrimaryTracks();
  for(int i=0;i<nPrimarys;i++) {
    StMuTrack *pTrk = (StMuTrack *)mMuDst->primaryTracks(i);
    if(!pTrk) continue;
    if(pTrk->id()<0 || pTrk->id()>=50000) {
      LOG_WARN << " This primary track has a track id out of the range : " << pTrk->id() << endm;
      continue;
    }
    mIndex2Primary[pTrk->id()] = i;
  }

  Int_t nGlobals = mMuDst->numberOfGlobalTracks();
  for(int i=0;i<nGlobals;i++) {
    StMuTrack *gTrk = (StMuTrack *)mMuDst->globalTracks(i);
    if(!gTrk) continue;
    if(!mPicoCut->passTrack(gTrk)) continue;
    if(gTrk->id()<0 || gTrk->id()>=50000) {
      LOG_WARN << " This global track has a track id out of the range : " << gTrk->id() << endm;
      continue;
    }
    int index = mIndex2Primary[gTrk->id()];
    StMuTrack *pTrk = (index>=0) ? (StMuTrack *)mMuDst->primaryTracks(index) : 0;

    int id = -1;
    int adc0; float e[5]; float dist[4]; int nhit[2]; int ntow[3];
    if(mEmcMode) getBEMC(gTrk, &id, &adc0, e, dist, nhit, ntow);

    if(mProdMode==4)
      {
	// save only electron or muon candidates
	Double_t nsigmaE = gTrk->nSigmaElectron();
	Double_t beta = (gTrk) ? gTrk->btofPidTraits().beta() : -999.;

	// running on st_mtd data
	Bool_t isTPC = kFALSE, isTOF = kFALSE, isEMC = kFALSE, isMTD = kFALSE;
	if(gTrk->index2MtdHit()>=0) isMTD = kTRUE;
	if(nsigmaE>=-3 && nsigmaE<=3)   isTPC = kTRUE;
	if(TMath::Abs(1/beta-1)<0.05) isTOF = kTRUE;
	if(gTrk->pt()>1.5 && id>=0)   isEMC = kTRUE;

	if( ! ( (isTPC&&isTOF) ||
		(isTPC&&isEMC) ||
		isMTD)
	    )
	  continue;
      }

    if(gTrk->index2Cov()<0) continue;
    StDcaGeometry *dcaG = mMuDst->covGlobTracks(gTrk->index2Cov());
    if(!dcaG) { cout << "No dca Geometry for this track !!! " << i << endm; }
    int counter = mPicoArrays[picoTrack]->GetEntries();
    new((*(mPicoArrays[picoTrack]))[counter]) StPicoTrack(gTrk, pTrk, mBField, dcaG);

    StPicoTrack *picoTrk = (StPicoTrack*)mPicoArrays[picoTrack]->At(counter);
    // Fill pid traits
    if(id>=0)
      {
	Int_t emc_index = mPicoArrays[picoEmcPidTraits]->GetEntries();
	new((*(mPicoArrays[picoEmcPidTraits]))[emc_index]) StPicoEmcPidTraits(counter, id, adc0, e, dist, nhit, ntow);
	picoTrk->setEmcPidTraitsIndex(emc_index);
      }

    if(gTrk->tofHit())
      {
	Int_t btof_index = mPicoArrays[picoBTofPidTraits]->GetEntries();
	new((*(mPicoArrays[picoBTofPidTraits]))[btof_index]) StPicoBTofPidTraits(gTrk, pTrk, counter);
	picoTrk->setBTofPidTraitsIndex(btof_index);
      }

    if(gTrk->mtdHit())
      {
	Int_t emc_index = mPicoArrays[picoMtdPidTraits]->GetEntries();
	new((*(mPicoArrays[picoMtdPidTraits]))[emc_index]) StPicoMtdPidTraits(gTrk->mtdHit(), &(gTrk->mtdPidTraits()),counter);
	picoTrk->setMtdPidTraitsIndex(emc_index);
      }
  }

//  cout << "   ++ track branch size = " <<  mPicoArrays[picoTrack]->GetEntries() << endl;
}

//-----------------------------------------------------------------------
bool StPicoDstMaker::getBEMC(StMuTrack *t, int *id, int *adc, float *ene, float *d, int *nep, int *towid) {
  *id = -1; *adc = 0;
  for(int i=0;i<5;i++) { ene[i] = 0.; }
  for(int i=0;i<4;i++) { d[i] = 1.e9; }
  for(int i=0;i<2;i++) { nep[i] = 0; }
  for(int i=0;i<3;i++) { towid[i] = -1; }

  if(!mEmcCollection) {
    LOG_WARN << " No Emc Collection for this event " << endm;
    return kFALSE;
  }

  StThreeVectorD position, momentum;
  StThreeVectorD positionBSMDE, momentumBSMDE;
  StThreeVectorD positionBSMDP, momentumBSMDP;
  Double_t bFld = mBField*kilogauss/tesla; // bFld in Tesla
  bool ok       = false;
  bool okBSMDE  = false;
  bool okBSMDP  = false;
  if(mEmcPosition) {
    ok      = mEmcPosition->projTrack(&position, &momentum, t, bFld, mEmcGeom[0]->Radius());
    okBSMDE = mEmcPosition->projTrack(&positionBSMDE, &momentumBSMDE, t, bFld, mEmcGeom[2]->Radius());
    okBSMDP = mEmcPosition->projTrack(&positionBSMDP, &momentumBSMDP, t, bFld, mEmcGeom[3]->Radius());
  }
//  if(!ok || !okBSMDE || !okBSMDP) {
  if(!ok) {
    LOG_WARN << " Projection failed for this track ... " << endm;
    return kFALSE;
  }

  if(ok && okBSMDE && okBSMDP) {

  Int_t mod=0, eta=0, sub=0;
  StSPtrVecEmcPoint& bEmcPoints = mEmcCollection->barrelPoints();
  int index=0;
  float mindist=1.e9;
  mEmcGeom[0]->getBin(positionBSMDP.phi(), positionBSMDE.pseudoRapidity(), mod, eta, sub); //project on SMD plan
  for(StSPtrVecEmcPointIterator it = bEmcPoints.begin(); it != bEmcPoints.end(); it++, index++) {
    bool associated=false;
    StPtrVecEmcCluster& bEmcClusters = (*it)->cluster(kBarrelEmcTowerId);
    if(bEmcClusters.size()==0 ) continue;
    if(bEmcClusters[0]==NULL) continue;
    for(StPtrVecEmcClusterIterator cIter = bEmcClusters.begin(); cIter != bEmcClusters.end(); cIter++) {
      StPtrVecEmcRawHit& bEmcHits = (*cIter)->hit();
      for(StPtrVecEmcRawHitIterator hIter = bEmcHits.begin(); hIter != bEmcHits.end(); hIter++) {
        if(mod == (Int_t)(*hIter)->module() && eta == (Int_t)(*hIter)->eta() && sub == (Int_t)(*hIter)->sub()) {
          associated=true;
          break;
        }
      }
      if(associated) {
        for(StPtrVecEmcRawHitIterator hitit=bEmcHits.begin(); hitit!=bEmcHits.end();hitit++) {
          if((*hitit)->energy()>ene[0]) ene[0]=(*hitit)->energy();
          if((int)(*hitit)->adc()>(*adc)) *adc=(*hitit)->adc();
        }
      }
    }

    StPtrVecEmcCluster& smdeClusters = (*it)->cluster(kBarrelSmdEtaStripId);
    StPtrVecEmcCluster& smdpClusters = (*it)->cluster(kBarrelSmdPhiStripId);

    if(associated) {
      *id = index;
      ene[1] = ene[1] + (*it)->energy(); //use point's energy, not tower cluster's energy

      float deltaphi=(*it)->position().phi()-positionBSMDP.phi();
      if(deltaphi>=TMath::Pi()) deltaphi=deltaphi-TMath::TwoPi();
      if(deltaphi<-TMath::Pi()) deltaphi=deltaphi+TMath::TwoPi();

      float rsmdp=mEmcGeom[3]->Radius();
      float pointz=(*it)->position().z();
      float deltaz=pointz-positionBSMDE.z();
      if(sqrt(deltaphi*deltaphi*rsmdp*rsmdp+deltaz*deltaz)<mindist) {
        d[1]=deltaphi;
        d[0]=deltaz;
        if(smdeClusters.size()>=1) nep[0]=smdeClusters[0]->nHits();
        if(smdpClusters.size()>=1) nep[1]=smdpClusters[0]->nHits();
        mindist=sqrt(deltaphi*deltaphi*rsmdp*rsmdp+deltaz*deltaz);
      }
    }//associated
  }

  } // end if (ok && okBSMDE && okBSMDP)

  //Get BEMC tower energy from matched tower + 2 nearest towers

  int towerId = 0;
  int localTowerId = -1;
  int localId1 = -1;
  int localId2 = -1;
  double energy1 = 0, energy2 = 0;
  double energyTemp = 0;
  double dist1 = 1000, dist2 = 1000;
  double distTemp = 0;
  Float_t etaTemp = 0, phiTemp = 0;

  if(mEmcGeom[0]->getId(position.phi(),position.pseudoRapidity(),towerId) == 1) return kTRUE;
  for(int ieta=-1;ieta<2;ieta++){
    for(int iphi=-1;iphi<2;iphi++){
      localTowerId++;//loops from 0 to 8
      int nextTowerId = mEmcPosition->getNextTowerId(towerId, ieta, iphi);
      if(nextTowerId < 1 || nextTowerId > 4800) continue;
      StEmcRawHit* emcHit = mEmcIndex[nextTowerId-1];
      if (emcHit==0) continue;
      if (emcHit->energy()<0.2) continue; // don't include any noise tower
      if(ieta==0&&iphi==0) {
        mEmcGeom[0]->getEta(nextTowerId, etaTemp);
        mEmcGeom[0]->getPhi(nextTowerId, phiTemp);
        ene[2] = emcHit->energy();
        d[2] = position.pseudoRapidity() - etaTemp;
        d[3] = position.phi() - phiTemp;
      }
      else {
        energyTemp = emcHit->energy();
        mEmcGeom[0]->getEta(nextTowerId, etaTemp);
        mEmcGeom[0]->getPhi(nextTowerId, phiTemp);
        distTemp = sqrt((etaTemp-position.pseudoRapidity())*(etaTemp-position.pseudoRapidity()) + (phiTemp-position.phi())*(phiTemp-position.phi()));
        if(distTemp < dist1) {
          dist2 = dist1;
          dist1 = distTemp;
	  energy2 = energy1;
          energy1 = energyTemp;
          localId1 = localTowerId;
        }
        else if(distTemp < dist2){
          dist2 = distTemp;
          energy2 = energyTemp;
          localId2 = localTowerId;
        }
      }
    }
  }
  towid[0] = towerId;
  ene[3] = energy1;//closest tower
  towid[1] = localId1;
  ene[4] = energy2;//2nd closest tower
  towid[2] = localId2;

  if(Debug()) {
//  if(1) {
    cout << " ====== BEMC results ====== " << endl;
    cout << " Energy = " << ene[0] << " " << ene[1] << " " << ene[2] << " " << ene[3] << " " << ene[4] << endl;
    cout << " BSMD = " << nep[0] << " " << nep[1] << endl;
    cout << " TowerId = " << towid[0] << " " << towid[1] << " " << towid[2] << endl;
  }

  return kTRUE;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::fillEvent() {
  Int_t nTracks = mPicoArrays[picoTrack]->GetEntries();

  for(int i=0;i<nTracks;i++) {
    StPicoTrack *t = (StPicoTrack *)mPicoArrays[picoTrack]->UncheckedAt(i);
    if(!t) continue;
    mMap2Track[t->id()] = i;     // map2track index - used for v0 branch
  }
  int counter = mPicoArrays[picoEvent]->GetEntries();
  new((*(mPicoArrays[picoEvent]))[counter]) StPicoEvent(*mMuDst);

//  mPicoDst->Print() ;
}
//-----------------------------------------------------------------------
void StPicoDstMaker::fillEmcTrigger() {

      // test for EMC trigger
  StTriggerSimuMaker *trigSimu = (StTriggerSimuMaker *)GetMaker("StarTrigSimu");
  if(!trigSimu) return;

  int bht0 = trigSimu->bemc->barrelHighTowerTh(0);
  int bht1 = trigSimu->bemc->barrelHighTowerTh(1);
  int bht2 = trigSimu->bemc->barrelHighTowerTh(2);
  int bht3 = trigSimu->bemc->barrelHighTowerTh(3);
  LOG_DEBUG << " bht thresholds " << bht0 << " " << bht1 << " " << bht2 << " " << bht3 << endm;
  for(int i=0;i<4;i++) mPicoDst->event()->setHT_Th(i, trigSimu->bemc->barrelHighTowerTh(i));

  for (int towerId = 1; towerId <= 4800; ++towerId)
  {
    int status;
    trigSimu->bemc->getTables()->getStatus(BTOW, towerId, status);
    int adc = trigSimu->bemc->barrelHighTowerAdc(towerId);
    int flag = 0;

    if(adc>bht1) {
      LOG_DEBUG << " id = " << towerId << " adc = " << adc << endm;
      flag |= 1<<1;
    }

    if(adc>bht2) {
      LOG_DEBUG << " id = " << towerId << " adc = " << adc << endm;
      flag |= 1<<2;
    }

    if(adc>bht3) {
      LOG_DEBUG << " id = " << towerId << " adc = " << adc << endm;
      flag |= 1<<3;
    }

    if( flag & 0xf ) {
      int counter = mPicoArrays[picoEmcTrigger]->GetEntries();
      new((*(mPicoArrays[picoEmcTrigger]))[counter]) StPicoEmcTrigger(flag, towerId, adc);
    }
  }
}

//-----------------------------------------------------------------------
void StPicoDstMaker::fillMtdTrigger()
{
  StTriggerData *trigger = const_cast<StTriggerData*>(mMuDst->event()->triggerData());
  int counter = mPicoArrays[picoMtdTrigger]->GetEntries();
  new((*(mPicoArrays[picoMtdTrigger]))[counter]) StPicoMtdTrigger(trigger);
}


//-----------------------------------------------------------------------
void StPicoDstMaker::fillBTOWHits() {

#if 0
  if(!mEmcCollection) {
    LOG_WARN << " No Emc Collection for this event " << endm;
    return;
  }

  StSPtrVecEmcPoint& bEmcPoints = mEmcCollection->barrelPoints();

  for(StSPtrVecEmcPointIterator it = bEmcPoints.begin(); it != bEmcPoints.end(); it++) {
    StPtrVecEmcCluster& bEmcClusters = (*it)->cluster(kBarrelEmcTowerId);
    if(bEmcClusters.size()==0 ) continue;
    if(bEmcClusters[0]==NULL) continue;
    for(StPtrVecEmcClusterIterator cIter = bEmcClusters.begin(); cIter != bEmcClusters.end(); cIter++) {
      StPtrVecEmcRawHit& bEmcHits = (*cIter)->hit();
      for(StPtrVecEmcRawHitIterator hIter = bEmcHits.begin(); hIter != bEmcHits.end(); hIter++) {
        int softId = (*hIter)->softId(1);
        int adc = (*hIter)->adc();
        float energy = (*hIter)->energy();

        int counter = mPicoArrays[picoBTOWHit]->GetEntries();
        new((*(mPicoArrays[picoBTOWHit]))[counter]) StPicoBTOWHit(softId, adc, energy);
      }
    }
  }
#endif

#if 1
  for(int i=0;i<4800;i++) {
    StEmcRawHit *aHit = mEmcIndex[i];
    if(!aHit) continue;
    if(aHit->energy()<0.2) continue;  // remove noise towers
    int softId = aHit->softId(1);
    int adc = aHit->adc();
    float energy = aHit->energy();

    int counter = mPicoArrays[picoBTOWHit]->GetEntries();
    new((*(mPicoArrays[picoBTOWHit]))[counter]) StPicoBTOWHit(softId, adc, energy);
  }

#endif

}
//-----------------------------------------------------------------------
void StPicoDstMaker::fillBTofHits() {
  if(!mMuDst) {
    LOG_WARN << " No MuDst for this event " << endm;
    return;
  }

  for(unsigned int i=0;i<mMuDst->numberOfBTofHit();i++) {
    StMuBTofHit *aHit = (StMuBTofHit *)mMuDst->btofHit(i);
    if(aHit->tray()>120) continue;
    int cellId = (aHit->tray()-1)*192+(aHit->module()-1)*6+(aHit->cell()-1);

    int counter = mPicoArrays[picoBTofHit]->GetEntries();
    new((*(mPicoArrays[picoBTofHit]))[counter]) StPicoBTofHit(cellId);
  }
}
//-----------------------------------------------------------------------
void StPicoDstMaker::fillMtdHits() {
  if(!mMuDst) {
    LOG_WARN << " No MuDst for this event " << endm;
    return;
  }
  Int_t nMtdHits = mMuDst->numberOfMTDHit();
  for(Int_t i=0; i<nMtdHits; i++)
    {
      StMuMtdHit *hit = (StMuMtdHit *)mMuDst->mtdHit(i);
      if(!hit) continue;
      Int_t counter = mPicoArrays[picoMtdHit]->GetEntries();
      new((*(mPicoArrays[picoMtdHit]))[counter]) StPicoMtdHit(hit);
    }

  // check the firing hits
  if(mPicoArrays[picoMtdTrigger]->GetEntries()!=1)
    {
      LOG_ERROR << "There are " << mPicoArrays[picoMtdTrigger]->GetEntries() << " MTD trigger. Check it!" << endm;
      return;
    }

  StPicoMtdTrigger *trigger = dynamic_cast<StPicoMtdTrigger*>(mPicoArrays[picoMtdTrigger]->At(0));

  Int_t triggerQT[4][2];
  Bool_t triggerBit[4][8];
  Int_t pos1 = 0, pos2 = 0;
  for(Int_t i=0; i<4; i++)
    {
      for(Int_t j=0; j<2; j++)
	triggerQT[i][j] = 0;
      for(Int_t j=0; j<8; j++)
	triggerBit[i][j] = kFALSE;

      trigger->getMaximumQTtac(i+1,pos1,pos2);
      triggerQT[i][0] = pos1;
      triggerQT[i][1] = pos2;
      for(Int_t j=0; j<2; j++)
	{
	  if( triggerQT[i][j]>0 && ((trigger->getTF201TriggerBit()>>(i*2+j))&0x1) )
	    {
	      triggerBit[i][triggerQT[i][j]-1] = kTRUE;
	    }
	}
    }


  Int_t nHits = mPicoArrays[picoMtdHit]->GetEntries();
  vector<Int_t> triggerPos;
  vector<Int_t> hitIndex;

  for(Int_t i=0; i<nHits; i++)
    {
      StPicoMtdHit *hit = dynamic_cast<StPicoMtdHit*>(mPicoArrays[picoMtdHit]->At(i));
      Int_t backleg = hit->backleg();
      Int_t module  = hit->module();
      Int_t qt = mModuleToQT[backleg-1][module-1];
      Int_t pos = mModuleToQTPos[backleg-1][module-1];
      if(qt>0 && qt<=4 && pos>0 && triggerBit[qt-1][pos-1])
	{
	  triggerPos.push_back(qt*10+pos);
	  hitIndex.push_back(i);
	}
      else
	{
	  hit->setTriggerFlag(0);
	}
    }

  vector<Int_t> hits;
  hits.clear();
  while(triggerPos.size()>0)
    {
      hits.clear();
      hits.push_back(0);
      for(Int_t j=1; j<(Int_t)triggerPos.size(); j++)
	{
	  if(triggerPos[j] == triggerPos[0])
	    hits.push_back(j);
	}

      for(Int_t k=(Int_t)hits.size()-1; k>-1; k--)
	{
	  StPicoMtdHit *hit = dynamic_cast<StPicoMtdHit*>(mPicoArrays[picoMtdHit]->At(hitIndex[hits[k]]));
	  hit->setTriggerFlag((Int_t)hits.size());
	  triggerPos.erase(triggerPos.begin()+hits[k]);
	  hitIndex.erase(hitIndex.begin()+hits[k]);
	}
    }
}

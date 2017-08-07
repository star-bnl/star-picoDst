class StMaker;
class StChain;
class StPicoDstMaker;
class StMuDstMaker;


void loadLibs()
{
  gSystem->Load("libTable");
  gSystem->Load("libPhysics");
  gSystem->Load("libSt_base");
  gSystem->Load("libStChain");
  gSystem->Load("libSt_Tables");
  gSystem->Load("libStUtilities");        // new addition 22jul99
  gSystem->Load("libStTreeMaker");
  gSystem->Load("libStIOMaker");
  gSystem->Load("libStarClassLibrary");
  gSystem->Load("libStTriggerDataMaker"); // new starting from April 2003
  gSystem->Load("libStBichsel");
  gSystem->Load("libStEvent");
  gSystem->Load("libStEventUtilities");
  gSystem->Load("libStDbLib");
  gSystem->Load("libStEmcUtil");
  gSystem->Load("libStTofUtil");
  gSystem->Load("libStPmdUtil");
  gSystem->Load("libStPreEclMaker");
  gSystem->Load("libStStrangeMuDstMaker");
  gSystem->Load("libStMuDSTMaker");
  gSystem->Load("libStarAgmlUtil");

  gSystem->Load("libStTpcDb");
  gSystem->Load("libStMcEvent");
  gSystem->Load("libStMcEventMaker");
  gSystem->Load("libStDaqLib");
  gSystem->Load("libgen_Tables");
  gSystem->Load("libsim_Tables");
  gSystem->Load("libglobal_Tables");
  gSystem->Load("libStEmcTriggerMaker");
  gSystem->Load("libStEmcRawMaker");
  gSystem->Load("libStEmcADCtoEMaker");
  gSystem->Load("libStPreEclMaker");  // XXX: loaded twice !
  gSystem->Load("libStEpcMaker");
  gSystem->Load("libStEmcSimulatorMaker");
  gSystem->Load("libStDbBroker");
  gSystem->Load("libStDetectorDbMaker");
  gSystem->Load("libStDbUtilities");
  gSystem->Load("libStEEmcUtil");
  gSystem->Load("libStEEmcDbMaker");
  gSystem->Load("libSt_db_Maker");
  gSystem->Load("libStTriggerUtilities");

  gSystem->Load("libStMagF");
  gSystem->Load("libStMtdUtil");
  gSystem->Load("libStMtdMatchMaker");
  gSystem->Load("libStMtdCalibMaker");

  //FMS
  gSystem->Load("libStFmsUtil");
  gSystem->Load("libStFmsDbMaker");

  gSystem->Load("libStPicoEvent");
  gSystem->Load("libStPicoDstMaker");

  gSystem->ListLibraries();
}


void loadAgML( const char* name=0 )
{
  gROOT->LoadMacro("bfc.C");
  bfc(0,"agml nodefault mysql");

  AgModule::SetStacker( new StarTGeoStacker() );

  if (name) StarGeometry::Construct(name);
}


void makePicoDst(const Char_t *inputFile, int nEvents = 100000)
{
  loadLibs();

  StChain* chain = new StChain();

  StMuDstMaker* MuDstMaker = new StMuDstMaker(0, 0, "", inputFile, "MuDst", 100);
  MuDstMaker->SetStatus("*", 0);
  MuDstMaker->SetStatus("MuEvent", 1);
  MuDstMaker->SetStatus("PrimaryVertices", 1);
  MuDstMaker->SetStatus("PrimaryTracks", 1);
  MuDstMaker->SetStatus("GlobalTracks", 1);
  MuDstMaker->SetStatus("CovGlobTrack", 1);
  MuDstMaker->SetStatus("BTof*", 1);
  MuDstMaker->SetStatus("Emc*", 1);
  MuDstMaker->SetStatus("MTD*", 1);
  MuDstMaker->SetStatus("Fms*", 1);

  St_db_Maker* dbMk = new St_db_Maker("db", "MySQL:StarDb", "$STAR/StarDb", "StarDb");

  //Makers needed for FMS
  //TODO:remove dependence on StEvent(Maker)
  StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");  

  // Endcap database
  StEEmcDbMaker* eemcDb = new StEEmcDbMaker();

  StEmcADCtoEMaker* adc2e = new StEmcADCtoEMaker();
  adc2e->setPrint(false);
  adc2e->saveAllStEvent(true);

  StPreEclMaker* pre_ecl = new StPreEclMaker();
  pre_ecl->setPrint(kFALSE);
  StEpcMaker* epc = new StEpcMaker();
  epc->setPrint(kFALSE);

  // Trigger simulator
  StTriggerSimuMaker* trigSimu = new StTriggerSimuMaker();
  trigSimu->setMC(false);
  trigSimu->useBemc();
  trigSimu->useEemc();
  trigSimu->useOfflineDB();
  trigSimu->bemc->setConfig(StBemcTriggerSimu::kOffline);

  StMagFMaker* magfMk = new StMagFMaker();
  StMtdMatchMaker* mtdMatchMaker = new StMtdMatchMaker();
  StMtdCalibMaker* mtdCalibMaker = new StMtdCalibMaker("mtdcalib");

  StPicoDstMaker* picoMaker = new StPicoDstMaker(StPicoDstMaker::IoWrite, inputFile, "picoDst");
  picoMaker->setVtxMode((int)(StPicoDstMaker::PicoVtxMode::Default));

  chain->Init();
  cout << "chain->Init();" << endl;

  loadAgML("y2017");

  int total = 0;
  for (Int_t i = 0; i < nEvents; i++)
  {
    if (i % 100 == 0)
      cout << "Working on eventNumber " << i << endl;

    chain->Clear();
    int iret = chain->Make(i);

    if (iret)
    {
      cout << "Bad return code!" << iret << endl;
      break;
    }

    total++;
  }

  cout << "****************************************** " << endl;
  cout << "Work done... now its time to close up shop!" << endl;
  cout << "****************************************** " << endl;
  chain->Finish();
  cout << "****************************************** " << endl;
  cout << "total number of events  " << total << endl;
  cout << "****************************************** " << endl;

  delete chain;
}

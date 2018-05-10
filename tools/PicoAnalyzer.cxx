#include "tools/PicoAnalyzer.h"
#include "StPicoEvent/StPicoEpdHit.h"
#include "StPicoEvent/StPicoBbcHit.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StEpdUtil/StEpdGeom.h"
#include "StEpdUtil/StBbcGeom.h"

#include "TTree.h"
#include "TLeaf.h"
#include "TMath.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TRandom3.h"

#include <iostream>
using namespace std;


double PicoAnalyzer::GetBbcPmtPhi(short PmtId){
  unsigned short nBbcTiles;        // how many (1 or 2) tiles are associated with a given BBC phototube
  unsigned short tileNumbers[2];   // what are the tile ids of tiles associated with a given BBC phototube
  int chooseOne=0;
  // here we go with the bloody nightmare of the BBC's "shared phototubes"....
  mBbcGeom->GetTilesOfPmt(abs(PmtId),&nBbcTiles,tileNumbers);
  if (nBbcTiles>1) chooseOne = (mRan->Rndm()<0.5)?0:1;
  double phi = mBbcGeom->TileCenter(tileNumbers[chooseOne]*PmtId/abs(PmtId)).Phi();
  return phi;
}




//=================================================
PicoAnalyzer::PicoAnalyzer() : nEvents(0), mNmipQtB(115), mNmipQtC(160), mnMipThreshold(0.3), mPicoDst(0), mEpdBranch(0), mBbcBranch(0), mEventBranch(0), mEpdHits(0), mBbcHits(0), mQ1NtupleFile(0), mQ2NtupleFile(0)
{
  mEpdGeom = new StEpdGeom;
  mBbcGeom = new StBbcGeom;
  mRan = new TRandom3;
  mRan->GetSeed();
}

//=================================================
PicoAnalyzer::~PicoAnalyzer(){
  /* no-op */
}


//=================================================
void PicoAnalyzer::SetPicoDst(TTree* PicoDst){
  mPicoDst        = PicoDst;
  mEpdBranch      = mPicoDst->GetBranch("EpdHit");
  mBbcBranch      = mPicoDst->GetBranch("BbcHit");
  mEventBranch    = mPicoDst->GetBranch("Event");

  mRefMultNegLeaf = mPicoDst->GetLeaf("Event.mRefMultNeg");
  mRefMultPosLeaf = mPicoDst->GetLeaf("Event.mRefMultPos");
  mVxLeaf         = mPicoDst->GetLeaf("Event.mPrimaryVertex.mX1");
  mVyLeaf         = mPicoDst->GetLeaf("Event.mPrimaryVertex.mX2");
  mVzLeaf         = mPicoDst->GetLeaf("Event.mPrimaryVertex.mX3");
  mRunIdLeaf      = mPicoDst->GetLeaf("Event.mRunId");
  mVzVpdLeaf      = mPicoDst->GetLeaf("Event.mVzVpd");

  mPicoDst->SetBranchStatus("*",0);         // turns OFF all branches  (speeds it up :-)
  mPicoDst->SetBranchStatus("EpdHit*",1);   // note you need the asterisk
  mPicoDst->SetBranchStatus("BbcHit*",1);
  mPicoDst->SetBranchStatus("Event*",1);

  // this below MIGHT not work to do only once.  might have to do each time (i.e. in make)
  //  Well, it seems to be okay to do it here.
  if (mEpdHits!=0) delete mEpdHits;
  if (mBbcHits!=0) delete mBbcHits;
  mEpdHits = new TClonesArray("StPicoEpdHit");
  mBbcHits = new TClonesArray("StPicoBbcHit");
  mEpdBranch->SetAddress(&mEpdHits);
  mBbcBranch->SetAddress(&mBbcHits);
  
  cout << "I have set all branches, leaves, etc \n";
}

//=================================================
void PicoAnalyzer::ReadLeaves(){
  mRefMult = mRefMultNegLeaf->GetValue()+mRefMultPosLeaf->GetValue();
  // primary vertex position:
  mPrimVertPos[0] = mVxLeaf->GetValue();
  mPrimVertPos[1] = mVyLeaf->GetValue();
  mPrimVertPos[2] = mVzLeaf->GetValue();
  mRunId          = mRunIdLeaf->GetValue();
  mVzVpd          = mVzVpdLeaf->GetValue() + 36.4046 - 3.13415;  // numbers from Rosi's email of 3may2018
}

//=================================================
short PicoAnalyzer::Init(){
  mHistoFile = new TFile("EpdHists.root","RECREATE");

  // 1D histograms for nMIP distributions
  for (int ew=0; ew<2; ew++){
    for (int pp=1; pp<13; pp++){
      for (int tt=1; tt<32; tt++){
	mNmipDists[ew][pp-1][tt-1] = new TH1D(Form("NmipEW%dPP%dTT%d",ew,pp,tt),Form("NmipEW%dPP%dTT%d",ew,pp,tt),500,0,20);
      }
    }
  }

  // Miscellaneous One-dimensional histograms
  mHisto1D[0] = new TH1D("Vz","Vz",100,-80,80);
  mHisto1D[1] = new TH1D("RefMult","RefMult",100,-10,600);
  mHisto1D[2] = new TH1D("dNdeta","dNdeta",100,-5.5,5.5);
  mHisto1D[3] = new TH1D("Cos2DeltaPsi2","Cos2DeltaPsi2",1000,-1,1);
  mHisto1D[4] = new TH1D("Cos1DeltaPsi1","Cos1DeltaPsi1",1000,-1,1);
  mHisto1D[5] = new TH1D("BbcCos1DeltaPsi1","BbcCos1DeltaPsi1",1000,-1,1);
  mHisto1D[6] = new TH1D("BbcCos2DeltaPsi2","BbcCos2DeltaPsi2",1000,-1,1);

  // Miscellaneous Two-dimensional histograms
  mHisto2D[0] = new TH2D("Phi2WestVsPhiEast","Phi2WestVsPhiEast",40,-TMath::Pi()/2.0,TMath::Pi()/2.0,40,-TMath::Pi()/2.0,TMath::Pi()/2.0);
  mHisto2D[0]->GetXaxis()->SetTitle("#phi_{2,East}");     mHisto2D[0]->GetYaxis()->SetTitle("#phi_{2,West}");
  mHisto2D[1] = new TH2D("Phi1WestVsPhiEast","Phi1WestVsPhiEast",40,-TMath::Pi(),TMath::Pi(),40,-TMath::Pi(),TMath::Pi());
  mHisto2D[1]->GetXaxis()->SetTitle("#phi_{1,East}");     mHisto2D[1]->GetYaxis()->SetTitle("#phi_{1,West}");
  mHisto2D[2] = new TH2D("RefMultVsEpdMipSum","RefMultVsEpdMipSum",100,0,5000,100,0,500);
  mHisto2D[2]->GetXaxis()->SetTitle("Epd nMIP Sum");      mHisto2D[2]->GetYaxis()->SetTitle("RefMult");
  mHisto2D[3] = new TH2D("BbcAdcSumVsEpdMipSum","BbcAdcSumVsEpdMipSum",100,0,5000,100,0,50000);
  mHisto2D[3]->GetXaxis()->SetTitle("BBC ADC Sum");      mHisto2D[3]->GetYaxis()->SetTitle("RefMult");
  mHisto2D[4] = new TH2D("BbcPhi1WestVsPhiEast","BbcPhi1WestVsPhiEast",40,-TMath::Pi(),TMath::Pi(),40,-TMath::Pi(),TMath::Pi());
  mHisto2D[4]->GetXaxis()->SetTitle("#phi_{1,East}");     mHisto2D[4]->GetYaxis()->SetTitle("#phi_{1,West}");
  mHisto2D[5] = new TH2D("BbcPhi2WestVsPhiEast","BbcPhi2WestVsPhiEast",40,-TMath::Pi()/2.0,TMath::Pi()/2.0,40,-TMath::Pi()/2.0,TMath::Pi()/2.0);
  mHisto2D[5]->GetXaxis()->SetTitle("#phi_{2,East}");     mHisto2D[5]->GetYaxis()->SetTitle("#phi_{2,West}");
  mHisto2D[6] = new TH2D("VyVx","V_{y} vs V_{x}",400,-1,1,400,1,1);
  mHisto2D[6]->GetXaxis()->SetTitle("V_{x} (cm)");        mHisto2D[6]->GetYaxis()->SetTitle("V_{y} (cm)");

  for (int ibbc=0; ibbc<16; ibbc++){
    mWestXY[ibbc] = new TH2D(Form("BBC%dWestFires",ibbc),Form("When PMT%d fires on BBC West",ibbc),500,-1,1,500,-1,1);
    mEastXY[ibbc] = new TH2D(Form("BBC%dEastFires",ibbc),Form("When PMT%d fires on BBC East",ibbc),500,-1,1,500,-1,1);
  }

  for (int icent=0; icent<7; icent++) mRefMultHist[icent] = new TH1D(Form("RefMult%d",icent),Form("RefMult %d-%d%s",70-10*icent,80-10*icent,"%"),600,-0.5,599.5);
  mRefMultHist[7] = new TH1D("RefMult7","RefMult 5-10%",600,-0.5,599.5);
  mRefMultHist[8] = new TH1D("RefMult8","RefMult 0-5%",600,-0.5,599.5);

  // histograms and profiles of event planes
  // EPD "correction level" (last index):  0=raw; 1=shifted
  // BBC "correction level" (last index):  0=raw; 1=gain; 2=shifted
  for (int n=1; n<4; n++){
    double PhiMax = 2.0*TMath::Pi()/((double)n);
    mEpdEwPsi[n-1][0]  = new TH2D(Form("EpdEwPsi%draw",n),  Form("EPD raw #Psi_{%d,W} vs #Psi_{%d,E}",n,n),  100,0.0,PhiMax,100,0.0,PhiMax);
    mEpdEwPsi[n-1][1]  = new TH2D(Form("EpdEwPsi%dshift",n),Form("EPD shift #Psi_{%d,W} vs #Psi_{%d,E}",n,n),100,0.0,PhiMax,100,0.0,PhiMax);
    //
    mBbcEwPsi[n-1][0]  = new TH2D(Form("BbcEwPsi%draw",n),  Form("BBC raw #Psi_{%d,W} vs #Psi_{%d,E}",n,n),  100,0.0,PhiMax,100,0.0,PhiMax);
    mBbcEwPsi[n-1][1]  = new TH2D(Form("BbcEwPsi%dgain",n), Form("BBC gain #Psi_{%d,W} vs #Psi_{%d,E}",n,n), 100,0.0,PhiMax,100,0.0,PhiMax);
    mBbcEwPsi[n-1][2]  = new TH2D(Form("BbcEwPsi%dshift",n),Form("BBC shift #Psi_{%d,W} vs #Psi_{%d,E}",n,n),100,0.0,PhiMax,100,0.0,PhiMax);
    //
    mEpdEwPsi_midCentral[n-1][0]  = new TH2D(Form("EpdEwPsi%drawMidCent",n),  Form("MidCentral EPD raw #Psi_{%d,W} vs #Psi_{%d,E}",n,n),  100,0.0,PhiMax,100,0.0,PhiMax);
    mEpdEwPsi_midCentral[n-1][1]  = new TH2D(Form("EpdEwPsi%dshiftMidCent",n),Form("MidCentral EPD shift #Psi_{%d,W} vs #Psi_{%d,E}",n,n),100,0.0,PhiMax,100,0.0,PhiMax);

    for (int icor=0; icor<2; icor++){
      mEpdEwPsi[n-1][icor]->GetXaxis()->SetTitle(Form("#Psi_{%d,E}",n));                 mEpdEwPsi[n-1][icor]->GetYaxis()->SetTitle(Form("#Psi_{%d,W}",n));
      mEpdEwPsi_midCentral[n-1][icor]->GetXaxis()->SetTitle(Form("#Psi_{%d,E}",n));      mEpdEwPsi_midCentral[n-1][icor]->GetYaxis()->SetTitle(Form("#Psi_{%d,W}",n));
    }
    for (int icor=0; icor<3; icor++){
      mBbcEwPsi[n-1][icor]->GetXaxis()->SetTitle(Form("#Psi_{%d,E}",n));      mBbcEwPsi[n-1][icor]->GetYaxis()->SetTitle(Form("#Psi_{%d,W}",n));
    }

    //
    mEpdAveCos[n-1][0] = new TProfile(Form("EpdCos%draw",n),  Form("EPD raw #LT cos(%d#Psi_{%d,W}-%d#Psi_{%d,E}) #GT",n,n,n,n)  ,9,-0.5,8.5);
    mEpdAveCos[n-1][1] = new TProfile(Form("EpdCos%dshift",n),Form("EPD shift #LT cos(%d#Psi_{%d,W}-%d#Psi_{%d,E}) #GT",n,n,n,n),9,-0.5,8.5);
    //
    mBbcAveCos[n-1][0] = new TProfile(Form("BbcCos%draw",n),  Form("BBC raw #LT cos(%d#Psi_{%d,W}-%d#Psi_{%d,E}) #GT",n,n,n,n),  9,-0.5,8.5);
    mBbcAveCos[n-1][1] = new TProfile(Form("BbcCos%dgain",n), Form("BBC gain #LT cos(%d#Psi_{%d,W}-%d#Psi_{%d,E}) #GT",n,n,n,n),9,-0.5,8.5);
    mBbcAveCos[n-1][2] = new TProfile(Form("BbcCos%dshift",n),Form("BBC shift #LT cos(%d#Psi_{%d,W}-%d#Psi_{%d,E}) #GT",n,n,n,n),9,-0.5,8.5);
  }





  // "Shift correction" histograms that we INPUT and apply here
  mCorrectionInputFile = new TFile("./EPcorrectionHistogramsINPUT.root","READ");
  for (int ew=0; ew<2; ew++){
    for (int order=1; order<4; order++){
      mEpdShiftInput_sin[ew][order-1] = (TProfile2D*)mCorrectionInputFile->Get(Form("EpdShiftEW%dPsi%d_sin",ew,order));
      mEpdShiftInput_cos[ew][order-1] = (TProfile2D*)mCorrectionInputFile->Get(Form("EpdShiftEW%dPsi%d_cos",ew,order));
      mBbcShiftInput_sin[ew][order-1] = (TProfile2D*)mCorrectionInputFile->Get(Form("BbcShiftEW%dPsi%d_sin",ew,order));
      mBbcShiftInput_cos[ew][order-1] = (TProfile2D*)mCorrectionInputFile->Get(Form("BbcShiftEW%dPsi%d_cos",ew,order));
    }
  }
  
  // "Shift correction" histograms that we produce and OUTPUT
  mCorrectionOutputFile = new TFile("./EPcorrectionHistogramsOUTPUT.root","RECREATE");
  for (int ew=0; ew<2; ew++){
    for (int order=1; order<4; order++){
      mEpdShiftOutput_sin[ew][order-1] = new TProfile2D(Form("EpdShiftEW%dPsi%d_sin",ew,order),Form("EpdShiftEW%dPsi%d_sin",ew,order),20,0,20,10,0,10.0,-1.0,1.0);
      mEpdShiftOutput_cos[ew][order-1] = new TProfile2D(Form("EpdShiftEW%dPsi%d_cos",ew,order),Form("EpdShiftEW%dPsi%d_cos",ew,order),20,0,20,10,0,10.0,-1.0,1.0);
      mBbcShiftOutput_sin[ew][order-1] = new TProfile2D(Form("BbcShiftEW%dPsi%d_sin",ew,order),Form("BbcShiftEW%dPsi%d_sin",ew,order),20,0,20,10,0,10.0,-1.0,1.0);
      mBbcShiftOutput_cos[ew][order-1] = new TProfile2D(Form("BbcShiftEW%dPsi%d_cos",ew,order),Form("BbcShiftEW%dPsi%d_cos",ew,order),20,0,20,10,0,10.0,-1.0,1.0);
    }
  }



  //----------------- Ntuples -----------------
  //   TString VariableList = "";
  //   for (int ew=0; ew<2; ew++){
  //     TString ewstring = (ew==0)?"ER":"WR";
  //     for (int ring=1; ring<17; ring++){
  //       VariableList += Form("%s%dQx:%s%dQy",ewstring.Data(),ring,ewstring.Data(),ring);
  //       if (!((ew==1)&&(ring==16))) VariableList += ":";
  //     }
  //   }
  //   mQ1NtupleFile = new TFile("Q1ntuple.root","RECREATE");
  //   mQ1vectorNtuple = new TNtuple("RingQ1vectors","RingQ1vectors",VariableList.Data());
  //   mQ2NtupleFile = new TFile("Q2ntuple.root","RECREATE");
  //   mQ2vectorNtuple = new TNtuple("RingQ2vectors","RingQ2vectors",VariableList.Data());

  cout << "Init done\n";
  return 0;
}

  
//=================================================
short PicoAnalyzer::Make(int iEvent){
  //----------------- get data --------------
  mPicoDst->GetEntry(iEvent);
  ReadLeaves();
  //----- done getting data; have fun! ------

  double pi = TMath::Pi();

  TVector3 PV(mPrimVertPos[0],mPrimVertPos[1],mPrimVertPos[2]);
  int CentId = FindCent(mRefMult);   // returns an integer between 0 (70-80%) and 8 (0-5%)
  int RunYear = 19;
  int RunDay = floor( (mRunId - RunYear*pow(10,6))/pow(10,3) );
  int DayBinId = RunDay-89;

  if (CentId<0) return 0;            // 80-100% - very peripheral
  /*
  if (mRefMult>50) return 0;

  // okay, I am looking for events when ONLY one BBC tube fires on East or West...
  int nBbcWest(0),nBbcEast(0),whichBbcWest,whichBbcEast;
  for (int hit=0; hit<mBbcHits->GetEntries(); hit++){
    StPicoBbcHit* bbcHit = (StPicoBbcHit*)((*mBbcHits)[hit]);
    if (bbcHit->id()>0){
      nBbcWest++;
      whichBbcWest = abs(bbcHit->id());
    }
    else{
      nBbcEast++;
      whichBbcEast = abs(bbcHit->id());
    }
  }
  for (int hit=0; hit<mEpdHits->GetEntries(); hit++){
    StPicoEpdHit* epdHit = (StPicoEpdHit*)((*mEpdHits)[hit]);
    if (epdHit->id()>0){
      if (nBbcWest==1){
	TVector3 pos = mEpdGeom->RandomPointOnTile(epdHit->id());
	mWestXY[whichBbcWest]->Fill(pos.X(),pos.Y());
      }
    }
    else{
      if (nBbcEast==1){
	TVector3 pos = mEpdGeom->RandomPointOnTile(epdHit->id());
	mEastXY[whichBbcEast]->Fill(pos.X(),pos.Y());
      }
    }
  }
  return 0;
  */


  mHisto1D[0]->Fill(mPrimVertPos[2]);
  mHisto1D[1]->Fill(mRefMult);
  mRefMultHist[CentId]->Fill(mRefMult);
  mHisto2D[6]->Fill(mPrimVertPos[0],mPrimVertPos[1]);   // Vy versus Vx

  if (fabs(mPrimVertPos[2])>50.0) return 0;
  if (sqrt(pow(mPrimVertPos[0],2)+pow(mPrimVertPos[1],2))>1.0) return 0;
  //  if (fabs(mVzVpd-mPrimVertPos[2])>6.0) return 0;                   // check consistency b/t TPC and VPD - thanks Rosi 3may2018








  StPicoEpdHit* epdHit;
  double Q[2][3][2] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}; // indices are east/west, order (1, 2 or 3), component (x or y)
  double nMipSum(0.0);
  double maxWeight = 3;

  // ==================== this Q1 and Q2 stuff is only for the Ntuples ====================
  //  float Q1[64];   // Qx and Qy from all 16 rins on both sides.  Index = 32*EW + 2*(ring-1) + xy.  Where EW=0/1 for East/West.  Ring=1..16.  xy=0/1 for x/y
  //  float Q2[64];   // Qx and Qy from all 16 rins on both sides.  Index = 32*EW + 2*(ring-1) + xy.  Where EW=0/1 for East/West.  Ring=1..16.  xy=0/1 for x/y
  //  for (int iii=0; iii<64; iii++){Q1[iii]=0.0;  Q2[iii]=0.0;}
  // ======================================================================================

  //------------------------------------------------------
  //--------------- Begin loop over EPD hits --------------
  for (int hit=0; hit<mEpdHits->GetEntries(); hit++){
    epdHit = (StPicoEpdHit*)((*mEpdHits)[hit]);
    int ew = (epdHit->id()<0)?0:1;
    double nMip = (epdHit->tile()<10)?epdHit->adc()/mNmipQtC:epdHit->adc()/mNmipQtB;
    if (nMip<mnMipThreshold) continue;
    double weight = (nMip>maxWeight)?maxWeight:nMip;

    TVector3 StraightLine = mEpdGeom->RandomPointOnTile(epdHit->id()) -PV;
    double eta = StraightLine.Eta();
    mHisto1D[2]->Fill(eta,nMip);
    nMipSum += nMip;
    mNmipDists[ew][epdHit->position()-1][epdHit->tile()-1]->Fill(nMip);

    double phi = mEpdGeom->TileCenter(epdHit->id()).Phi();

    // ============ this below is only for the Ntuples ============    
    //     int Qindex = 32*ew + 2*(epdHit->row()-1);
    //    double EWsign = (ew==0)?1.0:-1.0;
    //     Q1[Qindex]   += EWsign*weight*cos(phi);    // for first-order plane, east and west will point "in opposite directions"
    //     Q1[Qindex+1] += EWsign*weight*sin(phi);
    //     Q2[Qindex]   += weight*cos(2.0*phi);
    //     Q2[Qindex+1] += weight*sin(2.0*phi);
    // =============================================================

    for (int order=1; order<4; order++){
      Q[ew][order-1][0] += weight*cos((double)order*phi);
      Q[ew][order-1][1] += weight*sin((double)order*phi);
    }
  }
  //--------------- End loop over EPD hits --------------
  //------------------------------------------------------

  // for first-order plane, gotta flip the sign of Qvector on the East side. ("rapidity odd v1")
  Q[0][0][0] *= -1.0;   // remember indices.... [ew][order-1][x or y]
  Q[0][0][1] *= -1.0;
  
  // calculate raw EP angles and fill histograms
  double PsiEPDraw[2][3];     // indices are east/west and order (1, 2, or 3)

  for (int order=1; order<4; order++){
    for (int ew=0; ew<2; ew++){
      PsiEPDraw[ew][order-1] = atan2(Q[ew][order-1][1],Q[ew][order-1][0])/(double)order;
      if (PsiEPDraw[ew][order-1]<0.0) PsiEPDraw[ew][order-1] += 2.0*pi/((double)order);
    }
    mEpdEwPsi[order-1][0]->Fill(PsiEPDraw[0][order-1],PsiEPDraw[1][order-1]);
    if ((CentId>=4)&&(CentId<=6)) mEpdEwPsi_midCentral[order-1][0]->Fill(PsiEPDraw[0][order-1],PsiEPDraw[1][order-1]);
    mEpdAveCos[order-1][0]->Fill(CentId,cos((double)order*(PsiEPDraw[0][order-1]-PsiEPDraw[1][order-1])));

  }

  // Now fill the shift histograms that can be used for corrections in a future run
  //   (or just ignored if you already have the corrections....)
  for (int nfill=1; nfill<21; nfill++){
    for (int ew=0; ew<2; ew++){
      for (int order=1; order<4; order++){
	mEpdShiftOutput_sin[ew][order-1]->Fill(nfill-1,CentId,sin((double)(order*nfill)*PsiEPDraw[ew][order-1]));
	mEpdShiftOutput_cos[ew][order-1]->Fill(nfill-1,CentId,cos((double)(order*nfill)*PsiEPDraw[ew][order-1]));
      }
    }
  }

  // Now APPLY the shift corrections using histograms generated in a PREVIOUS run of this code.
  // This gives the "shifted" EP angles.
  double PsiEPDshifted[2][3];   // indices are east/west and order (1, 2, or 3)  
  for (int order=1; order<4; order++){
    for (int ew=0; ew<2; ew++){
      PsiEPDshifted[ew][order-1] = PsiEPDraw[ew][order-1];
      for (int i=1; i<21; i++){
	double sinAve = mEpdShiftInput_sin[ew][order-1]->GetBinContent(i,CentId+1);
	double cosAve = mEpdShiftInput_cos[ew][order-1]->GetBinContent(i,CentId+1);
	PsiEPDshifted[ew][order-1] += 2.0*(cosAve*sin((double)(order*i)*PsiEPDraw[ew][order-1]) - sinAve*cos((double)(order*i)*PsiEPDraw[ew][order-1]))/(double)(order*i);
      }
      double AngleWrapAround = 2.0*pi/(double)order;
      if (PsiEPDshifted[ew][order-1]<0.0) PsiEPDshifted[ew][order-1]+=AngleWrapAround;  else if(PsiEPDshifted[ew][order-1]>AngleWrapAround) PsiEPDshifted[ew][order-1]-=AngleWrapAround;
    }
    mEpdEwPsi[order-1][1]->Fill(PsiEPDshifted[0][order-1],PsiEPDshifted[1][order-1]);
    if ((CentId>=4)&&(CentId<=6)) mEpdEwPsi_midCentral[order-1][1]->Fill(PsiEPDshifted[0][order-1],PsiEPDshifted[1][order-1]);
    mEpdAveCos[order-1][1]->Fill(CentId,cos((double)order*(PsiEPDshifted[0][order-1]-PsiEPDshifted[1][order-1])));
  }
  

  /*

  //  double RowWeight[16]={3.8140,0.5399,-0.5231,0.3281,0.8812,1.0733,0.9113,0.9067,1.0962,1.1436,0.9466,0.8508,0.9539,1.0178,0.9952,1.00000000};

  double Q1Xsum[2]={0.0,0.0};  // index = ew
  double Q1Ysum[2]={0.0,0.0};
  double Q2Xsum[2]={0.0,0.0};
  double Q2Ysum[2]={0.0,0.0};
  for (int ew=0; ew<2; ew++){
    for (int jrow=0; jrow<16; jrow++){
      Q1Xsum[ew] += RowWeight[jrow] * Q1[32*ew+2*jrow];
      Q1Ysum[ew] += RowWeight[jrow] * Q1[32*ew+2*jrow+1];
      Q2Xsum[ew] += RowWeight[jrow] * Q2[32*ew+2*jrow];
      Q2Ysum[ew] += RowWeight[jrow] * Q2[32*ew+2*jrow+1];
    }
    PsiEP[ew][0] = atan2(Q1Ysum[ew],Q1Xsum[ew]);
    if (PsiEP[ew][0]<-TMath::Pi()) PsiEP[ew][0] += 2.0*TMath::Pi();
    if (PsiEP[ew][0]>TMath::Pi())  PsiEP[ew][0] -= 2.0*TMath::Pi();
    PsiEP[ew][1] = 0.5*atan2(Q2Ysum[ew],Q2Xsum[ew]);
    if (PsiEP[ew][1]<-TMath::Pi()/2.0) PsiEP[ew][0] += TMath::Pi();
    if (PsiEP[ew][1]>TMath::Pi()/2.0)  PsiEP[ew][0] -= TMath::Pi();
  }




  if ((mRefMult>93)&&(mRefMult<172)){    // according to Isaac, this should be 10%-40%, our "best" centrality.
    mHisto1D[3]->Fill(cos(2.0*(PsiEP[1][1]-PsiEP[0][1])));
    mHisto1D[4]->Fill(cos(1.0*(PsiEP[1][0]-PsiEP[0][0])));
    mHisto2D[0]->Fill(PsiEP[0][1],PsiEP[1][1]);
    mHisto2D[1]->Fill(PsiEP[0][0],PsiEP[1][0]);
    //    if (mQ1vectorNtuple) mQ1vectorNtuple->Fill(Q1);
    //    if (mQ2vectorNtuple) mQ2vectorNtuple->Fill(Q2);
  }
  mHisto2D[2]->Fill(nMipSum,mRefMult);

  // now look also at BBC stuff
  // 1dhisto[5] = cos2deltapsi2
  // 1dhisto[4] = phi2West vs East

  for (int ew=0; ew<2; ew++){
    for (int order=1; order<3; order++){
      for (int xy=0; xy<2; xy++){
	Q[ew][order-1][xy] = 0.0;
      }
    }
  }

  StPicoBbcHit* bbcHit;
  double BbcAdcSum(0.0);
  
  for (int hit=0; hit<mBbcHits->GetEntries(); hit++){
    bbcHit = (StPicoBbcHit*)((*mBbcHits)[hit]);
    double adc = bbcHit->adc();
    BbcAdcSum += adc;
    int ew = (bbcHit->side()>0)?1:0;

    double phi = GetBbcPmtPhi(bbcHit->id());  // this will take care of the nightmare of BBC's tile-pmt mapping...

    Q[ew][0][0] += adc*cos(phi);
    Q[ew][0][1] += adc*sin(phi);
    Q[ew][1][0] += adc*cos(2*phi);
    Q[ew][1][1] += adc*sin(2*phi);
  }
  mHisto2D[3]->Fill(nMipSum,BbcAdcSum);
  for (int ew=0; ew<2; ew++){
    for (int order=1; order<3; order++){
      PsiEP[ew][order-1] = atan2(Q[ew][order-1][1],Q[ew][order-1][0])/(double)order;
    }
  }
  if ((mRefMult>100)&&(mRefMult<240)){
    mHisto1D[5]->Fill(cos(1.0*(PsiEP[1][0]-PsiEP[0][0])));
    mHisto1D[6]->Fill(cos(2.0*(PsiEP[1][1]-PsiEP[0][1])));

    mHisto2D[4]->Fill(PsiEP[0][0],PsiEP[1][0]);
    mHisto2D[5]->Fill(PsiEP[0][1],PsiEP[1][1]);
  }
  

  */

  return 0;
}

//=================================================
short PicoAnalyzer::Finish(){
  mHistoFile->Write();
  mHistoFile->Close();

  mCorrectionInputFile->Close();

  mCorrectionOutputFile->Write();
  mCorrectionOutputFile->Close();

  if (mQ1NtupleFile){
    mQ1NtupleFile->Write();
    mQ1NtupleFile->Close();
  }
  if (mQ2NtupleFile){
    mQ2NtupleFile->Write();
    mQ2NtupleFile->Close();
  }

  cout << "Finish!!\n\n";
  /* save histograms to a file if you want */
  return 0;
}

//-----------------------------------
// I copied this directly from Isaac
// it's for the 2018 isobars
int PicoAnalyzer::FindCent(int Multiplicity){
  int CentId = -1;
  if(Multiplicity <= 19) CentId = -1; // > 80%                                 
  else if (Multiplicity > 19 && Multiplicity <= 31) CentId = 0; // 70-80%      
  else if (Multiplicity > 31 && Multiplicity <= 46) CentId = 1; // 60-70%      
  else if (Multiplicity > 46 && Multiplicity <= 67) CentId = 2; // 50-60%      
  else if (Multiplicity > 67 && Multiplicity <= 93) CentId = 3; // 40-50%      
  else if (Multiplicity > 93 && Multiplicity <= 128) CentId = 4; // 30-40%     
  else if (Multiplicity > 128 && Multiplicity <= 172) CentId = 5; // 20-30%    
  else if (Multiplicity > 172 && Multiplicity <= 230) CentId = 6; // 10-20%    
  else if (Multiplicity > 230 && Multiplicity <= 267) CentId = 7; // 5-10%     
  else if (Multiplicity > 267) CentId = 8; // 0-5%                             
  return CentId;
}

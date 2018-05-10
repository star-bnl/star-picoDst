// Accessing individual TLeaf objects doesn't (easily) work with TChain objects
// the address changes every time a new file is loaded (which makes sense if you think of it)
// should stick with TTrees.
// https://root-forum.cern.ch/t/reading-exactly-1-leaf-from-tchain/14129/3

#include <string>
#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "tools/PicoAnalyzer.h"


void AnalyzePico(int nRootFilesToProcess=1, std::string FileListName = "DataFile.list"){

  //  string rootFileName;
  TString rootFileName;
  TTree* picoDst;
  PicoAnalyzer* anal = new PicoAnalyzer();
  anal->Init();

  std::ifstream ifs(FileListName,std::ifstream::in);
  for (int iFile=0; iFile<nRootFilesToProcess; iFile++){
    ifs >> rootFileName;
    if (!(ifs.good())) break;
    std::cout << "Reading data from " << rootFileName << " (File " << iFile << " of " << nRootFilesToProcess << ")" << std::endl;
    TFile* inFile = new TFile(rootFileName);
    if(inFile->IsZombie()){
       std::cout << rootFileName << " is a zombie!!!" << std::endl;
      delete inFile;
      continue;
    }
    inFile->GetObject("PicoDst",picoDst);
    anal->SetPicoDst(picoDst);              // this must be done for each new file.  that's why we don't use TChain
    for (int ievent=0; ievent<picoDst->GetEntries(); ievent++){
      anal->Make(ievent);
    }
    inFile->Close();
    delete inFile;
  }
  anal->Finish();
  
}
  

int main()
{
  AnalyzePico();

  return EXIT_SUCCESS;
}

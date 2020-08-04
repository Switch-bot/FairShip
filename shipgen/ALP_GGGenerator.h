#ifndef ALP_GGGENERATOR_H
#define ALP_GGGENERATOR_H 1
// Avoid the inclusion of dlfcn.h by Pyhtia.h that CINT is not able to process
//#ifdef __CINT__
//#define _DLFCN_H_
//#define _DLFCN_H
//#endif

#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "FairGenerator.h"
#include "Pythia8/Pythia.h"
#include "TRandom1.h"
#include "TRandom3.h"
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "HNLPythia8Generator.h"

class FairPrimaryGenerator;
using namespace Pythia8;

class ALP_GGGenerator : public FairGenerator
{
 public:
  
  /** default constructor **/
  ALP_GGGenerator(Double_t, Double_t);
  
  /** destructor **/
  virtual ~ALP_GGGenerator();
  
  /** public method ReadEvent **/
  Bool_t ReadEvent(FairPrimaryGenerator*);
 
  virtual Bool_t Init(); //!
   
 protected:

  //Bool_t fHadDecay;    //select hadronic decay
  Int_t    fbeam;       // proton PDG
  Int_t    fALP;       // ALP PDG
  Int_t    fgamma;       // gamma PDG
  Double_t    fALPmass;       // ALP mass
  Double_t    fALPcoupling;       // ALP coupling to gamma gamma
 
  ClassDef(ALP_GGGenerator,1);
};

#endif /* !ALP_GGGENERATOR_H */

#include <math.h>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "FairPrimaryGenerator.h"
#include "TDatabasePDG.h"               // for TDatabasePDG
#include "ALP_GGGenerator.h"
#include "Pythia8/Pythia.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom3.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
const Double_t c_light = 2.99792458e+10; // speed of light in cm/sec (c_light   = 2.99792458e+8 * m/s)
const Double_t hGeV = 6.58211928*pow(10.,-16)* pow(10.,-9);// # no units or it messes up!!
using namespace Pythia8;

// -----   Default constructor   -------------------------------------------
ALP_GGGenerator::ALP_GGGenerator(Double_t mass, Double_t coupling) 
{
  fbeam      = 2212;    // proton  pdg code
  fALP         = 90;    // ALP  pdg code
  fgamma       = 22;    // gamma  pdg code
  fALPmass     = mass;
  fALPcoupling = coupling;
}
// -------------------------------------------------------------------------

// -----   Default constructor   -------------------------------------------
Bool_t ALP_GGGenerator::Init() 
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
ALP_GGGenerator::~ALP_GGGenerator() 
{
}
// -------------------------------------------------------------------------

// -----   Passing the event   ---------------------------------------------
Bool_t ALP_GGGenerator::ReadEvent(FairPrimaryGenerator* cpg)
{

  static Int_t event_number = 0;
  static vector<Double_t> idPartVect0, statusPartVect0, mother1PartVect0, mother2PartVect0, col1PartVect0, col2PartVect0, pxPartVect0, pyPartVect0, pzPartVect0, ePartVect0, mPartVect0, tauPartVect0, spinPartVect0;
  static vector<Double_t> idPartVect, statusPartVect, mother1PartVect, mother2PartVect, col1PartVect, col2PartVect, pxPartVect, pyPartVect, pzPartVect, ePartVect, mPartVect, tauPartVect, spinPartVect;
  static vector<Double_t> idPartVect1, statusPartVect1, mother1PartVect1, mother2PartVect1, col1PartVect1, col2PartVect1, pxPartVect1, pyPartVect1, pzPartVect1, ePartVect1, mPartVect1, tauPartVect1, spinPartVect1;
  static vector<Double_t> idPartVect2, statusPartVect2, mother1PartVect2, mother2PartVect2, col1PartVect2, col2PartVect2, pxPartVect2, pyPartVect2, pzPartVect2, ePartVect2, mPartVect2, tauPartVect2, spinPartVect2;
  
  if (event_number == 0){   
    
    std::ifstream file("/afs/cern.ch/work/c/celship/SHIPBUILD1/FairShip/shipgen/evrectest.dat");
    if (!file.is_open()){
      std::cerr << "Failed to open file!\n";
      return 0;
    }
    
    const std::string event = "<event>";
    
    std::string line;
    Int_t counter = 0;

    //Beam
    Double_t idPart0, statusPart0, mother1Part0, mother2Part0, col1Part0, col2Part0, pxPart0, pyPart0, pzPart0, ePart0, mPart0, tauPart0, spinPart0;
    
    
    //ALP
    Double_t idPart, statusPart, mother1Part, mother2Part, col1Part, col2Part, pxPart, pyPart, pzPart, ePart, mPart, tauPart, spinPart;
    
    //Gamma1
    Double_t idPart1, statusPart1, mother1Part1, mother2Part1, col1Part1, col2Part1, pxPart1, pyPart1, pzPart1, ePart1, mPart1, tauPart1, spinPart1;
    
    //Gamma2
    Double_t idPart2, statusPart2, mother1Part2, mother2Part2, col1Part2, col2Part2, pxPart2, pyPart2, pzPart2, ePart2, mPart2, tauPart2, spinPart2;
    
    while (std::getline(file, line)){
      
      if (line.find(event) != std::string::npos){
	counter = 1;
	continue;
      }

      if (counter == 2){
	counter++;
	continue;
      }
	      
      if (counter == 1){
	counter++;
	file >> idPart0 >> statusPart0 >> mother1Part0 >> mother2Part0 >> col1Part0 >> col2Part0 >> pxPart0 >> pyPart0 >> pzPart0 >> ePart0 >> mPart0 >> tauPart0 >> spinPart0;  
	idPartVect0.push_back(idPart0) ; statusPartVect0.push_back(statusPart0) ; mother1PartVect0.push_back(mother1Part0) ; mother2PartVect0.push_back(mother2Part0) ; col1PartVect0.push_back(col1Part0) ; col2PartVect0.push_back(col2Part0) ; pxPartVect0.push_back(pxPart0) ; pyPartVect0.push_back(pyPart0) ; pzPartVect0.push_back(pzPart0) ; ePartVect0.push_back(ePart0) ; mPartVect0.push_back(mPart0) ; tauPartVect0.push_back(tauPart0) ; spinPartVect0.push_back(spinPart0);
	continue;
      }
      
      if (counter == 3){
	counter++;
	file >> idPart >> statusPart >> mother1Part >> mother2Part >> col1Part >> col2Part >> pxPart >> pyPart >> pzPart >> ePart >> mPart >> tauPart >> spinPart;  
	idPartVect.push_back(idPart) ; statusPartVect.push_back(statusPart) ; mother1PartVect.push_back(mother1Part) ; mother2PartVect.push_back(mother2Part) ; col1PartVect.push_back(col1Part) ; col2PartVect.push_back(col2Part) ; pxPartVect.push_back(pxPart) ; pyPartVect.push_back(pyPart) ; pzPartVect.push_back(pzPart) ; ePartVect.push_back(ePart) ; mPartVect.push_back(mPart) ; tauPartVect.push_back(tauPart) ; spinPartVect.push_back(spinPart);
	continue;
      }
      
      if (counter == 4){
	counter++;
	file >> idPart1 >> statusPart1 >> mother1Part1 >> mother2Part1 >> col1Part1 >> col2Part1 >> pxPart1 >> pyPart1 >> pzPart1 >> ePart1 >> mPart1 >> tauPart1 >> spinPart1;  
	idPartVect1.push_back(idPart1) ; statusPartVect1.push_back(statusPart1) ; mother1PartVect1.push_back(mother1Part1) ; mother2PartVect1.push_back(mother2Part1) ; col1PartVect1.push_back(col1Part1) ; col2PartVect1.push_back(col2Part1) ; pxPartVect1.push_back(pxPart1) ; pyPartVect1.push_back(pyPart1) ; pzPartVect1.push_back(pzPart1) ; ePartVect1.push_back(ePart1) ; mPartVect1.push_back(mPart1) ; tauPartVect1.push_back(tauPart1) ; spinPartVect1.push_back(spinPart1);  
	continue;
      }
      
      if (counter == 5){
	file >> idPart2 >> statusPart2 >> mother1Part2 >> mother2Part2 >> col1Part2 >> col2Part2 >> pxPart2 >> pyPart2 >> pzPart2 >> ePart2 >> mPart2 >> tauPart2 >> spinPart2;  
	idPartVect2.push_back(idPart2) ; statusPartVect2.push_back(statusPart2) ; mother1PartVect2.push_back(mother1Part2) ; mother2PartVect2.push_back(mother2Part2) ; col1PartVect2.push_back(col1Part2) ; col2PartVect2.push_back(col2Part2) ; pxPartVect2.push_back(pxPart2) ; pyPartVect2.push_back(pyPart2) ; pzPartVect2.push_back(pzPart2) ; ePartVect2.push_back(ePart2) ; mPartVect2.push_back(mPart2) ; tauPartVect2.push_back(tauPart2) ; spinPartVect2.push_back(spinPart2);  
	counter = 0;
      }          
    }
  }
 
 double mA = fALPmass;
 double gA = fALPcoupling;  
 double ctau = hGeV*c_light/(((gA*gA)*(mA*mA*mA))/64*TMath::Pi());
 
 double px, py, pz, EA;
 px = pxPartVect[event_number];
 py = pyPartVect[event_number];
 pz = pzPartVect[event_number];
 EA = ePartVect[event_number];
 
 TLorentzVector ALP_Lz;
 ALP_Lz.SetPxPyPzE(px, py, pz, EA);
 
 double pA = TMath::Sqrt(px*px+py*py+pz*pz); 
 double gama = EA/TMath::Sqrt(EA*EA-pA*pA);
 double beta = ALP_Lz.Beta();  
 double ctau_bg = ctau*beta*gama;
 
 TRandom3 * randm = new TRandom3();
 randm->SetSeed(0);
 
 double z_decay = randm->Exp(ctau_bg);
 
 randm->SetSeed(0);
 
 double target0 = randm->Uniform(13);
 
 if(target0 == 13){
   randm->SetSeed(0);
   target0 = randm->Uniform(13);
 }
 
 double target = Int_t(target0);
 
 randm->SetSeed(0);
 
 double z_target;
 
 if(target == 0)
   z_target = randm->Uniform(-7228.5000, -7220.5000);
 if(target == 1)
   z_target = randm->Uniform(-7220.0000, -7217.5000);
 if(target == 2)
   z_target = randm->Uniform(-7217.0000, -7214.5000);
 if(target == 3)
   z_target = randm->Uniform(-7214.0000, -7211.5000);
 if(target == 4)
   z_target = randm->Uniform(-7211.0000, -7208.5000);
 if(target == 5)
   z_target = randm->Uniform(-7208.0000, -7205.5000);
 if(target == 6)
   z_target = randm->Uniform(-7205.0000, -7202.5000);
 if(target == 7)
   z_target = randm->Uniform(-7202.0000, -7199.5000);
 if(target == 8)
   z_target = randm->Uniform(-7199.0000, -7194.0000);
 if(target == 9)
   z_target = randm->Uniform(-7193.5000, -7188.5000);
 if(target == 10)
   z_target = randm->Uniform(-7188.0000, -7181.5000);
 if(target == 11)
   z_target = randm->Uniform(-7181.0000, -7173.0000);
 if(target == 12)
   z_target = randm->Uniform(-7172.5000, -7164.5000);
 
 randm->SetSeed(0);
 
 double x_target, y_target, r_target;
 r_target = 5; //25 cm target diameter and 5 cm beam diameter
 
 randm->Circle(x_target, y_target, r_target);
 
 TVector3 vv;
 vv.SetXYZ(x_target, y_target, z_target);
 
 double x_decay =  ((TMath::Sin(vv.Theta())*TMath::Cos(vv.Phi())*sqrt(x_target*x_target +y_target*y_target+ z_target*z_target))/z_decay) + x_target;
 double y_decay =  ((TMath::Sin(vv.Theta())*TMath::Sin(vv.Phi())*sqrt(x_target*x_target +y_target*y_target+ z_target*z_target))/z_decay) + y_target; 
 
 z_decay = z_target + z_decay; 
 
 double x_decay2 = x_target + (z_decay/pA) * px;
 double y_decay2 = y_target + (z_decay/pA) * py;
 double z_decay2 = z_target + (z_decay/pA) * pz;
 
 double t_target = 0;
 double t_decay = t_target + (z_decay - z_target)/beta; // [cm/c] + [cm/beta] (beta is dimensionless speed, and c=1 here)
 
 ////////////////////
 
 //gamma1
 double pxg1 = pxPartVect1[event_number];
 double pyg1 = pyPartVect1[event_number];
 double pzg1 = pzPartVect1[event_number];
 double Eg1 = ePartVect1[event_number];
 
 //gamma2
 double pxg2 = pxPartVect2[event_number];
 double pyg2 = pyPartVect2[event_number];
 double pzg2 = pzPartVect2[event_number];
 double Eg2 = ePartVect2[event_number];

 //beam
 double ppx, ppy, ppz, pEA;
 ppx = pxPartVect0[event_number];
 ppy = pyPartVect0[event_number];
 ppz = pzPartVect0[event_number];
 pEA = ePartVect0[event_number];


 //Add beam
 cpg->AddTrack(fbeam, ppx, ppy, ppz, x_target, y_target, z_target, -1,false,pEA,t_target/c_light,1); 
 //Add ALP
 cpg->AddTrack(fALP, px, py, pz, x_target, y_target, z_target, 0,false,EA,t_target/c_light,1); 
 //Add gamma1
 cpg->AddTrack(fgamma, pxg1, pyg1, pzg1, x_decay, y_decay, z_decay, 1,true,Eg1,t_decay/c_light,1); 
 //Add gamma2
 cpg->AddTrack(fgamma, pxg2, pyg2, pzg2, x_decay, y_decay, z_decay, 1,true,Eg2,t_decay/c_light,1); 
 
 
 //cout << event_number << " " <<  px << " " << py << " " << pz << " " << pxg1 << " " << pyg1 << " " << pzg1 << " " << pxg2 << " " << pyg2 << " " << pzg2 << " " << x_target << " " << y_target << " " << z_target << " " << target0 << " " << target << " " << x_decay << " " << y_decay << " " << z_decay << " " << x_decay2 << " " << y_decay2 << " " << z_decay2 << " " << ctau << " " << ctau_bg << " " << ctau/c_light << " " << t_decay << " " << t_decay/c_light << endl; 
 
 //}

 event_number++;
 return kTRUE;
}

ClassImp(ALP_GGGenerator)

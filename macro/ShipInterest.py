# example for accessing smeared hits and fitted tracks
from __future__ import division
import ROOT,os,sys,getopt
import rootUtils as ut
import shipunit as u
from ShipGeoConfig import ConfigRegistry
from rootpyPickler import Unpickler
from decorators import *
import shipRoot_conf
shipRoot_conf.configure()

from ROOT import TMath
from ROOT import TLorentzVector
from ROOT import TVector3
from argparse import ArgumentParser


debug = False
chi2CutOff  = 4.
PDG = ROOT.TDatabasePDG.Instance()
inputFile  = None
geoFile    = None
newFile    = '/afs/cern.ch/work/g/gmachado/SHIPBUILD_NEW/MuBack/Collected0/ship.conical.Pythia8-TGean4.root'
dy         = None
nEvents    = 9999999
fiducialCut = True
measCutFK = 25
measCutPR = 22
docaCut = 2.
flag0 = 1


#
# THIS IS SUPPOSED TO BE A FILE THAT SELECTS
# THE EVENTS THAT HAD MORE THAN 2 HITS ON
# THE TIME DETECTOR (AKA THE USEFULL EVENTS)
#
###############################################################
###############################################################
########## READING THE FILES WITH THE SIMULATIONS #############
###############################################################
###############################################################

 
import os

Events_w_more_than_2_hits = 0

#rootdir = '/eos/home-g/gmachado/gmachado/VACUUM/combinatorial/'
rootdir = '/eos/home-g/gmachado/gmachado/VACUUM/HNL/HNLtoPimu/Mass=1.0/Coupling=5e-10/mu/'
parser = ArgumentParser()
parser.add_argument("-r", "--rootdir", dest="rootdir", help="Root directory from which the macro starts searching \'_rec.root\' files", required=False, default=False)

options = parser.parse_args()

if options.rootdir:
  rootdir = options.rootdir

rec_events_file="reconstructed_events_with_more_than_2_hits.txt"

if os.path.exists(rec_events_file): os.remove(rec_events_file)
reconstructed_events=open(rec_events_file,"w")


for subdir, dirs, files in os.walk(rootdir):
  for file in files:
    if file.startswith("ship.conical") and file.endswith("_rec.root"):
      inputFile =  os.path.join(subdir, file)

      f = ROOT.TFile(inputFile)
      try:
        sTree = f.cbmsim
      except:
	continue

      print" INPUT FILE: ", inputFile, sTree.GetEntries()
      nEvents    = 9999999

      if flag0:
        
        if not geoFile:
          geoFile = inputFile.replace('ship.','geofile_full.').replace('_rec.','.')
        fgeo = ROOT.TFile(geoFile)



        # new geofile, load Shipgeo dictionary written by run_simScript.py
        upkl    = Unpickler(fgeo)
        ShipGeo = upkl.load('ShipGeo')
        ecalGeoFile = ShipGeo.ecal.File
        dy = ShipGeo.Yheight/u.m

        # -----Create geometry----------------------------------------------
        import shipDet_conf
        run = ROOT.FairRunSim()
        run.SetName("TGeant4")  # Transport engine
        run.SetOutputFile(ROOT.TMemFile('output', 'recreate'))  # Output file
        run.SetUserConfig("g4Config_basic.C") # geant4 transport not used, only needed for the mag field
        vrtdb = run.GetRuntimeDb()
        # -----Create geometry----------------------------------------------
	print(ShipGeo)
        modules = shipDet_conf.configure(run,ShipGeo)

	

        import geomGeant4
        if hasattr(ShipGeo.Bfield,"fieldMap"):
          fieldMaker = geomGeant4.addVMCFields(ShipGeo, '', True, withVirtualMC = False)
        else:
          print "no fieldmap given, geofile too old, not anymore support"
          exit(-1)
        sGeo   = fgeo.FAIRGeom
        geoMat =  ROOT.genfit.TGeoMaterialInterface()
        ROOT.genfit.MaterialEffects.getInstance().init(geoMat)
        bfield = ROOT.genfit.FairShipFields()
        bfield.setField(fieldMaker.getGlobalField())
        fM = ROOT.genfit.FieldManager.getInstance()
        fM.init(bfield)

        volDict = {}
        i=0
        for x in ROOT.gGeoManager.GetListOfVolumes():
         volDict[i]=x.GetName()
         i+=1

	writenew = ROOT.TFile(newFile)

        newTree = sTree.CloneTree(0)

        flag0 = 0

      nEvents = min(sTree.GetEntries(),nEvents)


      for n in range(10):
      #for n in range(nEvents)
	sTree.GetEntry(n)
	l = 0
	for phit in sTree.TimeDetPoint:
	  l = l + 1
	  if l > 1:
	    Events_w_more_than_2_hits += 1
	    rc = newTree.Fill()
	    break

print(newTree.GetEntries())

newTree.AutoSave()

  
if inputFile == None:
   print("there is no \"ship.conical\" file in the desired directory")


# output histograms
ROOT.gROOT.cd()

reconstructed_events.write("Events with more than 2 hits on a detector = " + str(Events_w_more_than_2_hits) + "\n")

# close some files
writenew.Close()
reconstructed_events.close()

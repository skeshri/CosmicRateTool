import FWCore.ParameterSet.Config as cms

import os

process = cms.Process("Demo")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load('Configuration.StandardSequences.MagneticField_cff') # B-field map
process.load('Configuration.Geometry.GeometryRecoDB_cff') # Ideal geometry and interface
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff") # Global tag
#process.GlobalTag.connect   = "frontier://FrontierProd/CMS_CONDITIONS"
 
#process.GlobalTag.globaltag ='80X_dataRun2_Prompt_v2' 
process.options = cms.untracked.PSet(
     SkipEvent= cms.untracked.vstring("ProductNotFound"), # make this exception fatal
  )
process.maxEvents=cms.untracked.PSet(input=cms.untracked.int32(-1)) 

import FWCore.Utilities.FileUtils as FileUtils
 
readFiles = cms.untracked.vstring()


readFiles = cms.untracked.vstring( FileUtils.loadListFromFile (os.environ['CMSSW_BASE']+'/src/CosmicTrackTool/TrackAnalyzer/test/'+'list.txt') )
process.source = cms.Source("PoolSource",
			   fileNames = readFiles,
			   eventsToProcess = cms.untracked.VEventRange("271861:MIN-271992:MAX")
			   )

process.demo = cms.EDAnalyzer("TrackAnalyzer",
#				tracks = cms.InputTag("ctfWithMaterialTracksP5"),                # Track collection for prompt RECO Dataset
				tracks = cms.InputTag("ALCARECOTkAlCosmicsCTF0T"),		 # Track collection for stream and prompt ALCARECO Dataset
				muons = cms.InputTag("muons1Leg"),		 # for muon Trigger timing information  
				fileName = cms.untracked.string("Cosmic_rate_tuple.root")
)

process.p = cms.Path(process.demo)



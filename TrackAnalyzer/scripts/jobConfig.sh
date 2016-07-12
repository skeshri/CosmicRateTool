#!/bin/bash

cd $CMSSW_BASE/src/CosmicRateTool/TrackAnalyzer/test/
eval `scramv1 runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/CosmicRateTool/TrackAnalyzer/test/cosmicRateAnalyzer_cfg.py

rfcp Cosmic_rate_tuple.root $CMSSW_BASE/src/CosmicRateTool/TrackAnalyzer/test/


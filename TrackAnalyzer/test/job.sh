#!/bin/bash

cd $CMSSW_BASE/src/CosmicTrackTool/TrackAnalyzer/test
eval `scramv1 runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/CosmicTrackTool/TrackAnalyzer/test/trackAnalyzer_cfg.py

rfcp Cosmic_rate_tuple.root $CMSSW_BASE/src/CosmicTrackTool/TrackAnalyzer/test


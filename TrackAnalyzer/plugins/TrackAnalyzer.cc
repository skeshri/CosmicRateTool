// -*- C++ -*-
//
// Package:    CosmicTrackTool/TrackAnalyzer
// Class:      TrackAnalyzer
// 
/**\class TrackAnalyzer TrackAnalyzer.cc CosmicTrackTool/TrackAnalyzer/plugins/TrackAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
// Originally created:  Justyna Magdalena Tomaszewska,,,
// Revisited by: Ashutosh Bhardwaj and Kirti Ranjan
// Further Developed by: Sumit Keshri (sumit.keshri@cern.ch)
//
//         Created:  Sat, 30 May 2015 20:14:35 GMT
//



// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DPGAnalysis/SiStripTools/interface/APVCyclePhaseCollection.h"
#include "CondFormats/SiStripObjects/interface/SiStripLatency.h"                
#include "CondFormats/DataRecord/interface/SiStripCondDataRecords.h"


#include "DataFormats/Provenance/interface/Timestamp.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"

#include "DataFormats/SiStripDetId/interface/TECDetId.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelBarrelName.h"
#include "DataFormats/SiPixelDetId/interface/PixelEndcapName.h"


#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"



#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <TTree.h>


//
// class declaration
//

// http://cms-service-sdtweb.web.cern.ch/cms-service-sdtweb/doxygen/new1/CMSSW_3_6_0/doc/html/d7/d7d/DQMEventInfo_8cc-source.html
 static inline double stampToReal(edm::Timestamp time)
 {
         return (time.value() >> 32) + 1e-6 * (time.value() & 0xffffffff);
         }





class TrackAnalyzer : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
   public:
      explicit TrackAnalyzer(const edm::ParameterSet&);
      ~TrackAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      virtual void endRun(edm::Run const&, edm::EventSetup const&) override;

      void ClearInEventLoop();
      void ClearInEndRun();
      // ----------member data ---------------------------
      edm::EDGetTokenT<reco::TrackCollection> trackTags_;
      edm::EDGetTokenT<reco::MuonCollection> muonTags_;
      edm::RunNumber_t lastrunnum;
      edm::TimeValue_t lastruntime;

      std::string fileName_;
      TFile* file_;
      TTree* treeEvent;
      TTree* treeRun;

      int			events;
      int       		track_BPIX  ; 	
      int       		track_FPIX  ; 	
      int       		track_PIXEL ; 	
      int       		track_TEC   ; 	
      int       		track_TECM  ; 	
      int       		track_TECP  ; 	
      int       		track_TOB   ; 	
      int       		track_TIB   ;     
      int       		track_TID   ;     
      int       		track_TIDM  ;     
      int       		track_TIDP  ; 	
      
      std::vector<int>		v_ntrk;
      int 			ntrk;
      int			ntrk_runnum;
      std::vector<int>		StripId;
   
      int			number_of_tracks;
      int			number_of_tracks_PIX;
      int			number_of_tracks_FPIX;
      int			number_of_tracks_BPIX;
      int			number_of_tracks_TEC;
      int			number_of_tracks_TECP;
      int			number_of_tracks_TECM;
      int			number_of_tracks_TOB;
      int			number_of_tracks_TIB;
      int			number_of_tracks_TID;
      int			number_of_tracks_TIDP;
      int			number_of_tracks_TIDM;
      int			number_of_events;
      edm::RunNumber_t		runnum;
      edm::TimeValue_t		run_time ;
      std::vector<double>	pt;
      std::vector<double>	charge;
      std::vector<double>	chi2;
      std::vector<double>	chi2_ndof;
      std::vector<double>	eta;
      std::vector<double>	theta;
      std::vector<double>	phi;
      std::vector<double>	p;
      std::vector<double>	d0;
      std::vector<double>	dz;
      std::vector<double>	nvh;
      std::vector<double>	DTtime;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& iConfig):
  trackTags_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
  muonTags_(consumes<reco::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  fileName_(iConfig.getUntrackedParameter<std::string>("fileName"))

{
   //now do what ever initialization is needed
   //
    //edm::Service<TFileService> fs;
    //demohisto = fs->make<TFile>("");

}


TrackAnalyzer::~TrackAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//
void TrackAnalyzer::ClearInEventLoop() {

	pt			.clear();
	charge			.clear(); 
	chi2			.clear();
	chi2_ndof		.clear();
	eta			.clear();
	theta			.clear();
	phi			.clear();
	p			.clear();
	d0			.clear();
	dz			.clear();
	nvh			.clear();
	DTtime			.clear();

}

// ------------ method called for each event  ------------
void
TrackAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   using reco::TrackCollection;
  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByToken(trackTags_, tracks);
   edm::ESHandle<MagneticField> magfield;
   iSetup.get<IdealMagneticFieldRecord>().get(magfield);
   float B_=magfield.product()->inTesla(GlobalPoint(0,0,0)).mag();
//   std::cout<< " magfield " << B_ << std::endl;



   edm::Timestamp ts_begin = iEvent.getRun().beginTime();
   double t_begin = stampToReal(ts_begin);
   edm::Timestamp ts_end = iEvent.getRun().endTime();
   double t_end = stampToReal(ts_end);

   lastruntime = t_end - t_begin;
   lastrunnum = iEvent.getRun().run();

   edm::ESHandle<SiStripLatency> apvlat;
   iSetup.get<SiStripLatencyRcd>().get(apvlat);
//   int mode = -1;
//   if(apvlat->singleReadOutMode()==1) mode = 47; // peak mode
//   if(apvlat->singleReadOutMode()==0) mode = 37; // deco mode


   if (tracks->size()>0) v_ntrk.push_back(tracks->size());

   ntrk	= 0;
   for(TrackCollection::const_iterator itTrack1 = tracks->begin(); itTrack1 != tracks->end(); ++itTrack1)
        {

//	std::cout<< " ==========================================pt : " <<itTrack1->pt() <<std::endl;
	   	pt			.push_back(itTrack1->pt());
	    	charge			.push_back(itTrack1->charge());
	    	chi2			.push_back(itTrack1->chi2());
	    	chi2_ndof		.push_back(itTrack1->normalizedChi2());
	    	eta			.push_back(itTrack1->eta());
	    	theta			.push_back(itTrack1->theta());
	    	phi			.push_back(itTrack1->phi());
	    	p			.push_back(itTrack1->p());
	    	d0			.push_back(itTrack1->d0());
	    	dz			.push_back(itTrack1->dz());
	    	nvh			.push_back(itTrack1->numberOfValidHits());

                int nhitinBPIX  	= 0;
                int nhitinFPIX  	= 0;
                int nhitinPIXEL 	= 0;
                int nhitinTEC 		= 0;
                int nhitinTOB 		= 0;
                int nhitinTIB 		= 0;
                int nhitinTID 		= 0;
                int nhitinTECminus 	= 0;
                int nhitinTECplus 	= 0;
                int nhitinTIDminus 	= 0;
                int nhitinTIDplus 	= 0;
		int countHit 		= 0;
         for(trackingRecHit_iterator iHit1 = itTrack1->recHitsBegin(); iHit1 != itTrack1->recHitsEnd(); ++iHit1)
                {

                   const DetId detId1((*iHit1)->geographicalId());
                   const int subdetId1 = detId1.subdetId();
                   if (!(*iHit1)->isValid()) continue; // only real hits count as in itTrack1->numberOfValidHits()


///////////////////////////////////////////////////////////////////////////////////////////////////
// 			 Hit information in PixelBarrel                          		 //
///////////////////////////////////////////////////////////////////////////////////////////////////

                     if (PixelSubdetector::PixelBarrel == subdetId1) 
			   { 
			       ++nhitinBPIX; ++nhitinPIXEL;
                               PixelBarrelName pxbId1(detId1);
                    /*      if(pxbId1.isHalfModule())
			     {
                               ++nhitinPXBminus;
                             }
                          else
			     {
                               ++nhitinPXBplus;
			     }
		    */
                	   }



///////////////////////////////////////////////////////////////////////////////////////////////////
//			Hit information in PixelEndcap                                  	//
//////////////////////////////////////////////////////////////////////////////////////////////////


                      else if (PixelSubdetector::PixelEndcap == subdetId1) 
			   {
			      ++nhitinFPIX; ++nhitinPIXEL;
                           }



//////////////////////////////////////////////////////////////////////////////////////////////////
//			Hit information in TEC							//
//////////////////////////////////////////////////////////////////////////////////////////////////

                      else if (SiStripDetId::TEC == subdetId1)
                           {
                              ++nhitinTEC;
				StripId.push_back(subdetId1);
                              TECDetId tecId1(detId1);
                          if (tecId1.isZMinusSide()) 
			     {
                              ++nhitinTECminus;
                             }
                          else 
			     {
                              ++nhitinTECplus;
                             }

                           }



//////////////////////////////////////////////////////////////////////////////////////////////////
//			Hit information in TOB		   		                        //
/////////////////////////////////////////////////////////////////////////////////////////////////

                       else if (SiStripDetId::TOB == subdetId1)
                           {
                              ++nhitinTOB;
				StripId.push_back(subdetId1);
                              TOBDetId tobId1(detId1);
                           }



//////////////////////////////////////////////////////////////////////////////////////////////////
//			Hit information in TIB		                                	//
/////////////////////////////////////////////////////////////////////////////////////////////////

                        else if (SiStripDetId::TIB == subdetId1)
                           {
                              ++nhitinTIB;
				StripId.push_back(subdetId1);
                              TIBDetId tibId1(detId1);
                           }



//////////////////////////////////////////////////////////////////////////////////////////////////
//			Hit information in TID		                                	//
/////////////////////////////////////////////////////////////////////////////////////////////////


                        else if (SiStripDetId::TID == subdetId1)
                           {
                              ++nhitinTID;
				StripId.push_back(subdetId1);
                              TIDDetId tidId1(detId1);
                          if (tidId1.isZMinusSide())
                             {
                              ++nhitinTIDminus;
                             }

                          else 
			     {
                              ++nhitinTIDplus;
                             }
                           }
			

			countHit++;
                    } // for Loop over Hits


		StripId.clear();     		

                if (nhitinBPIX		 > 0 )    	{track_BPIX++	;}     
                if (nhitinFPIX  	 > 0 )    	{track_FPIX++	;} 
                if (nhitinPIXEL 	 > 0 )   	{track_PIXEL++	;} 
                if (nhitinTEC 		 > 0 )    	{track_TEC++	;}
                if (nhitinTECminus 	 > 0 ) 		{track_TECM++	;} 
                if (nhitinTECplus	 > 0 )  	{track_TECP++	;}
                if (nhitinTOB		 > 0 )    	{track_TOB++	;}
                if (nhitinTIB		 > 0 )    	{track_TIB++	;}
                if (nhitinTID		 > 0 )    	{track_TID++	;}
                if (nhitinTIDminus	 > 0 ) 		{track_TIDM++	;}
                if (nhitinTIDplus	 > 0 )  	{track_TIDP++	;}


		ntrk++;
		ntrk_runnum++;
		}  // for Loop over TrackCollection

		events++;		


  edm::Handle<reco::MuonCollection> muH;

  iEvent.getByToken(muonTags_, muH);
  const reco::MuonCollection& muonsT0 = *(muH.product()); 


  float time = -9999.;
  float time_error = -9999.;
  float time_ndof = -9999.;

    for (unsigned int i=0; i<muonsT0.size(); i++) {

      //DT time
      reco::MuonTime mt0 = muonsT0[i].time();
      time = mt0.timeAtIpInOut;
      time_error = mt0.timeAtIpInOutErr;
      time_ndof = mt0.nDof;
      DTtime.push_back(time);
//   std::cout<<time<<std::endl;

  }

treeEvent ->Fill();
ClearInEventLoop();

}   //Event Loop


// ------------ method called once each job just before starting event loop  ------------
void 
TrackAnalyzer::beginJob()
{
   file_ 		= new TFile(fileName_.c_str(),"RECREATE");
   treeEvent		= new TTree("Event","");
   treeRun		= new TTree("Run","");

   treeEvent 	->Branch("pt",&pt);
   treeEvent 	->Branch("charge",&charge);
   treeEvent 	->Branch("chi2",&chi2);
   treeEvent 	->Branch("chi2_ndof",&chi2_ndof);
   treeEvent 	->Branch("eta",&eta);
   treeEvent 	->Branch("theta",&theta);
   treeEvent 	->Branch("phi",&phi);
   treeEvent 	->Branch("p",&p);
   treeEvent 	->Branch("d0",&d0);
   treeEvent 	->Branch("dz",&dz);
   treeEvent 	->Branch("nvh",&nvh);
   treeEvent	->Branch("ntrk",&ntrk);
   treeEvent	->Branch("DTtime",&DTtime);
   treeRun	->Branch("run_time",&run_time);   
   treeRun	->Branch("runnum",&runnum);   
   treeRun	->Branch("number_of_events",&number_of_events);
   treeRun	->Branch("number_of_tracks",&number_of_tracks);
   treeRun	->Branch("number_of_tracks_PIX",&number_of_tracks_PIX);
   treeRun	->Branch("number_of_tracks_FPIX",&number_of_tracks_FPIX);
   treeRun	->Branch("number_of_tracks_BPIX",&number_of_tracks_BPIX);
   treeRun	->Branch("number_of_tracks_TID",&number_of_tracks_TID);
   treeRun	->Branch("number_of_tracks_TIDM",&number_of_tracks_TIDM);
   treeRun	->Branch("number_of_tracks_TIDP",&number_of_tracks_TIDP);
   treeRun	->Branch("number_of_tracks_TIB",&number_of_tracks_TIB);
   treeRun	->Branch("number_of_tracks_TEC",&number_of_tracks_TEC);
   treeRun	->Branch("number_of_tracks_TECP",&number_of_tracks_TECP);
   treeRun	->Branch("number_of_tracks_TECM",&number_of_tracks_TECM);
   treeRun	->Branch("number_of_tracks_TOB",&number_of_tracks_TOB);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackAnalyzer::endJob() 
{
   file_->Write();
   file_->Close();
}

// ------------ method called when starting to processes a run  ------------

void 
TrackAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
   lastruntime		= 0.0;
   lastrunnum		= 0.0;
   ntrk_runnum 		= 0.0;
   events		= 0.0;
   track_BPIX           = 0.0;  
   track_FPIX           = 0.0;
   track_PIXEL          = 0.0;
   track_TEC            = 0.0;
   track_TECM           = 0.0;
   track_TECP           = 0.0;
   track_TOB            = 0.0;
   track_TIB            = 0.0;
   track_TID            = 0.0;
   track_TIDM           = 0.0;
   track_TIDP           = 0.0;
}


// ------------ method called when ending the processing of a run  ------------

void 
TrackAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
//   if (lastrunnum !=0 && lastruntime !=0){
//   std::cout<<"lastruntime : "<<lastruntime<<"       lastrunnum : "<<lastrunnum<<std::endl;
//   std::cout<<" ################   : "<<ntrk_runnum<<std::endl;
   number_of_tracks	=ntrk_runnum;
   run_time		= double(lastruntime);
   runnum		= lastrunnum;
   number_of_tracks_PIX	= track_PIXEL ; 
   number_of_tracks_FPIX= track_FPIX ; 
   number_of_tracks_BPIX= track_BPIX; 
   number_of_tracks_TEC	= track_TEC  ; 
   number_of_tracks_TECM= track_TECM ; 
   number_of_tracks_TECP= track_TECP ; 
   number_of_tracks_TOB	= track_TOB  ; 
   number_of_tracks_TIB	= track_TIB  ; 
   number_of_tracks_TID	= track_TID  ; 
   number_of_tracks_TIDM= track_TIDM ; 
   number_of_tracks_TIDP= track_TIDP ; 
   number_of_events	= events;
   treeRun  ->Fill();
}


// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
TrackAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
TrackAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrackAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalyzer);


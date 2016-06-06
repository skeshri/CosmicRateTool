#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <cmath>

void CosmicRates()
{
	TFile *file = new TFile("Cosmic_rate_tuple.root");
	TTree *tree;
	tree = (TTree*)file->Get("Run");
	
   ULong64_t  run_time;
   unsigned int runnum;
   int     number_of_events;
   int     number_of_tracks;
   int     number_of_tracks_PIX;
   int     number_of_tracks_FPIX;
   int     number_of_tracks_BPIX;
   int     number_of_tracks_TID;
   int     number_of_tracks_TIDM;
   int     number_of_tracks_TIDP;
   int     number_of_tracks_TIB;
   int     number_of_tracks_TEC;
   int     number_of_tracks_TECP;
   int     number_of_tracks_TECM;
   int     number_of_tracks_TOB;
   
   tree->SetBranchAddress("run_time", &run_time);
   tree->SetBranchAddress("runnum", &runnum);
   tree->SetBranchAddress("number_of_events", &number_of_events);
   tree->SetBranchAddress("number_of_tracks", &number_of_tracks);
   tree->SetBranchAddress("number_of_tracks_PIX", &number_of_tracks_PIX);
   tree->SetBranchAddress("number_of_tracks_FPIX", &number_of_tracks_FPIX);
   tree->SetBranchAddress("number_of_tracks_BPIX", &number_of_tracks_BPIX);
   tree->SetBranchAddress("number_of_tracks_TID", &number_of_tracks_TID);
   tree->SetBranchAddress("number_of_tracks_TIDM", &number_of_tracks_TIDM);
   tree->SetBranchAddress("number_of_tracks_TIDP", &number_of_tracks_TIDP);
   tree->SetBranchAddress("number_of_tracks_TIB", &number_of_tracks_TIB);
   tree->SetBranchAddress("number_of_tracks_TEC", &number_of_tracks_TEC);
   tree->SetBranchAddress("number_of_tracks_TECP", &number_of_tracks_TECP);
   tree->SetBranchAddress("number_of_tracks_TECM", &number_of_tracks_TECM);
   tree->SetBranchAddress("number_of_tracks_TOB", &number_of_tracks_TOB);
   
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//		Various Rates Declerations				
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

   Long64_t n = tree->GetEntriesFast();

   double * event_rate 		= new double[n];
   double * event_rate_err	= new double[n]; 
   double * track_rate 		= new double[n]; 
   double * track_rate_err	= new double[n]; 
   double * runNumber  		= new double[n];
   double * runNumber_err	= new double[n];
   double * track_rate_PIX 	= new double[n]; 
   double * track_rate_PIX_err 	= new double[n]; 
   double * track_rate_FPIX	= new double[n]; 
   double * track_rate_FPIX_err	= new double[n]; 
   double * track_rate_BPIX 	= new double[n]; 
   double * track_rate_BPIX_err	= new double[n]; 
   double * track_rate_TOB 	= new double[n]; 
   double * track_rate_TOB_err 	= new double[n]; 
   double * track_rate_TIB 	= new double[n]; 
   double * track_rate_TIB_err 	= new double[n]; 
   double * track_rate_TID 	= new double[n]; 
   double * track_rate_TID_err 	= new double[n]; 
   double * track_rate_TEC 	= new double[n];
   double * track_rate_TEC_err 	= new double[n];
   double * track_rate_TECP 	= new double[n];
   double * track_rate_TECP_err	= new double[n];
   double * track_rate_TECM 	= new double[n];
   double * track_rate_TECM_err	= new double[n];
   double * tracks		= new double[n];
   double * tracks_err		= new double[n];
   double * tracks_bpix		= new double[n];
   double * tracks_fpix		= new double[n];
   double * tracks_pix		= new double[n];
   double * tracks_tec		= new double[n];
   double * weight		= new double[n];
   double * weight2		= new double[n];



   
   string Bar_Xtitle[8] = {"Event","Track","FPIX","BPIX","TIB","TID","TOB","TEC"};
   double Bar_Ytitle[8] = {0};
   
   
   int j=0;
   double total_tracks = 0;
   double bpix_tracks = 0;
   double fpix_tracks = 0;
   double pix_tracks = 0;
   double tracks_TECoff = 0;
   
   cout<<n<<endl;
   cout<<"##############################################################\n";
   cout<<"		Track rate for each run number			\n";
   cout<<"##############################################################\n"; 

   for (Long64_t jentry=0; jentry<n;jentry++) 
   {
     tree->GetEntry(jentry);
     if (run_time == 0 ) continue;
 //     cout<< number_of_tracks/double(run_time)<<endl;
      event_rate[j] = number_of_events/double(run_time);
      runNumber [j] = runnum;
      track_rate[j] = number_of_tracks/double(run_time);
      track_rate_PIX[j] = number_of_tracks_PIX/double(run_time);
      track_rate_FPIX[j] = number_of_tracks_FPIX/double(run_time);
      track_rate_BPIX[j] = number_of_tracks_BPIX/double(run_time);
      track_rate_TOB[j] = number_of_tracks_TOB/double(run_time);
      track_rate_TIB[j] = number_of_tracks_TIB/double(run_time);
      track_rate_TID[j] = number_of_tracks_TID/double(run_time);
      track_rate_TEC[j] = number_of_tracks_TEC/double(run_time);
      track_rate_TECP[j] = number_of_tracks_TECP/double(run_time);
      track_rate_TECM[j] = number_of_tracks_TECM/double(run_time);
      tracks[j]  	   	= number_of_tracks;
      tracks_bpix[j]  	   	= number_of_tracks_BPIX;
      tracks_fpix[j]  	   	= number_of_tracks_FPIX;
      tracks_pix[j]  	   	= number_of_tracks_PIX;
      tracks_tec[j]  	   	= number_of_tracks_TECM;
      total_tracks		+= tracks[j];
      bpix_tracks += tracks_bpix[j];
      fpix_tracks += tracks_fpix[j];
      pix_tracks += tracks_pix[j];


//       cout<<"runnum  :  "<<runnum[j]<<"  tracks tec  : "<< tracks_tec[j]<<endl;
       cout<<"runnum  :  "<<runnum[j]<<"  tracks  : "<< tracks[j]<<"   track rates :  "<<track_rate[j]<<endl;
       track_rate_err[j] = sqrt(float(number_of_tracks))/double(run_time);
       event_rate_err[j] = sqrt(float(number_of_events))/double(run_time);
       track_rate_PIX_err[j] = sqrt(float(number_of_tracks_PIX))/double(run_time);

       track_rate_FPIX_err[j] = sqrt(float(number_of_tracks_FPIX))/double(run_time);
       track_rate_BPIX_err[j] = sqrt(float(number_of_tracks_BPIX))/double(run_time);
       track_rate_TOB_err[j] = sqrt(float(number_of_tracks_TOB))/double(run_time);
       track_rate_TIB_err[j] = sqrt(float(number_of_tracks_TIB))/double(run_time);
       track_rate_TID_err[j] = sqrt(float(number_of_tracks_TID))/double(run_time);
       track_rate_TEC_err[j] = sqrt(float(number_of_tracks_TEC))/double(run_time);
       track_rate_TECP_err[j] = sqrt(float(number_of_tracks_TECP))/double(run_time);
       track_rate_TECM_err[j] = sqrt(float(number_of_tracks_TECM))/double(run_time);

      runNumber_err[j]  = 0;   
	if (number_of_tracks_TECM == 0){
	tracks_TECoff += tracks[j];}

      j++;
	

     
     }

   cout<<endl<<endl;
   cout<<"##############################################################\n";
   cout<<"	Some information on total number of tracks		\n";
   cout<<"##############################################################\n";

     cout<<"total tracks  : "<<total_tracks<<endl;
     cout<<"tracks bpix  : "<<bpix_tracks<<endl;
     cout<<"tracks fpix  : "<<fpix_tracks<<endl;
     cout<<"tracks pix  : "<<pix_tracks<<endl;
     cout<<"tracks TEC off   : "<<tracks_TECoff<<endl;
     cout<<endl<<endl;
     
//+++++++++++++++++++++++++++++       Make Directories     +++++++++++++++++++++++++++++++++++++

	gSystem->Exec("mkdir -p Rate_Plots");

//----------------------------------------------------------------------------------------------


	TCanvas *c  = new TCanvas("c","c",800,600);    // Declare canvas


//+++++++++++++++++++++++++++++  Overall event event rate  +++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_event_rate = new TGraphErrors(j,runNumber,event_rate,runNumber_err,event_rate_err);
	gr_event_rate->GetXaxis()->SetTitle("Run Number");
	gr_event_rate->GetXaxis()->SetLabelSize(0.03);
	gr_event_rate->GetXaxis()->SetNoExponent();
	gr_event_rate->GetYaxis()->SetTitle("Event Rate (in Hz)");
	gr_event_rate->SetMarkerStyle(20);
	gr_event_rate->SetMarkerSize(1.2);
	gr_event_rate->SetMarkerColor(kBlue);
	gr_event_rate->SetTitle("Event Rate");
	gr_event_rate->GetYaxis()->SetRangeUser(0,7);
	gr_event_rate->Draw("AP");
	c->SetGrid();
    	c->SaveAs("event_rate.png");
	c->Clear();
	gSystem->Exec("mv event_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++  Overall track rate  +++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate = new TGraphErrors(j,runNumber,track_rate,runNumber_err,track_rate_err);
	gr_track_rate->GetXaxis()->SetTitle("Run Number");
	gr_track_rate->GetXaxis()->SetLabelSize(0.03);
	gr_track_rate->GetXaxis()->SetNoExponent();
	gr_track_rate->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate->SetMarkerStyle(20);
	gr_track_rate->SetMarkerSize(1.2);
	gr_track_rate->SetMarkerColor(kBlue);
	gr_track_rate->SetTitle("Track Rate");
	gr_track_rate->GetYaxis()->SetRangeUser(0,5);
	gr_track_rate->Draw("AP");
	c->SetGrid();
        c->SaveAs("track_rate.png");
	c->Clear();
	gSystem->Exec("mv track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++  Total Pixel track rate +++++++++++++++++++++++++++++++++++++++  

	TGraphErrors * gr_track_rate_PIX = new TGraphErrors(j,runNumber,track_rate_PIX,runNumber_err,track_rate_PIX_err);
	gr_track_rate_PIX->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_PIX->GetXaxis()->SetNoExponent();
	gr_track_rate_PIX->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_PIX->SetMarkerStyle(20);
	gr_track_rate_PIX->SetMarkerSize(1.2);
	gr_track_rate_PIX->SetMarkerColor(kBlue);
	gr_track_rate_PIX->SetTitle("Pixel Track Rate");
	gr_track_rate_PIX->Draw("AP");
	c->SetGrid();
        c->SaveAs("pixel_track_rate.png");
	c->Clear();
	gSystem->Exec("mv pixel_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++  FPIX track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_FPIX = new TGraphErrors(j,runNumber,track_rate_FPIX,runNumber_err,track_rate_FPIX_err);
	gr_track_rate_FPIX->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_FPIX->GetXaxis()->SetNoExponent();
	gr_track_rate_FPIX->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_FPIX->SetMarkerStyle(20);
	gr_track_rate_FPIX->SetMarkerSize(1.2);
	gr_track_rate_FPIX->SetMarkerColor(kBlue);
	gr_track_rate_FPIX->SetTitle("FPIX Track Rate");
	gr_track_rate_FPIX->Draw("AP");
	c->SetGrid();
        c->SaveAs("fpix_track_rate.png");
	c->Clear();
	gSystem->Exec("mv fpix_track_rate.png Rate_Plots");
//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  BPIX track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_BPIX = new TGraphErrors(j,runNumber,track_rate_BPIX,runNumber_err,track_rate_BPIX_err);
	gr_track_rate_BPIX->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_BPIX->GetXaxis()->SetNoExponent();
	gr_track_rate_BPIX->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_BPIX->SetMarkerStyle(20);
	gr_track_rate_BPIX->SetMarkerSize(1.2);
	gr_track_rate_BPIX->SetMarkerColor(kBlue);
	gr_track_rate_BPIX->SetTitle("BPIX Track Rate");
	gr_track_rate_BPIX->Draw("AP");
	c->SetGrid();
        c->SaveAs("bpix_track_rate.png");
	c->Clear();
	gSystem->Exec("mv bpix_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  TOB track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_TOB = new TGraphErrors(j,runNumber,track_rate_TOB,runNumber_err,track_rate_TOB_err);
	gr_track_rate_TOB->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_TOB->GetXaxis()->SetNoExponent();
	gr_track_rate_TOB->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_TOB->SetMarkerStyle(20);
	gr_track_rate_TOB->SetMarkerSize(1.2);
	gr_track_rate_TOB->SetMarkerColor(kBlue);
	gr_track_rate_TOB->SetTitle("TOB Track Rate");
	gr_track_rate_TOB->Draw("AP");
	c->SetGrid();
        c->SaveAs("tob_track_rate.png");
	c->Clear();
	gSystem->Exec("mv tob_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  TIB track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_TIB = new TGraphErrors(j,runNumber,track_rate_TIB,runNumber_err,track_rate_TIB_err);
	gr_track_rate_TIB->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_TIB->GetXaxis()->SetNoExponent();
	gr_track_rate_TIB->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_TIB->SetMarkerStyle(20);
	gr_track_rate_TIB->SetMarkerSize(1.2);
	gr_track_rate_TIB->SetMarkerColor(kBlue);
	gr_track_rate_TIB->SetTitle("TIB Track Rate");
	gr_track_rate_TIB->Draw("AP");
	c->SetGrid();
        c->SaveAs("tib_track_rate.png");
	c->Clear();
	gSystem->Exec("mv tib_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  TID track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_TID = new TGraphErrors(j,runNumber,track_rate_TID,runNumber_err,track_rate_TID_err);
	gr_track_rate_TID->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_TID->GetXaxis()->SetNoExponent();
	gr_track_rate_TID->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_TID->SetMarkerStyle(20);
	gr_track_rate_TID->SetMarkerSize(1.2);
	gr_track_rate_TID->SetMarkerColor(kBlue);
	gr_track_rate_TID->SetTitle("TID Track Rate");
	gr_track_rate_TID->Draw("AP");
	c->SetGrid();
        c->SaveAs("tid_track_rate.png");
	c->Clear();
	gSystem->Exec("mv tid_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  Total TEC track rate  ++++++++++++++++++++++++++++++++++++++++++++ 

	TGraphErrors * gr_track_rate_TEC = new TGraphErrors(j,runNumber,track_rate_TEC,runNumber_err,track_rate_TEC_err);
	gr_track_rate_TEC->GetXaxis()->SetTitle("Run Number");
	gr_track_rate_TEC->GetXaxis()->SetNoExponent();
	gr_track_rate_TEC->GetYaxis()->SetTitle("Track Rate (in Hz)");
	gr_track_rate_TEC->SetMarkerStyle(20);
	gr_track_rate_TEC->SetMarkerSize(1.2);
	gr_track_rate_TEC->SetMarkerColor(kBlue);
	gr_track_rate_TEC->SetTitle("TEC Track Rate");
	gr_track_rate_TEC->Draw("AP");
	c->SetGrid();
        c->SaveAs("tec_track_rate.png");
	c->Clear();
	gSystem->Exec("mv tec_track_rate.png Rate_Plots");

//-----------------------------------------------------------------------------------------------


//++++++++++++++++++++++++++++++++  TEC+/- track rate  ++++++++++++++++++++++++++++++++++++++++++++ 
	TMultiGraph *mg = new TMultiGraph("track rate","TRack Rate TEC+/-");		// Multigraph decleration
	
	TGraphErrors * gr_track_rate_TECP = new TGraphErrors(j,runNumber,track_rate_TECP,runNumber_err,track_rate_TECP_err);
	gr_track_rate_TECP->SetMarkerStyle(20);
	gr_track_rate_TECP->SetMarkerSize(1.2);
	gr_track_rate_TECP->SetMarkerColor(kBlack);

	TGraphErrors * gr_track_rate_TECM = new TGraphErrors(j,runNumber,track_rate_TECM,runNumber_err,track_rate_TECM_err);
	gr_track_rate_TECM->SetMarkerStyle(20);
	gr_track_rate_TECM->SetMarkerSize(1.2);
	gr_track_rate_TECM->SetMarkerColor(kRed);

	mg->Add(gr_track_rate_TECP);
	mg->Add(gr_track_rate_TECM);
	mg->Draw("AP");
	mg->GetXaxis()->SetTitle("Run Number");
	mg->GetXaxis()->SetNoExponent();
	mg->GetYaxis()->SetTitle("Track Rate (in Hz)");
	
	TLegend *leg = new TLegend(0.8,0.8,0.94,0.92);			// Legend for TEC+/-
	leg -> AddEntry(gr_track_rate_TECP, "TEC+","p");
	leg -> AddEntry(gr_track_rate_TECM, "TEC-","p");
	leg -> SetBorderSize(1);
	leg -> SetShadowColor(0);
	leg -> SetFillColor(0);
	leg -> Draw();
	c->SetGrid();
        c->SaveAs("tec_track_ratePM.png");
	c->Clear();
	gSystem->Exec("mv tec_track_ratePM.png Rate_Plots");

//-----------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------
//					Weighted Mean calculation
//-----------------------------------------------------------------------------------------------

						
        double total_weight		= 0;
	double weighted_mean_track_rate;
	double weighted_mean_track_rate_TEC;
	double weighted_mean_track_rate_TOB;
	double weighted_mean_track_rate_TIB;
	double weighted_mean_track_rate_TID;
	double weighted_mean_track_rate_FPIX;
	double weighted_mean_track_rate_BPIX;
	double weighted_mean_event_rate;
	
	for (int k = 0; k < j; k++)
	{
		weight[k] = tracks[k]/total_tracks;
	}


	for (int a = 0; a < j ; a++)
	{
          weighted_mean_track_rate 		+= track_rate[a]     * weight[a] ; 		
          weighted_mean_track_rate_TEC 		+= track_rate_TEC[a] * weight[a] ; 	
          weighted_mean_track_rate_TOB 		+= track_rate_TOB[a] * weight[a] ; 	
          weighted_mean_track_rate_TIB 		+= track_rate_TIB[a] * weight[a] ;	
          weighted_mean_track_rate_TID 		+= track_rate_TID[a] * weight[a] ;	
          weighted_mean_track_rate_FPIX 	+= track_rate_FPIX[a]* weight[a] ;	
          weighted_mean_track_rate_BPIX 	+= track_rate_BPIX[a]* weight[a] ; 	
          weighted_mean_event_rate 		+= event_rate[a]     * weight[a] ; 		
	  total_weight			    	+= weight[a] ;
	}

        cout<<endl<<endl;
	cout<< "##########################################################################################"<<endl;
	cout<< "				Weighted Mean 						  "<<endl;
	cout<< "##########################################################################################"<<endl;
	cout<<endl; 
	cout<<"weighted_mean_track_rate       :   "<<weighted_mean_track_rate      <<endl;
	cout<<"weighted_mean_track_rate_TEC   :   "<<weighted_mean_track_rate_TEC  <<endl;
	cout<<"weighted_mean_track_rate_TOB   :   "<<weighted_mean_track_rate_TOB  <<endl;
	cout<<"weighted_mean_track_rate_TIB   :   "<<weighted_mean_track_rate_TIB  <<endl;
	cout<<"weighted_mean_track_rate_TID   :   "<<weighted_mean_track_rate_TID  <<endl;
	cout<<"weighted_mean_track_rate_FPIX  :   "<<weighted_mean_track_rate_FPIX <<endl;
	cout<<"weighted_mean_track_rate_BPIX  :   "<<weighted_mean_track_rate_BPIX <<endl;
	cout<<"weighted_mean_event_rate       :   "<<weighted_mean_event_rate      <<endl;
    	cout<<endl<<endl;

	
 
//-----------------------------------------------------------------------------------------------
//			Summary Plot for track rate in each Subdetector				 
//-----------------------------------------------------------------------------------------------

   	TH1F *h1b = new TH1F("h1b","rate summary",8,0,8);
   	h1b->SetFillColor(4);
   	h1b->SetBarWidth(0.3);
   	h1b->SetBarOffset(0.35);
   	h1b->SetStats(0);

	Bar_Ytitle[0] = weighted_mean_event_rate;     
	Bar_Ytitle[1] = weighted_mean_track_rate;     
	Bar_Ytitle[2] = weighted_mean_track_rate_FPIX;     
	Bar_Ytitle[3] = weighted_mean_track_rate_BPIX; 
	Bar_Ytitle[4] = weighted_mean_track_rate_TIB; 
	Bar_Ytitle[5] = weighted_mean_track_rate_TID;
	Bar_Ytitle[6] = weighted_mean_track_rate_TOB; 
	Bar_Ytitle[7] = weighted_mean_track_rate_TEC;

      for (int i=1; i<=8; i++)
        {
      	h1b->SetBinContent(i, Bar_Ytitle[i-1]);
      	h1b->GetXaxis()->SetBinLabel(i,Bar_Xtitle[i-1].c_str());
  	}

	gStyle->SetPaintTextFormat("1.4f");
	h1b->LabelsOption("d");
	h1b->SetLabelSize(0.04);
	h1b->GetYaxis()->SetTitle("Average Rate (Hz)");
	h1b->Draw("bTEXT");
	c->SaveAs("Summary_Chart.png");
        c->Close();

  }
   
   
   
   
   
   

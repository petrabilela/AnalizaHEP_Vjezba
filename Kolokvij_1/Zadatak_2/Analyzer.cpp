#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::Plot() {
    

    TCanvas* plotCanvas = new TCanvas();
    plotCanvas->SetCanvasSize(900, 900);
    TH2F* histogram = new TH2F("J/psi Mass vs dR", "J/psi Mass vs dR", 100, 2.0, 4.0, 100, 0.0, 1.5);


    for (Long64_t i = 0; i < entries; i++) {
        fChain->GetEntry(i);
        TLorentzVector electron1, electron2, jpsi;
	
	
        electron.SetPtEtaPhiM (ele_pt -> at (0), ele_eta -> at (0), ele_phi -> at (0), 0);
	pozitron.SetPtEtaPhiM (ele_pt -> at (1), ele_eta -> at (1), ele_phi -> at (1), 0);
	Jpsi = electron + pozitron;

        jpsi = electron1 + electron2;

        float dR = electron1.DeltaR(electron2);
        histogram->Fill(jpsi.M(), dR);
    }


    plotCanvas->SetLeftMargin(0.15);
    plotCanvas->SetBottomMargin(0.15);
    plotCanvas->SetTitle("J/psi Mass vs dR");
    histogram->Draw("COLZ");
    histogram->SetStats(0);
    histogram->GetXaxis()->SetTitle("J/psi Mass (GeV)");
    histogram->GetYaxis()->SetTitle("dR");
    histogram->GetXaxis()->SetLabelSize(0.04);
    histogram->GetYaxis()->SetLabelSize(0.04);
    histogram->SetFillColor(kRainBow);

    plotCanvas->Print("Jpsi_mass_dR_histogram.pdf");
    plotCanvas->Print("Jpsi_mass_dR_histogram.png");
    plotCanvas->Print("Jpsi_mass_dR_histogram.root");

    delete plotCanvas;
    delete histogram;



}

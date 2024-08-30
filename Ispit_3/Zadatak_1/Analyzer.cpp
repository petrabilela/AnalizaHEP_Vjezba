#include "Analyzer.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Analyzer::Analyzer(const char* filename) : alpha_0(0.9), alpha_1(1.1), numMeasurements(1000), numExperiments(10000) {
    TFile* file = new TFile(filename);
    tree = (TTree*)file->Get("tree");
    tree->SetBranchAddress("x", &x);
    InitializeHistograms();
}

Analyzer::~Analyzer() {
    delete hist_H0;
    delete hist_H1;
}

void Analyzer::InitializeHistograms() {
    hist_H0 = new TH1F("hist_H0", "Hypothesis H0; Median; Frequency", 100, 0, 5);
    hist_H1 = new TH1F("hist_H1", "Hypothesis H1; Median; Frequency", 100, 0, 5);
}

void Analyzer::GeneratePseudoExperiments() {
    for (int i = 0; i < numExperiments; ++i) {
        vector<double> data_H0, data_H1;
        
        for (int j = 0; j < numMeasurements; ++j) {
            double x_H0 = randGen.Exp(1.0 / alpha_0);
            double x_H1 = randGen.Exp(1.0 / alpha_1);
            data_H0.push_back(x_H0);
            data_H1.push_back(x_H1);
        }

        nth_element(data_H0.begin(), data_H0.begin() + data_H0.size() / 2, data_H0.end());
        nth_element(data_H1.begin(), data_H1.begin() + data_H1.size() / 2, data_H1.end());
        double median_H0 = data_H0[data_H0.size() / 2];
        double median_H1 = data_H1[data_H1.size() / 2];

        hist_H0->Fill(median_H0);
        hist_H1->Fill(median_H1);
    }
}

void Analyzer::PlotResults() {
    TCanvas* canvas = new TCanvas("canvas", "Test of Hypotheses", 800, 600);
    
    gStyle->SetOptStat(0);    
    
 
    hist_H0->SetLineColor(kRed);
    hist_H0->DrawNormalized();
    
    hist_H1->SetLineColor(kBlue);
    hist_H1->DrawNormalized("SAME");
    
    hist_H0->Scale(1.0 / hist_H0->Integral());
    hist_H1->Scale(1.0 / hist_H1->Integral());

    hist_H0->GetXaxis()->SetRangeUser(0, 2.5); 
    hist_H0->SetMinimum(0.0);                  
    hist_H0->SetMaximum(1.0);

    TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
    legend->AddEntry(hist_H0, "Hypothesis H0", "l");
    legend->AddEntry(hist_H1, "Hypothesis H1", "l");
    legend->Draw();

    canvas->SaveAs("hypotheses_test.png");
    delete canvas;
}

double Analyzer::ComputeObservedMedian() {
    vector<double> observedValues;
    Long64_t nentries = tree->GetEntries();

    for (Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        observedValues.push_back(x);
    }

    nth_element(observedValues.begin(), observedValues.begin() + observedValues.size() / 2, observedValues.end());
    double observedMedian = observedValues[observedValues.size() / 2];

    cout << "Medijan uočenih vrijednosti: " << observedMedian << endl;
    return observedMedian;
}

double Analyzer::CalculatePValue(double observedMedian) {
    int bin = hist_H0->FindBin(observedMedian);
    double pValue = hist_H0->Integral(bin, hist_H0->GetNbinsX()) / hist_H0->Integral();
    
    cout << "P-vrijednost: " << pValue << endl;
    return pValue;
}

double Analyzer::CalculateConfidenceLevel(double observedMedian) {
    double confidenceLevel = 1.0 - CalculatePValue(observedMedian);
    cout << "Razina pouzdanosti za odbacivanje hipoteze H1: " << confidenceLevel << endl;
    return confidenceLevel;
}

void Analyzer::TestHypotheses() {
    GeneratePseudoExperiments();
    PlotResults();
    
    double observedMedian = ComputeObservedMedian();
    CalculatePValue(observedMedian);
    CalculateConfidenceLevel(observedMedian);
}


#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

Analyzer::Analyzer(const char* filename) : N(20), p_H0(0.62), p_H1(0.66), numExperiments(1000), numMeasurements(100) {
    inputFile = new TFile(filename, "READ");
    if (!inputFile || inputFile->IsZombie()) {
        cout << "Error..." << endl;
        return;
    }
    Initialize();
}

Analyzer::~Analyzer() {
    delete histogram;
    delete h_H0;
    delete h_H1;
    inputFile->Close();
    delete inputFile;
}

void Analyzer::Initialize() {
    inputFile->GetObject("histogram", histogram);
    if (!histogram) {
        cout << "Histogram error..." << endl;
        return;
    }

    histogram->Scale(1.0 / histogram->Integral()); 

    h_H0 = new TH1F("h_H0", "Distribucija hipoteza", 100, 0, 1);
    h_H1 = new TH1F("h_H1", "Distribucija hipoteza", 100, 0, 1);

    FillHistograms();
}

void Analyzer::FillHistograms() {
    for (int i = 0; i < numExperiments; ++i) {
        double success_H0 = 0;
        double success_H1 = 0;

        for (int j = 0; j < numMeasurements; ++j) {
            int k_H0 = randGen.Binomial(N, p_H0);
            int k_H1 = randGen.Binomial(N, p_H1);

            success_H0 += static_cast<double>(k_H0) / N;
            success_H1 += static_cast<double>(k_H1) / N;
        }

        success_H0 /= numMeasurements;
        success_H1 /= numMeasurements;

        h_H0->Fill(success_H0);
        h_H1->Fill(success_H1);
    }

    h_H0->Scale(1.0 / h_H0->Integral());
    h_H1->Scale(1.0 / h_H1->Integral());
}

void Analyzer::GeneratePseudoExperiments() {
    FillHistograms();
}

double Analyzer::BinomialFunction(int n, double p, int k) {
    double prob = TMath::Binomial(n, k) * TMath::Power(p, k) * TMath::Power(1 - p, n - k);
    return prob;
}

double Analyzer::GetObservedProbability() {
    double totalSuccesses = 0;
    double totalEntries = histogram->GetEntries();

    for (int i = 1; i <= histogram->GetNbinsX(); ++i) {
        double k = histogram->GetBinCenter(i);
        double freq = histogram->GetBinContent(i);
        totalSuccesses += k * freq;  
    }

    double observed_p = totalSuccesses / (N * totalEntries);  
    cout << "Uočena vjerojatnost uspjeha: " << observed_p << endl;
    return observed_p;
}

void Analyzer::CalculatePValue() {
    double observed_p = GetObservedProbability();

    int bin_H0 = h_H0->FindBin(observed_p);
    int bin_H1 = h_H1->FindBin(observed_p);

    double p_H0_obs = h_H0->Integral(bin_H0, h_H0->GetNbinsX());
    double p_H1_obs = h_H1->Integral(bin_H1, h_H1->GetNbinsX());

    double pValue = 1 - (p_H1_obs / p_H0_obs);
    cout << "P-vrijednost: " << pValue << endl;
}

void Analyzer::DrawResults() {
    TCanvas* canvas = new TCanvas("canvas", "Distribucija Hipoteza", 800, 600);

    gStyle->SetOptStat(0);

    h_H0->SetLineColor(kRed);
    h_H1->SetLineColor(kBlue);

    h_H0->GetXaxis()->SetTitle("Vjerojatnost uspjeha (p)");
    h_H0->GetYaxis()->SetTitle("Normalizirani broj dogadaja");

    h_H0->SetTitle("Distribucija Hipoteza");

    h_H0->Draw("HIST");
    h_H1->Draw("HIST SAME");

    TLegend* legend = new TLegend(0.7, 0.8, 0.9, 0.9);
    legend->AddEntry(h_H0, "Hipoteza H0 (p = 0.62)", "l");
    legend->AddEntry(h_H1, "Hipoteza H1 (p = 0.66)", "l");
    legend->Draw();

    canvas->SaveAs("TestHipoteza.png");
    delete canvas;
}


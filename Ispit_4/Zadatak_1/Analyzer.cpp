#include "Analyzer.h"

Analyzer::Analyzer() {
    randGen = new TRandom3();
    chiSquareDist = new TH1F("chiSquareDist", "Chi-Square Minimum Distribution; #chi^{2}_{min}; Frequency", 100, 0, 60);
    nPseudoExperiments = 1000;

    fitFunc = new TF1("fitFunc", "[0] * exp(-0.8 * x)", 0, 60);
    fitFunc->SetParameter(0, 1.0 / 12.5);
}

Analyzer::~Analyzer() {
    delete randGen;
    delete chiSquareDist;
    delete fitFunc;
}

void Analyzer::GeneratePseudoExperiments() {
    for (int i = 0; i < nPseudoExperiments; ++i) {
        TH1F* pseudoHist = new TH1F("pseudoHist", "Pseudo-Experiment", 100, 0, 60);

        for (int j = 0; j < 10000; ++j) {
            double x = randGen->Exp(1 / 0.8);
            pseudoHist->Fill(x);
        }

        pseudoHist->Scale(1.0 / pseudoHist->Integral());

        pseudoHist->Fit(fitFunc, "Q");
        double chiSquareMin = fitFunc->GetChisquare();
        chiSquareDist->Fill(chiSquareMin);

        delete pseudoHist;
    }
}

void Analyzer::PlotChiSquareDistribution() {
    TCanvas* canvas = new TCanvas("canvas", "Chi-Square Minimum Distribution", 800, 600);
    chiSquareDist->Draw("HIST");

    canvas->SaveAs("ChiSquareDistribution.png");
    delete canvas;    
}

double Analyzer::CalculateChiSquareMin(const char* filename) {
    TFile* inputFile = new TFile(filename, "READ");
    TH1F* histogram;
    inputFile->GetObject("histogram", histogram);

    histogram->Scale(1.0 / histogram->Integral());
    histogram->Fit(fitFunc, "Q");

    double chiSquareMin = fitFunc->GetChisquare();

    inputFile->Close();

    return chiSquareMin;
}


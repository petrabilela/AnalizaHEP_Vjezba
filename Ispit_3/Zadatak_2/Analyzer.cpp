#include "Analyzer.h"

Analyzer::Analyzer() {}

Analyzer::~Analyzer() {}

void Analyzer::QuadraticFit() {
    TFile *inputFile = new TFile("/home/public/data/QuadraticHisto.root");
    TH1F *histogram;
    inputFile->GetObject("histogram", histogram);

    if (!histogram) {
        cerr << "Histogram nije pronađen!" << endl;
        return;
    }

    histogram->SetTitle("Histogram i Fit Funkcija; Vrijednosti x; Frekvencija");

    TF1 *fitFunction = new TF1("fitFunction", "[0] * ([1] * x * x + 3)", -10, 10);
    fitFunction->SetParameters(100, 0.0); 

    histogram->Fit(fitFunction, "L");

    TCanvas *canvas1 = new TCanvas("canvas1", "Likelihood Function", 600, 400);
    TF1 *negLogLikelihood = new TF1("negLogLikelihood", "-2*([0]*TMath::Log([1]*(x*x + 3)))", -0.1, 0.1);
    negLogLikelihood->SetParameters(fitFunction->GetParameter(0), histogram->GetEntries());

    negLogLikelihood->SetTitle("Negativni Log-Likelihood; Parametar a; -2lnL");
    negLogLikelihood->Draw();
    canvas1->SaveAs("NegLogLikelihood.pdf");

    double a_value = fitFunction->GetParameter(1);
    double a_error = fitFunction->GetParError(1);
    cout << "Vrijednost parametra a: " << a_value << " ± " << a_error << endl;

    double minimum = negLogLikelihood->GetMinimum(-0.1, 0.1);
    double threshold = minimum + 25; 

    double a_min = negLogLikelihood->GetX(threshold, -0.1, a_value);
    double a_max = negLogLikelihood->GetX(threshold, a_value, 0.1);

    if (std::isnan(a_min) || std::isnan(a_max)) {
        cout << "Greška: interval pouzdanosti nije pravilno izračunat." << endl;
    } else {
        cout << "Interval pouzdanosti [a-, a+]: [" << a_min << ", " << a_max << "]" << endl;
    }

    TCanvas *canvas2 = new TCanvas("canvas2", "Fit and Histogram", 600, 400);
    histogram->Draw("E");
    fitFunction->Draw("SAME");
    canvas2->SaveAs("FitAndHistogram.pdf");

    delete inputFile;
    delete fitFunction;
    delete negLogLikelihood;
    delete canvas1;
    delete canvas2;
}


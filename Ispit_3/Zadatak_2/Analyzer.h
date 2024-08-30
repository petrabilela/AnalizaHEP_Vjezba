#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TLegend.h>
#include <TF1.h>
#include <TFitResult.h>

#include <iostream>

using namespace std;

class Analyzer {
public:
    Analyzer();
    ~Analyzer();

    void QuadraticFit();
};

#endif


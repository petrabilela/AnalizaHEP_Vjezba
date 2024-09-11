#ifndef ANALYZER_H
#define ANALYZER_H

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <iostream>


using namespace std;

class Analyzer {
public:
    Analyzer();
    virtual ~Analyzer();
    void GeneratePseudoExperiments();
    void PlotChiSquareDistribution();
    double CalculateChiSquareMin(const char* filename);

private:
    TRandom3* randGen;
    TH1F* chiSquareDist;
    TF1* fitFunc;
    int nPseudoExperiments;
};

#endif


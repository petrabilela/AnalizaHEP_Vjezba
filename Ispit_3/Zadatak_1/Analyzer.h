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

#include <iostream>
#include <vector>

using namespace std;

class Analyzer {
public:
    Analyzer(const char* filename);
    virtual ~Analyzer();
    void GeneratePseudoExperiments();
    void TestHypotheses();
    void PlotResults();

private:
    TTree* tree;
    TH1F* hist_H0;
    TH1F* hist_H1;
    double x;
    TRandom3 randGen;
    int numMeasurements;
    int numExperiments;
    double alpha_0;
    double alpha_1;

    void InitializeHistograms();
    double CalculatePValue(double observedMedian);
    double CalculateConfidenceLevel(double observedMedian);
    double ComputeObservedMedian();
};

#endif


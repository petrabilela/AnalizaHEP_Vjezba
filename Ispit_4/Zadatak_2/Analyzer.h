#ifndef ANALYZER_H
#define ANALYZER_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLegend.h>
#include <iostream>
#include <vector>

using namespace std;

class Analyzer {
public:
    Analyzer(const char* filename);  
    ~Analyzer();  
    void GeneratePseudoExperiments();  
    void DrawResults();  
    void CalculatePValue();  

private:
    TFile* inputFile;
    TH1F* histogram;
    TH1F* h_H0;
    TH1F* h_H1;
    int N;  
    double p_H0;  
    double p_H1;  
    int numExperiments;  
    int numMeasurements;  
    TRandom3 randGen;

    void Initialize();  
    void FillHistograms();  
    double BinomialFunction(int n, double p, int k);  
    double GetObservedProbability();  
};

#endif


#include "PDFGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

PDFGenerator::PDFGenerator() {}

void PDFGenerator::GenerateHistogram() {
    srand(static_cast<unsigned>(time(nullptr)));
    generatedCount = 0;
    plotCanvas = new TCanvas();
    histogram = new TH1F("GeneratedHistogram", "GeneratedHistogram", 48, -3., 9.);

    while (generatedCount < 1E5) {
        randomVal = -3 + 12 * static_cast<float>(rand()) / RAND_MAX;
        functionVal = (-randomVal * randomVal + 6 * randomVal + 27) / 36;
        randomVal2 = static_cast<float>(rand())/RAND_MAX;; 

        if (randomVal2 < functionVal) {
            histogram->Fill(randomVal);
            generatedCount++;
        }
    }

    
    gPad->SetLeftMargin(0.12);                   
    gPad->SetBottomMargin(0.12);                  
    plotCanvas->SetCanvasSize(800, 600);          
    plotCanvas->SetTitle("Generated Histogram");  

    histogram->Draw("HIST");                       
    histogram->GetXaxis()->SetTitle(" ");
    histogram->GetYaxis()->SetTitle(" ");
    histogram->GetXaxis()->SetLabelSize(0.035);    
    histogram->GetYaxis()->SetLabelSize(0.035);    
    histogram->SetFillColor(kBlue);               
    histogram->SetLineColor(kRed);                


    plotCanvas->Print("generated_histogram.pdf");  
    plotCanvas->Print("generated_histogram.png");  
    plotCanvas->Print("generated_histogram.root"); 

}

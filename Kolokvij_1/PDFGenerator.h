#ifndef PDF_GENERATOR_H
#define PDF_GENERATOR_H

#include <TH1F.h>
#include <TCanvas.h>

class PDFGenerator {
public:
    PDFGenerator();
    void GenerateHistogram();

private:
    int generatedCount;
    TH1F *histogram;
    float randomVal, functionVal, randomVal2;
    TCanvas *plotCanvas;
};

#endif // PDF_GENERATOR_H

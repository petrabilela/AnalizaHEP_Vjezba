#include "PDFGenerator.h"

int main() {
    PDFGenerator* pdfGenerator = new PDFGenerator();
    pdfGenerator->GenerateHistogram();
    delete pdfGenerator;
    return 0;
}

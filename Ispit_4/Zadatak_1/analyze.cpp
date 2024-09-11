#include "Analyzer.h"

int main() {
    Analyzer analyzer;
    
    analyzer.GeneratePseudoExperiments();
    analyzer.PlotChiSquareDistribution();

    const char* filename = "/home/public/data/GoodnessOfFit.root";
    double chiSquareMin = analyzer.CalculateChiSquareMin(filename);
    cout << "Chi-square minimum for the histogram in the file: " << chiSquareMin << endl;

    return 0;
}


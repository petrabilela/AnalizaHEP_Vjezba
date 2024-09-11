#include "Analyzer.h"

int main() {
    const char* filename = "/home/public/data/BinomialHisto.root";  
    Analyzer analyzer(filename);  

    analyzer.GeneratePseudoExperiments();  
    analyzer.DrawResults();  
    analyzer.CalculatePValue();  

    return 0;  
}


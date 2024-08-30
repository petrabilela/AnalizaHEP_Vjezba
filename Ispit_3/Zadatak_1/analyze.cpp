#include "Analyzer.h"

int main() {
    const char* filename = "/home/public/data/HypothesisTestMedian.root";
    Analyzer analyzer(filename);
    analyzer.TestHypotheses();

    return 0;
}


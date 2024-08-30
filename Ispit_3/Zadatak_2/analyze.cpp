#include "Analyzer.h"

int main() {
    Analyzer *analyzer = new Analyzer();
    analyzer->QuadraticFit();
    delete analyzer;
    return 0;
}


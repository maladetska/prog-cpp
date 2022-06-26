#include "polynomial.h"

#include <iostream>
#include <vector>

int main() {
    PolynomialElement el11(1, 1), el12(2, 2), el13(-3, 4);
    std::vector<PolynomialElement> elements1 = {el11, el12, el13};
    Polynomial pol1(elements1);

    PolynomialElement el21(5, 1), el22(-2, 2), el23(1, 3);
    std::vector<PolynomialElement> elements2 = {el21, el22, el23};
    Polynomial pol2(elements2);

    std::cout << pol1;
    std::cout << pol2;

    std::cout << "pol1 == pol2 ?\t" << (pol1 == pol2) << std::endl;
    std::cout << "pol2 == pol2 ?\t" << (pol2 == pol2) << std::endl;
    std::cout << "pol2 != pol2 ?\t" << (pol2 != pol2) << std::endl;


    pol1 *= pol2;
    std::cout << std::endl;
    std::cout << "pol1 * pol2:\t" << pol1 << std::endl;

    std::cout << pol2;
    std::cout << "pol2 / 2:\t" << pol2 / 2;
    std::cout << "pol2 * 4:\t" << pol2 * 4;
}

#include "EllipticCurve.h"
#include <iostream>

int main() {
    long long a, b, p, timeToCalculate;

    std::cout << "Enter a: ";
    std::cin >> a;
    std::cout << "Enter b: ";
    std::cin >> b;
    std::cout << "Enter p: ";
    std::cin >> p;
    std::cout << "Enter time in seconds: ";
    std::cin >> timeToCalculate;
    std::cout << std::endl;

    EllipticCurve ec(a, b, p);
    long long timePassed = 0;
    long long iter = 1;

    while (timePassed < timeToCalculate) {
        std::cout << "Iteration " << iter << std::endl;
        ec.setP(ec.getNextPrimeNumber(ec.getP() + iter * 3000));
        timePassed = ec.step();
        iter++;
    }

    std::cout << "Resulting elliptic curve: " << ec.toString() << std::endl;
    return 0;
}
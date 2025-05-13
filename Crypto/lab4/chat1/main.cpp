#include <iostream>
#include "EllipticCurve.h"

int main() {
    long a, b, p, timeToCalculate;

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

    long timePassed = 0
    long iter = 1;

    while (timePassed < timeToCalculate) {
        std::cout << "Iteration " << iter << std::endl;
        ec.setP(ec.getNextPrimeNumber(ec.getP() + iter * 3000));
        timePassed = ec.step();
        iter++;
    }

    std::cout << "Resulting elliptic curve: y^2 = x^3 + " << a % ec.getP() << "*x + " << b % ec.getP() << " mod " << ec.getP() << std::endl;
    return 0;
}
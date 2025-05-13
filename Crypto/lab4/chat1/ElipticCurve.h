#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include "Point.h"

class EllipticCurve {
private:
    long A, B, p;
    long ap, bp;
    std::mt19937 gen;

public:
    EllipticCurve(long A, long B, long P) : A(A), B(B), p(P), gen(2904) {
        ap = A % p;
        bp = B % p;
    }

    void setP(long newP) {
        p = newP;
        ap = A % p;
        bp = B % p;
    }

    long getP() const {
        return p;
    }

    bool isEllipticCurve(long x, long y) const {
        return ((y * y) % p) == ((x * x * x + ap * x + bp) % p);
    }

    long inverseOf(long n) const {
        long t = 0, newt = 1;
        long r = p, newr = n;

        while (newr != 0) {
            long quotient = r / newr;
            std::swap(t, newt -= quotient * t);
            std::swap(r, newr -= quotient * r);
        }

        if (r > 1) return -1;
        if (t < 0) t += p;
        return t;
    }

    Point addPoints(const Point& p1, const Point& p2) const {
    if (p1 == Point(0, 0)) return p2;
    if (p2 == Point(0, 0)) return p1;
    if (p1.x == p2.x && (p1.y + p2.y) % p == 0) return Point(0, 0);

    long s;
    if (p1 == p2) {
        long denom = inverseOf(2 * p1.y % p);
        if (denom == -1) return Point(0, 0);
        s = (3 * p1.x % p * p1.x % p + ap) % p;
        s = (s * denom) % p;
    } else {
        long denom = inverseOf((p2.x - p1.x + p) % p);
        if (denom == -1) return Point(0, 0);
        s = ((p2.y - p1.y + p) % p * denom) % p;
    }

    long xr = (s * s - p1.x - p2.x + 3 * p) % p;
    long yr = (s * (p1.x - xr + p) % p - p1.y + p) % p;

    return Point(xr, yr);
    }

    long orderPoint(const Point& point) const {
    Point acc = point;
    long i = 1;

    while (!(acc == Point(0, 0))) {
        acc = addPoints(acc, point);
        ++i;
        
        if (i % 10000 == 0) {
            std::cout << "    Iteration " << i << " in orderPoint" << std::endl;
        }

        // safety to avoid infinite loop
        if (i > p + 1) return -1;
    }
    return i;
    }


    long step() {
        std::cout << "y^2 = x^3 + " << ap << "*x + " << bp << " mod " << p << std::endl;

        std::vector<Point> points;
        auto start = std::chrono::high_resolution_clock::now();

        for (long x = 0; x < p; ++x) {
            for (long y = 0; y < p; ++y) {
                if (isEllipticCurve(x, y)) {
                    points.emplace_back(x, y);
                }
            }
        }

        std::cout << "Curve order: " << points.size() << std::endl;

        std::uniform_int_distribution<> distrib(0, points.size() - 1);
        Point randomPoint = points[distrib(gen)];
        std::cout << "Point (" << randomPoint.x << ", " << randomPoint.y << ") order: " << orderPoint(randomPoint) << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        std::cout << "Elapsed time: " << elapsed << " seconds\n" << std::endl;

        return elapsed;
    }

    long getNextPrimeNumber(long start) const {
        while (!isPrimeNumber(start)) ++start;
        return start;
    }

private:
    bool isPrimeNumber(long number) const {
        if (number < 2) return false;
        for (long i = 2; i * i <= number; ++i) {
            if (number % i == 0) return false;
        }
        return true;
    }
};

#endif
#pragma once
#include "Point.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <tuple>

class EllipticCurve {
private:
    long long A, B, p;
    long long ap, bp;

    std::mt19937_64 rng;

    bool isPrimeNumber(long long number) {
        if (number < 2) return false;
        for (long long i = 2; i * i <= number; ++i) {
            if (number % i == 0) return false;
        }
        return true;
    }

    long long mod(long long a) {
        return (a % p + p) % p;
    }

    std::tuple<long long, long long, long long> extendedEuclideanAlgorithm(long long a, long long b) {
        long long s = 0, t = 1, r = b;
        long long oldS = 1, oldT = 0, oldR = a;

        while (r != 0) {
            long long quotient = oldR / r;
            std::tie(oldR, r) = std::make_pair(r, oldR - quotient * r);
            std::tie(oldS, s) = std::make_pair(s, oldS - quotient * s);
            std::tie(oldT, t) = std::make_pair(t, oldT - quotient * t);
        }

        return {oldR, oldS, oldT};
    }

    long long inverseOf(long long n) {
        auto [gcd, x, y] = extendedEuclideanAlgorithm(n, p);
        if (gcd != 1) return -1;
        return mod(x);
    }

    Point addPoints(const Point& p1, const Point& p2) {
        if (p1 == Point(0, 0)) return p2;
        if (p2 == Point(0, 0)) return p1;
        if (p1.x == p2.x && p1.y != p2.y) return Point(0, 0);

        long long s;
        if (p1 == p2) {
            s = mod((3 * p1.x * p1.x + ap) * inverseOf(2 * p1.y));
        } else {
            s = mod((p1.y - p2.y) * inverseOf(p1.x - p2.x));
        }

        long long x3 = mod(s * s - p1.x - p2.x);
        long long y3 = mod(-1 * (p1.y + s * (x3 - p1.x)));
        return Point(x3, y3);
    }

    long long orderPoint(Point point) {
        long long i = 2;
        Point current = addPoints(point, point);
        while (!(current == Point(0, 0))) {
            current = addPoints(current, point);
            i++;
        }
        return i;
    }

public:
    EllipticCurve(long long A, long long B, long long P) : A(A), B(B), p(P), rng(2904) {
        ap = mod(A);
        bp = mod(B);
    }

    void setP(long long new_p) {
        p = new_p;
        ap = mod(A);
        bp = mod(B);
    }

    long long getP() const {
        return p;
    }

    bool isEllipticCurve(long long x, long long y) {
        return mod(y * y) == mod(x * x * x + ap * x + bp);
    }

    long long step() {
        std::cout << "y^2 = x^3 + " << ap << "*x + " << bp << " % " << p << std::endl;

        std::vector<Point> points;
        auto start = std::chrono::steady_clock::now();

        for (long long x = 0; x < p; ++x) {
            for (long long y = 0; y < p; ++y) {
                if (isEllipticCurve(x, y)) {
                    points.emplace_back(x, y);
                }
            }
        }

        std::cout << "Curve order: " << points.size() << std::endl;

        std::uniform_int_distribution<size_t> dist(0, points.size() - 1);
        Point randomPoint = points[dist(rng)];
        std::cout << "Point " << randomPoint.to_string() << " order: " << orderPoint(randomPoint) << std::endl;

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        std::cout << "Elapsed time: " << elapsed << " seconds" << std::endl << std::endl;

        return elapsed;
    }

    long long getNextPrimeNumber(long long start) {
        while (!isPrimeNumber(start)) ++start;
        return start;
    }

    std::string toString() const {
        return "y^2 = x^3 + " + std::to_string(ap) + "*x + " + std::to_string(bp) + " % " + std::to_string(p);
    }
};
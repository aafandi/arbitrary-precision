#include "randomrationals.h"
#include <random>

std::vector<Rational> random_rationals(int size, int num_bound, int den_bound) {

    // Returns a vector of 'size' many randomly generated rational numbers,
    // whose numerator is bounded by num_bound, and denominator is bounded
    // by den_bound.

    std::random_device rd;
    std::mt19937 g(rd());

    srand(time(NULL));

    std::vector<Rational> randoms {};

    int *num {nullptr};
    num = new int;

    int *den {nullptr};
    den = new int;

    Rational *rat {nullptr};
    rat = new Rational;

    for (int i = 0; i < size; i++) {
        *num = rand() % num_bound + 1;
        *den = rand() % den_bound + 1;
        *rat = Rational(LargeInteger(std::to_string(*num)), LargeInteger(std::to_string(*den))).simplify();
        while (std::count(randoms.begin(), randoms.end(), *rat) == 1 || *num >= *den) {
            *num = rand() % num_bound;
            *den = rand() % den_bound;
            *rat = Rational(LargeInteger(std::to_string(*num)), LargeInteger(std::to_string(*den))).simplify();
        }
        randoms.push_back(*rat);
    }

    delete num;
    delete den;
    delete rat;

    return randoms;
}
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "largeinteger.h"
#include "rational.h"
#include "randomrationals.h"

int main() {
// USE THIS MAIN.CPP TO TEST RUN THE LIBRARY

std::vector<Rational> *v {nullptr};
v = new std::vector<Rational>;
*v = random_rationals(50, 20, 20);

for (auto r: *v) {
    std::cout << r.get_string_representation() << std::endl;
}

delete v;

return 0;
}
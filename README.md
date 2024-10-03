# arbitrary precision

<precision> is A C++ library for arbitrary precision arithmetic.

The main class comprising the functionality is the LargeInteger class,
a class that can hold an integer with an arbitrary number of digits
(or rather, as many digits as the longest string that your machine can hold).

The key features/abilities of this library are:

1. All basic arithmetic operations (+, -, \*, /) on arbitrarily large integers,
   with arbitrary precision.

2. Testing whether a large integer is prime or composite (using Miller-Rabin).

3. Randomly generate large primes up to 1048 bits (i.e primes ~ 2^(1048)).

In addition to the LargeInteger class, one can also do arbitrary precision
arithmetic with rational numbers using the Rational class.

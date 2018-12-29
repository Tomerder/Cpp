#pragma once

#include <vector>

typedef std::vector<unsigned> primes_vector;

void find_primes(unsigned start, unsigned end, primes_vector& primes, unsigned parallelism);


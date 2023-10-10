#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


std::vector<long> sieve(long n) {
    std::vector<bool> arr((unsigned long)(n+1), true);

    for (long i = 2; i <= (long)std::ceil(std::sqrt(n)); ++i) {
        if (arr[i]) {
            for (long j = i*i; j <= n; j += i) {
                arr[j] = false;
            }
        }
    }

    std::vector<long> result;
    for (long k = 2; k <= n; ++k) {
        if (arr[k]) {
            result.emplace_back(k);
        }
    }
    return result;
}


[[noreturn]] void fail(const std::string& message, char* arg)
{
    std::cerr << message << ": '" << arg << "'" << std::endl;
    std::exit(EXIT_FAILURE);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " n" << std::endl;
        return EXIT_FAILURE; 
    }

    long n;
    try {
        n = std::stol(argv[1]);
    }
    catch (std::invalid_argument const& ex) {
        fail("invalid integer value", argv[1]);
    }
    catch (std::out_of_range const& ex) {
        fail("integer value out of range", argv[1]);
    }

    if (n < 2) {
        fail("argument must not be less than two", argv[1]);
    }

    // const auto start{std::chrono::steady_clock::now()};
    std::vector<long> primes = sieve(n);
    // const auto end{std::chrono::steady_clock::now()};

    std::cout << primes[primes.size() - 1] << "\n";

    // const std::chrono::duration<double> elapsed{end - start};
    // std::cout << "calculating took "
    //           << std::fixed << std::setprecision(2) << elapsed.count()
    //           << " seconds" << std::endl;

    return EXIT_SUCCESS;
}

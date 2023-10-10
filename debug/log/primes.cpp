#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace trivial = boost::log::trivial;

src::severity_logger<trivial::severity_level> LOG;


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
    for (long k = 2; k < n; ++k) {
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


void init_logging()
{
    logging::add_common_attributes();

    logging::add_file_log
    (
        keywords::file_name = "primes.log",
        keywords::format = "%TimeStamp% [%Severity%] %Message%"
    );

    logging::core::get()->set_filter
    (
        trivial::severity >= trivial::info
    );
}

int main(int argc, char* argv[]) {
    init_logging();

    BOOST_LOG_SEV(LOG, trivial::severity_level::info) << "an info message";

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

    for (long p : sieve(n)) {
        std::cout << p << "\n";
    }

    return EXIT_SUCCESS;
}

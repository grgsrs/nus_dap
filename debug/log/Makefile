BOOST_LIBS = -DBOOST_LOG_DYN_LINK -lboost_log_setup -lboost_log
BOOST_LIBS += -lboost_system -lboost_thread -lboost_filesystem

primes: primes.cpp
	$(CXX) -std=c++17 $< -o $@ $(BOOST_LIBS) 

#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include <chrono>
#include <boost/unordered_map.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;
// Setup cpp_int limits
cpp_int limit = (cpp_int(1) << 128) - 1;
// Setup clock
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;


/* Fibonacci functions */

// 1. Fibonacci (recursive)
cpp_int fibonacci(cpp_int n);
// 2. Fibonacci (non-recursive)
cpp_int looped_fibonacci(cpp_int n);
// 3. Fibonacci (cached)
cpp_int cached_fibonacci(cpp_int n);
// 4. Fibonacci (matrixed)
cpp_int matrixed_fibonacci(cpp_int n);

/* Helpers */

void start_fibonacci(cpp_int n, int flag, bool timed, bool silent);
void start_looped_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat);
void start_cached_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat);
void start_matrixed_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat);

// Prints the elapsed time of the running function
void print_time(std::string method, time_point<Clock> start, time_point<Clock> end);
void print_time(std::string method, time_point<Clock> start, time_point<Clock> end, int divisor);
// Parses argv and returns a tuple containing the parsed flags
std::tuple<unsigned long long, int, bool, bool, bool> parse_args(int argc, char * argv[]);
// Parses the flags from argv
int parse_flag(char * argv);
// Raises the power of a matrix by n
void power(cpp_int A[2][2], cpp_int n);
// Performs matrix multiplication
void multiply(cpp_int A[2][2], cpp_int B[2][2]);


int main(int argc, char * argv[]) {
  if (argc == 1) {
    std::cout << "usage: " << "./hw2-fibonacci <number> [-c cached | -l looped | -m matrixed] [-t timed] [-s silent]" << std::endl;
  }
  if (argc >= 2) {
    cpp_int n = 0;
    int flag = 0;
    bool timed = false, silent = false, repeat = false;
    std::tie(n, flag, timed, silent, repeat) = parse_args(argc, argv);
    if (n == 0) {
      std::cout << 0 << std::endl;
      return 0;
    }
    switch(flag) {
      case 1: start_cached_fibonacci(n, flag, timed, silent, repeat); break;
      case 2: start_looped_fibonacci(n, flag, timed, silent, repeat); break;
      case 3: start_matrixed_fibonacci(n, flag, timed, silent, repeat); break;
      case 4: {
        start_fibonacci(n, flag, timed, silent);
        start_looped_fibonacci(n, flag, timed, silent, repeat);
        start_cached_fibonacci(n, flag, timed, silent, repeat);
        start_matrixed_fibonacci(n, flag, timed, silent, repeat);
        break;
      }
      default: start_fibonacci(n, flag, timed, silent); break;
    }
  }
  return 0;
}

void start_fibonacci(cpp_int n, int flag, bool timed, bool silent) {
  auto start = Clock::now();
  auto result = fibonacci(n);
  auto end = Clock::now();
  auto method = "Fibonacci (recursive)";
  if (timed) print_time(method, start, end);
  if (!silent) std::cout << method << ":" << std::endl << result << std::endl;
}
void start_looped_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat) {
  cpp_int result = 0; int count = 1;
  auto start = Clock::now();
  if(!repeat) looped_fibonacci(n);
  else while(count++ < 100000001) looped_fibonacci(n);
  auto end = Clock::now();
  auto method = "Fibonacci (non-recursive)";
  if (timed) print_time(method, start, end, count);
  if (!silent) std::cout << method << ":" << std::endl << result << std::endl;
}
void start_cached_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat) {
  cpp_int result = 0; int count = 1;
  auto start = Clock::now();
  if(!repeat) cached_fibonacci(n);
  else while(count++ < 100000001) cached_fibonacci(n);
  auto end = Clock::now();
  auto method = "Fibonacci (cached)";
  if (timed) print_time(method, start, end, count);
  if (!silent) std::cout << method << ":" << std::endl << result << std::endl;
}
void start_matrixed_fibonacci(cpp_int n, int flag, bool timed, bool silent, bool repeat) {
  cpp_int result = 0; int count = 1;
  auto start = Clock::now();
  if(!repeat) matrixed_fibonacci(n);
  else while(count++ < 100000001) matrixed_fibonacci(n);
  auto end = Clock::now();
  auto method = "Fibonacci (matrixed)";
  if (timed) print_time(method, start, end, count);
  if (!silent) std::cout << method << ":" << std::endl << result << std::endl;
}

void print_time(std::string method, time_point<Clock> start, time_point<Clock> end) {
  milliseconds difference = duration_cast<milliseconds>(end - start);
  std::cout << method << " time: " << difference.count() << "ms" << std::endl;
}

void print_time(std::string method, time_point<Clock> start, time_point<Clock> end, int divisor) {
  milliseconds difference = duration_cast<milliseconds>(end - start);
  std::cout << method << " time: " << (difference.count() / (double) divisor) << "ms" << std::endl;
}

std::tuple<unsigned long long, int, bool, bool, bool> parse_args(int argc, char * argv[]) {
  unsigned long long n = 0, flag = 0;
  bool timed = false, silent = false, repeat = false;
  std::string::size_type sz = 0;
  for (int i = 1; i < argc; i++) {
    int f = parse_flag(argv[i]);
    auto v = strtoull(argv[i], NULL, 0);
    if (f >= 1 && f <= 4) flag = f;
    if (v != 0) n = v;
    if (f == 50) timed = true;
    if (f == 51) silent = true;
    if (f == 52) repeat = true;
  }
  return std::make_tuple(n, flag, timed, silent, repeat);
}

int parse_flag(char * argv) {
  std::string str(argv);
  std::map<std::string, int> options {
    {"-c", 1}, {"--cached", 1},
    {"-l", 2}, {"--looped", 2},
    {"-m", 3}, {"--matrixed", 3},
    {"-a", 4}, {"--all", 4},
    {"-t", 50}, {"--time", 50},
    {"-s", 51}, {"--silent", 51},
    {"-r", 52}, {"--repeat", 52}
  };
  auto it = options.find(str);
  if (it != options.end()) return it->second;
  return 0;
}


cpp_int fibonacci(cpp_int n) {
  if (n <= 2) return 1;
  else return fibonacci(n - 1) + fibonacci(n - 2);
}

cpp_int looped_fibonacci(cpp_int n) {
  if (n <= 2) return 1;
  cpp_int f1 = 0, f2 = 1, f = 0;
  for (int i = 2; i <= n; i++) {
    f = f1 + f2;
    f1 = f2;
    f2 = f;
  }
  return f;
}


cpp_int cached_fibonacci(cpp_int n) {
  static boost::unordered_map<cpp_int, cpp_int> cache { { 0, 0 }, { 1, 1 } };
  auto found = cache.find(n);
  if (found != cache.end()) return cache.at(n);
  cpp_int result = cached_fibonacci(n - 1) + cached_fibonacci(n - 2);
  cache[n] = result;
  return result;
}

cpp_int matrixed_fibonacci(cpp_int n) {
  cpp_int F[2][2] = { 
    {1,1}, 
    {1,0} 
  };
  if (n == 0) return 1;
  power(F, n - 1);
  return F[0][0];
}

void power(cpp_int A[2][2], cpp_int n) {
  if (n < 2) return;
  cpp_int B[2][2] = {
    {1, 1},
    {1, 0}
  };
  power(A, n / 2);
  multiply(A, A);
  if (n % 2 != 0) multiply(A, B);
}

void multiply(cpp_int A[2][2], cpp_int B[2][2]) {
  cpp_int a =  A[0][0] * B[0][0] + A[0][1] * B[1][0];
  cpp_int b =  A[0][0] * B[0][1] + A[0][1] * B[1][1];
  cpp_int c =  A[1][0] * B[0][0] + A[1][1] * B[1][0];
  cpp_int d =  A[1][0] * B[0][1] + A[1][1] * B[1][1];
  A[0][0] = a;
  A[0][1] = b;
  A[1][0] = c;
  A[1][1] = d;
}
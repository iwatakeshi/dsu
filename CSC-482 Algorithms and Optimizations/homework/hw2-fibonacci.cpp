#include <iostream>
#include <map>
#include <stdlib.h>
#include <tuple>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;
cpp_int limit = (cpp_int(1) << 128) - 1;

// #include <math.h>
void power(cpp_int A[2][2], cpp_int n);
void multiply(cpp_int A[2][2], cpp_int B[2][2]);

// 1. Fibonacci (recursive)
cpp_int fibonacci(cpp_int n);
// 2. Fibonacci (non-recursive)
cpp_int looped_fibonacci(cpp_int n);
// 3. Fibonacci (memoized)
cpp_int cached_fibonacci(cpp_int n);
// 4. Fibonacci (matrixed)
cpp_int matrixed_fibonacci(cpp_int n);

std::tuple<unsigned long long, int> parse_args(int argc, char * argv[]);
int parse_flag(char * argv);

int main(int argc, char * argv[]) {
  if (argc >= 2) {
    cpp_int n = 0;
    int flag = 0;
    std::tie(n, flag) = parse_args(argc, argv);
    switch(flag) {
      case 1: std::cout << cached_fibonacci(n) << std::endl; break;
      case 2: std::cout << looped_fibonacci(n) << std::endl; break;
      case 3: std::cout << matrixed_fibonacci(n) << std::endl; break;
      case 4: {
        std::cout << "Fibonacci (recursive) " << fibonacci(n) << std::endl;
        std::cout << "Fibonacci (non-recursive) " << looped_fibonacci(n) << std::endl;
        std::cout << "Fibonacci (memoized) " << cached_fibonacci(n) << std::endl;
        std::cout << "Fibonacci (matrixed) "<< matrixed_fibonacci(n) << std::endl;
        break;
      }
      default: std::cout << fibonacci(n) << std::endl; break;
    }
  }
  return 0;
}

std::tuple<unsigned long long, int> parse_args(int argc, char * argv[]) {
  unsigned long long n = 0, flag = 0;
  std::string::size_type sz = 0;
  for (int i = 1; i < argc; i++) {
    int f = parse_flag(argv[i]);
    auto v = strtoull(argv[i], NULL, 0);
    if (f != 0) flag = f;
    if (v != 0) n = v;
  }
  return std::make_tuple(n, flag);
}

int parse_flag(char * argv) {
  std::string str(argv);
  std::map<std::string, int> options {
    {"-c", 1}, {"--cached", 1},
    {"-l", 2}, {"--looped", 2},
    {"-m", 3}, {"--matrixed", 3},
    {"-a", 4}, {"--all", 4}
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
  std::cout << "n: " << n << std::endl;
  if (n <= 2) return 1;
  cpp_int f1 = 0, f2 = 1, f = 0;
  for (int i = 2; i <= n; i++) {
    f = f1 + f2;
    f1 = f2;
    f2 = f;
  }
  return f;
}

std::map<cpp_int, cpp_int> cache;
cpp_int cached_fibonacci(cpp_int n) {
  if (n <= 2) return 1;
  auto it = cache.find(n);
  if (it != cache.end()) return it->second;
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
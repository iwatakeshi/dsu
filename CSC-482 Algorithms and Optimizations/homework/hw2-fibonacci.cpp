#include <iostream>
#include <map>
#include <stdlib.h>
#include <tuple>
// #include <math.h>
void power(long long A[2][2], int n);
void multiply(long long A[2][2], long long B[2][2]);

// 1. Fibonacci (recursive)
long long fibonacci(long long n);
// 2. Fibonacci (non-recursive)
long long looped_fibonacci(int n);
// 3. Fibonacci (memoized)
long long cached_fibonacci(long long n);
// 4. Fibonacci (matrixed)
long long matrixed_fibonacci(int n);

std::tuple<int, int> parse_args(int argc, char * argv[]);
int parse_flag(char * argv);

int main(int argc, char * argv[]) {
  if (argc >= 2) {
    int n = 0, flag = 0;
    std::tie(n, flag) = parse_args(argc, argv);
    switch(flag) {
      case 1: std::cout << cached_fibonacci((long long) n) << std::endl; break;
      case 2: std::cout << looped_fibonacci(n) << std::endl; break;
      case 3: std::cout << matrixed_fibonacci(n) << std::endl; break;
      case 4: {
        std::cout << "Fibonacci (recursive) " << fibonacci((long long) n) << std::endl;
        std::cout << "Fibonacci (non-recursive) " << looped_fibonacci(n) << std::endl;
        std::cout << "Fibonacci (memoized) " << cached_fibonacci((long long) n) << std::endl;
        std::cout << "Fibonacci (matrixed) "<< matrixed_fibonacci(n) << std::endl;
        break;
      }
      default: std::cout << fibonacci((long long) n) << std::endl; break;
    }
  }
  return 0;
}

std::tuple<int, int> parse_args(int argc, char * argv[]) {
  int n = 0, flag = 0;
  for (int i = 1; i < argc; i++) {
    int f = parse_flag(argv[i]);
    int v = atoi(argv[i]);
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


long long fibonacci(long long n) {
  if (n <= 2) return 1;
  else return fibonacci(n - 1) + fibonacci(n - 2);
}

long long looped_fibonacci(int n) {
  if (n <= 2) return 1;
  long long f1 = 0, f2 = 1, f = 0;
  for (int i = 2; i <= n; i++) {
    f = f1 + f2;
    f1 = f2;
    f2 = f;
  }
  return f;
}

std::map<long long, long long> cache;
long long cached_fibonacci(long long n) {
  if (n <= 2) return 1;
  auto it = cache.find(n);
  if (it != cache.end()) return it->second;
  int result = cached_fibonacci(n - 1) + cached_fibonacci(n - 2);
  cache[n] = result;
  return result;
}

long long matrixed_fibonacci(int n) {
  long long F[2][2] = { 
    {1,1}, 
    {1,0} 
  };
  if (n == 0) return 1;
  power(F, n - 1);
  return F[0][0];
}

void power(long long A[2][2], int n) {
  if (n < 2) return;
  long long B[2][2] = {
    {1, 1},
    {1, 0}
  };
  power(A, n / 2);
  multiply(A, A);
  if (n % 2 != 0) multiply(A, B);
}

void multiply(long long A[2][2], long long B[2][2]) {
  long long a =  A[0][0] * B[0][0] + A[0][1] * B[1][0];
  long long b =  A[0][0] * B[0][1] + A[0][1] * B[1][1];
  long long c =  A[1][0] * B[0][0] + A[1][1] * B[1][0];
  long long d =  A[1][0] * B[0][1] + A[1][1] * B[1][1];
  A[0][0] = a;
  A[0][1] = b;
  A[1][0] = c;
  A[1][1] = d;
}
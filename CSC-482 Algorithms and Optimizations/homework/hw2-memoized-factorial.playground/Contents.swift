//: Playground - noun: a place where people can play

import Cocoa

typealias RecursiveFunction = (Int) -> Int;

func memoize(_ body: @escaping RecursiveFunction) -> RecursiveFunction {
  var cache: [Int: Int] = [:];
  func memoized(_ n: Int) -> Int {
    if let result = cache[n] {
      return result
    } else {
      let result = body(n);
      cache[n] = result
      return result
    }
  }
  return memoized
}


var factorial: RecursiveFunction = { return $0; };
factorial = memoize({ return $0 == 0 ? 1: factorial($0 - 1)});
print(factorial(2))

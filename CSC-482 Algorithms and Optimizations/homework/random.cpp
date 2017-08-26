#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;


bool isOk(long int min, long int max) {
  if (min > -max && min < max) return true;
  return false;
}

/*
  X_n = seed
  a = multiplier
  c = incrementer
  m = modulus
  credits: https://www.youtube.com/watch?v=4sYawx70iP4
*/
long int random(long int seed, long int max) {
  int a = 34, c = 24823, m = max;
  return (a * seed + c) % m;
}

int test(long int seed, int rows, long int max) {
  cout << "Testing with seed " << seed << " for " << rows << " times..." << endl;
  long int s = seed;
  bool* results = new bool[rows];
  int count = 0;
  for(int i = 0; i < rows; i++) {
    s = random(s, max);
    if (results[i]) {
      count = i;
      break;
    }
    results[i] = true;
  }
  delete[] results;
  cout << "Test completed. " << endl;
  if (count > 0) {
    cout << count << " was the number of times before it started to repeat." << endl;
  } else {
    cout << "Good seed." << endl;
  }
  return 0;
}

int main (int argc, const char * argv[]) {
    if (argc <= 4 || argc > 5) {
      cout << "usage: ./random <rows> <columns> <min> <max>" << endl;
      cout << "       ./random <rows> <min> <max> [-t --test]" << endl;
      return 0;
    }
    
    auto rows = atoi(argv[1]);
    auto columns = atoi(argv[2]);
    auto min = atoi(argv[3]);
    auto max = atoi(argv[4]);
    bool test_flag = ((strcmp(argv[4], "--test") == 0) || (strcmp(argv[4], "-t") == 0));
    // Check rows
    if (rows < 1) {
      cout << "Invalid number of rows entered." << endl;
      return 0;
    }

    if (columns < 1) {
      if (argc == 5 && test_flag) {
        return test(atoi(argv[2]), atoi(argv[1]), atoi(argv[3]));
      }
      cout << "Invalid number of columns entered." << endl;
      return 0;
    }

    if (max < 10) {
      if (argc == 5 && test_flag) {
        return test(atoi(argv[2]), atoi(argv[1]), atoi(argv[3]));
      }
      cout << "Enter a maximum value greater than or equal to 10." << endl;
      return 0;
    }

    // Check bounds
    if (!isOk(min, max)) {
      cout << "The seed must be between -" << max << " and +" << max << endl;
      return 0;
    }
    string line = "";

    while (rows--) {
      auto col = columns;
      while (col--) {
        min = random(min, max);
        if (!isOk(min, max)) break;
        line += to_string(min);
        if (rows >= 0 && col > 0) line += ", ";
      }
      if (rows > 0) line += ", ";
      line += "\n";
    }

    cout << line << endl;
    return 0;
}
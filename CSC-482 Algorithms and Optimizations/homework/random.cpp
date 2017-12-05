#include <iostream>
#include <random>
using namespace std;

int main (int argc, const char * argv[]) {
    if (argc <= 4 || argc > 5) {
      cout << "usage: ./random <rows> <columns> <min> <max>" << endl;
      return 0;
    }
    
    auto rows = atoi(argv[1]);
    auto columns = atoi(argv[2]);
    auto min = atoi(argv[3]);
    auto max = atoi(argv[4]);
    // Check rows
    if (rows < 1) {
      cout << "Invalid number of rows entered." << endl;
      return 0;
    }

    if (columns < 1) {
      cout << "Invalid number of columns entered." << endl;
      return 0;
    }

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> dist(min, max);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        cout << dist(mt) << " ";
      }
      cout << '\n';
    }
    
    return 0;
}

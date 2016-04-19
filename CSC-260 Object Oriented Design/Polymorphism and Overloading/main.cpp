#include <iostream>
#include <string>

class Mammal {
  protected:
    int _speed = 0;
  public:
    virtual void run() = 0;
    virtual void run(double) = 0;
};

class Tiger: public Mammal {
  public:
    void run () {
      _speed = 1;
      std::cout << "Class: Tiger, Base: Mammal" << std::endl;
      std::cout << "Method: run() "<< std::endl;
      std::cout << "The tiger is running at normal speed." << std::endl;
      std::cout << std::endl;
    }
    void run (double speed) {
      _speed = speed;
      std::cout << "Class: Tiger, Base: Mammal" << std::endl;
      std::cout << "Method: run(double), Input: "<< std::to_string(speed) << std::endl;
      std::string message = "";
      if (speed == 0) message = "The tiger is not running.";
      else if (speed >= 1 && speed <= 4) message = "The tiger is running at normal speed.";
      else message = "The tiger is running at high speed.";
      std::cout << message << std::endl;
      std::cout << std::endl;
    }
};

class Fox: public Mammal {
  public:
    void run () {
      _speed = 1;
      std::cout << "Class: Fox, Base: Mammal" << std::endl;
      std::cout << "Method: run() "<< std::endl;
      std::cout << "The fox is running at normal speed." << std::endl;
      std::cout << std::endl;
    }
    void run (double speed) {
      _speed = speed;
      std::cout << "Class: Fox, Base: Mammal" << std::endl;
      std::cout << "Method: run(double), Input: "<< std::to_string(speed) << std::endl;
      std::string message = "";
      if (speed == 0) message = "The fox is not running.";
      else if (speed >= 1 && speed <= 2) message = "The fox is running at normal speed.";
      else message = "The fox is running at high speed.";
      std::cout << message << std::endl;
      std::cout << std::endl;
    }
};

int main(int argc, char const *argv[]) {
  Mammal * mammals[] = { new Tiger(), new Fox() };
  double inputs[] = { 5, 2 };
  for (size_t i = 0; i < 2; i++) {
    mammals[i]->run();
    mammals[i]->run(inputs[i]);
  }
  return 0;
}

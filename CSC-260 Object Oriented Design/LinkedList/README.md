# LinkedList

## Classes

### Node (`node.h`)

#### Constructors

* `Node()`
* `Node(data: int)`

#### Methods

* `setData(): void`
* `getData(): int`
* `setNext(): void`
* `getNext(): Node*`
* `print(): void`
* `print(int index): void`

### LinkedList (`link.h`)

#### Constructors

* `LinkedList()`

#### Methods

* `insert(data:int, index: int) : void`
* `append(data: int): void`
* `remove(): void`
* `remove(index: int): void`
* `clear() : void`
* `print(): void`
* `isEmpty(): bool`


## Usage

```cpp
#include "link.h"

int main () {
  LinkedList list;
  list.append(2);
  list.append(3);
  list.append(5);
  list.print();
  
  std::cout << std::endl;
  
  list.remove();
  list.print();
  return 0;
}
```

## Build

### OSX

```bash
g++ main.cpp link.cpp -std=gnu++11 -o main.out && ./main.out
```

### Windows

* Open the Visual Studio Project
* Run without debugging (CTRL + F5)
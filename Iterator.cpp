#include <iostream>

using namespace std;

// Класс стека данных
class Stack {
  private:
    int items[10];
    int length;
  
  public:
    friend class StackIterator;
    Stack() {
      length = -1;
    }

    void push(int value) {
      items[++length] = value;
    }

    int pop() {
      return items[length--];
    }
};

// Класс итератора
class StackIterator {
  private:
    const Stack& stack;
    int index;

  public:
    StackIterator(const Stack& stack) : stack(stack) {
      index = 0;
    }

    void operator++() {
      index++;
    }

    int operator*() { 
      return stack.items[index];
    }

    bool operator()() {
      return index != stack.length + 1;
    }
};

// перегрузим оператор сравнения 2 экземпляров класса Stack
bool operator==(const Stack& s1, const Stack& s2) {
  StackIterator it1(s1), it2(s2);

  for (; it1(); ++it1, ++it2) {
    if (*it1 != *it2) break;
  }
  return !it1() && !it2();
}

int main() {
  Stack stack1;

  for (int i = 0; i < 5; ++i) {
    stack1.push(i);
  }

  Stack stack2(stack1);

  cout << boolalpha << (stack1 == stack2) << endl;
  // true

  stack2.push(10);

  cout << boolalpha << (stack1 == stack2) << endl;
  // false
}
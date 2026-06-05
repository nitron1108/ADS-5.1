// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename ElementType, int Capacity>
class TStack {
 public:
  TStack(){
    topIndex = -1;
  }

  bool isVoid() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == Capacity - 1;
  }

  void add(const ElementType& value) {
    if (isFull()) {
      throw std::overflow_error("overflow");
    }
    data[++topIndex] = value;
  }

  ElementType remove() {
    if (isVoid()) {
      throw std::underflow_error("underflow");
    }
    return data[topIndex--];
  }

  ElementType getTop() const {
    if (isVoid()) {
      throw std::underflow_error("empty stack ");
    }
    return data[topIndex];
  }

 private:
  ElementType data[Capacity];
  int topIndex;
};

#endif  

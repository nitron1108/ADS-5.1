// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

static int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::ostringstream result;
  for (size_t i=0; i<inf.length();i++) {
    char ch = inf[i];
    if (std::isdigit(ch)) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        result << inf[i++];
      }
      result << ' ';
      --i;
    } else if (ch == '(') {
      operators.add(ch);
    } else if (ch == ')') {
      while (!operators.isVoid() && operators.getTop() != '(') {
        result << operators.remove() << ' ';
      }
      if (!operators.isVoid()) {
        operators.remove();
      }
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!operators.isVoid() &&
             getPriority(operators.getTop()) >= getPriority(ch)) {
        result << operators.remove() << ' ';
      }
      operators.add(ch);
    }
  }

  while (!operators.isVoid()) {
    result << operators.remove() << ' ';
  }

  std::string res = result.str();
  if (!res.empty() && res.back() == ' ') {
    res.pop_back();
  }
  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> numbers;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      numbers.add(std::stoi(token));
    } else {
      int right = numbers.remove();
      int left = numbers.remove();
      switch (token[0]) {
        case '+': numbers.add(left + right); break;
        case '-': numbers.add(left - right); break;
        case '*': numbers.add(left * right); break;
        case '/': numbers.add(left / right); break;
      }
    }
}
  return numbers.remove();
}

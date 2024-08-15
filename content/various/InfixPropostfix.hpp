#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-01
 * License: CC0
 * Description: Infix to Pro-Postfix
 */

stack<char> opr;
stack<int> val;

bool isOpr(char x){
  return x == '+' || x == '*';
}

int prio(char x) {
  if(x == '(') return -1;
  if(x == '+') return 1;
  if(x == '*') return 2;
  return 0;
}

int do_opr(int l, int r, char o) {
  if(o == '+') {
    return l + r;
  }
  return l * r;
}

void pop_stack() {
  int rhs = val.top(); val.pop();
  int lhs = val.top(); val.pop();
  int new_val = do_opr(lhs, rhs, opr.top());
  val.emplace(new_val);
  opr.pop();
}

int cal(string s) {
  for(auto x: s) {
    if(isdigit(x)) val.emplace(x - '0');
    else if(x == '(') opr.emplace('(');
    else if(x == ')') {
      while(!opr.empty() && opr.top() != '(')
        pop_stack();
      opr.pop();
    }
    else {
      while(!opr.empty() && prio(opr.top()) >= prio(x))
        pop_stack();
      opr.emplace(x);
    }
  }
  while(!opr.empty()) pop_stack();
  return val.top();
}
#pragma once
#include "FastEratosthenes.hpp"

/**
 * Author: Borworntat D.
 * Date: 2023-12-02
 * License: CC0
 * Source: https://www.geeksforgeeks.org/program-for-goldbachs-conjecture-two-primes-with-given-sum/
 * Description: Find two prime numbers which sum equals $s$
 * Time: $O(N\log{N})$
 */

pair<int, int> goldbatchConjecture(int s, vi pr = {}){
  if (s <= 2 || s % 2 != 0) {
    return make_pair(-1, -1);
  }
  if (pr.size() == 0) {
    pr = eratosthenes();
  }
  for (auto x : pr) {
    if (x > s / 2) {
      break;
    }
    int d = s - x;
    if (binary_search(pr.begin(), pr.end(), d)) {
      return make_pair(min(x, d), max(x, d));
    }
  }
  return make_pair(-1, -1);
}


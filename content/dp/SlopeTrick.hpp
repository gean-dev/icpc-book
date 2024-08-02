#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-02
 * Description: Absolute Smth
 */

ll extending_value;

struct slope_trick {
  multiset<ll> ms_l, ms_r;
  ll min_y = 0ll, lz_l = 0ll, lz_r = 0ll;
  bool extending = false;
  void add_line(ll v) {
    if(extending) {
      lz_l -= extending_value;
      lz_r -= extending_value;
    }
    extending = true;
    if(ms_l.empty() && ms_r.empty()) {
      ms_l.emplace(v);
      ms_r.emplace(v);
    }
    else if(v <= *ms_l.rbegin() + lz_l) {
      min_y += (*ms_l.rbegin() + lz_l) - v;
      ms_r.emplace(*ms_l.rbegin() + lz_l - lz_r);
      ms_l.erase(--ms_l.end());
      ms_l.emplace(v - lz_l);
      ms_l.emplace(v - lz_l);
    }
    else if(v >= *ms_r.begin() + lz_r) {
      min_y += v - (*ms_r.begin() + lz_r);
      ms_l.emplace(*ms_r.begin() + lz_r - lz_l);
      ms_r.erase(ms_r.begin());
      ms_r.emplace(v - lz_r);
      ms_r.emplace(v - lz_r);
    }
    else {
      ms_l.emplace(v - lz_l);
      ms_r.emplace(v - lz_r);
    }
  }
};
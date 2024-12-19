#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-12-14
 * Description: geometry using std complex
 */

#include <complex>
using namespace std;

using point = complex<double>;

double dot(const point &a,const point &b){ return real(conj(a)*b); }
double cross(const point &a,const point &b){ return imag(conj(a)*b); }

point rotate_by(const point &p,const point about, double radians){
    return (p-about)*exp(point(0,radians))+about;
}

point project(const point &p,const point &about1,const point &about2){
    point z=p-about1;
    point w=about2-about1;
    return w*dot(z,w)/norm(w)+about1;
}

point reflex(const point &p,const point &about1,const point &about2){
    point z=p-about1;
    point w=about2-about1;
    return conj(z/w)*w+about1;
}

point intersect(const point &a,const point &b,const point &p,const point &q){
    double d1=cross(p-a,b-a);
    double d2=cross(q-a,b-a);
    return (d1*q-d2*p)/(d1-d2); // undefined if they are parallel
}

// find angle abc
point angle(const point &a,const point &b,const point &c){
    return abs(remainder(arg(a-b)-arg(c-b),2.0*M_PI));
}


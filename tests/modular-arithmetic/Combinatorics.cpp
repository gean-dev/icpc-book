#include <bits/stdc++.h>
#include "../../content/modular-arithmetic/Combinatorics.hpp"

using namespace std;

const int N=1000;

mint C[N][N],P[N][N];

int main(int argc,char* argv[]){
    for(int i=1;i<N;i++){
        assert(i*invmod(i)==1);
    }
    mint val=1;
    for(int i=0;i<N;i++){
        assert(fac(i)==val);
        assert(fac(i)*invfac(i)==1);
        val*=i+1;
    }
    for(int i=0;i<N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
        for(int j=0;j<=i;j++){
            assert(nCr(i,j)==C[i][j]);
        }
    }
    for(int i=0;i<N;i++){
        P[i][0]=1;
        for(int j=1;j<=i;j++){
            P[i][j]=P[i-1][j-1]*i;
        }
        for(int j=0;j<=i;j++){
            assert(nPr(i,j)==P[i][j]);
        }
    }
	cout << "Tests passed!" << endl;
}
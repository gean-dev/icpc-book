#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-06-12
 * Description: Sparse Table class.
 */

template<class Monoid>
struct SparseTable{
    using T = typename Monoid::value_type;
    int n;
    vector<vector<T>> t;
    SparseTable(){}
    SparseTable(const vector<T> &a){init(a);}
    void init(const vector<T> &a){
        n=(int)a.size();
        int lg=31-__builtin_clz(n);
        t.assign(lg+1,vector<T>(n,Monoid::unit()));
        t[0]=a;
        for(int i=0;i<lg;i++){
            for(int j=0;j+(2<<i)<=n;j++){
                t[i+1][j]=Monoid::op(t[i][j],t[i][j+(1<<i)]);
            }
        }
    }
    T query(int l,int r){
        int lg=31-__builtin_clz(r-l+1);
        return Monoid::op(t[lg][l],t[lg][r-(1<<lg)+1]);
    }
};


#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-06-28
 * Description: Persistent Queue.
 */

template<class T>
struct PersistentQueue{
    int n,lg;
    vector<T> dat;
    vector<int> back_id,len;
    vector<vector<int>> par;
    PersistentQueue():n(1),lg(1),dat(0),back_id(0),len(0),par(1,{0}){}
    void calc_par(){
        if(n<(1<<lg))return;
        for(int i=0;i<n;i++)par[i].emplace_back(par[par[i][lg-1]][lg-1]);
        lg++;
    }
    int push(int t,const T &val){
        dat.emplace_back(val);
        back_id.emplace_back(n);
        len.emplace_back((t==-1?0:len[t])+1);
        par.emplace_back(vector<int>(lg,0));
        par[n][0]=t==-1?0:back_id[t];
        for(int i=1;i<lg;i++)par[n][i]=par[par[n][i-1]][i-1];
        n++;
        calc_par();
        return back_id.size()-1;
    }
    int pop(int t){
        back_id.emplace_back(back_id[t]);
        len.emplace_back(len[t]-1);
        return back_id.size()-1;
    }
    T front(int t){
        int d=size(t)-1;
        int x=back_id[t];
        for(int j=lg-1;j>=0;j--)if(d>>j&1)x=par[x][j];
        return dat[x-1];
    }
    int size(int t){
        return len[t];
    }
};


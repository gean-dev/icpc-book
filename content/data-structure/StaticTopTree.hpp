#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-11-14
 * Description: Static Top Tree.
 */

template<class HLD>
struct StaticTopTree{
    using P = pair<int,int>;
    enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};
    int n,root;
    HLD &hld;
    vector<int> lch,rch,par;
    vector<Type> type;
    StaticTopTree(HLD &_hld):hld(_hld){build();}
    void build(){
        n=hld.n;
        lch=rch=par=vector<int>(n,-1);
        type.assign(n,Compress);
        root=compress(hld.root).second;
    }
    int add(int i,int l,int r,Type t){
        if(i==-1){
            i=n++;
            lch.emplace_back(l);
            rch.emplace_back(r);
            par.emplace_back(-1);
            type.emplace_back(t);
        }else{
            lch[i]=l,rch[i]=r,type[i]=t;
        }
        if(l!=-1)par[l]=i;
        if(r!=-1)par[r]=i;
        return i;
    }
    /*
    pair<int,int> merge(vector<pair<int,int>> a,Type t){
        if(a.size()==1)return a[0];
        int tot=0;
        vector<pair<int,int>> l,r;
        for(auto [i,s]:a)tot+=s;
        for(auto [i,s]:a){
            (tot>s?l:r).emplace_back(i,s);
            tot-=s*2;
        }
        auto [i,si]=merge(l,t);
        auto [j,sj]=merge(r,t);
        return {add(-1,i,j,t),si+sj};
    }
    */
    P compress(int i){
        vector<P> a{add_vertex(i)};
        auto work=[&](){
            auto [sj,j]=a.back();
            a.pop_back();
            auto [si,i]=a.back();
            a.back()={max(si,sj)+1,add(-1,i,j,Compress)};
        };
        while(hld.hv[i]!=-1){
            a.emplace_back(add_vertex(i=hld.hv[i]));
            while(true){
                if(a.size()>=3&&(a.end()[-3].first==a.end()[-2].first||a.end()[-3].first<=a.back().first)){
                    P tmp=a.back();
                    a.pop_back();
                    work();
                    a.emplace_back(tmp);
                }else if(a.size()>=2&&a.end()[-2].first<=a.back().first){
                    work();
                }else break;
            }
        }
        while(a.size()>=2)work();
        return a[0];
    }
    P rake(int i){
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int j:hld.g[i])if(j!=hld.par[i]&&j!=hld.hv[i])pq.emplace(add_edge(j));
        while(pq.size()>=2){
            auto [si,i]=pq.top();pq.pop();
            auto [sj,j]=pq.top();pq.pop();
            pq.emplace(max(si,sj)+1,add(-1,i,j,Rake));
        }
        return pq.empty()?make_pair(0,-1):pq.top();
    }
    P add_edge(int i){
        auto [sj,j]=compress(i);
        return {sj+1,add(-1,j,-1,AddEdge)};
    }
    P add_vertex(int i){
        auto [sj,j]=rake(i);
        return {sj+1,add(i,j,-1,j==-1?Vertex:AddVertex)};
    }
};

/*
struct TreeDP{
    struct Path{
        static Path unit();
    };
    struct Point{
        static Point unit();
    };
    static Path compress(Path l,Path r);
    static Point rake(Point l,Point r);
    static Point add_edge(Path p);
    static Path add_vertex(Point p,int u);
    static Path vertex(int u);
};
*/

template<class HLD,class TreeDP>
struct StaticTopTreeRerootingDP{
    using Path = typename TreeDP::Path;
    using Point = typename TreeDP::Point;
    StaticTopTree<HLD> stt;
    vector<Path> path,rpath;
    vector<Point> point;
    StaticTopTreeRerootingDP(HLD &hld):stt(hld){
        int n=stt.n;
        path.resize(n);
        point.resize(n);
        rpath.resize(n);
        dfs(stt.root);
    }
    void _update(int u){
        if(stt.type[u]==stt.Vertex){
            path[u]=rpath[u]=TreeDP::vertex(u);
        }else if(stt.type[u]==stt.Compress){
            path[u]=TreeDP::compress(path[stt.lch[u]],path[stt.rch[u]]);
            rpath[u]=TreeDP::compress(rpath[stt.rch[u]],rpath[stt.lch[u]]);
        }else if(stt.type[u]==stt.Rake){
            point[u]=TreeDP::rake(point[stt.lch[u]],point[stt.rch[u]]);
        }else if(stt.type[u]==stt.AddEdge){
            point[u]=TreeDP::add_edge(path[stt.lch[u]]);
        }else{
            path[u]=rpath[u]=TreeDP::add_vertex(point[stt.lch[u]],u);
        }
    }
    void dfs(int u){
        if(u==-1)return;
        dfs(stt.lch[u]);
        dfs(stt.rch[u]);
        _update(u);
    }
    void update(int u){
        for(;u!=-1;u=stt.par[u])_update(u);
    }
    Path query_all(){
        return path[stt.root];
    }
    Path query_subtree(int u){
        Path res=path[u];
        while(true){
            int p=stt.par[u];
            if(p==-1||stt.type[p]!=stt.Compress)break;
            if(stt.lch[p]==u)res=TreeDP::compress(path[stt.rch[p]],res);
        }
        return res;
    }
    Path query_reroot(int u){
        auto rec=[&](auto &&rec,int u)->Point {
            int p=stt.par[u];
            Path below=Path::unit(),above=Path::unit();
            while(p!=-1&&stt.type[p]==stt.Compress){
                int l=stt.lch[p],r=stt.rch[p];
                if(l==u)below=TreeDP::compress(below,path[r]);
                else above=TreeDP::compress(above,rpath[l]);
                u=p;
                p=stt.par[u];
            }
            if(p!=-1){
                u=p;
                p=stt.par[u];
                Point sum=Point::unit();
                while(stt.type[p]==stt.Rake){
                    int l=stt.lch[p],r=stt.rch[p];
                    sum=TreeDP::rake(sum,u==r?point[l]:point[r]);
                    u=p;
                    p=stt.par[u];
                }
                sum=TreeDP::rake(sum,rec(rec,p));
                above=TreeDP::compress(above,TreeDP::add_vertex(sum,p));
            }
            return TreeDP::rake(TreeDP::add_edge(below),TreeDP::add_edge(above));
        };
        Point res=rec(rec,u);
        if(stt.type[u]==stt.AddVertex){
            res=TreeDP::rake(res,point[stt.lch[u]]);
        }
        return TreeDP::add_vertex(res,u);
    }
};


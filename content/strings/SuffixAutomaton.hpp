#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-06-14
 * Description: Suffix Automaton.\\
 * Find whether a string $t$ is a substring of a string $s$ by traversing the automaton.\\
 * Find whether a string $t$ is a suffix of a string $s$ by checking whether the last node is a terminal node.\\
 * Find the number of distinct substrings of a string $s$ by calculating the number of distinc path using DP.\\
 * Count the number of occurrences of string $t$ in string $s$. Let $p$ be the node we end up at after traversing $t$ in the automaton. The answer is the number of paths from $p$ to terminal nodes.\\
 * Find first occurrence of string $t$ in string $s$ by calculating the longest path in the automaton after reaching node $p$.\\
 */

template<class STR>
struct SuffixAutomaton{
    using T = typename STR::value_type;
    struct Node{
        map<T,int> nxt;
        int link,len;
        Node(int link,int len):link(link),len(len){}
    };
    vector<Node> nodes;
    int last;
    SuffixAutomaton():nodes{Node(-1,0)},last(0){}
    SuffixAutomaton(const STR &s):SuffixAutomaton(){
        for(auto c:s)extend(c);
    }
    int new_node(int link,int len){
        nodes.emplace_back(Node(link,len));
        return (int)nodes.size()-1;
    }
    void extend(T c){
        int cur=new_node(0,nodes[last].len+1);
        int p=last;
        while(p!=-1&&!nodes[p].nxt.count(c)){
            nodes[p].nxt[c]=cur;
            p=nodes[p].link;
        }
        if(p!=-1){
            int q=nodes[p].nxt[c];
            if(nodes[p].len+1==nodes[q].len){
                nodes[cur].link=q;
            }else{
                int r=new_node(nodes[q].link,nodes[p].len+1);
                nodes[r].nxt=nodes[q].nxt;
                while(p!=-1&&nodes[p].nxt[c]==q){
                    nodes[p].nxt[c]=r;
                    p=nodes[p].link;
                }
                nodes[q].link=nodes[cur].link=r;
            }
        }
        last=cur;
    }
    ll distinct_substrings(){
        ll res=0;
        for(int i=1;i<(int)nodes.size();i++){
            res+=nodes[i].len-nodes[nodes[i].link].len;
        }
        return res;
    }
};
#include "TSP.h"

TSP_Class::TSP_Class(int* realFirst,int* first,double cost,double** adj,vector<int*>& S)
{
    this->realFirst = realFirst;
    this->first = first;
    this->adj = adj;
    auto* n = new NodeStack;
    n->node = first;
    n->cost = cost;
    n->ls.push_back(realFirst);
    n->ls.push_back(first);
    n->remaining = S;
    st.push(n);
}



Path* TSP_Class::start(){
    Path* p = new Path;
    NodeStack* np = nullptr;
    while (!st.empty())
    {
        NodeStack* n = st.top();
        st.pop();
        vector<int*>* S = &n->remaining;
        if(S->empty()){
            n->cost = n->cost + adj[*n->node][*realFirst];
            if(np == nullptr || np->cost > n->cost){
                n->ls.push_back(realFirst);
                np = n;
            } else {
                n->ls.clear();
                n->remaining.clear();
                delete n;
            }
        } else {
            int scount = S->size();
            for(int count = 0; count < scount; count++){
                int* s = (*S)[count];
                double actual = n->cost + adj[*n->node][*s];
                if(np != nullptr && np->cost <= actual)
                    continue;
                auto* nd = new NodeStack{s,actual,vector<int*>(n->ls.size() + 1),vector<int*>(S->size() - 1)};
                int i = 0;
                for(int* inside:*S){
                    if(*inside != *s){
                        nd->remaining[i++] = inside;
                    }
                } 
                i = 0;
                for(int* cp: n->ls){
                    nd->ls[i++] = cp;
                }
                nd->ls[i] = s; 
                st.push(nd); 
            } 
            n->ls.clear();
            n->remaining.clear();
            delete n; 
        } 
    } 
    p->cost = np->cost;
    p->path = np->ls;
    return p;
}
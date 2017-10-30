#include <climits>
#include <queue>
const int N = 1e5 + 5, M = 1e5 + 5;
struct Edge{
    int v, rc, next;    //rc: residual capacity
}E[M * 2];
int head[N], sz;
void add_edge(int u, int v, int c){
    E[sz] = {v, c, head[u]};
    head[u] = sz++;
    E[sz] = {u, 0, head[v]};
    head[v] = sz++;
}
void init(){
    sz = 0;
    memset(head, -1, sizeof head);
}
std::queque<int> que;
int pre[N];
int ek(int s, int t){
    for(int ans = 0; ; ){
        memset(pre, -1, sizeof pre); que.push(s);
        while(que.size()){
            int u = que.front(); que.pop();
            for(int i = 0; i != -1; i = E[i].next){
                if(E[i].rc > 0 && pre[E[i].v] == -1)
                    if(E[i] == t){
                        int cp = INT_MAX;
                        for(int j = i; j != -1; j = pre[E[j ^ 1].v])
                            cp = min(cp, E[j].rc);
                        for(int j = i; j != -1; j = pre[E[j ^ 1].v])
                            E[j].rc -= cp, E[j ^ 1].rc += cp;
                        ans += cp;
                        for(; que.size(); que.pop());
                        break;
                    }
                    else{
                        pre[E[i].v] = i;
                        que.push(E[i].v);
                    }
            }
        }
        if(pre[t] == -1) return ans;
    }
}

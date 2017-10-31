#include <algorithm>
#include <climits>
int q[N], n, m, s, t;
bool bfs(){
    memset(level, -1, sizeof(int[n + 1]));
    int beg = 0, end = 0;
    level[s] = 0; q[end++] = s;
    while(beg < end){
        int u = q[beg++];
        for(int i = head[u]; i != -1; i = E[i].next)
            if(E[i].rc && level[E[i].v] == -1){
                level[E[i].v] = level[u] + 1;
                if(E[i].v == t) return true;
                q[end++] = E[i].v;
            }
    }
    return false;
}
using LL = long long;
LL dfs(int u, LL rc){
    if(u == t) return rc;
    LL total = 0;
    for(int &i = cur[u]; i != -1; i = E[i].next)
        if(level[E[i].v] == level[u] + 1 && E[i].rc > 0){
            int tmp = dfs(E[i].v, std::min(rc, LL(E[i].rc)));
            if(tmp > 0){
                E[i].rc -= tmp;
                E[i ^ 1].rc += tmp;
                total += tmp;
                rc -= tmp;
                if(rc == 0) break;
            }
        }
    return total;
}
LL dinic(){
    LL ans = 0;
    while(bfs()){
        memcpy(cur, head, sizeof(int[n + 1]));
        for(LL f; f = dfs(s, LLONG_MAX); ans += f);
    }
    return ans;
}

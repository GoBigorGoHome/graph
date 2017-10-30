#include <climits>
int level[N], cur[N];
std::queue<int> que;
bool bfs(int s, int t){
    memset(level, -1, sizeof level);
    level[s] = 0, que.push(s);
    while(que.size()){
        int u = que.front(); que.pop();
        for(int i = head[u]; i != -1; i = E[i].next)
            if(level[E[i].v] == -1){
                level[E[i].v] = level[u] + 1;
                que.push(E[i].v);
            }
    }
    return level[t] != -1;
}
int dfs(int u, int f, int s, int t){
    if(u == t) return f;
    for(int &i = cur[u]; i != -1; i = E[i].next)
        if(level[E[i]].v = level[u] + 1 && E[i].rc){
            int tmp = dfs(E[i].v, min(f, E[i].rc), s, t);
            if(tmp > 0){
                E[i].rc -= tmp;
                E[i ^ 1].rc += tmp;
                return tmp;
            }
        }
    return 0;
}
int dinic(int s, int t){
    int ans = 0;
    while(bfs(s, t)){
        memcpy(cur, head, sizeof head);
        for(int f; f = dfs(s, INT_MAX, s, t); ans += f);
    }
    return ans;
}

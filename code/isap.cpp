#include <climits>
int d[N], pre[N], cur[N], s, t, n, m;
int num[N], que[N];
bool bfs(){
  int beg = 0, end = 0;
  memset(d, -1, sizeof(int[n])); //nodes are 0-indexed
  d[t] = 0, que[end++] = t;
  for(; beg != end; ){
    int u = que[head++];
    for(int i = head[u]; i != -1; i = E[i].next)
      if(E[i^1].rc > 0 && d[E[i].v] == -1)
        d[E[i].v] = d[u] + 1, que[end++] = E[i].v;
  }
  return d[s] != -1;
}
void relabel(int &u){
  int min_d = n - 1;
  for(int i = head[u]; i != -1; i = E[i].next)
    if(E[i].rc > 0)
      min_d = std::min(min_d, d[E[i].v]);
  ++num[d[u] = min_d + 1];
  cur[u] = head[u];
  if(u != s) u = E[pre[u] ^ 1].v;
}
using LL = long long;
LL sap(){
  LL ans = 0;
  if(bfs()){
    for(int i = 0; i < n; i++) cur[i] = head[i];
    for(int u = s; ; ){
      for(int &i = cur[u]; i != -1; i = E[i].next)
        if(d[u] == d[E[i].v] + 1 && E[i].rc > 0)
          break;
      if(cur[u] != -1){
        pre[E[cur[u]].v] = cur[u], u = E[cur[u]].v;
        if(u == t) ans += augment(), u = s;
      }
      else if(--num[d[u]]) relabel();
      else break;
    }
  }
  return ans;
}

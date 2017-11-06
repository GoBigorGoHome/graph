#include <climits>
int d[N], pre[N], cur[N], s, t, n, m;
int augment(){
  int rc = INT_MAX;
  for(int v = u; v != s; v = E[pre[v] ^ 1].v)
    rc = std::min(rc, E[pre[v]].rc);
  for(int v = u; v != s; v = E[pre[v] ^ 1].v)
    E[pre[v]].rc -= rc, E[pre[v] ^ 1].rc += rc;
  return rc;
}
void relabel(int &u){
  int min_d = n - 1;
  for(int i = head[u]; i != -1; i = E[i].next)
    if(E[i].rc > 0)
      min_d = std::min(min_d, d[E[i].v]);
  d[u] = min_d + 1;
  cur[u] = head[u];
  if(u != s) u = E[pre[u] ^ 1].v;
}
using LL = long long;
LL sap(){
  LL ans = 0;
  for(int i = 0; i < n; i++)  // nodes are 0-indexed
    d[i] = 0, cur[i] = head[i];
  for(int u = s; d[s] < n; ){
    for(int &i = cur[u]; i != -1; i = E[i].next)
      if(d[u] == d[E[i].v] + 1 && E[i].rc > 0)
        break;
    if(cur[u] != -1){
      pre[E[cur[u]].v] = cur[u], u = E[cur[u]].v;
      if(u == t) ans += augment, u = s;
    }
    else relabel(u);
  }
  return ans;
}

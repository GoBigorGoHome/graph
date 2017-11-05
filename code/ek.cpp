#include <climits>
#include <algorithm>
const int N = 1e5 + 5, M = 1e5 + 5;
struct Edge{
  int v, rc, next;    //rc: residual capacity
}E[M * 2];
int head[N], sz, n, m, s, t;
void add_edge(int u, int v, int c){
  E[sz] = {v, c, head[u]};
  head[u] = sz++;
  E[sz] = {u, 0, head[v]};
  head[v] = sz++;
}
void init(){
  sz = 0;
  memset(head, -1, sizeof(int[n + 1]));
}
int pre[N], q[N];
int ek(){
  for(int ans = 0; ; ){
    int beg = 0, end = 0;
    memset(pre, -1, sizeof(int[n + 1])); q[end++] = s;
    while(beg < end){
      int u = q[beg++];
      for(int i = 0; i != -1; i = E[i].next){
        if(E[i].rc > 0 && pre[E[i].v] == -1)
          if(E[i].v == t){
            int cp = INT_MAX;
            for(int j = i; j != -1; j = pre[E[j^1].v])
                cp = std::min(cp, E[j].rc);
            for(int j = i; j != -1; j = pre[E[j^1].v])
                E[j].rc -= cp, E[j ^ 1].rc += cp;
            ans += cp; break;
          }
          else{
            pre[E[i].v] = i;
            q[end++] = E[i].v;
          }
      }
    }
    if(pre[t] == -1) return ans;
  }
}

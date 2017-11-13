int n, m, s, t;
int d[N], pre[N]; // pre[u]: the edge to u in augmenting path
bool inq[N]; // inq[u]: is node u in queue?
using LL = long long;
LL flow, cost;
bool bellman_ford(){
  for(int i = 0; i < n; i++) d[i] = INT_MAX;
  memset(inq, 0, sizeof inq);
  d[s] = 0, inq[s] = true, a[s] = INF;
  std::queue<int> q;
  q.push(s);
  while(q.size()){
    int u = q.front(); q.pop();
    inq[u] = 0;
    for(int i = head[u]; i != -1; i= E[i].next){
      if(E[i].rc > 0 && d[E[i].v] > d[u] + E[i].cost){
        d[E[i].v] = d[u] + E[i].cost;
        pre[E[i].v] = i;
        if(!inq[E[i].v]) q.push(E[i].v), inq[E[i].v] = true;
      }
    }
  }
  if(d[t] == INT_MAX) return false;
  int rc = INT_MAX;
  for(int u = t; u != s; u = E[pre[u] ^ 1].v){
    rc = std::min(rc, E[pre[u]].rc);
  }
  for(int u = t; u != s; u = E[pre[u] ^ 1].v){
    E[pre[u]].rc -= rc;
    E[pre[u] ^ 1].rc += rc;
  }
  flow += rc, cost += LL(rc) * d[t];
  return true;
}

LL mcmf(){
  flow = cost = 0;
  while(bellman_ford());
}

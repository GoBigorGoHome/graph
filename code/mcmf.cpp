#include <climits>
int n, m, s, t;
int pre[N]; // pre[u]: the edeg to node u in partial augmenting path
bool inq[N]; // inq[u]: is node u in queue?
bool Bellman_Ford(int &flow, int &cost){
  for(int i = 0; i < n; i++) d[i] = INT_MAX;
  memset(inq, 0, sizeof inq);
  d[s] = 0, inq[s] = true, a[s] = INF;
  for(int i = 0; i < n; i++)
  queue<int> q;
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

}

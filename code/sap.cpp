int d[N];
int s, t, n, m;
using LL = long long;
LL sap(){
    for(int i = 0; i < n; i++)  // nodes are 0-indexed
        d[i] = 0;
    int u = s;
    while(d[s] < n){
        for(int i = head[u]; i != -1; i = E[i].next)
            if(d[E[i].v] + 1 == d[u] && E[i].rc > 0)
                u = E[i].v;
            
    }
}

int w[N][N], Lx[N], Ly[N], slack[N], match[N];
bool S[N], T[N];
int n;
bool dfs(int u){
  S[u]=true;
  for(int v=1; v<=n; v++){
    if(T[v]) continue;
    int tmp=Lx[u]+Ly[v]-w[u][v];
    if(tmp==0){
      T[v]=true;
      if(!match[v] || dfs(match[v])){
        match[v]=u; return true;
      }
    }
    else slack[v] = min(slack[v], tmp);
  }
  return false;
}
int KM(){
  memset(match, 0, sizeof match);
  memset(Lx, 0x3f, sizeof Lx);
  memset(Ly, 0x3f, sizeof Ly);
  for(int i = 1; i <= n; i++){    //phase
    for(int j = 1; j <= n; j++)
      slack[j]=INT_MAX;
    for(; ;){
      memset(S, 0, sizeof S);
      memset(T, 0, sizeof T);
      if(dfs(i)) break; int a = INT_MAX;
      for(int j = 1; j <= n; j++) if(!T[j]) a=min(a, slack[j]);
      for(int j = 1; j <= n; j++){
        if(S[j]) Lx[j] -= a;
        if(T[j]) Ly[j] += a;
        else slack[j] -= a;
      }
    }
  }
  int ans = 0;
  for(int i = 1; i <= n; i++) ans += w[match[i]][i];
  return ans;
}

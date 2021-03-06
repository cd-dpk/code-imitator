/*#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define dbg(x)  cout<<#x<<"="<<x<<endl
#define N 2001025
#define MOD  786433
#define pb push_back
#define iosbase  ios_base::sync_with_stdio(false)
#define dbg(x)  cout<<#x<<"="<<x<<endl
*/

#include <bits/stdc++.h>
using namespace std;
// maxflow

long long res[2600][2600];
long long cap[2600][2600];
long long comp1[2600][2600], comp2[2600][2600];
vector<long long> adj[2600];
bool mark[2600];
long long par[2600];
string s[2600];
vector<long long> vec[2];
long long avail[50][100], tak[50][100];
long long req[100];

bool can(long long u, long long v) { return ((cap[u][v] - res[u][v]) > 0); }

bool bet(long long amt, long long tm, long long num) {
  long double am = amt, t = tm;
  long double tot = req[num] * tm;
  long double ans = am * 100 / tot;
  if (ans >= 90.0 && ans <= 110.0)
    return true;
  else
    return false;
}
bool more(long long amt, long long tm, long long num) {
  long double am = amt, t = tm;
  long double tot = req[num] * tm;
  long double ans = am * 100 / tot;
  if (ans >= 90.0)
    return true;
  else
    return false;
}

bool bfs(long long source, long long sink) {
  memset(mark, 0, sizeof(mark));

  queue<long long> q;
  q.push(source);
  mark[source] = 1;
  while (!q.empty()) {
    long long u = q.front();
    q.pop();
    for (long long i = 0; i < adj[u].size(); i++) {
      long long v = adj[u][i];
      if (!mark[v] && can(u, v)) {
        mark[v] = 1;
        q.push(v);
        par[v] = u;
      }
    }
  }
  return (mark[sink] == 1);
}

long long Augment(long long source, long long sink) {
  long long cur = sink, flow = 1e7;
  while (cur != source) {

    long long p = par[cur]; // p--sink edge
    flow = min(flow, cap[p][cur] - res[p][cur]);
    cur = p;
  }
  cur = sink;
  while (cur != source) {
    long long p = par[cur]; // p--sink edge

    res[p][cur] += flow;
    res[cur][p] -= flow;
    cur = p;
  }
  return flow;
}

long long maxF(long long source, long long sink) {
  long long maxflow = 0;
  while (bfs(source, sink)) {

    long long k = Augment(source, sink);

    maxflow += k;
  }
  return maxflow;
}

int main() {
  long long n, p, m, t, ans, maxt, mint;

  cin >> t;
  for (long long tc = 1; tc <= t; tc++) {
    mint = 1e7;
    cout << "Case #" << tc << ": ";
    ans = 0;
    memset(tak, 0, sizeof(0));
    cin >> n >> p;

    maxt = -1;
    for (long long i = 0; i < n; i++) {
      cin >> req[i];
    }
    for (long long i = 0; i < n; i++) {
      for (long long j = 0; j < p; j++) {
        cin >> avail[i][j];
        maxt = max(avail[i][j], maxt);
        mint = min(avail[i][j] * 100 / (90 * req[i]), mint);
      }
    }

    if (n == 1) {
      for (int i = 0; i < maxt; i++) {
        for (int j = 0; j < p; j++) {
          if (bet(avail[0][j], i, 0)) {
            if (!mark[j]) {
              ans++;
              mark[j] = 1;
            }
          }
        }
      }
      memset(mark, 0, sizeof(mark));
      cout << ans << endl;
      continue;
    }

    int flag = 0, yes = 0, ex = 0;
    for (long long i = mint; i <= maxt; i++) {
      if (ex == 1)
        break;

      for (long long j = 0; j < n; j++) {
        flag = j % 2;
        yes = 0;
        for (long long k = 0; k < p; k++) {
          if (more(avail[j][k], i, j))
            yes++;
          if (bet(avail[j][k], i, j)) {

            vec[flag ^ 1].push_back(k);
          }
        }

        if (yes == 0)
          ex = 1;
        if (vec[flag ^ 1].size() == 0)
          break;
        if (j == 0)
          continue;

        for (long long x = 0; x < vec[flag].size(); x++) {
          for (long long y = 0; y < vec[flag ^ 1].size(); y++) {

            if (tak[(j - 1) * p + vec[flag][x]][j * p + vec[flag ^ 1][y]] == 1)
              continue;
            adj[(j - 1) * p + vec[flag][x]].push_back(
                (j * p + vec[flag ^ 1][y]));
            cap[(j - 1) * p + vec[flag][x]][j * p + vec[flag ^ 1][y]] = 1;
            adj[j * p + vec[flag ^ 1][y]].push_back((j - 1) * p + vec[flag][x]);
            // cout<<(j-1)*p+vec[flag][x]<<"--"<<j*p+vec[flag^1][y]<<endl;
            tak[(j - 1) * p + vec[flag][x]][j * p + vec[flag ^ 1][y]] = 1;
          }
        }
        vec[flag].clear();
      }
    }

    vec[0].clear();
    vec[1].clear();

    long long source = n * p + 1;
    long long sink = n * p + 2;

    for (long long i = 0; i < p; i++) {
      cap[source][i] = 1;
      adj[source].push_back(i);
      adj[i].push_back(source);
      adj[(n - 1) * p + i].push_back(sink);
      adj[sink].push_back((n - 1) * p + i);
      cap[(n - 1) * p + i][sink] = 1;
    }

    ans = maxF(source, sink);
    cout << ans << endl;

    for (long long i = 0; i < 2600; i++)
      adj[i].clear();

    memset(cap, 0, sizeof(cap));
    memset(res, 0, sizeof(res));
    memset(mark, 0, sizeof(mark));
  }
}

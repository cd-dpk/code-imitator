
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;

const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;
// extended template
#pragma comment(linker, "/STACK:36777216")
typedef vector<int> vi;
typedef vector<vi> vvi;

template <typename T> istream &operator>>(istream &, vector<T> &);
template <typename T> ostream &operator<<(ostream &, const vector<T> &);

vector<LL> mas(1);

int getLevel(LL k) {
  return lower_bound((mas).begin(), (mas).end(), k) - mas.begin();
}

void solve() {
  int t;
  cin >> t;
  for (int q = 0; q < t; q++) {
    LL n, k;
    cin >> n >> k;

    int lvl = getLevel(k);
    LL ost = k - mas[lvl - 1];
    LL countInLvl = (1LL << (lvl - 1));
    LL ostFromN = n - mas[lvl - 1];

    LL value = ostFromN / countInLvl;
    LL incV = ostFromN % countInLvl;

    cout << "Case #" << q + 1 << ": ";
    if (ost <= incV)
      value++;

    cout << (value) / 2 << " " << (value - 1) / 2 << endl;
  }
}

int main() {
  mas[0] = 0;
  for (int i = 1; i < 63; i++)
    mas.push_back(mas[i - 1] + (1LL << (i - 1)));

  ios_base::sync_with_stdio(false);
  // START
  // freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
  freopen("C-small-1-attempt0.in", "r", stdin);
  freopen("output.txt", "w", stdout);
  solve();

  // END
  return 0;
}
/*******************************************
*******************************************/

template <typename T> istream &operator>>(istream &is, vector<T> &v) {
  for (int i = 0; i < v.size(); ++i)
    is >> v[i];
  return is;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  for (int i = 0; i < v.size(); ++i)
    os << v[i] << " ";
  return os;
}
#define _USE_MATH_DEFINES

#ifdef LOCAL
#include "prettyprint.hpp"
#endif

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

template <typename... Ts>
void eprint(Ts&&... ts) {
#ifdef LOCAL
    ((cerr << ts << " "), ...) << endl;
#endif
}

#define DEBUG(x...) eprint("[" #x "]:", x)

const ld EPS = 1e-10;

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    assert(argc >= 2); // an input file please!
    ifstream fin(argv[1]);
    int nElements, nSets;
    fin >> nElements >> nSets;
    vector<int> costs(nSets);
    for (int i = 0; i < nSets; ++i) {
        fin >> costs[i];
    }
    string str;
    getline(fin, str);
    vector<set<int>> sets(nSets);
    for (int i = 0; i < nSets; ++i) {
        getline(fin, str);
        istringstream ss(str);
        int e;
        while (ss >> e) {
            sets[i].insert(e);
        }
    }
    vector<ld> ans(nSets);
    vector<bool> chosen(nSets);
    for (int i = 0; i < nSets; ++i) {
        fin >> ans[i];
    }
    for (int i = 0; i < nSets; ++i) {
        if (ans[i] > 1.l / nSets + EPS) {
            chosen[i] = 1;
        }
    }
    for (int i : chosen)
        cout << i << ' ';
    cout << '\n';
}

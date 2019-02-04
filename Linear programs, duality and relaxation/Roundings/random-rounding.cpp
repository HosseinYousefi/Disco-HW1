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
    vector<ld> prob(nSets);
    vector<bool> chosen(nSets);
    for (int i = 0; i < nSets; ++i) {
        fin >> prob[i];
    }
    set<int> u;
    unsigned long seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 generator(seed);
    while (int(u.size()) < nElements) {
        for (int i = 0; i < nSets; ++i) {
            if (!chosen[i]) {
                auto rnd = generator();
                if (1.l * rnd < 1.l * UINT_FAST64_MAX * prob[i]) {
                    chosen[i] = 1;
                    for (int e : sets[i])
                        u.insert(e);
                }
            }
        }
    }
    for (int i : chosen)
        cout << i << ' ';
    cout << '\n';
}

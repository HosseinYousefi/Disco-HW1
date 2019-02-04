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

#define DEBUG(x...) eprint("[" #x "]: ", x)

struct Item {
    int value, weight;
};

ostream& operator<<(ostream& out, const Item& it) {
    return out << "(" << it.value << ", " << it.weight << ")";
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin(argv[1]);
    int n, w;
    fin >> n >> w;
    vector<Item> items(n);
    for (auto& it : items)
        fin >> it.value;
    for (auto& it : items)
        fin >> it.weight;

    // Greedy 1: Scan through items in the order of decrease of their value. 
    //           If the current item fits into the knapsack, put it.
    sort(items.begin(), items.end(), [](auto a, auto b) {
        return a.value > b.value;
    });

    int ks1 = 0, ans1 = 0;
    for (auto it : items) {
        if (ks1 + it.weight <= w) {
            ks1 += it.weight;
            ans1 += it.value;
        }
    }

    // Greedy 2: Scan through items in the order of increase of their weight.
    //           If the current item fits into the knapsack, put it.
    sort(items.begin(), items.end(), [](auto a, auto b) {
        return a.weight < b.weight;
    });

    int ks2 = 0, ans2 = 0;
    for (auto it : items) {
        if (ks2 + it.weight <= w) {
            ks2 += it.weight;
            ans2 += it.value;
        }
    }

    // Greedy 2: Scan through items in the order of decrease of their “value per weight”.
    //           If the current item fits into the knapsack, put it.
    sort(items.begin(), items.end(), [](auto a, auto b) {
        return 1.l * a.value / a.weight > 1.l * b.value / b.weight;
    });

    int ks3 = 0, ans3 = 0;
    for (auto it : items) {
        if (ks3 + it.weight <= w) {
            ks3 += it.weight;
            ans3 += it.value;
        }
    }

    // Combining everything
    cout << max({ans1, ans2, ans3}) << '\n';
}

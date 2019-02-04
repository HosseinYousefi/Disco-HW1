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

struct Item {
    int value, weight;
};

vector<Item> items;
vector<int> psw, psv;

int findUpperBound(int index, int capacity) {
    ld ans = 0;
    for (int i = index; i < int(items.size()) && capacity > 0; ++i) {
        int taken = min(items[i].weight, capacity);
        capacity -= taken;
        ans += taken * (1.l * items[i].value / items[i].weight);
    }
    return int(floor(ans));
}

int lowerBound = 0;
ll counter = 0;
int lastRes = 0;

void dfs(int index, int capacity, int answer) {
    ++counter;
    if (counter % 10000 == 9999) {
        if (lowerBound > lastRes) {
            cout << lowerBound << '\n'; // intermediate results
            lastRes = lowerBound;
        }
    }
    lowerBound = max(lowerBound, answer);
    if (index >= int(items.size()))
        return;
    if (items[index].weight <= capacity) {
        if (answer + items[index].value + findUpperBound(index + 1, capacity - items[index].weight) > lowerBound) {
           dfs(index + 1, capacity - items[index].weight, answer + items[index].value);
        }
    }
    if (answer + findUpperBound(index + 1, capacity) > lowerBound) {
        dfs(index + 1, capacity, answer);
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    clock_t startTime = clock();
    assert(argc >= 2); // an input file please!
    ifstream fin(argv[1]);
    int n, w;
    fin >> n >> w;
    items.resize(n);
    for (auto& it : items)
        fin >> it.value;
    for (auto& it : items)
        fin >> it.weight;
    sort(items.begin(), items.end(), [](auto a, auto b) {
        return 1.l * a.value / a.weight > 1.l * b.value / b.weight;
    });

    psv.resize(n + 1);
    psw.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        psv[i] = psv[i - 1] + items[i].value;
        psw[i] = psw[i - 1] + items[i].weight;
    }
    dfs(0, w, 0);
    cout << "Final result: " << lowerBound << '\n';
    ld timeTook = (1.l * clock() - startTime) / CLOCKS_PER_SEC;
    DEBUG(timeTook);
}

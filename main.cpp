#include <bits/stdc++.h>

using namespace std;

int n;
long long a[500001];
long long tree[2000004];

void build_tree(int v, int tl, int tr)
{
    if (tl == tr)
        tree[v] = a[tl];
    else
    {
        int tm = (tl + tr) / 2;
        build_tree(v * 2, tl, tm);
        build_tree(v * 2 + 1, tm + 1, tr);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
}

long long get_sum(int r, int v, int tl, int tr)
{
    if (tr <= r)
        return tree[v];

    if (r < tl)
        return 0;

    int tm = (tl + tr) / 2;
    return get_sum(r, v * 2, tl, tm) + get_sum(r, v * 2 + 1, tm + 1, tr);
}

void update(int idx, int v, int tl, int tr)
{
    if (idx <= tl && tr <= idx)
    {
        a[idx]++;
        tree[v]++;
        return;
    }

    if (tr < idx || idx < tl)
        return;

    int tm = (tl + tr) / 2;
    update(idx, v * 2, tl, tm);
    update(idx, v * 2 + 1, tm + 1, tr);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> n;
    int x, y;
    int *res = new int [n];
    for(int i = 0; i < n; i++)
        res[i] = 0;
    build_tree(1, 0, 500000);
    for(int i = 0; i < n; i++)
    {
        fin >> x;
        fin >> y;
        update(x, 1, 0, 500000);
        res[get_sum(x, 1, 0, 500000) - 1]++;
    }
    for(int i = 0; i < n; i++)
        fout << res[i] << "\n";
    return 0;
}

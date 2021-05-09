#include <iostream>
using namespace std;

void updateBtree(int *btree, int val, int n, int index)
{
    index++;

    while (index <= n)
    {
        btree[index] += val;
        index += (index & -index);
    }
}

int query(int *btree, int index)
{
    index++;

    int sum = 0;
    while (index > 0)
    {
        sum += btree[index];
        index -= ((index) & (-index));
    }
    return sum;
}

int *constructBTree(int arr[], int n)
{
    int *btree = new int[n + 1];
    for (int i = 0; i <= n; i++)
        btree[i] = 0;
    for (int i = 0; i < n; i++)
        updateBtree(btree, arr[i], n, i);

    return btree;
}

int rangeQuery(int *btree, int start, int end)
{
    if (start > 0)
        return query(btree, end) - query(btree, start - 1);
    return query(btree, end);
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int *btree = constructBTree(arr, 5);

    cout << rangeQuery(btree, 1, 4);
    return 0;
}

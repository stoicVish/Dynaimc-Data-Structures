#include <iostream>
#include <math.h>
using namespace std;

int sizeOfSegTree(int n)
{
    n = ceil(log2(n)) + 1;
    return (1 << n) - 1;
}

void constructSegTree(int arr[], int segTree[], int low, int high, int i)
{
    if (low > high)
        return;
    if (low == high)
    {
        segTree[i] = arr[low];
        return;
    }

    int mid = low + (high - low) / 2;
    constructSegTree(arr, segTree, low, mid, 2 * i + 1);
    constructSegTree(arr, segTree, mid + 1, high, 2 * i + 2);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

int query(int start, int end, int low, int high, int sTree[], int i)
{
    if (start > high || end < low)
        return 0;

    if (start <= low && high <= end)
        return sTree[i];

    int mid = low + (high - low) / 2;
    return query(start, end, low, mid, sTree, 2 * i + 1) +
           query(start, end, mid + 1, high, sTree, 2 * i + 2);
}

void update(int index, int segTree[], int low, int high, int i, int inc)
{
    if (low > high)
        return;
    if (low == high)
    {
        if (low == index)
            segTree[i] += inc;
        return;
    }
    int mid = low + (high - low) / 2;
    update(index, segTree, low, mid, 2 * i + 1, inc);
    update(index, segTree, mid + 1, high, 2 * i + 2, inc);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int segTree[sizeOfSegTree(n)];

    constructSegTree(arr, segTree, 0, n - 1, 0);

    cout << query(0, n - 2, 0, n - 1, segTree, 0) << "\n";
    update(0, segTree, 0, n - 1, 0, 5);
    cout << query(0, n - 2, 0, n - 1, segTree, 0);

    return 0;
}

#include <iostream>
#include <math.h>
using namespace std;

//done
int sizeOfSegTree(int n)
{
    n = ceil(log2(n)) + 1;
    return (1 << n) - 1;
}

//done
void constructSegTree(int arr[], int lazy[], int segTree[], int low, int high, int i)
{
    if (low > high)
        return;
    if (low == high)
    {
        lazy[i] = 0;
        segTree[i] = arr[low];
        return;
    }

    int mid = low + (high - low) / 2;
    constructSegTree(arr, lazy, segTree, low, mid, 2 * i + 1);
    constructSegTree(arr, lazy, segTree, mid + 1, high, 2 * i + 2);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
    lazy[i] = 0;
}

//done
int query(int start, int end, int low, int high, int sTree[], int lazy[], int i)
{
    if (start > high || end < low)
        return 0;

    if (lazy[i])
    {
        sTree[i] += (high - low + 1) * lazy[i];
        if (low != high)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }

    if (start <= low && end >= high)
        return sTree[i];

    int mid = low + (high - low) / 2;
    return query(start, end, low, mid, sTree, lazy, 2 * i + 1) +
           query(start, end, mid + 1, high, sTree, lazy, 2 * i + 2);
}

//done
void update(int start, int end, int segTree[], int lazy[], int low, int high, int i, int inc)
{
    if (start > high || end < low)
        return;

    if (lazy[i])
    {
        segTree[i] += (high - low + 1) * lazy[i];
        if (low != high)
        {
            lazy[2 * i + 1] += lazy[i];
            lazy[2 * i + 2] += lazy[i];
        }
        lazy[i] = 0;
    }

    if (start >= low && end <= high)
    {
        segTree[i] += (high - low + 1) * inc;
        if (low != high)
        {
            lazy[2 * i + 1] += inc;
            lazy[2 * i + 2] += inc;
        }
        return;
    }
    int mid = low + (high - low) / 2;
    update(start, end, segTree, lazy, low, mid, 2 * i + 1, inc);
    update(start, end, segTree, lazy, mid + 1, high, 2 * i + 2, inc);
    segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int segSize = sizeOfSegTree(n);

    int segTree[segSize] = {0};
    int lazy[segSize] = {0};

    constructSegTree(arr, lazy, segTree, 0, n - 1, 0);

    cout << query(0, n - 2, 0, n - 1, segTree, lazy, 0) << "\n";
    update(0, n - 1, segTree, lazy, 0, n - 1, 0, 5);

    cout << query(0, n - 2, 0, n - 1, segTree, lazy, 0);

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void buildTree(vector<int>& arr, int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, start, mid, 2 * node + 1);
            buildTree(arr, mid + 1, end, 2 * node + 2);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int querySum(int start, int end, int l, int r, int node) {
        if (r < start || l > end) {
            return 0;
        }
        if (l <= start && r >= end) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int leftSum = querySum(start, mid, l, r, 2 * node + 1);
        int rightSum = querySum(mid + 1, end, l, r, 2 * node + 2);
        return leftSum + rightSum;
    }

    void updateTree(int start, int end, int idx, int value, int node) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateTree(start, mid, idx, value, 2 * node + 1);
            } else {
                updateTree(mid + 1, end, idx, value, 2 * node + 2);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(arr, 0, n - 1, 0);
    }

    int querySum(int l, int r) {
        return querySum(0, n - 1, l, r, 0);
    }

    void update(int idx, int value) {
        updateTree(0, n - 1, idx, value, 0);
    }
};

int main() {
    int N, Q;
    cout << "Enter the size of the array: ";
    cin >> N;
    vector<int> arr(N);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    cout << "Enter the number of queries: ";
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int type;
        cout << "Enter query type (1 for sum, 2 for update): ";
        cin >> type;
        if (type == 1) {
            int l, r;
            cout << "Enter the range [l, r]: ";
            cin >> l >> r;
            cout << "Sum of range [" << l << ", " << r << "] is " << segTree.querySum(l, r) << endl;
        } else if (type == 2) {
            int idx, value;
            cout << "Enter the index and new value: ";
            cin >> idx >> value;
            segTree.update(idx, value);
            cout << "Updated index " << idx << " to " << value << endl;
        }
    }

    return 0;
}

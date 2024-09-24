<<<<<<< HEAD
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
=======
//this solution is wrong
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return 0;
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_sum = query(2 * node, start, mid, L, R);
        int right_sum = query(2 * node + 1, mid + 1, end, L, R);
        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    int query(int L, int R) {
        return query(1, 0, n - 1, L, R);
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }
    SegmentTree segTree(arr);
    while (Q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            segTree.update(idx, val);
        } else if (type == 2) {
            int L, R;
            cin >> L >> R;
            cout << segTree.query(L, R) << endl;
        }
    }
    return 0;
}
>>>>>>> d58ef679970717060f17e792b78f41bc06682387

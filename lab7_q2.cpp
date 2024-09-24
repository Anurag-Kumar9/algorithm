#include <iostream>
#include <set>
using namespace std;

class IntervalTree {
private:
    set<pair<int, int>> intervals;

public:
    // Add an interval [L, R]
    void addInterval(int L, int R) {
        intervals.insert({L, R});
    }

    // Remove an interval [L, R]
    void removeInterval(int L, int R) {
        intervals.erase({L, R});
    }

    // Check if an interval [L, R] overlaps with any existing interval
    bool isOverlapping(int L, int R) {
        auto it = intervals.lower_bound({L, R});
        if (it != intervals.end() && it->first <= R) {
            return true;
        }
        if (it != intervals.begin() && prev(it)->second >= L) {
            return true;
        }
        return false;
    }
};

int main() {
    IntervalTree tree;
    tree.addInterval(1, 5);
    tree.addInterval(10, 15);
    tree.addInterval(20, 25);

    cout << "Is [3, 7] overlapping? " << (tree.isOverlapping(3, 7) ? "Yes" : "No") << endl;
    cout << "Is [16, 19] overlapping? " << (tree.isOverlapping(16, 19) ? "Yes" : "No") << endl;

    tree.removeInterval(10, 15);
    cout << "Is [12, 14] overlapping after removal? " << (tree.isOverlapping(12, 14) ? "Yes" : "No") << endl;

    return 0;
}
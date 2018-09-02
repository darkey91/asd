#include <iostream>

using namespace std;

class Tree {
    int from;
    int to;
    bool isUpdated = false;
    long long maxHeight = 0;
    long long height = 0;
    long long sum = 0;
    Tree *leftChild, *rightChild;

public:
    Tree(int from, int to) {
        this->from = from;
        this->to = to;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    void updateData(long long new_height) {
        isUpdated = true;
        height = new_height;
        maxHeight = sum = (to - from + 1) * new_height;
    }

    void makeChildren() {
        int m = (from + to) >> 1;
        if (leftChild == nullptr)
            leftChild = new Tree(from, m);
        if (rightChild == nullptr)
            rightChild = new Tree(m + 1, to);
    }

    void push() {
        makeChildren();
        if (isUpdated) {
            leftChild->updateData(height);
            rightChild->updateData(height);
            isUpdated = false;
        }
    }

    void update(int l, int r, int new_h) {

        if (l > to || from > r) {
            return;
        }

        if (from >= l && r >= to) {
            updateData(new_h);
            return;
        }

        push();
        leftChild->update(l, r, new_h);
        rightChild->update(l, r, new_h);
        sum = leftChild->sum + rightChild->sum;
        maxHeight = max(leftChild->maxHeight, leftChild->sum + rightChild->maxHeight);
    }

    long long get(long long h) {
        if (to == from) {
            if (maxHeight <= h) {
                return to ;
            }
            else {
                return to - 1;
            }

        } else {
            push();
            if (leftChild->maxHeight > h) {
                return leftChild->get(h);
            } else {
                return rightChild->get(h - leftChild->sum);
            }
        }
    }


};

int main() {
    int n;
    cin >> n;
    char w;

    Tree t(1, n);
    do {
        cin >> w;
        switch (w) {
            case 'Q' : {
                int h;
                cin >> h;
                long long ans = t.get(h);
                cout << ans << "\n";
                break;
            }
            case 'I': {
                int a, b, d;
                cin >> a >> b >> d;
                t.update(a, b, d);
                break;
            }
        }


   } while (w != 'E');

    return 0;
}
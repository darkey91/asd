#include <iostream>
#include <climits>

using std::cin;
using std::cout;


class Treap {
    struct Node {
        long long key;
        long long priority;
        long long sum;

        Node *left, *right;

        Node(long long key, Node *l = nullptr, Node *r = nullptr) {
            this->key = key;
            sum = key;
            priority = (INT_MIN + 10) + rand() % (INT_MAX - 18);
            left = l;
            right = r;
        }
    };

    Node *root = nullptr;

private:
    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;

        if (l->priority > r->priority) {
            l->right = merge(l->right, r);
            fixSum(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            fixSum(r);
            return r;
        }
    }

    void split(Node *node, long long key, Node *&l, Node *&r) {
        if (node == nullptr) {
            l = r = nullptr;
            return;
        }

        if (key > node->key) {
            split(node->right, key, node->right, r);
            l = node;
            fixSum(l);
        } else {
            split(node->left, key, l, node->left);
            r = node;
            fixSum(r);
        }
    }

    long long getSum(Node *node) {
        return (node ? node->sum : 0);
    }

    void fixSum(Node *node) {
        if (node)
            node->sum = node->key + getSum(node->left) + getSum(node->right);
    }

    bool exists(Node *node, long long key) {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) return true;

        if (node->key < key) {
            return exists(node->right, key);
        } else {
            return exists(node->left, key);
        }
    }

    void printTreap(Node *p, long long level) {
        if (p) {
            printTreap(p->left, level + 1);
            for (long long i = 0; i < level; i++) std::cout << " ";
            std::cout << "(" << p->key << "," << p->sum << ")" << std::endl;
            printTreap(p->right, level + 1);
        }
    }


public:
    void insert(long long key) {
        if (!exists(root, key)) {
            Node *l, *r;
            l = r = nullptr;
            split(root, key, l, r);
            root = merge(merge(l, new Node(key)), r);
            fixSum(root);
        }
    }

    long long getSum(long long l, long long r) {
        Node *q, *w, *e;
        q = w = e = nullptr;
        long long ans;
        split(root, l, q, w);
        split(w, r + 1, w, e);
        ans = getSum(w);
        root = merge(merge(q, w), e);
        return ans;
    }

    void split(long long key) {
        Node *l, *r;
        split(root, key, l, r);
        cout << "Split key = " << key << std::endl;
        cout << "1st tree: \n";
        printTreap(l, 0);
        cout << "\n2d tree: \n";
        printTreap(r, 0);
    }

    void printTreap() {
        printTreap(root, 0);
    }

};

int main() {
    Treap tree;
    long long n, x, l, r, y;
    cin >> n;
    char q, prev = '+';

    for (long long i = 0; i < n; ++i) {
        cin >> q;
        switch(q) {
            case '+' : {
                cin >> x;
                if (prev == '?') {
                    x  = (x + y) % 1000000000;
                }
                tree.insert(x);
                break;
            }
            case '?' :{
                cin >> l >> r;
                y = tree.getSum(l, r);
                cout << y << "\n";
                break;
            }
        }
        prev = q;
    }

    return 0;

}

#include <string>
#include <iostream>
#include <climits>
#include <algorithm>

using std::max;
using std::cin;
using std::cout;

struct Node {
    int key;
    int prior;
    int sizeT;

    Node *left, *right;

    Node(int key, Node *l = nullptr, Node *r = nullptr) {
        this->key = key;
        this->sizeT = 1;
        this->prior = (INT_MIN + 5) + rand() % (INT_MAX - 10);
        left = l;
        right = r;
    }
};

class Treap {
    Node *root = nullptr;

private:
    void split(Node *root, int key, Node *&tree1, Node *&tree2) {
        if (root == nullptr) {
            tree1 = tree2 = nullptr;
            return;
        }

        if (root->key < key) {
            split(root->right, key, root->right, tree2);
            tree1 = root;
            fixSize(tree1);
        } else {
            split(root->left, key, tree1, root->left);
            tree2 = root;
            fixSize(tree2);
        }
    }

    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;

        if (l->prior > r->prior) {
            l->right = merge(l->right, r);
            fixSize(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            fixSize(r);
            return r;
        }
    }



    bool exists(Node *root, int x) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == x) {
            return true;
        } else if (root->key > x) {
            return exists(root->left, x);
        } else if (root->key < x) {
            return exists(root->right, x);
        }
    }
    Node *kTh(Node *node, int k) {
        if (k <= getSize(node->left)) {
            return kTh(node->left, k);
        } else {
            if (k == 1 + getSize(node->left)) {
                return node;
            }
            return kTh(node->right,k - getSize(node->left) - 1);
        }
    }

    int getKey(Node *node) {
        return (node ? node->key : INT_MIN);
    }

    void fixSize(Node *node) {
        node->sizeT = getSize(node->left) + getSize(node->right) + 1;
    }

    void printTreap(Node *p, int level) {
        if (p) {
            printTreap(p->left, level + 1);
            for (int i = 0; i < level; i++) std::cout << " ";
            std::cout << p->key << std::endl;
            printTreap(p->right, level + 1);
        }
    }

public:
    int getSize(Node *node) {
        return (node ? node->sizeT : 0);
    }
    void remove(int key) {
        Node *t1, *t2, *t3;
        split(root, key, t1, t2);
        split(t2, key + 1, t2, t3);
        root = merge(t1, t3);
        delete (t2);
    }

    bool exists(int x) {
        return exists(root, x);
    }

    void insert(int key) {
        Node *l, *r;
        split(root, key, l, r);
        root = merge(merge(l, new Node(key)), r);

    }

    int kTh(int k) {
        k = getSize(root) - k + 1;
       return kTh(root, k)->key;
    }

    Node *prev(int x) {
        Node *cur = root;
        Node *prev = nullptr;

        while (cur != nullptr) {
            if (cur->key < x) {
                prev = cur;
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return prev;
    }

    Node *next(int x) {
        Node *cur = root;
        Node *n = nullptr;

        while (cur != nullptr) {
            if (cur->key > x) {
                n = cur;
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return n;
    }

    void printTreap() {
        printTreap(root, 0);
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
    int n, command, x;
    Treap tree;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> command >> x;

        switch (command) {
            case 1: {
                tree.insert(x);
                break;
            }
            case 0: {
                cout << tree.kTh(x) << "\n";
                break;
            }
            case -1 : {
                tree.remove(x);
                break;
            }
        }
    }

    return 0;
}
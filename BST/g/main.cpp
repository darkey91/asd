#include <iostream>
#include <climits>

struct Node {
    int data;
    int key;
    int p;


    Node *left, *right;

    Node(int data) {
        this->data = data;
        p = (INT_MIN + 15) + rand() % (INT_MAX - 19);
        key = 1;
        left = right = nullptr;
    }
};

class Treap {
    Node *root = nullptr;

    Node *merge(Node *l, Node *r) {
        if (!l || !r)
            return (l ? l : r);

        if (l->p > r->p) {
            l->right = merge(l->right, r);
            fixKey(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            fixKey(r);
            return r;
        }
    }

    void split(Node *node, int key, Node *&l, Node *&r) {
        if (node == nullptr) {
            l = r = nullptr;
            return;
        }

        if (getKey(node->left) < key) {
            split(node->right, key - getKey(node->left) - 1, node->right, r);
            l = node;
            fixKey(l);
        } else {
            split(node->left, key, l, node->left);
            r = node;
            fixKey(r);
        }
    }

    int getKey(Node *node) {
        return node ? node->key : 0;
    }

    void fixKey(Node *node) {
        node->key = getKey(node->left) + getKey(node->right) + 1;
    }

    void printTreap(Node *p, int level) {
        if (p) {
            printTreap(p->left, level + 1);
            //for (int i = 0; i < level; i++) std::cout << " ";
           // std::cout << "(" << p->data << "," << p->key << ")" << std::endl;
             std::cout << p->data <<" ";
            printTreap(p->right, level + 1);
        }
    }

public :
    void grow(int n) {
        for (int i = 1; i <= n; ++i) {
            root = merge(root, new Node(i));
        }
    }

    void printTree() {
        printTreap(root, 0);
    }

    void moveSeg(int l, int r) {
        Node *q, *w, *e, *t;
        q = w = e = nullptr;
        split(root, r , q, w);
        split(q, l - 1, e, t);
        root = merge(merge(t, e), w);
    }
};

int main() {
    Treap tree;
    int n, m;
    std::cin >> n >> m;
    tree.grow(n);
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        tree.moveSeg(l, r);
    }
    tree.printTree();

    return 0;

}
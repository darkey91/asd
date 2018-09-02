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
    Node *left, *right;

    Node(int key, Node *l = nullptr, Node *r = nullptr) {
        this->key = key;
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
        } else {
            split(root->left, key, tree1, root->left);
            tree2 = root;
        }
    }

    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;

        if (l->prior > r->prior) {
            l->right = merge(l->right, r);
            return l;
        } else {
            r->left = merge(l, r->left);
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

    void printTreap(Node *p, int level) {
        if (p) {
            printTreap(p->left, level + 1);
            for (int i = 0; i < level; i++) std::cout << "   ";
            std::cout << p->key << std::endl;
            printTreap(p->right, level + 1);
        }
    }

public:
    void remove(int key) {
        Node *t1, * t2, *t3;
        split(root, key, t1, t2);
        split(t2, key + 1, t2, t3);
        root = merge(t1, t3);
        delete(t2);
    }

    bool exists(int x) {
        return exists(root, x);
    }

    void insert(int key) {
        if (!exists(key)) {
            Node *l, *r;
            split(root, key, l, r);
            root = merge(merge(l, new Node(key)), r);
        }
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
    int x;
    std::string word;

    Treap tree;

    while (cin >> word >> x) {
        switch (word[0]) {
            case 'i': {
               tree.insert(x);
                break;
            }
            case 'e': {
                if (tree.exists(x)) {
                    cout << "true\n";
                } else {
                    cout << "false\n";
                }
                break;
            }
            case 'n': {
                Node *n = tree.next(x);
                if (n == nullptr) {
                    cout << "none\n";
                } else {
                    cout << n->key << "\n";
                }
                break;
            }
            case 'p': {
                Node *n = tree.prev(x);
                if (n == nullptr) {
                    cout << "none\n";
                } else {
                    cout << n->key << "\n";
                }
                break;
            }
            case 'd' : {
                tree.remove(x);
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
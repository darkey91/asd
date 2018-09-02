#include <iostream>
#include <climits>
#include <vector>

struct Node {
    int key;
    int p;
    int data;
    bool isZero;

    Node *left, *right;

    Node(int data = 0, bool isZero = true) {
        this->data = data;
        this->isZero = isZero;
        p = (rand() << 15) + rand();
        key = 1;
        left = right = nullptr;
    }
};

class Treap {
    Node *root = nullptr;
    int num = 0;

    Node *merge(Node *l, Node *r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;

        if (l->p > r->p) {
            l->right = merge(l->right, r);
            fixKey(l);
            fixZeroInf(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            fixKey(r);
            fixZeroInf(r);
            return r;
        }
    }

    void split(Node *node, int key, Node *&l, Node *&r) {
        if (!node) {
            l = r = nullptr;
            return;
        }
        if (getKey(node->left) < key) {
            split(node->right, key - getKey(node->left) - 1, node->right, r);
            l = node;
            fixKey(l);
            fixZeroInf(l);
        } else {
            split(node->left, key, l, node->left);
            r = node;
            fixKey(r);
            fixZeroInf(r);
        }
    }

    int getKey(Node *node) {
        return node ? node->key : 0;
    }

    void fixKey(Node *node) {
        node->key = getKey(node->left) + getKey(node->right) + 1;
    }

    void fixZeroInf(Node *node) {
        node->isZero = getZeroInf(node->left) || getZeroInf(node->right) || (node->data == 0);
    }

    bool getZeroInf(Node *node) {
        return node ? node->isZero : false;
    }

    Node *findEmptyNode(Node *node, int &ind) {
        Node *cur = node;
        ind = getKey(cur->left);

        while (getZeroInf(cur)) {
            if (cur->left != nullptr && getZeroInf(cur->left)) {
                cur = cur->left;
                ind = ind - getKey(cur->right) - 1;
            } else if (getData(cur) == 0) {
                break;
            } else {
                cur = cur->right;
                ind += 1 + getKey(cur->left);
            }
        }

        return cur;
    }

    int getData(Node *node) {
        return node ? node->data : -1;
    }

    void printTree(Node *node, int lvl) {
        if (node) {
            printTree(node->left, lvl + 1);
            std::cout << node->data << " ";
            printTree(node->right, lvl + 1);
        }
    }

    void arr(Node *node, std::vector<int> &a) {
        if (node) {
            arr(node->left, a);
            a.push_back(getData(node));
            arr(node->right, a);
        }
    }

    Node *remove(Node *r, int key) {
        Node *t1, *t2, *t3;
        split(r, key, t1, t2);
        split(t2, 1, t2, t3);
        r = merge(t1, t3);
        delete (t2);
        return r;
    }

public :
    void build(int n) {
        for (int i = 0; i < n; ++i) {
            root = merge(new Node, root);
        }
    }

    int size() {
        return getKey(root);
    }

    void insert(int ind) {
        Node *l, *r, *findZero;
        int jind;

        split(root, ind, l, r);
        findZero = findEmptyNode(r, jind);
        if (findZero != nullptr && findZero->data == 0) {
            r = remove(r, jind);
        }
        root = merge(merge(l, new Node(++num, false)), r);
    }

    void arr() {
        std::vector<int> ans;
        arr(root, ans);
        while(!ans.empty() && ans.back() == 0) {
            ans.pop_back();
        }


        std::cout << ans.size() << "\n";
        for (auto it : ans) {
            std::cout << it << " ";
        }

    }

    void printTree() {
        printTree(root, 0);
    }
};

int main() {
    int n, j, m;
    std::cin >> n >> m;
    Treap tree;
    tree.build(m);

    for (int i = 0; i < n; ++i) {
        std::cin >> j;
        tree.insert(j - 1);
    }

    tree.arr();
    return 0;
}


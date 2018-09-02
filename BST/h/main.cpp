#include <fstream>
#include <iostream>
#include <climits>

using std::cin;
using std::cout;

struct Node {
    int p;
    char let;
    int n;
    int k;
    int isChar;
    Node *left, *right;

    Node(char l, int n) {
        this->let = l;
        this->n = n;
        this->k = n;
        this->isChar = (1 << (let - 'a'));
        this->p = (INT_MIN + 372) + rand() % (INT_MAX - 199);
        left = right = nullptr;
    }
};

class Treap {
    Node *root = nullptr;

    int getIsChar(Node *node) {
        return node ? node->isChar : 0;
    }

    void fixCharOcc(Node *node) {
        int i = node->let - 'a';
        node->isChar = getIsChar(node->left) | getIsChar(node->right) | (1 << i);
    }

    int amountOfLet(Node *node) {
        int cnt = 0, tmp = node->isChar;

        while (tmp != 0) {
            cnt += (((1 & tmp) == 1));
            tmp >>= 1;
        }

        return cnt;
    }

    Node *find(Node *node, int k, int &dif) {
        if (node == nullptr || (getKey(node->left) <= k && k <= (getKey(node->left) + getN(node) - 1))) {

            if (node != nullptr) dif = k - getKey(node->left);
            return node;
        }

        if (k > getKey(node->left)) {
            return find(node->right, k - getKey(node->left) - getN(node), dif);
        } else {
            return find(node->left, k, dif);
        }


    }

    int getN(Node *node) {
        return node ? node->n : 0;
    }

    int getKey(Node *node) {
        return node ? node->k : 0;
    }

    void fixKey(Node *node) {
        node->k = getKey(node->left) + getKey(node->right) + getN(node);
    }

    Node *merge(Node *l, Node *r) {
        if (!l || !r)
            return (l ? l : r);

        if (l->p > r->p) {
            l->right = merge(l->right, r);
            fixKey(l);
            fixCharOcc(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            fixKey(r);
            fixCharOcc(r);
            return r;
        }
    }

    void split(Node *node, int key, Node *&l, Node *&r) {
        if (node == nullptr) {
            l = r = nullptr;
            return;
        }

        if (getKey(node->left) + getN(node) - 1 < key) {
            split(node->right, key - getKey(node->left) - getN(node), node->right, r);
            l = node;
            fixKey(l);
            fixCharOcc(l);
        } else {
            split(node->left, key, l, node->left);
            r = node;
            fixKey(r);
            fixCharOcc(r);
        }
    }

    void divideNode(int ind) {
        int dif = 0;
        Node *node = find(root, ind, dif);

        if (dif != 0) {
            Node *t1, *t2, *t3;
            split(root, ind, t1, t2);
            split(t2, ind - getKey(t1) + getN(t2), t2, t3);
            Node *new_node = new Node(node->let, node->n - dif);
            new_node = merge(new_node, t3);
            t2->n = dif;
            fixKey(t2);
            fixCharOcc(t2);
            t2 = merge(t1, t2);
            root = merge(t2, new_node);
        }
    }



    void printTreap(Node *p, int level) {
        if (p) {
            printTreap(p->left, level + 1);
            //for (int i = 0; i < level; i++) std::cout << " ";
            // std::cout << "(" << p->data << "," << p->key << ")" << std::endl;
            for (int i = 0; i < p->n; ++i)
                std::cout << p->let << " ";
            printTreap(p->right, level + 1);
        }
    }

public :
    int query(int a, int b) {
        divideNode(a);
        divideNode(b + 1);
        Node *l, *m, *r;
        split(root, a, l, m);
        split(m, b + 1, m, r);
        int y = amountOfLet(m);
        root = merge(merge(l, m), r);
        return y;
    }

    void insert(char let, int n, int ind) {
        int dif = 0;
        Node *node = find(root, ind, dif);
        Node *t1, *t2, *t3;


        if (dif == 0) {
            split(root, ind, t1, t2);
            root = merge(merge(t1, new Node(let, n)), t2);
        } else {
            split(root, ind, t1, t2);
            split(t2, ind - getKey(t1) + getN(t2), t2, t3);
            if (t2->let != let) {
                Node *new_node = new Node(node->let, node->n - dif);
                new_node = merge(new_node, t3);
                t2->n = dif;
                fixKey(t2);
                fixCharOcc(t2);
                t2 = merge(t1, t2);
                root = merge(merge(t2, new Node(let, n)), new_node);
            } else {
                t2->n = t2->k = t2->n + n;
                root = merge(merge(t1, t2), t3);
            }
        }
    }

    void remove(int a, int b) {
        divideNode(a);
        divideNode(b + 1);
        Node *l, *m, *r;
        split(root, a, l, m);
        split(m, b + 1, m, r);
        root = merge(l, r);
    }
    void printTree() {
        printTreap(root, 0);
    }
};

int main() {

    /*
    std::ifstream in("log.in");
    std::ofstream out("log.out");
*/
    int n;
    cin >> n;
    char c;
    Treap tree;

    for (int i = 0; i < n; ++i) {
       cin >> c;
        switch (c) {
            case '+' : {
                int ind, num;
                char let;
                cin >> ind >> num >> let;
                tree.insert(let, num, ind - 1);
                tree.printTree();
                std::cout << std::endl;
                break;
            }
            case '?': {
                int a, b;
                cin >> a >> b;
                cout << tree.query(a - 1, b - 1) << std::endl;
                break;
            }
            case '-' : {
                int a, b;
                cin >> a >> b;
                tree.remove(a - 1, b - 1);
                tree.printTree();
                break;
            }
        }
    }
}

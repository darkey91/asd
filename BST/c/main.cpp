#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

struct ans {
    int p = 0;
    int l = 0;
    int r = 0;
};

ans answer[300005];

struct Node {
    int a;
    int b;
    int index;
    Node *parent, *left, *right;

    Node(int a, int b, int ind) {
        this->a = a;
        this->b = b;
        index = ind;
        parent = left = right = nullptr;
    }

};

struct data {
    int a, b, num;
};

bool cmp(data q, data w) {
    return (q.a < w.a);
}

int ind(Node *node) {
    return (node ? node->index : 0);
}

void build(Node *&root, const std::vector<data> &d) {
    Node *last = new Node(d[0].a, d[0].b, d[0].num);

    for (int i = 1; i < d.size(); ++i) {
        while (last->parent != nullptr && d[i].b < last->b) {
            last = last->parent;
        }
        Node *tmp = new Node(d[i].a, d[i].b, d[i].num);

        if (d[i].b >= last->b) {
            tmp->left = last->right;
            tmp->parent = last;
            answer[ind(tmp)].l = ind(last->right);
            answer[ind(tmp)].p = ind(last);

            if (last->right) {
                last->right->parent = tmp;
                answer[(ind(last->right))].p = ind(tmp);
            }
            last->right = tmp;
            answer[ind(last)].r = ind(tmp);
        } else {
            tmp->parent = nullptr;
            tmp->left = last;
            answer[ind(tmp)].l = ind(last);
            last->parent = tmp;
            answer[ind(last)].p = ind(tmp);
            root = tmp;
        }
        last = tmp;

    }
}

int main() {
    int n, a, b;
    std::cin >> n;
    std::vector<data> d(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> a >> b;
        d[i].a = a;
        d[i].b = b;
        d[i].num = i + 1;
    }

    std::sort(d.begin(), d.end(), cmp);
    Node *tree;
    build(tree, d);

    std::cout << "YES\n";

    for (int i = 1; i <= n; ++i) {
        std::cout << answer[i].p <<" " << answer[i].l <<" " << answer[i].r <<"\n";
    }

    return 0;
}
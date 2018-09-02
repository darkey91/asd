#include <algorithm>
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Node {
    int key;
    Node *leftChild, *rightChild;
    int height = 1;

    Node(int data) {
        key = data;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

int height(Node *root) {
    return (root ? root->height : 0);
}

int difBalance(Node *root) {
    return height(root->rightChild) - height(root->leftChild);
}

void fixH(Node *ver) {
    int leftH = height(ver->leftChild);
    int rightH = height(ver->rightChild);
    ver->height = (leftH > rightH ? leftH : rightH) + 1;
}

Node *rotateR(Node *ver) {
    Node *temp = ver->leftChild;
    ver->leftChild = temp->rightChild;
    temp->rightChild = ver;
    fixH(ver);
    fixH(temp);
    return temp;
}

Node *rotateL(Node *ver) {
    Node *temp = ver->rightChild;
    ver->rightChild = temp->leftChild;
    temp->leftChild = ver;
    fixH(ver);
    fixH(temp);
    return temp;
}

Node *balance(Node *ver) {
    fixH(ver);
    if (difBalance(ver) == 2) {
        if (difBalance(ver->rightChild) < 0) {
            ver->rightChild = rotateR(ver->rightChild);
        }
        return rotateL(ver);
    } else if (difBalance(ver) == -2) {
        if (difBalance(ver->leftChild) > 0) {
            ver->leftChild = rotateL(ver->leftChild);
        }
        return rotateR(ver);
    }
    else return ver;
}

Node *insert(Node *root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }

    if (root->key > data) {
        root->leftChild = insert(root->leftChild, data);
    } else if (root->key < data) {
        root->rightChild = insert(root->rightChild, data);
    }
    return balance(root);
}

bool exists(Node *root, int x) {
    if (root == nullptr) {
        return false;
    }
    if (root->key == x) {
        return true;
    } else if (root->key > x) {
        return exists(root->leftChild, x);
    } else if (root->key < x) {
        return exists(root->rightChild, x);
    }
}

Node *prev(Node *root, int x) {
    Node *cur = root;
    Node *prev = nullptr;

    while (cur != nullptr) {
        if (cur->key < x) {
            prev = cur;
            cur = cur->rightChild;
        } else {
            cur = cur->leftChild;
        }
    }
    return prev;
}

Node *next(Node *root, int x) {
    Node *cur = root;
    Node *n = nullptr;

    while (cur != nullptr) {
        if (cur->key > x) {
            n = cur;
            cur = cur->leftChild;
        } else {
            cur = cur->rightChild;
        }
    }
    return n;
}

Node *minimumKey(Node *root) {
    Node *cur = root;

    while (cur->leftChild != nullptr) {
        cur = cur->leftChild;
    }
    return cur;
}

Node *remove(Node *root, int x) {
    if (root == nullptr) {
        return nullptr;
    }

    if (x < root->key) {
        root->leftChild = remove(root->leftChild, x);
    } else if (x > root->key) {
        root->rightChild = remove(root->rightChild, x);
    } else if (root->leftChild != nullptr && root->rightChild != nullptr) {
        root->key = minimumKey(root->rightChild)->key;
        root->rightChild = remove(root->rightChild, root->key);
    } else {
        Node *temp = root;
        if (root->leftChild != nullptr) {
            root = root->leftChild;
        } else {
            root = root->rightChild;
        }
        delete temp;
    }
    return root;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    Node *tree = nullptr;
    int x;
    string word;

    while (cin >> word >> x) {
        switch (word[0]) {
            case 'i': {
                    tree = insert(tree, x);

                break;
            }
            case 'e': {
                if (exists(tree, x)) {
                    cout << "true\n";
                } else {
                    cout << "false\n";
                }
                break;
            }
            case 'n': {
                Node *n = next(tree, x);
                if (n == nullptr) {
                    cout << "none\n";
                } else {
                    cout << n->key << "\n";
                }
                break;
            }
            case 'p': {
                Node *n = prev(tree, x);
                if (n == nullptr) {
                    cout << "none\n";
                } else {
                    cout << n->key << "\n";
                }
                break;
            }
            case 'd' : {
                tree = remove(tree, x);
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
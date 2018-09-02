/*
#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::string;

struct Node {
    int key;
    Node *leftChild, *rightChild;
    Node *parent;

    explicit Node(int data) {
        key = data;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    Node *createNode(int data) {
        return new Node(data);
    }

};

class BST {


private:
    Node *insert(Node *v, int data) {
        if (v == nullptr) {
            return new Node(data);
        }
        if (v->key > data) {
            v->leftChild = insert(v->leftChild, data);
        } else {
            v->rightChild = insert(v->rightChild, data);
        }
    }

    Node *find(Node *v, int key) {
        if (v == nullptr || v->key == key) {
            return v;
        }

        if (key < v->key) {
            find(v->leftChild, key);
        } else {
            find(v->rightChild, key);
        }
    }

public:
    Node *root;
    BST(){
        root = nullptr;
    };
    bool exists(int data) {
        Node *tmp = find(root, data);
        if (tmp == nullptr) {
            return false;
        }
        return tmp->key == data;
    }

    void prev(int x) {
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

        if (prev == nullptr) {
            printf("none\n");
        } else {
            printf("%d\n", prev->key);
        };
    }

    Node *next(int x) {
        Node *cur = root;
        Node *next = nullptr;

        while (cur != nullptr) {
            if (cur->key > x) {
                next = cur;
                cur = cur->leftChild;
            } else {
                cur = cur->rightChild;
            }
        }

        return next;
    }

    Node *minimumKey(Node *start) {
        Node *v = start;
        while (v->leftChild != nullptr) {
            v = v->leftChild;
        }
        return v;
    }

    void insert(int data) {
        if (root == nullptr) {
            root = insert(root, data);
        } else {
            insert(root, data);
        }
    }
    void del(int x) {
        //  Node *tmp = find(root, x);
        remove(root, x);
        // delete (tmp);
    }

};


*/
/*

#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>


struct Node {
    int key;
    Node *leftChild, *rightChild;
    Node *parent;

    explicit Node(int data) {
        key = data;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    Node *createNode(int data) {
        return new Node(data);
    }

};


void inorderTraversal(Node *v) {
    if (v != nullptr) {
        inorderTraversal(v->leftChild);
        printf("%d ", v->key);
        inorderTraversal(v->rightChild);
    }
}


*//*

int main() {
    BST tree;

    int x;
    string word;

    while (cin >> word >> x) {
        switch (word[0]) {
            case 'i': {
                tree.insert(x);
                break;
            }
            case 'e': {
                if (tree.exists(x)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            }
            case 'n': {
                Node *n = tree.next(x);
                if (n == nullptr) {
                    printf("none\n");
                } else {
                    printf("%d\n", n->key);
                }
                break;
            }
            case 'p': {
                tree.prev(x);
                break;
            }
            case 'd' : {
                tree.del(x);
                break;
            }
            default:
                break;
        }
    }

*/
/*


    void insert(Node *root, int data) {
        if (root == nullptr) {
            root = new Node(data);
            root->parent = root;
        } else {
            insert(root, data);
        }
    }
    *//*

*/
/*
Node *insert(Node *v, int data) {
    Node *new_node = new Node(data);

    while (v != nullptr) {
        if (new_node->key > v->key) {
            if (v->rightChild != nullptr)
                v = v->rightChild;
            else {
                new_node->parent = v;
                v->rightChild = new_node;
                break;
            }
        } else if (new_node->key < v->key) {
            if (v->leftChild != nullptr)
                v = v->leftChild;
            else {
                new_node->parent = v;
                v->leftChild = new_node;
                break;
            }
        }
    }


}
*//*

*/
/*
    Node *remove(Node *v, int x) {
        Node *toDel = find(root, x);
        bool wasRoot = (root == toDel);
        Node *p = toDel->parent;

        if (toDel->leftChild == nullptr && toDel->rightChild == nullptr) {
            if (p->leftChild == toDel) {
                p->leftChild = nullptr;
            }
            if (p->rightChild == toDel) {
                p->rightChild = nullptr;
            }
            if(wasRoot)
                root = nullptr;

            delete (toDel);
        } else if(toDel->leftChild == nullptr || toDel->rightChild == nullptr) {
            if (toDel->leftChild == nullptr) {
                if (p->leftChild == toDel) {
                    p->leftChild = toDel->rightChild;
                } else {
                    p->rightChild = toDel->rightChild;
                }
                toDel->rightChild->parent = p;
            } else {
                if (p->leftChild == toDel) {
                    p->leftChild = toDel->leftChild;
                } else {
                    p->rightChild = toDel->leftChild;
                }
                toDel->leftChild->parent = p;
            }
            delete (toDel);
        } else {
            Node *n = next(toDel->key);
            toDel->key = n->key;
            if(n->parent->leftChild == n) {
                n->parent->leftChild = n->rightChild;
                if(n->rightChild != nullptr) {
                    n->rightChild->parent = n->parent;
                }
            } else {
                n->parent->rightChild = n->rightChild;
                if (n->rightChild != nullptr) {
                    n->rightChild->parent = n->parent;
                }
            }
            delete (n);
        }
        *//*


*/
/*
if (v == nullptr) {
    return v;
}

if (x < v->key) {
    v->leftChild = remove(v->leftChild, x);
} else if (x > v->key) {
    v->rightChild = remove(v->rightChild, x);
} else if (v->leftChild != nullptr && v->rightChild != nullptr) {
    v->key = minimumKey(v->rightChild)->key;
    v->rightChild = remove(v->rightChild, v->key);
} else {
    if (v->leftChild != nullptr) {
        v = v->leftChild;
    } else {
        v = v->rightChild;
    }
}
return v;
}
 *//*

*/
/*

*//*



    */
/*
   tree.insert(8);
   tree.insert(10);
   tree.insert(3);
   tree.insert(1);
   tree.insert(6);
   tree.insert(4);
   tree.insert(7);
   tree.insert(14);
   tree.insert(13);

   tree.inorderTraversal();

   printf("\nNEXT: \n");

   tree.del(7);
   tree.inorderTraversal();


   for (int i = 0; i <= 14; ++i) {
       printf("\n %d: %d", i, tree.exists(i));
   }

   printf("\nNEXT: \n");
   for (int i = 0; i <= 14; ++i) {
       printf("%d :", i);
        tree.next(i);
   }
   printf("\nPREV: \n");
   for (int i = 0; i <= 14; ++i) {
       printf("%d :", i);
       tree.prev(i);
   }

   tree.del(8);
*//*

    return 0;
}*/

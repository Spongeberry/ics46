#include "bstree.h"

/*
Node * root;
const string name;
int count;

*/

Node * BSTree::insert_node(Node * t, string key) {
    if (!t)
        t = new Node(key, nullptr, nullptr);
    Node* temp = t;
    while(temp->key != key)
        if(key < temp->key){
            if(temp->left == nullptr)
                temp->left = new Node(key, nullptr, nullptr);
            temp = temp->left;
        }else if(key > temp->key){
            if(temp->right == nullptr)
                temp->right = new Node(key, nullptr, nullptr);
            temp = temp->right;}
    return t;
}

Node * BSTree::find_node(Node * t, string key) {
    if (t == nullptr) {
        return nullptr;
    }
    if (key < t->key) {
        return find_node(t->left, key);
    } else if (key > t->key) {
        return find_node(t->right, key);
    }
    return t;
}

Node * BSTree::left_most(Node * t) {
    while (t && t->left != nullptr) {
        t = t->left;
    }
    return t;
}

Node * BSTree::delete_node(Node * t, string key) {
    if (!t) return t;
    if (key < t->key)
        t->left = delete_node(t->left, key);
    else if (key > t->key)
        t->right = delete_node(t->right, key);
    else { // delete node t
        // Case 1: Node has one or no child
        if (t->left == nullptr || t->right == nullptr) {
            Node * child = t->left ? t->left : t->right;
            // No child case
            if (child == nullptr) {
                child = t;
                t = nullptr;
            } else { // One child case
                *t = *child; // copy data up from child
            }
            delete child;
        }
        else {
            Node * succ = left_most(t->right);
            swap(t->key, succ->key);
            t->right = delete_node(t->right, key);
        }
    }
    return t;
}


int BSTree::compute_height(Node * t) {
    if (t == nullptr) {
        return 0;
    }
    return 1 + max(compute_height(t->left), compute_height(t->right));
}

BSTree::BSTree():BST("BST"){}

void BSTree::insert(const string & key){
    root = insert_node(root, key);
    ++count;
}

bool BSTree::find(const string & key) const {
    return find_node(root, key) != nullptr;
}

void BSTree::remove(const string & key) {
    root = delete_node(root, key);
    count--;
}

bool BSTree::is_empty() const {
    return root == nullptr;
}

int BSTree::get_height() const {
    return compute_height(root);
}


#include "avltree.h"

int AVLTree::get_height(Node * node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::get_balance(Node * node) {
    if (node == nullptr)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::set_height(Node * node) {
    if (node != nullptr) {
        node->height = (max(get_height(node->right), get_height(node->left)) + 1);
    }
}

Node * AVLTree::right_rotate(Node * y) {
    Node * x = y->left;
    Node * T = x->right;
    x->right = y;
    y->left = T;
    set_height(y);
    set_height(x);
    return x;
}

Node * AVLTree::left_rotate(Node * x) {
    Node * y = x->right;
    Node * T = y->left;
    y->left = x;
    x->right = T;
    set_height(x);
    set_height(y);
    return y;
}

Node * AVLTree::rebalance(Node * t) {
    set_height(t);
    int balance = get_balance(t);
    if ( balance > 1 ) {
        if ( get_balance(t->left) < 0 )
            t->left = left_rotate(t->left);
        return right_rotate(t);
    } else if ( balance < -1 ) {
        if ( get_balance(t->right ) > 0)
            t->right = right_rotate(t->right);
        return left_rotate(t);
    }
    return t;
}

Node * AVLTree::insert_node(Node * t, string key){
        if (t == nullptr) {
        return new Node(key, nullptr, nullptr);
    }

    if (key < t->key) {
        t->left = insert_node(t->left, key);
    } else if (key > t->key) {
        t->right = insert_node(t->right, key);
    } else {
        // Equal keys are not allowed in AVL tree
        return t;
    }
    return AVLTree::rebalance(t);
}

Node * AVLTree::find_node(Node * t, string key){
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

Node * AVLTree::delete_node(Node * t, string key){
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
            Node * succ = AVLTree::left_most(t->right);
            swap(t->key, succ->key);
            t->right = delete_node(t->right, key);
        }
    }
    return AVLTree::rebalance(t);
}

AVLTree::AVLTree():BST("AVL"){}

void AVLTree::insert(const string &key) {
    root = insert_node(root, key);
    count += 1;
}

bool AVLTree::find(const string &key) const {
    return find_node(root, key) != nullptr;
}

void AVLTree::remove(const string &key) {
    root = delete_node(root, key);
    count -= 1;
}

bool AVLTree::is_empty() const {
    return root == nullptr;
}

int AVLTree::get_height() const {
    return AVLTree::get_height(root);
}

Node * AVLTree::left_most(Node * t) {
    while (t && t->left != nullptr) {
        t = t->left;
    }
    return t;
}

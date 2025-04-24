// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr; 
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root); 
    root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) {
        return; 
    } 
    clear(n->left); 
    clear(n->right); 
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(root == nullptr) {
        root = new Node(); 
        root->info = value;
        root->parent = nullptr;
    }
    return insert(value, root); 
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(n->info == value) {
        return false;
    }
    if(n->right == nullptr && value > n->info) {
        Node* insert = new Node();
        n->right = insert; 
        insert->parent = n; 
        insert->info = value; 
        return true; 
    } else if(n->left == nullptr && value < n->info) {
        Node* insert = new Node();
        n->left = insert; 
        insert->parent = n; 
        insert->info = value; 
        return true; 
    }
    if(value > n->info) {
        insert(value, n->right); 
    } else {
        insert(value, n->left);
    }
    return true; 
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root); // IMPLEMENT HERE
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n == nullptr) {
        return; 
    }
    cout << n->info << " "; 
    printPreOrder(n->left); // IMPLEMENT HERE
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root); // IMPLEMENT HERE
}
void IntBST::printInOrder(Node *n) const {
    if(n == nullptr) {
        return; 
    }
    printInOrder(n->left); // IMPLEMENT HERE
    cout << n->info << " "; 
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root); 
}

void IntBST::printPostOrder(Node *n) const {
    if(n == nullptr) {
        return; 
    }
    printPostOrder(n->left);
    printPostOrder(n->right); // IMPLEMENT HERE
    cout << n->info << " "; 
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n == nullptr) {
        return 0; 
    }
    return n->info + sum(n->left) + sum(n->right); 
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n == nullptr) {
        return 0; 
    }
    return 1 + count(n->left) + count(n->right); 
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(n == nullptr || value == n->info) {
        return n; 
    } else if(value > n->info) {
        return getNodeFor(value, n->right); 
    } else if(value < n->info) {
        return getNodeFor(value, n->left); 
    }
    return nullptr; 
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value, root) == nullptr) {
        return false; 
    } else {
        return true; 
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    IntBST::Node* loc = getNodeFor(value, root); 
    if(loc == nullptr) {
        return nullptr; 
    }
    if(loc->left != nullptr) {
        loc = loc->left; 
        while(loc->right != nullptr) {
            loc = loc->right; 
        } 
        return loc; 
    } else {
        if(loc->parent == nullptr) {
            return nullptr; 
        }
        while(loc->parent != nullptr) {
            IntBST::Node*  parent = loc->parent; 
            if(parent->left != nullptr) {
                if(parent->left == loc) {
                    loc = parent; 
                } else {
                    return parent; 
                }
            } else {
                loc = parent; 
            }
        }
        return nullptr; 
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(getPredecessorNode(value) == nullptr) {
        return 0; 
    }
    return getPredecessorNode(value)->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    IntBST::Node* loc = getNodeFor(value, root); 
    if(loc == nullptr) {
        return nullptr; 
    }
    if(loc->right != nullptr) {
        loc = loc->right; 
        while(loc->left != nullptr) {
            loc = loc->left; 
        } 
        return loc; 
    } else {
        if(loc->parent == nullptr) {
            return nullptr; 
        }
        while(loc->parent != nullptr) {
            IntBST::Node*  parent = loc->parent; 
            if(parent->right != nullptr) {
                if(parent->right == loc) {
                    loc = parent; 
                } else {
                    return parent; 
                }
            } else {
                loc = parent; 
            }
        }
        return nullptr;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if(getSuccessorNode(value) == nullptr) {
        return 0; 
    }
    return getSuccessorNode(value)->info;
}


// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* target = getNodeFor(value, root);  
    if(target != nullptr) {
        if(target->left != nullptr) {
            Node* p = getPredecessorNode(target->info); 
            target->info = p->info; 
            if(p->right == nullptr && p->left == nullptr) {
                Node* parent = p->parent; 
                if(p == parent->left) {
                    delete parent->left; 
                    parent->left = nullptr; 
                } else if(p == parent->right) {
                    delete parent->right; 
                    parent->right = nullptr; 
                }
                return true; 
            } else {
                Node* temp = p->left; 
                p->info = temp->info;
                p->left = temp->left; 
                p->right = temp->right; 
                delete temp; 
                return true; 
            }
        } else if(target->right != nullptr) {
            Node* s = getSuccessorNode(target->info); 
            target->info = s->info; 
            Node* temp = s->right; 
            if(s->right == nullptr && s->left == nullptr) {
                Node* parent = s->parent; 
                if(s == parent->left) {
                    delete parent->left; 
                    parent->left = nullptr; 
                } else if(s == parent->right) {
                    delete parent->right; 
                    parent->right = nullptr; 
                }
                return true; 
            } else {
                s->info = temp->info; 
                s->left = temp->left; 
                s->right = temp->right; 
                delete temp; 
                return true; 
            }
        } else {
            Node* parent = target->parent; 
            if(target == root) {
                delete target; 
                root = nullptr;
            } else if(target == parent->left) {
                delete parent->left; 
                parent->left = nullptr; 
            } else if(target == parent->right) {
                delete parent->right; 
                parent->right = nullptr; 
            }
            return true; 
        }
    } else {
        return false;
    }
}

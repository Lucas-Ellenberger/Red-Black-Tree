//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for the Dictionary ADT
// Lucas Ellenberger
// lmellenb
// pa8
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>

#include"Dictionary.h"
#define BLACK -123
#define RED -975

using namespace std;

// Class Constructors & Destructors ----------------------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    color = RED;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = new Dictionary::Node("NIL", -999);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    this->nil = new Dictionary::Node("NIL", -999);
    this->nil->color = BLACK;
    this->root = this->nil;
    this->current = this->nil;
    this->num_pairs = 0;
    this->preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    this->postOrderDelete(this->root);
    delete this->nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return this->num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    return (this->search(this->root, k) != this->nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return (this->search(this->root, k))->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    return (this->current != this->nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return this->current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    // cerr << endl << "got to current val" << endl << endl;
    return this->current->val;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != this->nil) {
        if (R == nullptr || R->left == nullptr || R->right == nullptr) {
            // cerr << "about to segfault on key: " << R->key << endl;
            return;
        }
        this->inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += '\n';
        this->inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != this->nil) {
        s += R->key;
        s += '\n';
        this->preOrderString(s, R->left);
        this->preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != this->nil) {
        if (R != N) {
            this->setValue(R->key, R->val);
            this->preOrderCopy(R->left, N);
            this->preOrderCopy(R->right, N);
        }
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != this->nil) {
        this->postOrderDelete(R->left);
        this->postOrderDelete(R->right);
        Dictionary::Node* delete_this = R;
        R = this->nil;
        this->num_pairs--;
        delete delete_this;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == this->nil || R->key == k) {
        return R;
    } else if (k < R->key) {
        return this->search(R->left, k);
    } else {
        return this->search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    Dictionary::Node* curr = R;
    while (curr->left != this->nil) {
        curr = curr->left;
    }
    return curr;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    Dictionary::Node* curr = R;
    while (curr->right != this->nil) {
        curr = curr->right;
    }
    return curr;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    Dictionary::Node* next = N->right;
    if (next != this->nil) {
        next = this->findMin(next);
    }
    return next;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    Dictionary::Node* prev = N->left;
    if (prev != this->nil) {
        prev = this->findMax(prev);
    }
    return prev;
}

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    // set y
    Node * y = N->right; 

    // turn y's left subtree into x's right subtree
    N->right = y->left; 
    if (y->left != this->nil) {  // not necessary if using sentinal nil node
        y->left->parent = N;
    }
    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = y;
    }
    else if (N == N->parent->left) {
        N->parent->left = y;
    }
    else {
        N->parent->right = y;
    }
    // put x on y's left
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y
    Node * y = N->left; 

    // turn y's right subtree into x's left subtree
    N->left = y->right; 
    if (y->right != this->nil) {  // not necessary if using sentinal nil node
        y->right->parent = N;
    }
    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == this->nil) {
        this->root = y;
    }
    else if (N == N->parent->right) {
        N->parent->right = y;
    }
    else {
        N->parent->left = y;
    }
    // put x on y's right
    y->right = N; 
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    Node * y;
    while (N->parent->color == RED) {
        if (N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;
            if (y->color == RED) {
                N->parent->color = BLACK;             // case 1
                y->color = BLACK;                     // case 1
                N->parent->parent->color = RED;       // case 1
                N = N->parent->parent;                // case 1
            }
            else {
                if (N == N->parent->right) {
                    N = N->parent;                    // case 2
                    this->LeftRotate(N);              // case 2
                }
                N->parent->color = BLACK;             // case 3
                N->parent->parent->color = RED;       // case 3
                this->RightRotate(N->parent->parent); // case 3
            }
        }
        else {
            y = N->parent->parent->left;
            if (y->color == RED) {
                N->parent->color = BLACK;             // case 4
                y->color = BLACK;                     // case 4
                N->parent->parent->color = RED;       // case 4
                N = N->parent->parent;                // case 4
            } else { 
                if (N == N->parent->left) {
                    N = N->parent;                    // case 5
                    this->RightRotate(N);             // case 5
                }
                N->parent->color = BLACK;             // case 6
                N->parent->parent->color = RED;       // case 6
                this->LeftRotate(N->parent->parent);  // case 6
            }
        }
    }
    this->root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == this->nil) {
        this->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    Node * w;
    while (N != this->root && N->color == BLACK) {
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;                      // case 1
                N->parent->color = RED;                // case 1
                this->LeftRotate(N->parent);           // case 1
                w = N->parent->right;                  // case 1
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;                    // case 2
                    N = N->parent;                     // case 2
                }
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;             // case 3
                    w->color = RED;                     // case 3
                    this->RightRotate(w);               // case 3
                    w = N->parent->right;               // case 3
                }
                w->color = N->parent->color;            // case 4
                N->parent->color = BLACK;               // case 4
                w->right->color = BLACK;                // case 4
                this->LeftRotate(N->parent);            // case 4
                N = this->root;                         // case 4
            }
        }
        else {
            w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;                       // case 5
                N->parent->color = RED;                 // case 5
                this->RightRotate(N->parent);           // case 5
                w = N->parent->left;                    // case 5
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                         // case 6
                N = N->parent;                          // case 6
            } else { 
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;            // case 7
                    w->color = RED;                     // case 7
                    this->LeftRotate(w);                // case 7
                    w = N->parent->left;                // case 7
                }
                w->color = N->parent->color;            // case 8
                N->parent->color = BLACK;               // case 8
                w->left->color = BLACK;                 // case 8
                this->RightRotate(N->parent);           // case 8
                N = this->root;                         // case 8
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
// void Dictionary::RB_Delete(Node* N) {
// Logic inside remove() function
// }

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    this->postOrderDelete(this->root);
    this->root = this->nil;
    this->current = this->nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // cerr << endl << "got to set val" << endl << endl;
    Node * y = this->nil;
    Node * x = this->root;
    while (x != this->nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            return;
        }
        else if (k < x->key) {
            x = x->left;
        }
        else { 
            x = x->right;
        }
    }
    Dictionary::Node* add_this = new Dictionary::Node(k, v);
    add_this->left = this->nil;
    add_this->right = this->nil;
    add_this->color = RED;
    add_this->parent = y;
    this->num_pairs++;
    if (y == this->nil) {
        this->root = add_this;
    }
    else if (add_this->key < y->key) {
        y->left = add_this;
    }
    else {
        y->right = add_this;
    }
    this->RB_InsertFixUp(add_this);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    // cerr << endl << "got to remove" << endl << endl;
    Dictionary::Node* z = this->search(this->root, k);
    if (z == this->nil) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    if (z == this->current) {
        this->current = this->nil;
    }
    Node * y = z;
    Node * x;
    int y_original_color = y->color;
    if (z->left == this->nil) {
        x = z->right;
        this->RB_Transplant(z, z->right);
    } else if (z->right == this->nil) {
        x = z->left;
        this->RB_Transplant(z, z->left);
    } else {
        y = this->findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            this->RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        this->RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK) {
        this->RB_DeleteFixUp(x);
    }
    this->num_pairs--;
    delete z;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    // cerr << endl << "got to begin" << endl << endl;
    if (this->num_pairs) {
        this->current = this->findMin(this->root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (this->num_pairs) {
        this->current = this->findMax(this->root);  
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    if (this->current->right != this->nil) {
        this->current = this->findMin(this->current->right);
    } else {
        Dictionary::Node* curr_y = this->current->parent;
        while (curr_y != this->nil && this->current == curr_y->right) {
            this->current = curr_y;
            curr_y = curr_y->parent;
        }
        this->current = curr_y;
    } 
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if (this->current->left != this->nil) {
        this->current = this->findMax(this->current->left);
    } else {
        Dictionary::Node* curr_y = this->current->parent;
        while (curr_y != this->nil && this->current == curr_y->left) {
            this->current = curr_y;
            curr_y = curr_y->parent;
        }
        this->current = curr_y;
    }
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    this->inOrderString(s, this->root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    this->preOrderString(s, this->root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    return (this->to_string() == D.to_string());
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    // cerr << "root: " << D.root->key << endl;
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary temp = D;

        std::swap(this->root, temp.root);
        std::swap(this->current, temp.current);
        std::swap(this->nil, temp.nil);
        std::swap(this->num_pairs, temp.num_pairs);
        this->current = this->nil;
    }
    return *this;
}

#include<iostream>

class BinarySearchTree {
    public:        
        explicit BinarySearchTree() {
            // Zero argument constructor - creates a BST
            
            root = nullptr;
        }

        explicit BinarySearchTree(const BinarySearchTree & rhs) {
            // Copy constructor - creates a copy of rhs, another BST

            root = rhs.root;
            copyChildren(rhs.root, root);
        }

        explicit BinarySearchTree(BinarySearchTree && rhs) {
            // Move constructor - sets this BST to rhs, another BST
            
            root = std::move(rhs.root);
            copyChildren(rhs.root, root);
        }

        ~BinarySearchTree() {
            // Destructor - deletes the BST

            while (root->left != nullptr or root->right != nullptr) {
                remove(const int & x, BinaryNode* t);
            }
            root = nullptr;
        }

        BinarySearchTree & operator=(const BinarySearchTree & rhs) {
            // Copy assignment - makes this BST rhs, another BST

            std::swap(*this, rhs);
            return *this;
        }

        BinarySearchTree & operator=(BinarySearchTree && rhs) {
            // Move assignment - swaps this BST with rhs, another BST

            *this = std::move(rhs);
            return *this;
        }

        void insert(const int x) {
            // insert - inserts x, an lvalue, to the BST

            insert(x, root);
        }

        void insert(const int && x) {
            // insert - inserts x, an rvalue, to the BST

            insert(x, root);
        }

        void remove(const int x) {
            // remove - removes x from the BST

            remove(x, root);
        }

        bool contains(const int x) const {
            /* contains - checks if x is in the BST
             *          - returns true if in the BST, false otherwise
             */

            return contains(x, root); 
        }

        class BinaryNode {
            public:
                explicit BinaryNode(const int n = 0, BinaryNode* l = nullptr, BinaryNode* r = nullptr, bool containment = false)
                    : val{n}, left{l}, right{r}, inTree{containment} {
                        // Copy constructor - creates a copy of BinaryNode
                }

                explicit BinaryNode(int && n, BinaryNode* l = nullptr, BinaryNode* r = nullptr, bool containment = false)
                    : val{std::move(n)}, left{l}, right{r}, inTree{containment} {
                        // Move constructor - sets this deque to rhs, another deque
                }

                ~BinaryNode() {
                    // deletes BinaryNode

                    delete val;
                }

                BinaryNode & operator=(const BinaryNode &  rhs) {
                    // Copy assignment - makes this BinaryNode rhs, another BinaryNode

                    if (this != &rhs) {
                        val = rhs.val;
                        inTree = rhs.inTree;
                    }
                    return *this;
                }

                BinaryNode & operator=(BinaryNode && rhs) {
                    // Move assignment - swaps this BinaryNode with rhs, another BinaryNode

                    std::swap(val, rhs.val);
                    std::swap(inTree, rhs.inTree);
                    return *this;
                }
            
            private:
                int val;                // value stored
                BinaryNode* left;       // pointer to next Node
                BinaryNode* right;      // pointer to previous Node
                bool inTree;            // tells whether a node has been "removed"
            
            friend class BinarySearchTree;      // lets BST access BinaryNode
        }

    private:
        Node *root;     // stores the root of BST

        void insert(const int x, BinaryNode* t) {
            // insert - inserts x, an lvalue, to the BST
            
            if (t == nullptr) {
                t = new BinaryNode{x, nullptr, nullptr, true};
            } else if (x < t->val) {
                insert(x, t->left);
            } else if (x > t->right) {
                insert(x, t->right);
            } else {
                if (!(t->inTree)) {
                    t->inTree = true;
                }
            }
        }

        void insert(const int && x, BinaryNode* t) {
            // insert - inserts x, an rvalue, to the BST
            
            if (t == nullptr) {
                t = new BinaryNode{std::move(x), nullptr, nullptr};
            } else if (x < t->val) {
                insert(std::move(x), t->left);
            } else if (x > t->right) {
                insert(std::move(x), t->right);
            } else {
                if (!(t->inTree)) {
                    t->inTree = true;
                }
            }
        }

        void remove(const int x, BinaryNode* t) {
            // remove - removes x from the BST

            if (t == nullptr) {
            } else if (x < t->val) {
                remove(x, t->left);
            } else if (x > t->right) {
                remove(x, t->right);
            } else {
                if (t->inTree) {
                    t->inTree = false;
                }
            }
        }

        bool contains(const int x, BinaryNode* t) const {
            /* contains - checks if x is in the BST
             *          - returns true if in the BST, false otherwise
             */

            if (t == nullptr) {
                return false;
            } else if (x < t->val) {
                return contains(x, t->left)
            } else if (x > t->val) {
                return contains(x, t->right);
            } else {
                if (t->inTree) {
                    return true;
                } else {
                    return false;
                }
            }
        }

        void copyChildren(BinaryNode* t, BinaryNode* tNew) {
            /* copyChildren - copies the children of a root node
             * 
             * t - a root node of the original BST; an lvalue
             * tNew -  a root node of the copy
             */

            tNew->left = t->left;
            tNew->right = t->right;
            if (t->left != nullptr) {
                copyChildren(t->left, tNew->left);
            }
            if (t->right != nullptr) {
                copyChildren(t->right, tNew->right);
            }
            
        }

        void copyChildren(BinaryNode* && t, BinaryNode* tNew) {
            /* copyChildren - copies the children of a root node
             * 
             * t - a root node of the original BST; an rvalue
             * tNew -  a root node of the copy
             */

            tNew->left = std::move(t->left);
            tNew->right = std::move(t->right);
            if (t->left != nullptr) {
                copyChildren(t->left, tNew->left);
            }
            if (t->right != nullptr) {
                copyChildren(t->right, tNew->right);
            }
            
        }
};

/* With lazy deletion, we cannot merely find the min and max (by going to the furthest left and right, respectively).
 * Instead, we had to take into account if the node t is even in the BST — that is, if (t->inTree == true). 
 * Once we found the min (or max — the logic is the same), we'd have to then check if t is in the BST.
 * If not, then we must find the second smallest number.
 * The process would repeat until we find the smallest number where (t->inTree == true).
 * 
 * The challenge with this is we could potentially go through the BST O(n^2) times.
 * (This would imply that the min is the root, where the BST is a path/linked list.)
 * We can't possibly know how many nodes to the left of the root are in the BST, let along "in the tree" — thus, the difficulties.
 */
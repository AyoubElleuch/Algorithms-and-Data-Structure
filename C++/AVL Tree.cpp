#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

// AVL tree node structure <generics>
template<class T> struct Node {
    T val;
    long long height;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    // Constructor
    Node(T v){
        val = v;
        height = 1;
    }
};

// Max function
long long max(long long a, long long b){
    if(a>b) return a;
    return b;
}

// AVL Tree structure <generics>
template<class T> struct AVL{
    public:
        // Root of the tree
        Node<T>* root = NULL;

        // Function that returns the height of a node. Worst case: O(1)
        long long height(Node<T>* node){
            if(node==NULL) return 0;
            return node->height;
        }

        // Function that return the balance factor of a node. Worst case: O(1)
        long long BF(Node<T>* node){
            if(node==NULL) return 0;
            return height(node->left) - height(node->right);
        }
        
        // Function that updates the height of a node. Worst case: O(1)
        void newHeight(Node<T>* node){
            node->height = 1 + max(height(node->left), height(node->right));
        }

        // Function that performs a left-rotation. Worst case: O(1)
        Node<T>* leftRotate(Node<T>* x){
            Node<T>* y = x->right;
            Node<T>* beta = y->left;
            y->left = x;
            x->right = beta;
            newHeight(x);
            newHeight(y);
            return y;
        }

        // Function that performs a right-rotation. Worst case: O(1)
        Node<T>* rightRotate(Node<T>* y){
            Node<T>* x = y->left;
            Node<T>* beta = x->right;
            x->right = y;
            y->left = beta;
            newHeight(y);
            newHeight(x);
            return x;
        }
        
        // Function that performs a left-right-roration. Worst case: O(1)
        Node<T>* leftRightRotate(Node<T>* y){ 
            y->left = leftRotate(y->left);
            return rightRotate(y);
        }

        // Function that performs a right-left-rotation. Worst case: O(1)
        Node<T>* rightLeftRotate(Node<T>* y){
            y->right = rightRotate(y->right);
            return leftRotate(y);
        }

        // The steps of "add" function are inspired from: https://www.programiz.com/dsa/avl-tree

        // Function that add a new node to the AVL Tree. Worst case: O(log(n))
        Node<T>* add(Node<T>* node, T v){
            // Find the correct position to insert the tree
            if(node==NULL){
                return new Node<T>(v);
            }
            if(v < node->val){
                node->left = add(node->left, v);
            }else if(v > node->val){
                node->right = add(node->right, v);
            }else{
                return node;
            }

            // After insertigng the new node, we update the height of the parent node
            newHeight(node);

            // Check the balance factor after the insertion 
            long long balanceFactor = BF(node);

            // Perform the adequate rotation if the tree is not balanced
            if(balanceFactor>1){
                if(v < node->left->val){
                    return rightRotate(node);
                }
                else if(v > node->left->val){
                    return leftRightRotate(node);
                }
            }
            if(balanceFactor<-1){
                if(v>node->right->val){
                    return leftRotate(node);
                }
                else if(v<node->right->val){
                    return rightLeftRotate(node);
                }
            }
            return node;
        }

        // A function that insert a new value to the tree which uses add() function above: O(log(n))
        void insert(T v){
            root = add(root, v);
            return;
        }

        // A function that find the node with the minimum value in a subtree. Worst case: O(log(n))
        Node<T>* findMin(Node<T>* node){
            if(node->left==NULL){
                return node;
            }
            return findMin(node->left);
        }

        // The steps of "erase" function are inspired by: https://www.programiz.com/dsa/avl-tree

        // A function that removes a node from the tree. Worst case: O(log(n))
        Node<T>* erase(Node<T>* node, T v){

            // Find the node to be deleted
            if(node==NULL) return NULL;
            else if(v < node->val) node->left = erase(node->left, v);
            else if(v > node->val) node->right = erase(node->right, v);
            else{
                if(node->left==NULL && node->right==NULL){
                    return NULL;
                }
                else if(node->left!=NULL && node->right==NULL){
                    *node = *node->left;
                }
                else if(node->right!=NULL && node->left==NULL){
                    *node = *node->right;
                }
                else{
                    Node<T>* minNode = findMin(node->right);
                    node->val = minNode->val;
                    node->right = erase(node->right, minNode->val);
                }
            }
            
            // Update the height of the parent node
            newHeight(node);

            // Check the balance factor after the deletion 
            long long balanceFactor = BF(node);

            // Perform the adequate rotation if the tree is not balanced
            if(balanceFactor>1){
                if(BF(node->left)>=0){
                    return rightRotate(node);
                }else{
                    return leftRightRotate(node);
                }
            }
            if(balanceFactor<-1){
                if(BF(node->right)<=0){
                    return leftRotate(node);
                }else{
                    return rightLeftRotate(node);
                }
            }

            return node;
        }

        // A function that deletes a value from the tree which uses erase() function above. Worst case: O(log(n));
        void del(T v){
            root = erase(root, v);
        }

        // A function that find a specific value in the tree. Worst case: O(log(n));
        Node<T>* find(Node<T>* node, T v){
            if(node==NULL){
                return nullptr;
            }
            if(node->val == v){
                return node;
            }
            if(v>node->val){
                return find(node->right, v);
            }else{
                return find(node->left, v);
            }
        }


        // A function that finds the largest value that is strictly less than v. Worst case: O(log(n));
        Node<T>* prev(Node<T>* node, T v){
            T temp = v;
            Node<T>* p = node;
            while(node!=NULL){
                if(node->val<v){
                    temp = node->val;
                    p = node;
                    node = node->right;
                }else if(node->val>=v){
                    node = node->left;
                }
            }
            if(temp==v){
                return NULL;
            }else{
                return p;
            }
        }

        // A function that finds the smallest value that is strictly larger than v. Worst case: O(log(n));
        Node<T>* next(Node<T>* node, T v){
            T temp = v;
            Node<T>* n = node;
            while(node!=NULL){
                if(node->val<=v){
                    node = node->right;
                }else if(node->val>v){
                    temp = node->val;
                    n = node;
                    node = node->left;
                }
            }
            if(temp==v){
                return NULL;
            }else{
                return n;
            }
        }
};

int main(){


  return 0;
}

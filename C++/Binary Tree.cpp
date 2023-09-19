#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;


class Node{
    public:
        int value;
        Node* left;
        Node* right;
};

void insertValue(int value);
void BFS();
void DFS();
void largest();
void smallest();
void searchValue(int value);
Node* root = NULL;


int main(){
    insertValue(15);
    insertValue(10);
    insertValue(20);
    insertValue(5);
    insertValue(12);
    insertValue(18);
    insertValue(22);
    cout << "Breadth First Search:" << endl;
    BFS();
    cout << "Depth First Search:" << endl;
    DFS();
    searchValue(12);
    searchValue(19);
    smallest();
    largest();
    return 0;
}


void insertValue(int value){
    Node* new_node;
    new_node = new Node;
    new_node->value = value;
    if(root == NULL){
        root = new_node;
        root->left = root->right = NULL;
        return;
    }
    Node* current_node;
    current_node = root;
    while(current_node){
        if(value < current_node->value){
            if(current_node->left != NULL){
                current_node = current_node->left;
            }else{
                current_node->left = new_node;
                new_node->left = new_node->right = NULL;
                return;
            }
        }else{
            if(current_node->right !=NULL){
                current_node = current_node->right;
            }else{
                current_node->right = new_node;
                new_node->left = new_node->right = NULL;
                return;
            }
        }
    }
}

void BFS(){
    queue<Node*> q;
    if(root == NULL){
        cout << "Tree is empty!";
        return;
    }
    q.push(root);
    while(q.size() > 0){
        Node* last;
        last = q.front();
        q.pop();
        if(last->left != NULL){
            q.push(last->left);
        }
        if(last->right != NULL){
            q.push(last->right);
        }
        cout << last->value << endl;
    }
    return;
}

void DFS(){
    stack<Node* > s;
    if(root == NULL){
        cout << "Three is empty!" << endl;
        return;
    }
    s.push(root);
    while(s.size() > 0){
        Node* last;
        last = s.top();
        s.pop();
        if(last->right != NULL){
            s.push(last->right);
        }
        if(last->left != NULL){
            s.push(last->left);
        }
        cout << last->value << endl;
    }
}

void searchValue(int value){
    if(root == NULL){
        cout << "There's no tree!" << endl;
    }
    Node* current_node;
    current_node = root;
    while(current_node){
        if(current_node->value == value){
            cout << current_node->value << " exists in the tree!" << endl;
            return;
        }else{
            if(value < current_node->value){
                if(current_node->left != NULL){
                    current_node = current_node->left;
                }else{
                    cout << value << " doesn't exist in the tree!" << endl;
                    return;
                }
            }else if(value > current_node->value){
                if(current_node->right != NULL){
                    current_node = current_node->right;
                }else{
                    cout << value << " doesn't exist in the tree!" << endl;
                    return;
                }
            }
        }
    }
}

void largest(){
    Node* current_node;
    if(root == NULL){
        cout << "There's no tree!" << endl;
        return;
    }
    current_node = root;
    while(current_node->value){
        if(current_node->right != NULL){
            current_node = current_node->right;
        }else{
            cout << "Largest value in the tree is: " << current_node->value << endl;
            return;
        }
    }
}

void smallest(){
    Node* current_node;
    if(root == NULL){
        cout << "There's no tree!" << endl;
        return;
    }
    current_node = root;
    while(current_node->value){
        if(current_node->left != NULL){
            current_node = current_node->left;
        }else{
            cout << "The smallest value in the tree is: " << current_node->value << endl;
            return;
        }
    }
}

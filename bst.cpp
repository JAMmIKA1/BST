#include <cmath>
#include <iostream>
#include <vector>
#include "queue.cpp"
#include "stack.cpp"

template<typename T>
class node {
public:
    T value;
    node<T>* left;
    node<T>* right;

    node(T value) {
        left = right = NULL;
        this->value = value;
    }
};

template<typename T>
class BST_methods {
    virtual bool search(T target) = 0; // O(h)
    virtual void remove(T target) = 0; // O(h)
    virtual void insert(T value) = 0; // O(h)
    virtual unsigned height() = 0; // O(n)
    virtual void preorder() = 0; // O(n)
    virtual void inorder() = 0; // O(n)
    virtual void postorder() = 0; // O(n)
    virtual void levelorder() = 0; // O(n)
    virtual T successor(T target) = 0; // O(h)
    virtual T min() = 0; // O(h)
    virtual T max() = 0; // O(h)
    virtual bool is_BST() = 0; // O(n)
};

template<typename T>
class BST:BST_methods<T> {
private:
    node<T>* root;

public:
    BST() {
        root = NULL;
    }
    bool search(T target) {
        node<T>* temp = root;
        while(true) {
            if(temp == NULL) {
                return false;
                break;
            }
            if(target < temp -> value) {
                temp = temp->left;
            }
            else if(target > temp->value) {
                temp = temp->right;
            }
            else {
                return true;
                break;
            }
        }
    }
    void printBST() {
        queue_ds<node<T>*> queue;
        queue.push(this->root);
        int h = height();
        for(int i = 0; i <= h; i++) {
            for(int j = 0; j < (1 << (h - i)) - 1; j++)
                std::cout << ' ';
            for(int j = 0; j < (1 << i); j++) {
                node<T>* tmp = queue.pop();
                if(tmp == 0) {
                    cout << '.';
                    queue.push(0);
                    queue.push(0);
                }
                else {
                    cout << tmp->value;
                    queue.push(tmp->left);
                    queue.push(tmp->right);
                }
                for(int k = 0; k < (1 << (h + 1 - i)) - 1; k++)
                    std::cout << ' ';
            }
            for(int j = 1; j < 1 << ((h - i) - 1); j++) {
                cout << '\n';
                for(int k = 0; k < 1 << (h + 1); k++) {
                    if((k + j + 1) % (1 << (h + 1 - i)) == 1 << (h - i)) cout << '/';
                    else if((k + 1 - j) % (1 << (h + 1 - i)) == 1 << (h - i)) cout << '\\';
                    else cout << ' ';
                }
            }
            cout << '\n';
        }
    }
    void insert(T value) {
        if(root == NULL) {
            root = new node<T>(value);
        }
        else {
            node<T>* temp_node = root;
            while(true) {
                if(value < temp_node -> value) {
                    if(temp_node -> left == NULL) {
                        temp_node -> left = new node<T>(value);
                    }
                    else {
                        temp_node = temp_node->left;
                    }
                }
                else if(value > temp_node->value) {
                    if(temp_node -> right == NULL) {
                        temp_node -> right = new node<T>(value);
                    }
                    else {
                        temp_node = temp_node->right;
                    }
                }
                else {
                    break;
                }
            }

        }
    }
    T min() {
        if( root == NULL) {
            return 0;
        }
        node<T>* temp_node = root;
        while(true) {
            if(temp_node -> left == NULL) {
                return temp_node -> value;
            }
            temp_node = temp_node -> left;
        }
    }
    T max() {
        if( root == NULL) {
            return 0;
        }
        node<T>* temp_node = root;
        while(true) {
            if(temp_node -> right == NULL) {
                return temp_node -> value;
            }
            temp_node = temp_node -> right;
        }
    }
    unsigned height() {
        return height_recursion(root);
    }

    void preorder() {
        preorder_recursion(root);
    }
    void inorder() {
        inorder_recursion(root);
    }
    void postorder() {
        postorder_recursion(root);
    }
    void levelorder() {
        if(root == NULL) return;
        queue_ds<node<T>*> bst_queue;
        bst_queue.push(root);
        while(bst_queue.empty() == 0) {
            node<T>* temp_node = bst_queue.pop();
            std::cout << temp_node->value << ' ';
            if(temp_node->left) bst_queue.push(temp_node->left);
            if(temp_node->right) bst_queue.push(temp_node->right);
        }
    }
    void balance() {
        std::vector<node<T>*> data;
        inorder_traversal(root, &data);
        root = NULL;
        balance_recursion(0, data.size() - 1, data);
    }

    bool is_BST() {
        return is_BST_recursion(root, min(), max());
    }

    T successor(T target) {
        stack_ds<node<T>*> BST_stack;
        node<T> *temp_node = root, *targeted_node;

        if(target == max()) {
            std::cout << "No successor for max value!" << std::endl;
            return 0;
        }

        //Search for the node
        while(true) {
            if(temp_node == NULL) {
                std::cout << "Value not found!" << std::endl;
                return 0;
            }
            if(target == temp_node -> value) {
                targeted_node = temp_node;
                break;
            }

            BST_stack.push(temp_node);

            if(target < temp_node -> value) {
                temp_node = temp_node -> left;
            }
            else if(target > temp_node -> value) {
                temp_node = temp_node -> right;
            }
        }

        //Case 1 -> the target have a right subtree (find min of right subtree)
        if(temp_node -> right != NULL) {
            temp_node = temp_node -> right;
            while(true) {
                if(temp_node -> left == NULL) {
                    return temp_node -> value;
                }
                temp_node = temp_node -> left;
            }
        }

        //Case 2 -> Target not have a right subtree & It's a left child
        temp_node = BST_stack.pop();
        if(temp_node -> left == targeted_node) {
            return temp_node -> value;
        }

        //Last Case.
        while(true) {
            targeted_node = temp_node;
            temp_node = BST_stack.pop();
            if(temp_node -> left == targeted_node) {
                return temp_node -> value;
            }
        }
    }

    void remove(T target) {
        node<T>* temp_node = root, *targeted_node;
        while(true) {
            if(temp_node == NULL) {
                std::cout << "Value not found!" << std::endl;
                return;
            }
            if(temp_node->right != NULL) {
                if(temp_node->right->value == target) {
                    targeted_node = temp_node->right;
                    if(targeted_node->left == NULL) {
                        temp_node->right = targeted_node->right;
                        delete(targeted_node);
                    }
                    else if(targeted_node->right == NULL) {
                        temp_node->right = targeted_node->left;
                        delete(targeted_node);
                    }
                    else {
                        temp_node = targeted_node->right;
                        if(temp_node->left == NULL) {
                            targeted_node->value = temp_node->value;
                            targeted_node->right = temp_node->right;
                            delete(temp_node);
                        }
                        else {
                            while(true) {
                                if(temp_node->left->left == NULL) {
                                    targeted_node->value = temp_node->left->value;
                                    node<T>* temp_targeted_node = temp_node->left;
                                    temp_node->left = temp_targeted_node->right;
                                    delete(temp_targeted_node);
                                    break;
                                }
                                temp_node = temp_node->left;
                            }
                        }
                    }
                    return;
                }
            }

            if(temp_node->left != NULL) {
                if(temp_node->left->value == target) {
                    targeted_node = temp_node->left;
                    if(targeted_node->right == NULL) {
                        temp_node->left = targeted_node->left;
                        delete(targeted_node);
                    }
                    else if(targeted_node->left == NULL) {
                        temp_node->left = targeted_node->right;
                        delete(targeted_node);
                    }
                    else {
                        temp_node = targeted_node->left;
                        if(temp_node->right == NULL) {
                            targeted_node->value = temp_node->value;
                            targeted_node->left = temp_node->left;
                            delete(temp_node);
                        }
                        else {
                            while(true) {
                                if(temp_node->right->right == NULL) {
                                    targeted_node->value = temp_node->right->value;
                                    node<T>* temp_targeted_node = temp_node->right;
                                    temp_node->right = temp_targeted_node->left;
                                    delete(temp_targeted_node);
                                    break;
                                }
                                temp_node = temp_node->right;
                            }
                        }
                    }
                    return;
                }
            }
            if(target < temp_node -> value) {
                temp_node = temp_node->left;
            }
            else if(target > temp_node->value) {
                temp_node = temp_node->right;
            }
        }
    }

protected:
    int height_recursion(node<T>* root) {
        if (root == NULL) return -1;
        int left_height = height_recursion(root -> left);
        int right_height = height_recursion(root -> right);
        if(left_height > right_height) {
            return left_height + 1;
        }
        else {
            return right_height + 1;
        }
    }

    bool is_BST_recursion(node<T>* root, T min, T max) {
        if(root == NULL) return true;

        bool BST_node = false;
        if(root->value > min && root->value < max) {
            BST_node = true;
        }
        else if(root->value == min && root->left == NULL) {
            BST_node = true;
        }
        else if(root->value == max && root->right == NULL) {
            BST_node = true;
        }

        if( BST_node &&
            is_BST_recursion(root->left, min, root->value) &&
            is_BST_recursion(root->right, root->value, max) )
            return true;
        return false;
    }

    void balance_recursion(int start, int end, std::vector<node<T>*> data) { 
        if(start > end) return;
        int mid = start + (end - start) / 2;
        insert(data[mid]->value);
        delete(data[mid]);
        balance_recursion(mid + 1, end, data);
        balance_recursion(start, mid - 1, data);
    }
    void inorder_traversal(node<T>* root, std::vector<node<T>*>* data) {
        if(root == NULL) return;
        inorder_traversal(root->left, data);
        data->push_back(root);
        inorder_traversal(root->right, data);
    }

    void preorder_recursion(node<T>* root) {
        if(root == NULL) return;
        std::cout << root->value << ' ';
        preorder_recursion(root->left);
        preorder_recursion(root->right);
    }
    void inorder_recursion(node<T>* root) {
        if(root == NULL) return;
        inorder_recursion(root->left);
        std::cout << root->value << ' ';
        inorder_recursion(root->right);
    }
    void postorder_recursion(node<T>* root) {
        if(root == NULL) return;
        postorder_recursion(root->left);
        postorder_recursion(root->right);
        std::cout << root->value << ' ';
    }
};

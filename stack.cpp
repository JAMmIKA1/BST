#include <iostream>

template<typename T>
class stack_node {
public:
    stack_node* next;
    T value;

    stack_node(T Value){
        this->value = Value;
        this->next = NULL;
    }
};

template<typename T>
class stack_methods {
    virtual void push(T) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
    virtual unsigned long long size() = 0;
    virtual bool empty() = 0;
};

template<typename T>
class stack_ds:stack_methods<T> {
private:
    stack_node<T>* head;
    unsigned long long length;

public:
    stack_ds() {
        this->length = 0;
        this->head = NULL;
    }
    void push(T Value) {
        stack_node<T>* new_node = new stack_node<T>(Value);
        new_node -> next = head;
        head = new_node;
        length++;
    }
    T pop() {
        T temp_value = 0;
        if( head != NULL ) {
            stack_node<T>* temp_node = head;
            head = head -> next;
            temp_value = temp_node -> value;
            delete(temp_node);
            length--;
        }
        return temp_value;
    };
    T top() {
        if (head != NULL)
            return head -> value;
        return 0;
    };
    unsigned long long size() {
        return length;
    }
    bool empty() {
        if (head == NULL) 
           return true;
        return false;
    };
};

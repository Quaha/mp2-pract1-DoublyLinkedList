#pragma once

#include <iostream>

template<typename ListType> class List {
private:
    struct Node {
        ListType value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const ListType& value) {
            this->value = value;
        }
    };

    int size = 0;
    Node* head = nullptr;
    // head->next the first elem
    // head->prev the last elem

    void destruct();
    void roughCoping(const List& other);
    void insert(const ListType& value, Node* prev_node, Node* next_node);

public:

    class Iterator {
    private:

        Node* node = nullptr;

    public:

    };

    List();
    List(const List& other);
    List(List&& other);

    ~List() {
        destruct();
    }

    List& operator=(const List& other);
    List& operator=(List&& other);

    Iterator front() const;
    Iterator back() const;

    void push_front(const ListType& value) {
        insert(value, head, head->next);
    }

    void push_back(const ListType& value) {
        insert(value, head->prev, head);
    }

    void insert_after(const ListType& value, Node* prev_node) {
        insert(value, prev_node, prev_node->next);
    }

    void insert_before(const ListType& value, Node* next_node) {
        insert(value, next_node->prev, next_node);
    }
};

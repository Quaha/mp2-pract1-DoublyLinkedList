#include <iostream>

#include "DoublyLinkedList.h"

template<typename ListType>
void List<ListType>::destruct() {
    Node* curr = head->next;
    while (curr != head) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    delete head;
    head = nullptr;
}

template<typename ListType>
void List<ListType>::roughCoping(const List& other) {
    head = new Node;
    this->size = other.size;

    Node* other_ptr = other.head->next;
    Node* this_ptr = this->head;

    while (other_ptr != other.head) {
        this_ptr->next = new Node(other_ptr->value);
        this_ptr->next->prev = this_ptr;

        this_ptr = this_ptr->next;
        other_ptr = other_ptr->next;
    }

    this_ptr->next = this->head;
    this->head->prev = this_ptr;
}


template<typename ListType>
void List<ListType>::insert(const ListType& value, Node* prev_node, Node* next_node) {
    ++size;

    Node* curr_node = new Node(value);

    curr_node->next = prev_node->next;
    curr_node->prev = next_node->prev;

    next_node->prev = curr_node;
    prev_node->next = curr_node;
}

template<typename ListType>
List<ListType>::List() {
    head = new Node;
    head->prev = head;
    head->next = head;
}

template<typename ListType>
List<ListType>::List(const List& other) {
    roughCoping(other);
}

template<typename ListType>
List<ListType>::List(List&& other) {
    this->head = other.head;
    other.head = nullptr;
    other.size = 0;
}

template<typename ListType>
List<ListType>& List<ListType>::operator=(const List& other) {
    if (this != &other) {
        destruct();
        roughCoping(other);
    }
}

template<typename ListType>
List<ListType>& List<ListType>::operator=(List&& other) {
    if (this != &other) {
        this->head = other.head;
        other.head = new Node();
        other.size = 0;
    }
}

template<typename ListType>
typename List<ListType>::Iterator List<ListType>::front() const {
    return List<ListType>::Iterator();
}

template<typename ListType>
typename List<ListType>::Iterator List<ListType>::back() const {
    return List<ListType>::Iterator();
}


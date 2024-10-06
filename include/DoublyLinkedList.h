#pragma once

#include <iostream>

template<typename ListType> class List {
private:
    struct Node {
        ListType value;
        Node* next = nullptr;
        Node* prev = nullptr;

        bool is_head = false;

        Node() {}

        Node(const ListType& value) {
            this->value = value;
        }
    };

    size_t sz = 0;
    Node* head = nullptr;
    // head->next the first element of this list
    // head->prev the last element of this list

public:

    class Iterator {
        friend class List;
    private:
        Node* curr_node = nullptr;

        Iterator(Node* curr_node): curr_node(curr_node) {}
    public:
        Iterator() = delete;

        ListType& operator*() const {
            if (curr_node->is_head) {
                throw std::out_of_range("It is not allowed to dereference the .end() iterator");
            }
            return curr_node->value;
        }

        ListType* operator->() const {
            if (curr_node->is_head) {
                throw std::out_of_range("It is not allowed to dereference the .end() iterator");
            }
            return &(curr_node->value)
        }

        bool operator==(const Iterator& other) const {
            return this->curr_node == other.curr_node;
        }

        bool operator!=(const Iterator& other) const {
            return this->curr_node != other.curr_node;
        }

        Iterator& operator++() {
            curr_node = curr_node->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            curr_node = curr_node->next;
            return temp;
        }

        Iterator& operator--() {
            curr_node = curr_node->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            curr_node = curr_node->prev;
            return temp;
        }
    };
private:

    void destruct() {
        Node* curr = head->next;
        while (curr != head) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        delete head;
        head = nullptr;
    }

    void roughCoping(const List& other) {
        this->head = new Node;
        this->sz = other.sz;

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

    Iterator insert(const ListType& value, Node* prev_node, Node* next_node) {
        ++sz;

        Node* curr_node = new Node(value);

        curr_node->next = prev_node->next;
        curr_node->prev = next_node->prev;

        next_node->prev = curr_node;
        prev_node->next = curr_node;

        return Iterator(curr_node);
    }

    Iterator erase(Node* curr_node) {
        if (curr_node->is_head) {
            throw std::out_of_range("It is not allowed to erase the .end() iterator");
        }

        --sz;

        Node* prev_node = curr_node->prev;
        Node* next_node = curr_node->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete curr_node;
        return next_node;
    }

public:

    List() {
        head = new Node;
        head->prev = head;
        head->next = head;
        head->is_head = true;
    }

    List(int size, const ListType& value): List() {
        if (size < 0) {
            throw std::logic_error("The size of the list must be non-negative");
        }
        for (int i = 0; i < size; ++i) {
            push_back(value);
        }
    }

    List(const List& other) {
        roughCoping(other);
    }

    List(List&& other) {
        this->head = other.head;
        this->sz = other.sz;

        other.head = new Node;
        other.head->prev = other.head;
        other.head->next = other.head;
        other.head->is_head = true;

        other.sz = 0;
    }

    ~List() {
        destruct();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            destruct();
            roughCoping(other);
        }
        return *this;
    }

    List& operator=(List&& other) {
        if (this != &other) {
            this->head = other.head;
            this->sz = other.sz;

            other.head = new Node;
            other.head->prev = other.head;
            other.head->next = other.head;
            other.sz = 0;
        }
        return *this;
    }

    size_t size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    Iterator begin() {
        return Iterator(head->next);
    }

    Iterator end() {
        return Iterator(head);
    }


    ListType& front() const {
        if (head->next->is_head) {
            throw std::out_of_range("The list is empty");
        }
        return head->next->value;
    }

    ListType& back() const {
        if (head->prev->is_head) {
            throw std::out_of_range("The list is empty");
        }
        return head->prev->value;
    }


    Iterator push_front(const ListType& value) {
        return insert(value, head, head->next);
    }

    Iterator push_back(const ListType& value) {
        return insert(value, head->prev, head);
    }

    Iterator insert_after(const ListType& value, Iterator prev) {
        return insert(value, prev.curr_node, prev.curr_node->next);
    }

    Iterator insert_before(const ListType& value, Iterator next) {
        return insert(value, next.curr_node->prev, next.curr_node);
    }


    Iterator pop_front() {
        return erase(Iterator(head->next));
    }

    Iterator pop_back() {
        return erase(Iterator(head->prev));
    }

    Iterator erase(Iterator it) {
        return erase(it.curr_node);
    }

    ListType& operator[](int index) {
        if (index >= sz || index < 0) {
            throw std::out_of_range("List index out of range");
        }

        Node* current = head->next;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    const ListType& operator[](int index) const {
        if (index >= sz || index < 0) {
            throw std::out_of_range("List index out of range");
        }

        Node* current = head->next;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }
};

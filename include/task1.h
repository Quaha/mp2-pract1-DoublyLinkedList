#pragma once

#include <iostream>

struct List {

	struct Node {
		Node* next = nullptr;
		Node* data = nullptr;
	};

	Node* first = nullptr;

	void construct(int size) {
		for (int i = 0; i < size; i++) {
			Node* current_node = new Node;
			current_node->next = first;
			first = current_node;
		}
	}

	List(int size = 0) {
		if (size < 0) {
			throw std::logic_error("List size must be non-negative");
		}
		construct(size);
	}

	List(const List& other) = delete;
	List(List&& other) = delete;

	void destruct() {
		Node* current_node = first;
		while (current_node) {
			Node* next_node = current_node->next;
			delete current_node;
			current_node = next_node;
		}
	}

	~List() {
		destruct();
		first = nullptr;
	}

	List& operator=(const List& other) = delete;
	List& operator=(List&& other) = delete;

	List& getCopy(List& new_list) {

		List& old_list = (*this);

		// Getting the size of the old_list
		int size = 0;
		Node* curr_node = first;
		while (curr_node) {
			++size;
			curr_node = curr_node->next;
		}

		new_list.destruct();
		new_list.construct(size);

		// Step 1:
		// new_list has correct next ties
		// new_list data links to the corresponding nodes in the old_list
		// old_list has correct data ties
		// old_list next links to the corresponding nodes in the new_list
		Node* old_node_ptr = old_list.first;
		Node* new_node_ptr = new_list.first;

		for (int i = 0; i < size; i++) {
			Node* next_old_node_ptr = old_node_ptr->next;
			Node* next_new_node_ptr = new_node_ptr->next;

			old_node_ptr->next = new_node_ptr;
			new_node_ptr->data = old_node_ptr;

			old_node_ptr = next_old_node_ptr;
			new_node_ptr = next_new_node_ptr;
		}

		// Step 2:
		// new_list has correct next ties
		// new_list data links to the corresponding nodes in the old_list
		// old_list data links to a node in the new_list, which corresponds to the original data in the old_list
		// old_list next links to the corresponding nodes in the new_list
		new_node_ptr = new_list.first;
		for (int i = 0; i < size; i++) {
			old_node_ptr = new_node_ptr->data;

			// old_node_ptr->data = old_node_ptr->data->next; - old_node_ptr->data could be nullptr
			if (old_node_ptr->data) {
				old_node_ptr->data = old_node_ptr->data->next;
			}

			new_node_ptr = new_node_ptr->next;
		}

		// Step 3:
		// new_list has correct next ties
		// new_list data links to the corresponding nodes in the old_list
		// old_list has correct data ties
		// old_list next links to a node in the new_list, which corresponds to the original data in the old_list
		new_node_ptr = new_list.first;
		for (int i = 0; i < size; i++) {
			old_node_ptr = new_node_ptr->data;

			//old_node_ptr->next = old_node_ptr->data->data; - old_node_ptr->data could be nullptr
			old_node_ptr->next = old_node_ptr->data;
			if (old_node_ptr->next) {
				old_node_ptr->next = old_node_ptr->next->data;
			}

			std::swap(old_node_ptr->data, old_node_ptr->next);

			new_node_ptr = new_node_ptr->next;
		}

		// Step 4:
		// correct old_list and new_list

		new_node_ptr = new_list.first;
		for (int i = 0; i < size; i++) {
			Node* correct_new_data = new_node_ptr->data->next;
			Node* correct_old_next = new_node_ptr->next;
			if (correct_old_next) {
				correct_old_next = correct_old_next->data;
			}

			new_node_ptr->data->next = correct_old_next;
			new_node_ptr->data = correct_new_data;

			new_node_ptr = new_node_ptr->next;
		}

		return new_list;
	}
};
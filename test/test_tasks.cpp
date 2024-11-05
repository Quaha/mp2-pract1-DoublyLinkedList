#include "task1.h"

#include <gtest.h>

#include <random>
#include <vector>
#include <cmath>

TEST(task1, stress_test) {
    
    srand(time(0));

    const int COUNT_OF_TEST_CASES = 100000;
    const int MAX_LIST_SIZE = 15;

    for (int test_case = 0; test_case < COUNT_OF_TEST_CASES; ++test_case) {
        int size = rand() % MAX_LIST_SIZE;

        List list(size);

        std::vector<List::Node*> nodes(size);
        List::Node* curr_node = list.first;
        for (int i = 0; i < size; i++) {
            nodes[i] = curr_node;
            curr_node = curr_node->next;
        }

        std::vector<int> data(size);
        for (int i = 0; i < size; i++) {
            data[i] = rand() % (size + 1);
        }

        for (int i = 0; i < size; i++) {
            if (data[i] < size) {
                nodes[i]->data = nodes[data[i]];
            }
        }
        
        List result;
        list.getCopy(result);

        for (int curr_node_pos = 0; curr_node_pos < size; curr_node_pos++) {
            int data_node_pos = data[curr_node_pos];

            List::Node* curr_node = list.first;
            for (int j = 0; j < curr_node_pos; j++) {
                curr_node = curr_node->next;
            }

            if (data_node_pos == size) {
                EXPECT_EQ(curr_node->data, nullptr);
                continue;
            }

            List::Node* data_node = list.first;
            for (int j = 0; j < data_node_pos; j++) {
                data_node = data_node->next;
            }

            int cnt = 0;
            if (curr_node_pos < data_node_pos) {
                while (curr_node != data_node) {
                    ++cnt;
                    curr_node = curr_node->next;
                }
            }
            else {
                while (curr_node != data_node) {
                    ++cnt;
                    data_node = data_node->next;
                }
            }

            EXPECT_EQ(cnt, std::abs(curr_node_pos - data_node_pos));
        }
    }
}
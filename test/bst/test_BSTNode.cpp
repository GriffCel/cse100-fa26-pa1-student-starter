#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_WHEN_PRESENT){
    BSTNode<int> node1(3);
    BSTNode<int> node2(1);
    BSTNode<int> node3(-33);
    BSTNode<int> node4(10);
    BSTNode<int> node5(100);
    BSTNode<int> node6(2);
    BSTNode<int> node7(7);

    node1.left = &node2;
    node2.parent = &node1;
    node1.right = &node4;
    node4.parent = &node1;
    node2.left = &node3;
    node3.parent = &node2;
    node2.right = &node6;
    node6.parent = &node2;
    node4.right = &node5;
    node5.parent = &node4;
    node4.left = &node7;
    node7.parent = &node4;

    ASSERT_EQ(node1.successor(), &node7);
    ASSERT_EQ(node3.successor(), &node2);
    ASSERT_EQ(node4.successor(), &node5);
    ASSERT_EQ(node6.successor(), &node1);
}

TEST(BST_NODE_TESTS, GETTING_AND_SETTING){
    BSTNode<int> node(14);
    ASSERT_EQ(node.getData(), 14);
    node.setData(420);
    ASSERT_EQ(node.getData(), 420);
}
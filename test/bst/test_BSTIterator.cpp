#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);

    iter++;

    ASSERT_EQ(iter, nullptr);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_EQUALITY_WHEN_NOT_EQUAL){
    BSTNode<int> node1(5);
    BSTNode<int> node2(5);

    BSTIterator<int> itr1(&node1);
    BSTIterator<int> itr2(&node2);

    ASSERT_FALSE(itr1 == itr2);
    ASSERT_TRUE(itr1 != itr2);
}

TEST(BST_ITERATOR_TEST, TEST_EQUALITY_WHEN_EQUAL){
    BSTNode<int> node(5);

    BSTIterator<int> itr1(&node);
    BSTIterator<int> itr2(&node);

    ASSERT_TRUE(itr1 == itr2);
    ASSERT_FALSE(itr1 != itr2);
}

TEST(BST_ITERATOR_TEST, TEST_PRE_AND_POST_INCREMENTS){
    BSTNode<int> node1(5);
    BSTNode<int> node2(10);
    BSTNode<int> node3(50);

    node1.right=&node2;
    node2.parent=&node1;
    node2.right=&node3;
    node3.parent=&node2;

    BSTIterator<int> tracker(&node1);

    BSTIterator<int> check1(&node1);
    BSTIterator<int> check2(&node3);

    BSTIterator<int> result1 = tracker++;
    ASSERT_TRUE(result1 == check1);

    BSTIterator<int> result2 = ++tracker;
    ASSERT_TRUE(result2 == check2);
}
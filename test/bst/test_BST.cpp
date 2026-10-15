#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_NO_DUPES_TEST){
    // assert that a new value is properly inserted
    ASSERT_TRUE(bst.insert(2));
}

TEST_F(SmallBSTFixture, VALUES_RETURNED_IN_ORDER){
    vector<int> values = bst.inorder();
    for(int i = 1; i < (int)(values.size())-1; i++){
        ASSERT_TRUE(values[i - 1] < values[i]);
        ASSERT_TRUE(values[i] < values[i + 1]);
    }
}

TEST_F(SmallBSTFixture, TEST_HEIGHT_PRE_AND_POST_INSERTION){
    ASSERT_EQ(bst.height(), 2);
    bst.insert(0);
    ASSERT_EQ(bst.height(), 3);
}
// TODO: add more BST tests here

TEST(BSTTests, TEST_LARGE_TREE_BALANCING){
    BST<int> bst;
    vector<int> input = {81, 61, 55, 57, 50, 40, 45, 42, 36, 24, 16, 3, 0};
    for(int i = 0; i < (int)(input.size()); i++){
        bst.insert(input[i]);
    }
    ASSERT_EQ(bst.height(), 9);
    BST<int> bst2 = BST<int>(bst);
    ASSERT_EQ(bst2.height(), 3);
}

TEST(BSTTests, TEST_LARGE_UNBALANCED_DELETE_1_LEFT_CHILD){
    BST<int> bst;
    vector<int> input = {81, 61, 55, 57, 50, 40, 45, 42, 36, 24, 16, 3, 0};
    for(int i = 0; i < (int)(input.size()); i++){
        bst.insert(input[i]);
    }
    ASSERT_EQ(bst.height(), 9);
    ASSERT_EQ(bst.size(), 13);
    bst.deleteNode(36);
    ASSERT_EQ(bst.height(), 8);
    ASSERT_EQ(bst.size(), 12);
}

TEST_F(SmallBSTFixture, TEST_FIND_PRESENT_AND_NOT_PRESENT){
    ASSERT_EQ(*(bst.find(100)), 100);
    ASSERT_EQ(*(bst.find(69)), NULL);
}

TEST(BSTTests, TEST_DELETION_MULTIPLE_CHILDREN){
    BST<int> bst;
    vector<int> input = {50, 42, 57, 36, 45, 55, 61, 24, 40, 81, 3, 0, 16};
    for(int i = 0; i < (int)(input.size()); i++){
        bst.insert(input[i]);
    }
    ASSERT_FALSE(bst.deleteNode(100));
    ASSERT_TRUE(bst.deleteNode(42));
    ASSERT_EQ(bst.height(), 5);
    ASSERT_EQ(bst.size(), 12);
    ASSERT_EQ(bst.find(42), nullptr);
}

TEST(BSTTests, TEST_DELETION_0_CHILDREN){
    BST<int> bst;
    vector<int> input = {50, 42, 57, 36, 45, 55, 61, 24, 40, 81, 3, 0, 16};
    for(int i = 0; i < (int)(input.size()); i++){
        bst.insert(input[i]);
    }
    ASSERT_TRUE(bst.deleteNode(16));
    ASSERT_EQ(bst.size(), 12);
    ASSERT_EQ(bst.height(), 5);
}

TEST(BSTTests, TEST_DELETION_MULTIPLE_CHILDREN_TO_1_RIGHT_CHILD){
    BST<int> bst;
    vector<int> input = {50, 42, 57, 36, 45, 55, 61, 24, 40, 81, 3, 0, 16};
    for(int i = 0; i < (int)(input.size()); i++){
        bst.insert(input[i]);
    }
    ASSERT_TRUE(bst.deleteNode(61));
    ASSERT_EQ(bst.height(), 5);
    ASSERT_EQ(bst.size(), 12);
    ASSERT_EQ(bst.find(61), nullptr);
}


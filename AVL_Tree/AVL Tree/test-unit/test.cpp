#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("Basic Insert", "[flag]"){
		AVLTree tree;   // Create a Tree object
		tree.beginInsert(std::vector<string> {"00000003", "Name Three"});
		tree.beginInsert(std::vector<string> {"00000002", "Name Two"});
		tree.beginInsert(std::vector<string> {"00000001", "\"Name One\""});

        std::vector<string> actualOutput = tree.beginGetNodeValues();
		std::vector<string> expectedOutput = {"00000001", "00000002", "00000003"};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Testing Five Incorrect Commands", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.beginInsert(std::vector<string> {"00000001", "\"correct one\""});
    tree.beginInsert(std::vector<string> {"00000112", "\"n4me w1th numb3rs\""});
    tree.beginInsert(std::vector<string> {"1111", "\"too short number\""});
    tree.beginInsert(std::vector<string> {"0000000000001", "\"too long number\""});
    tree.beginInsert(std::vector<string> {"012345", "\"b0th 1nputs wr0ng\""});
    tree.beginInsert(std::vector<string> {"00000003", "no quotes around name"});
    tree.beginInsert(std::vector<string> {"19463827", "\"correct two\""});

    std::vector<string> actualOutput = tree.beginGetNodeValues();
    std::sort(actualOutput.begin(), actualOutput.end());
    std::vector<string> expectedOutput = {"00000001", "19463827"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Insert 100, Remove 10", "[flag]"){
    AVLTree tree;   // Create a Tree object
    std::vector<string> expectedOutput;
    std::vector<string> actualOutput;

    int countAdd = 0;

    while(countAdd != 100)
    {
        string randomID;
        for(int j = 0; j < 8; j++){
            int randomValue = rand() % 9;
            randomID += to_string(randomValue);
        }
        if (std::count(expectedOutput.begin(), expectedOutput.end(), randomID) == 0)
        {
            countAdd++;
            expectedOutput.push_back(randomID);
            tree.beginInsert(vector<string>{randomID, "name " + randomID});
        }
    }

    vector<int> deletionValues;
    int count = 0;
    while (count != 10){
        int randomValue = rand() % expectedOutput.size();
        deletionValues.push_back(randomValue);
        if (std::count(deletionValues.begin(), deletionValues.end(), randomValue) == 0)
        {
            count++;
            tree.beginRemoveInorder(randomValue);
        }
    }

    actualOutput = tree.beginGetNodeValues();
    std::sort(expectedOutput.begin(), expectedOutput.end());

    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(expectedOutput == actualOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("Testing Edge Cases", "[flag]"){

    AVLTree tree;   // Create a Tree object
    tree.beginRemove("12345678"); // Edge Case 1: Removing from empty tree
    tree.beginInsert(std::vector<string> {"00000001", "\"Kinnara\""});
    tree.beginInsert(std::vector<string> {"00000012", "\"Dara\""});
    tree.beginInsert(std::vector<string> {"00010101", "\"Martin\""});
    tree.beginRemoveInorder(5); // Edge Case 2: RemoveInOrder when index is out of range
    tree.beginRemove("00000005"); // Edge Case 3: Remove ID that doesn't exist

    std::vector<string> actualOutput = tree.beginGetNodeValues();
    //std::sort(actualOutput.begin(), actualOutput.end());
    std::vector<string> expectedOutput = {"00000001", "00000012", "00010101"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

TEST_CASE("Testing All 4 Rotations", "[flag]"){
    AVLTree tree;
    tree.beginInsert(std::vector<string> {"00000010", "\"Name Ten\""});
    tree.beginInsert(std::vector<string> {"00000009", "\"Name Nine\""});
    tree.beginInsert(std::vector<string> {"00000008", "\"Name Eight\""}); // left-left case
    tree.beginInsert(std::vector<string> {"00000006", "\"Name Six\""});
    tree.beginInsert(std::vector<string> {"00000007", "\"Name Seven\""}); // left-right case
    tree.beginInsert(std::vector<string> {"00000012", "\"Name Twelve\""});
    tree.beginInsert(std::vector<string> {"00000011", "\"Name Eleven\""}); //right-left case
    tree.beginInsert(std::vector<string> {"00000013", "\"Name Thirteen\""});
    tree.beginInsert(std::vector<string> {"00000014", "\"Name Fourteen\""}); //right-right case

    std::vector<string> actualOutput = tree.beginGetNodeValues();
    std::vector<string> expectedOutput = {"00000006", "00000007", "00000008", "00000009", "00000010", "00000011", "00000012", "00000013", "00000014"};

    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

// Test all three deletion cases (no children, 1 child, two children)
TEST_CASE("Testing All Deletion Cases", "[flag]"){
    AVLTree tree;   // Create a Tree object
    tree.beginRemove("12345678"); // Edge Case 1: Removing from empty tree
    tree.beginInsert(std::vector<string> {"00000001", "\"Kinnara\""});
    tree.beginInsert(std::vector<string> {"00000002", "\"Dara\""});
    tree.beginInsert(std::vector<string> {"00000003", "\"Martin\""});
    tree.beginInsert(std::vector<string> {"00000004", "\"Anabel\""});
    tree.beginRemove("00000003"); // ONE CHILD REMOVAL
    tree.beginInsert(std::vector<string> {"00000005", "\"Izzy\""});
    tree.beginInsert(std::vector<string> {"00000003", "\"Dani\""});
    tree.beginRemove("00000004"); // TWO CHILDREN REMOVAL
    tree.beginRemove("00000005"); // NO CHILD REMOVAL

    std::vector<string> actualOutput = tree.beginInorder();
    std::vector<string> expectedOutput = {"00000001", "00000012", "00010101"};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);

    REQUIRE(1 == 1);
}

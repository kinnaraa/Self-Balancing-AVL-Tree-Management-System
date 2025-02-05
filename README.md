**About:**

This project implements an AVL Tree, a self-balancing binary search tree, to manage hypothetical IDs and names of students. Operations include insertion, deletion, traversal (Inorder, Preorder, Postorder), and search by ID or name. The program maintains balance for efficient operations, using rotation mechanisms for rebalancing.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Challenges:**

- Dynamic memory allocation

- Memory leaks

- Handling edge cases (empty tree, unbalanced insertions requiring deep recursion, invalid inputs, etc)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

**Functions and Instructions for use:**

1. Insert a Node

   Command: insert "Name" ID

4. Remove a Node by ID

   Command: remove ID

5. Remove a Node by Inorder Index

   Command: removeInorder INDEX

6. Print Inorder Traversal

   Command: printInorder

7. Print Preorder Traversal

   Command: printPreorder

8. Print Postorder Traversal

   Command: printPostorder

9. Search for a Node by ID or Name

   Command: search ID  

   search "Name"

10. Print Tree Height

    Command: printLevelCount
   
**NOTES:**
- Names must be enclosed in double quotes ("") and IDs must be exactly 8 digits.
- Invalid inputs or unsupported commands will result in an "unsuccessful" message.

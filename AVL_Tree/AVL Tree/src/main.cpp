#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <sstream>
#include <regex>

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

class AVLTree // AVLTree class that stores TreeNodes and their functions
{
private:
    struct TreeNode // TreeNode struct inspired by the onlineGDB Wrapped BST example (https://www.onlinegdb.com/vWp_hhaQlC)
    {
        string id;
        string name;
        TreeNode *left;
        TreeNode *right;
        TreeNode(string x, string n) : id(x), name(n), left(nullptr), right(nullptr) {}
    };
    //initializing root node to a nullptr
    TreeNode* root = nullptr;

    // initializing all functions
    AVLTree::TreeNode* Insert(TreeNode* helpRoot, string id, const string& name);
    void Inorder(TreeNode* helpRoot);
    void Remove(TreeNode*& root, int id);
    void RemoveInorder(TreeNode* root, int index);
    void inorderNoPrint(TreeNode* root);
    void balanceTree(TreeNode*& root);
    int getBalanceFactor(TreeNode* node);
    int getHeight(TreeNode* node);
    void leftRotation(TreeNode*& node);
    void rightRotation(TreeNode*& node);
    void preorder(TreeNode* root);
    void postorder(TreeNode* root);
    void printLevelCount(TreeNode* root);
    void searchName(TreeNode* root, string name);
    void searchID(TreeNode* root, string id);
    void preorderNoPrint(TreeNode *root);
    vector<string> getNodeValues(); // for catch2 testing
    vector<TreeNode> nodeVector; //vector to store all nodes

public: // all public functions simply direct you to their corresponding private functions
    vector<string> beginGetNodeValues(); // for catch2 testing
    void beginInorder();
    void beginInsert(vector<string> inputVector);
    void beginRemove(string id);
    void beginRemoveInorder(int index);
    void beginPreorder();
    void beginPostorder();
    void beginSearchName(string name);
    void beginSearchID(string id);
    void beginPrintLevelCount();
};

vector<string> AVLTree::beginGetNodeValues(){ // for catch2 testing
    return getNodeValues();
}

vector<string> AVLTree::getNodeValues() { // for catch2 testing
    vector<string> nodeIntValues;
    for(int i = 0; i < nodeVector.size(); i++){
        nodeIntValues.push_back(nodeVector[i].id);
    }
    return nodeIntValues;
}

void AVLTree::Inorder(TreeNode* root) // 3 - Trees.pdf (slide 50-52)
{
    if(root != nullptr) {
        Inorder(root->left);
        if (nodeVector.empty()) {
            cout << root->name;
        } else {
            cout << ", " << root->name;
        }
        nodeVector.push_back(*root);
        Inorder(root->right);
    }
}

void AVLTree::preorder(TreeNode *root) { // 3 - Trees.pdf (slide 53)
    if(root != nullptr){
        if(nodeVector.empty()){
            cout<<root->name;
        }else{
            cout<<", "<<root->name;
        }
        nodeVector.push_back(*root);
        preorder(root->left);
        preorder(root->right);
    }
}

void AVLTree::postorder(TreeNode *root) { // 3 - Trees.pdf (slide 55)
    if(root != nullptr){
        postorder(root->left);
        postorder(root->right);
        if(nodeVector.empty()){
            cout<<root->name;
        }else{
            cout<<", "<<root->name;
        }
        nodeVector.push_back(*root);
    }
}

void AVLTree::printLevelCount(TreeNode *root) {
    cout<<getHeight(root)<<endl;
}

void AVLTree::searchID(TreeNode* root, string id) {
    if (root == nullptr){
        cout<<"unsuccessful"<<endl;
    }else{
        if(stoi(root->id) == stoi(id)){
            cout<<root->name<<endl;
        }else if (stoi(id) > stoi(root->id)){
            searchID(root->right, id);
        }else if (stoi(id) < stoi(root->id)){
            searchID(root->left, id);
        }else{
            cout<<"unsuccessful"<<endl;
        }
    }
}

void AVLTree::searchName(TreeNode* root, string name) {
    bool foundID = false;
    for(int i = 0; i < nodeVector.size(); i++){
        if(nodeVector[i].name == name){
            cout<<nodeVector[i].id<<endl;
            foundID = true;
        }
    }
    if (!foundID){
        cout<<"unsuccessful"<<endl;
    }
}

AVLTree::TreeNode* AVLTree::Insert(TreeNode* root, string id, const string& name) // 3 - Trees.pdf (slide 34)
{
    if (root == nullptr){
        auto newNode = new TreeNode(id, name);
        nodeVector.push_back(*newNode);
        cout<<"successful"<<endl;
        return newNode;
    }else if (id < root->id){
        root->left = Insert(root->left, id, name);
    }else if (id > root->id){
        root->right = Insert(root->right, id, name);
    }else{
        cout<<"unsuccessful"<<endl;
    }

    balanceTree(root);

    return root;
}

void AVLTree::Remove(TreeNode*& root, int id) { // 3 - Trees.pdf (slide 38)
    if(root == nullptr) {
        cout << "unsuccessful, root null" << endl;
        return;
    }
    if(id < stoi(root->id)) {
        Remove(root->left, id);
    }
    else if(id > stoi(root->id)) {
        Remove(root->right, id);
    }
    else {
        if(root->left == nullptr) { // has one child
            TreeNode* temp = root->right;
            delete root;
            root = temp;
        }
        else if(root->right == nullptr) { // has one child
            TreeNode* temp = root->left;
            delete root;
            root = temp;
        }
        else { // has two children
            TreeNode* successorParent = root;
            TreeNode* successor = root->right;
            while(successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            root->id = successor->id;
            root->name = successor->name;

            if(successorParent == root) { // remove successor
                successorParent->right = successor->right;
            }
            else {
                successorParent->left = successor->right;
            }
            delete successor;
        }
        cout << "successful" << endl;
    }
}

void AVLTree::balanceTree(TreeNode*& root) {
    if (getBalanceFactor(root) > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            rightRotation(root);
        }else {
            leftRotation(root->left);
            rightRotation(root);
        }
    }
    else if (getBalanceFactor(root) < -1) {
        if(getBalanceFactor(root->right) <= 0) {
            leftRotation(root);
        }else {
            rightRotation(root->right);
            leftRotation(root);
        }
    }
}

int AVLTree::getBalanceFactor(TreeNode* node) {
    if (node == nullptr){
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

int AVLTree::getHeight(TreeNode* node) {
    if (node == nullptr){
        return 0;
    }else{
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

void AVLTree::leftRotation(TreeNode*& node) {
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node = newRoot;
}

void AVLTree::rightRotation(TreeNode*& node) {
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node = newRoot;
}

void AVLTree::inorderNoPrint(TreeNode* root){
    if(root == nullptr)
        std::cout << "";
    else
    {
        inorderNoPrint(root->left);
        nodeVector.push_back(*root);
        inorderNoPrint(root->right);
    }
}

void AVLTree::preorderNoPrint(TreeNode *root) {
    if(root != nullptr){
        nodeVector.push_back(*root);
        preorderNoPrint(root->left);
        preorderNoPrint(root->right);
    }
}

void AVLTree::RemoveInorder(TreeNode* root, int index)
{
    if(index < nodeVector.size()){
        Remove(this->root, stoi(nodeVector[index].id));
    }else{
        cout<<"unsuccessful"<<endl;
    }
}

void AVLTree::beginInorder()
{
    nodeVector.clear();
    Inorder(this->root);
}

void AVLTree::beginInsert(vector<string> inputVector)
{
    std::regex names = std::regex("^\"[A-Za-z ]+\"$");
    std::regex ids = std::regex("[0-9]{8,8}");

    if(std::regex_search(inputVector[1], names) && std::regex_search(inputVector[2], ids)){
        inputVector[1] = inputVector[1].substr(1, inputVector[1].length() - 2);
        this->root = Insert(this->root, inputVector[2], inputVector[1]);
    }else{
        cout<<"unsuccessful"<<endl;
    }
}

void AVLTree::beginRemove(string id)
{
    std::regex ids = std::regex("[0-9]{8}");

    if(std::regex_search(id, ids)) {
        Remove(this->root, stoi(id));
    }else{
        cout<<"unsuccessful"<<endl;
    }
}

void AVLTree::beginRemoveInorder(int index){
    RemoveInorder(this->root, index);
}

void AVLTree::beginPreorder(){
    nodeVector.clear();
    preorder(this->root);
}

void AVLTree::beginPostorder() {
    nodeVector.clear();
    postorder(this->root);
}

void AVLTree::beginSearchID(string id) {
    searchID(this->root, id);
}

void AVLTree::beginSearchName(string name) {
    nodeVector.clear();
    inorderNoPrint(this->root);
    searchName(this->root, name);
}

void AVLTree::beginPrintLevelCount() {
    printLevelCount(this->root);
}


int main(){
    AVLTree *avl = new AVLTree;

    int commandCount = 0;
    cin>>commandCount;
    cin.ignore();

    string input;
    string x;
    vector<string> inputVector;
    string function;

    std::regex names = std::regex("^\"[A-Za-z ]+\"$");
    std::regex ids = std::regex("[0-9]{8,8}");

    for(int i = 0; i < commandCount; i++){
        getline(cin, input);
        istringstream inputStream(input);
        string currentWord;
        bool inQuotes = false;
        bool gotQuotes = false;
        int count = 0;

        for(auto x : input){
            count++;
            if(x == '"' && !inQuotes){
                currentWord += x;
                inQuotes = true;
            }else if (x == '"' && inQuotes){
                currentWord += x;
                inQuotes = false;
                gotQuotes = true;
            }else if (x == ' ' && inQuotes){
                currentWord += x;
            }else if (x == ' ' && !inQuotes){
                inputVector.push_back(currentWord);
                currentWord.clear();
            }else if (x == '"' && gotQuotes){
                cout<<"unsuccessful"<<endl;
                break;
            }else{
                currentWord += x;
            }
            if(x == input.back() && count == input.length()){
                inputVector.push_back(currentWord);
                currentWord.clear();
            }
        }

        if(inputVector[0] == "insert"){
            avl->beginInsert(inputVector);
        }else if (inputVector[0] == "remove"){
            avl->beginRemove(inputVector[1]);
        }else if (inputVector[0] == "printInorder"){
            avl->beginInorder();
            cout<<endl;
        }else if (inputVector[0] == "removeInorder"){
            avl->beginRemoveInorder(stoi(inputVector[1]));
        }else if (inputVector[0] == "printPreorder") {
            avl->beginPreorder();
            cout<<endl;
        }else if (inputVector[0] == "printPostorder"){
            avl->beginPostorder();
            cout<<endl;
        }else if (inputVector[0] == "search"){
            if (std::regex_search(inputVector[1], ids)){
                avl->beginSearchID(inputVector[1]);
            }else if (std::regex_search(inputVector[1], names)){
                inputVector[1] = inputVector[1].substr(1, inputVector[1].length() - 2);
                avl->beginSearchName(inputVector[1]);
            }
        }else if (inputVector[0] == "printLevelCount"){
            avl->beginPrintLevelCount();
        }else{
            cout<<"unsuccessful"<<endl;
        }
        inputVector.clear();
    }

    return 0;
}

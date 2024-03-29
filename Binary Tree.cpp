#include <iostream>
using namespace std;
//////////////////////
/////Introduction/////
//BT: every node has maximum two children. As a consequence, vector is not needed when constructing the BT
// We can realize it by Linked list, with `BTNode* left` and `BTNode* right` variables to store two children address
template<typename T>
class BTNode{
  public: 
    T data;
    BTNode* left;
    BTNode* right;
    // create the constructor
    BTNode(T data){
      this->data=data;
      // initialization
      left=NULL;
      right=NULL;
    }
    // recursive destructor:call the delete, delete the left child, delete the right child, then delete yourself
    ~BTNode(){
      delete left;
      delete right;
    }
};

int main(){
  // create nodes
  BTNode<int>* root=new BTNode<int>(1);
  BTNode<int>* n1=new BTNode<int>(2);
  BTNode<int>* n2=new BTNode<int>(3);
  // make connection
  root->left=n1;
  root->right=n2;
  // call the functions
  printTree(root);
  
  delete root;
  return 0;
}


//////////////////////////////
/////Print Tree Recursive/////
// Procedure: print the root, print the left sub-tree, print the right sub-tree recursively
void printTree(BTNode<int>* root){
  if(root==NULL){ //base case for binary tree
    return;
  }
  cout<<root->data<<": ";
  if(root->left!=NULL){
    cout<<"L"<<root->left->data;
  }
  if(root->right!=NULL){
    cout<<"R"<<root->right->data;
  }
  cout<<endl;

  printTree(root->left);
  printTree(root->right);
}
// return
// 1: L2R3
// 2: 
// 3:


//////////////////////////////
/////Take Input Recursive/////
// // Procedure: construct the root, construct the left sub-tree, construct the right sub-tree recursively
BTNode<int>* takeInput(){
  int rootData;
  cout<<"Enter Data: "<<endl;
  cin>>rootData;

  if(rootData==-1){ //for empty tree
    return NULL;
  }
  // create nodes
  BTNode<int>* root=new BTNode<int>(rootData);
  BTNode<int>* leftChild=takeInput(); //call takeInput function recursively for left tree
  BTNode<int>* rightChild=takeInput();
  // make connection
  root->left=leftChild;
  root->right=rightChild;
  return root;
}

int main(){
  BTNode<int>* root=takeInput();
  printTree(root);
  delete root;
  return 0;
}
// return
// Enter Data: 
// 1
// Enter Data: 
// 2
// Enter Data: 
// -1
// Enter Data: 
// -1
// Enter Data: 
// 3
// Enter Data: 
// -1
// Enter Data: 
// -1
// 1: L2R3
// 2: 
// 3:


///////////////////////////////
/////Take Input Level Wise/////
// use queue, create node, push inside queue, connect the node with its parent, then pop it from queue
#include <queue>
BTNode<int>* takeInputLevelWise(){
  // root data
  int rootData;
  cout<<"Enter Root Data: "<<endl;
  cin>>rootData;
  // create and push
  BTNode<int>* root=new BTNode<int>(rootData);
  queue<BTNode<int>*> q;
  q.push(root);
  // check the condition whether the q is empty
  while(!q.empty()){
    BTNode<int>* f=q.front();
    q.pop(); // remove
    
    // left side
    cout<<"Enter left child of "<<f->data<<endl;
    int leftChildData;
    cin>>leftChildData;

    if(leftChildData!=-1){ //create,push, connect
      BTNode<int>* child=new BTNode<int>(leftChildData);
      q.push(child);
      f->left=child;
    }
    // right side
    cout<<"Enter right child of "<<f->data<<endl;
    int rightChildData;
    cin>>rightChildData;

    if(rightChildData!=-1){ //create,push, connect
      BTNode<int>* child=new BTNode<int>(rightChildData);
      q.push(child);
      f->right=child;
    }
  }
  return root;
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);
  delete root;
  return 0;
}
// return
// Enter Root Data: 
// 1
// Enter left child of 1
// 2
// Enter right child of 1
// 3
// Enter left child of 2
// 4
// Enter right child of 2
// 5
// Enter left child of 3
// 6
// Enter right child of 3
// 7
// Enter left child of 4
// -1
// Enter right child of 4
// -1
// Enter left child of 5
// -1
// Enter right child of 5
// -1
// Enter left child of 6
// -1
// Enter right child of 6
// -1
// Enter left child of 7
// -1
// Enter right child of 7
// -1
// 1: L2R3
// 2: L4R5
// 4: 
// 5: 
// 3: L6R7
// 6: 
// 7: 


///////////////////////////////
/////Level Order Traversal/////
///Procedure:
// use queue, check the root, left side, right side exist or not
// if exists push the node inside the queue, pop the element, print the value
  // after finish pushing the elements in the same level, we push NULL in the queue
  // when print the elements as a binary tree, as soon as we meet a NULL, we start from a new line
  // In conclusion, NULL is used to differentiate between levels.
// when the queue is empty, stop execution

// LeetCode No.102 https://leetcode.com/problems/binary-tree-level-order-traversal/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > v; //create the vector
        if(root==NULL){
            return v; //now v is empty
        }
        vector<int> temp; //to store the result of current level
        // create a queue, push root level elements
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);

        while(!q.empty()){
            TreeNode* f=q.front();  //create a pointer variable
            q.pop(); //remove the element

            if(f==NULL){
                //cout<<endl; write in a new line
                v.push_back(temp);
                temp.clear(); //update to make temp empty
                if(!q.empty()){
                    q.push(NULL);
                }
            }else{ //print out the value
                temp.push_back(f->val); //left side
                if(f->left!=NULL){
                    q.push(f->left);
                }
                if(f->right!=NULL){  //right side
                    q.push(f->right);
                }
            }
        }
        return v;
    }
};
// T=O(N); S=O(N)


/////////////////////
/////Count Nodes/////
// Procedure: 
// answer=# of nodes present in left + # of nodes present in right + root(1)
// call the count recursion with left sub-trees and right sub-trees
// basic case: if the root is NULL;

// LeetCode No.222 https://leetcode.com/problems/count-complete-tree-nodes/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int countNodes(TreeNode* root) {
        // base case
        if(root==NULL){
            return 0;
        }
        // recursive case
        return countNodes(root->left)+countNodes(root->right)+1;
    }
};
// T=O(N); S=O(N) 


///////////////////////////
/////InOrder Traversal/////
// Rule: for every node use recursion, visit left side sub-tree->current root data->right side sub-tree (LDR)

// LeetCode No.94 https://leetcode.com/problems/binary-tree-inorder-traversal/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void InOrder(TreeNode* root, vector<int> &ans){ //pass by reference, change are permanent
        if(root==NULL) return ;

        InOrder(root->left, ans);
        ans.push_back(root->val);
        InOrder(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        // create a vector
        vector<int> ans;
        InOrder(root, ans);
        return ans;
    }
};
// T=O(N); S=O(N)


////////////////////////////
/////PreOrder Traversal/////
// Rule: for every node, D->L->R

// LeetCode No.144 https://leetcode.com/problems/binary-tree-preorder-traversal/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void PreOrder(TreeNode* root, vector<int> &ans){
        if(root==NULL) return ;

        ans.push_back(root->val);
        PreOrder(root->left, ans);
        PreOrder(root->right, ans);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        PreOrder(root, ans);
        return ans;
    }
};
// T=O(N); S=O(N);


//////////////////////////////////
/////Max Depth of Binary Tree/////
// `Height` of Binary Tree: find the farthest node from the root, recursing from left to right subtree->count the number of nodes between them with root node(+1)

// LeetCode No.104 Maximum Depth of Binary Tree  https://leetcode.com/problems/maximum-depth-of-binary-tree/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==NULL) return 0;
        //recursion
        int left=maxDepth(root->left);
        int right=maxDepth(root->right);

        return max(left,right)+1;
    }
};
// T=O(N), S=O(N)


///////////////////////////////
/////Symmetric Binary Tree/////
// task: to check whether it is a symmetric tree or not
// Procedure:
  // Draw a median vertical line
  // compare the strucure(Distance) and value of left and right side sub-trees, details as follow:
    // T1 root value=T2 root value
    // T1 left=T2 left
    // T1 right=T2 left
    // ...take recursion

// LeetCode No.101 https://leetcode.com/problems/symmetric-tree/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool helper(TreeNode* leftTree, TreeNode* rightTree){
        // compare the two trees
        // some special cases
        if(leftTree==NULL && rightTree!=NULL) return false;
        if(rightTree==NULL && leftTree!=NULL) return false;
        if(leftTree==NULL && rightTree==NULL) return true;
        // this line of code must be put at final, because of avoiding the running time error.
        if(leftTree->val != rightTree->val) return false;
        // recursion case
        return helper(leftTree->left, rightTree->right) && helper(leftTree->right, rightTree->left);
    }
    bool isSymmetric(TreeNode* root) {
        if(root==NULL) return true;
        return helper(root->left, root->right);
    }
};


///////////////////
/////Find Node/////
// Task: Given a binary tree and given a key, we need to find whether value is in this tree
// recursively searching the right and left sub-trees, if the value=key, then the key exists.
bool searchNode(BTNode<int>* root, int key){
  // base case
  if(root==NULL) return false;
  if(root->data==key){
    return true;
  }
  // recursive case
  return (searchNode(root->left, key) || searchNode(root->right, key));
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);

  cout<<"Searching for 8"<<endl;
  if(searchNode(root,8)){
    cout<<"Found"<<endl;
  }else{
    cout<<"Not Present"<<endl;
  }
  delete root;
  return 0;
}
// return:
// Enter Root Data: 
// 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1

// 1: L2R3
// 2: L4R5
// 4: 
// 5: 
// 3: L6R7
// 6: L8R9
// 8: 
// 9: 
// 7: 
// Searching for 8
// Found


///////////////////
/////Min Value/////
// Reference: INT_MAX and INT_MIN in C/C++ and Applications: https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
#include <climits>

int minValue(BTNode<int>* root){
  if(root==NULL){
    return INT_MAX; //specifies that an integer variable cannot store any value beyond this limit.
  }
  int leftMin=minValue(root->left); //give the minimum value of left side tree with recursion
  int rightMin=minValue(root->right);
  // comparison of these 2 values and root
  return min(root->data, min(leftMin, rightMin));
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);
  cout<<"Min Value: "<<minValue(root)<<endl;
  delete root;
  return 0;
}
// return:
// Enter Root Data: 
// 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1

// 1: L2R3
// 2: L4R5
// 4: 
// 5: 
// 3: L6R7
// 6: L8R9
// 8: 
// 9: 
// 7: 
// Min Value: 1

/////Another way:
void minValue1(BTNode<int>* root, int &ans){
  if(root==NULL){
    return ; 
  }
  ans=min(ans, root->data);
  minValue1(root->left, ans);
  minValue1(root->right, ans);
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);

  cout<<"Min Value using Another Way: ";
  int minimumValue=INT_MAX;
  minValue1(root, minimumValue); //update
  cout<<minimumValue<<endl;

  delete root;
  return 0;
}
// return:
// Min Value using Another Way: 1


///////////////////
/////Max Value/////
// Similar to find Min Value!
int maxValue(BTNode<int>* root){
  if(root==NULL){
    return INT_MIN; //specifies that an integer variable cannot store any value below this limit
  }
  int leftMax=maxValue(root->left); 
  int rightMax=maxValue(root->right);
  return max(root->data, max(leftMax, rightMax));
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);
  cout<<"Max Value: "<<maxValue(root)<<endl;
  delete root;
  return 0;
}
// return
// Max Value: 9


//////////////////////////////
/////🍃Count Leaf Nodes🍃/////
int countLeafNode(BTNode<int>* root){
  // base case
  if(root==NULL){
    return 0;
  }
  if(root->left==NULL && root->right==NULL){
    return 1;
  }
  // recursive case
  return countLeafNode(root->left)+countLeafNode(root->right);
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);
  cout<<"Number of Leaf Nodes: "<<countLeafNode(root)<<endl;
  delete root;
  return 0;
}
// return:
// Number of Leaf Nodes: 5


//////////////////////////////////////////////////////////////
/////Construct Tree from PreOrder and InOrder Traversal🤯/////
// The necessity to use two kinds of Traversals: if we only required to construct tree using InOrder method, the results are not unique. Adding another traversal method helps us get the `unique tree` at final.
// Procedure: construct the root, build left sub-tree recursively, build right sub-tree recursively
  // 🌟left sub-tree construction: leftInOrderStart(=InOrderStart) index, leftInOrderEnd(=RootIndex-1) index, leftPreOrderStart(=PreOrderStart+1) index, leftPreOrderEnd(=lInE-lInS+lPreS) index are needed.
    // Explanation: leftInOrderEnd Index - leftInOrderStart Index= leftPreOrderEnd Index - leftPreOrderStart Index
  // 🌟Similarly, right sub-tree construction: rightInOrderStart(=RootIndex+1) index, rightInOrderEnd(=InOrderEnd) index, rightPreOrderStart(=leftPreOrderEnd+1) index, rightPreOrderEnd(=PreOrderEnd) index are needed.

// LeetCode No.105 https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTreeHelper(vector<int>& InOrderTraversal, vector<int>& PreOrderTraversal, int InOrderStart, int InOrderEnd, int PreOrderStart, int PreOrderEnd){
        // Base case, empty
        if(InOrderStart>InOrderEnd || PreOrderStart>PreOrderEnd){
            return NULL;
        }
        // define the root data
        int rootData=PreOrderTraversal[PreOrderStart]; //initialization, passing PreOrderStart
        // find root index with no duplicates assumption by traversing
        int rootIndex=-1; //initialization
        for(int i=InOrderStart;i<=InOrderEnd; i++){
            if(InOrderTraversal[i]==rootData){
                rootIndex=i;
                break;
            }
        }
        // find out the leaf values
        int leftInOrderStart=InOrderStart;
        int leftInOrderEnd=rootIndex-1;
        int leftPreOrderStart=PreOrderStart+1;
        int leftPreOrderEnd=leftInOrderEnd - leftInOrderStart + leftPreOrderStart;

        int rightInOrderStart=rootIndex+1;
        int rightInOrderEnd=InOrderEnd;
        int rightPreOrderStart=leftPreOrderEnd+1;
        int rightPreOrderEnd=PreOrderEnd;

        // construct root node
        TreeNode* root=new TreeNode(rootData); //pass the root data
        // Call the recursion on left sub-tree and right sub-tree
        root->left=buildTreeHelper(InOrderTraversal, PreOrderTraversal, leftInOrderStart, leftInOrderEnd, leftPreOrderStart, leftPreOrderEnd);
        root->right=buildTreeHelper(InOrderTraversal, PreOrderTraversal, rightInOrderStart, rightInOrderEnd, rightPreOrderStart, rightPreOrderEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // find the total number of elements
        int n=inorder.size();
        // call the function
        return buildTreeHelper(inorder, preorder, 0, n-1, 0, n-1);
    }
};


/////////////////////////////////////////////////////////////
/////Construct Tree from PostOrder and InOrder Traversal/////
// 🌟left sub-tree construction: InOrderStart(=InOrderStart) index, leftInOrderEnd(=RootIndex-1) index, leftPostOrderStart(=PostOrderStart) index, leftPostOrderEnd(=lInE-lInS+lPostS) index are needed.
// 🌟Similarly, right sub-tree construction: rightInOrderStart(=RootIndex+1) index, rightInOrderEnd(=InOrderEnd) index, rightPostOrderStart(=leftPostOrderEnd+1) index, rightPostOrderEnd(=PostOrderEnd-1) index are needed.

// LeetCode No.106 https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTreeHelper(vector<int>& InOrderTraversal, vector<int>& PostOrderTraversal, int InOrderStart, int InOrderEnd, int PostOrderStart, int PostOrderEnd){
        // Base case, empty
        if(InOrderStart>InOrderEnd || PostOrderStart>PostOrderEnd){
            return NULL;
        }
        // define the root data
        int rootData=PostOrderTraversal[PostOrderEnd]; 
        // find root index with no duplicates assumption by traversing
        int rootIndex=-1; //initialization
        for(int i=InOrderStart;i<=InOrderEnd; i++){
            if(InOrderTraversal[i]==rootData){
                rootIndex=i;
                break;
            }
        }
        // find out the leaf values
        int leftInOrderStart=InOrderStart;
        int leftInOrderEnd=rootIndex-1;
        int leftPostOrderStart=PostOrderStart;
        int leftPostOrderEnd=leftInOrderEnd - leftInOrderStart + leftPostOrderStart;

        int rightInOrderStart=rootIndex+1;
        int rightInOrderEnd=InOrderEnd;
        int rightPostOrderStart=leftPostOrderEnd+1;
        int rightPostOrderEnd=PostOrderEnd-1;

        // construct root node
        TreeNode* root=new TreeNode(rootData); //pass the root data
        // Call the recursion on left sub-tree and right sub-tree
        root->left=buildTreeHelper(InOrderTraversal, PostOrderTraversal, leftInOrderStart, leftInOrderEnd, leftPostOrderStart, leftPostOrderEnd);
        root->right=buildTreeHelper(InOrderTraversal, PostOrderTraversal, rightInOrderStart, rightInOrderEnd, rightPostOrderStart, rightPostOrderEnd);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n=inorder.size(); //or the same as int n=postorder.size()
        return buildTreeHelper(inorder, postorder, 0, n-1, 0, n-1);
    }
};


/////////////////////////////////
/////Diameter of Binary Tree/////
// Diameter: the maximum distance between one node and another
  // Option1: the diameter=distance between the most left bottom node and the most right bottom node
    // the diameter not has to pass the root node
  // Option2: the diameter=distance between the most left bottom node and the most right bottom node both in left sub-tree
  // Option3: the diameter=distance between the most left bottom node and the most right bottom node both in right sub-tree

// LeetCode 543 https://leetcode.com/problems/diameter-of-binary-tree/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int height(TreeNode* root){
        if(root==NULL){
            return 0;
        }
        return 1+max(height(root->left),height(root->right));
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==NULL){
            return 0;
        }
        int option1=height(root->left)+height(root->right);
        int option2=diameterOfBinaryTree(root->left); //call the recursion
        int option3=diameterOfBinaryTree(root->right);
        return max(option1, max(option2, option3));
    }
};
// T=O(N^height), at worst, T=O(N^2)


/////Optimization Approach with two variables
  // Hight=1+max(leftHight, rightHeight)
  // Diameter=max(leftHeight+rightHeight, leftDiameter, rightDiameter)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    pair<int, int> heightDiameter(TreeNode* root){
        // basic case
        if(root==NULL){
            pair<int, int> p;
            p.first=0;
            p.second=0;
            return p;
        }
        // initialization, call the recursion
        pair<int,int> leftAns=heightDiameter(root->left);
        pair<int, int> rightAns=heightDiameter(root->right);
        // create variables
        int lh=leftAns.first;
        int ld=leftAns.second;
        int rh=rightAns.first;
        int rd=rightAns.second;

        // find out the overall height
        int height=1+max(lh,rh);
        int diameter=max(lh+rh, max(ld,rd));
        // create the pair to store the results
        pair<int, int> p;
        p.first=height;
        p.second=diameter;
        return p;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        pair<int, int> p=heightDiameter(root); //call the function
        return p.second;
    }
};
// T=O(N)


///////////////////////////
/////Root to Node Path/////
// print the path which is stored in a vector
bool getPath(BTNode* root, int value, vector<int> &ans){ //pass by reference, printing inside the main
  // basic case
  if(root==NULL){
    return false;
  }
  ans.push_back(root->data);
  if(root->data==value){
    return True;
  }
  // call the recursion on sub-trees
  bool left=getPath(root->left, value, ans);
  bool right=getPath(root->right, value, ans);

  if(left || right){ //if left is true or right is true, the path can be found
    return True;
  }
  // else:
  ans.pop_back(); //remove the elements from vector
  return false;
}

int main(){
  BTNode<int>* root=takeInputLevelWise();
  printTree(root);

  vector<int> v;
  if(getPath(root, 9, v)){ //given value presents
    for(int i=0;i<v.size();i++){
      cout<<v[i]<<" ";
    }
    else{
      cout<<"No Path Found"<<endl;
    }
  };
  delete root;
  return 0;
}


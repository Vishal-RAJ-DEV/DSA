#include <iostream>
#include <vector>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    // Constructor to initialize
    // the node with a value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to invert the binary tree
Node* invertTree(Node* root) {
    if (root == nullptr) return nullptr;

    Node* left = invertTree(root->left);   // Store the inverted left subtree
    Node* right = invertTree(root->right); // Store the inverted right subtree

    root->right = left;  // Swap: assign inverted left subtree to right
    root->left = right;  // Swap: assign inverted right subtree to left

    return root; 
}

// Function to perform inorder traversal
vector<int> inOrder(Node* root) {
    vector<int> result;
    if (root == nullptr) return result;
    
    // First visit left subtree
    vector<int> left = inOrder(root->left);
    result.insert(result.end(), left.begin(), left.end());
    
    // Then visit root
    result.push_back(root->data);
    
    // Finally visit right subtree
    vector<int> right = inOrder(root->right);
    result.insert(result.end(), right.begin(), right.end());
    
    return result;
}

// Main function
int main()
{
    // Creating a sample binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Before inversion - Inorder Traversal: ";
    vector<int> before = inOrder(root);
    for(int val : before) {
        cout << val << " ";
    }
    cout << endl;
    
    // Invert the tree
    root = invertTree(root);
    
    // Getting inorder traversal after inversion
    vector<int> result = inOrder(root);

    // Displaying the inorder traversal result
    cout << "After inversion - Inorder Traversal: ";
    // Output each value in the
    // inorder traversal result
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

/*
invertTree(1)
├── left = invertTree(2) ────────────────────┐
│   ├── left = invertTree(4) ─────────────┐   │
│   │   ├── left = invertTree(null) ──┐   │   │
│   │   │   └── return null           │   │   │
│   │   ├── right = invertTree(null) ─┼───┘   │
│   │   │    └── return null          │       │
│   │   ├── root->right = null ───────┘       │
│   │   ├── root->left = null                 │
│   │   └── return Node(4) ───────────────────┘
│   │                                         │
│   ├── right = invertTree(5) ────────────┐   │
│   │   ├── left = invertTree(null) ──┐   │   │
│   │   │   └── return null           │   │   │
│   │   ├── right = invertTree(null) ─┼───┘   │
│   │   │    └── return null          │       │
│   │   ├── root->right = null ───────┘       │
│   │   ├── root->left = null                 │
│   │   └── return Node(5) ───────────────────┘
│   │                                         │
│   ├── root->right = Node(4) [swap] ─────────┘
│   ├── root->left = Node(5) [swap]
│   └── return Node(2) with swapped children
│
├── right = invertTree(3) ───────────────────┐
│   ├── left = invertTree(null) ──┐          │
│   │   └── return null           │          │
│   ├── right = invertTree(null) ─┼──────────┘
│   │    └── return null          │
│   ├── root->right = null ───────┘
│   ├── root->left = null
│   └── return Node(3)
│
├── root->right = Node(2) [swap] ────────────┘
├── root->left = Node(3) [swap]
└── return Node(1) with swapped children

Original:       After Step 6:      Final Result:
    1               1                   1
   / \             / \                 / \
  2   3           2   3               3   2
 / \      →      / \          →          / \
4   5           5   4                   5   4
*/
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

// recursion
bool isSymmetric(TreeNode* root) {
    if(!root) return true; // can delete this line
    return isSame(root->left, root->right);
}

bool isSame(TreeNode* l, TreeNode* r){
    if(!l && !r) return true; // l and r are null
    if(!l || !r) return false; // l or r is null
    if(l->val != r->val) return false;
    return isSame(l->left, r->right) && isSame(l->right, r->left);
}

// iteration 没想出来
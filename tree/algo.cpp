#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void preorderHelper(TreeNode* root, std::vector<int> &vec) {
    if(root == nullptr) {
        return;
    }
    vec.push_back(root->val);
    preorderHelper(root->left, vec);
    preorderHelper(root->right, vec);
    return;
}

std::vector<int> preorderTraversal(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) {
        return result;
    }
    result.push_back(root->val);

    preorderHelper(root->left,result);
    preorderHelper(root->right,result);

    return result;
}

void inorderHelper(TreeNode* root, std::vector<int> &vec) {
    if(root == nullptr) {
        return;
    }
    inorderHelper(root->left, vec);
    vec.push_back(root->val);
    inorderHelper(root->right, vec);
    return;
}

std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) {
        return result;
    }

    inorderHelper(root->left,result);
    result.push_back(root->val);
    inorderHelper(root->right,result);

    return result;
}

void postorderHelper(TreeNode* root, std::vector<int> &vec) {
    if(root == nullptr) {
        return;
    }
    postorderHelper(root->left, vec);
    postorderHelper(root->right, vec);
    vec.push_back(root->val);
    return;
}

std::vector<int> postorderTraversal(TreeNode* root) {
    std::vector<int> result;
    if (root == nullptr) {
        return result;
    }

    postorderHelper(root->left,result);
    postorderHelper(root->right,result);
    result.push_back(root->val);

    return result;
}

void levelOrderHelper(TreeNode* root, std::vector<std::vector<int>> &vec, int level) {
    if(root == nullptr) {
        return;
    }

    if (level == vec.size()) {
        vec.push_back(std::vector<int>());
    }
    vec[level].push_back(root->val);
    levelOrderHelper(root->left, vec, level + 1);
    levelOrderHelper(root->right, vec, level + 1);
    return;
}

std::vector<std::vector<int>> levelOrderTraversal(TreeNode* root) {
    std::vector<std::vector<int>> result;
    int level = 0;
    if (root == nullptr) {
        return result;
    }

    if (level == result.size()) {
        result.push_back(std::vector<int>());
    }
    result[level].push_back(root->val);
    levelOrderHelper(root->left,result, level + 1);
    levelOrderHelper(root->right,result, level + 1);

    return result;
}

void rightSideHelper(TreeNode* root, std::vector<int> &vec, int level) {
    if(root == nullptr) {
        return;
    }

    if (level == vec.size()) {
        vec.push_back(0);
    }
    vec[level] = root->val;
    rightSideHelper(root->left, vec, level + 1);
    rightSideHelper(root->right, vec, level + 1);
    return;
}

std::vector<int> rightSideTraversal(TreeNode* root) {
    std::vector<int> result;
    int level = 0;
    if (root == nullptr) {
        return result;
    }

    if (level == result.size()) {
        result.push_back(0);
    }
    result[level] = root->val;
    rightSideHelper(root->left,result, level + 1);
    rightSideHelper(root->right,result, level + 1);

    return result;
}


bool isSymmetricHelper(TreeNode* l, TreeNode* r) {
    if(l == nullptr || r == nullptr)
        return l == nullptr && r == nullptr;

    if (l->val != r->val)
        return false;

    return isSymmetricHelper(l->left, r->right) && isSymmetricHelper(l->right, r->left);
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr)
        return true;
    return isSymmetricHelper(root->left, root->right);
}

bool isSameHelper(TreeNode* l, TreeNode* r) {
    if(l == nullptr || r == nullptr)
        return l == nullptr && r == nullptr;

    if (l->val != r->val)
        return false;

    return isSameHelper(l->left, r->left) && isSameHelper(l->right, r->right);
}

bool isSame(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr)
        return true;
    return isSameHelper(p, q);
}

bool isLeaf(TreeNode* root) {
    return root->left == nullptr && root->right == nullptr;
}

bool hasPathSumHelper(TreeNode* root, int currSum, int targetSum) {
    if (root == nullptr)
        return false;
    currSum += root->val;
    if (currSum == targetSum && isLeaf(root))
        return true;
    return hasPathSumHelper(root->left, currSum, targetSum) || hasPathSumHelper(root->right, currSum, targetSum);

}

bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) {
        return targetSum == 0 ? true : false;
    }
    return hasPathSumHelper(root->left, root->val, targetSum) || hasPathSumHelper(root->right, root->val, targetSum);
}

void depthHelper(TreeNode* root, int currDepth, std::vector<int> &data) {
    if(!root)
        return;
    currDepth += 1;
    if(isLeaf(root))
        data.push_back(currDepth);
    depthHelper(root->left, currDepth, data);
    depthHelper(root->right, currDepth, data);
}

int findMin(std::vector<int> &data) {
    if(!data.size())
        return 0;

    int result = data[0];
    for(auto &&el : data)
        if(el < result)
            result = el;

    return result;
}

int minDepth(TreeNode* root) {
    if(!root) {
        return 0;
    }
    int needle = 0;
    std::vector<int> data;
    depthHelper(root, needle, data);
    return findMin(data);
}

int main() {
    // Кривое дерево:
    //              1
    //               \
    //                2
    //                 \
    //                  3
    //                   \
    //                    4
    //                     \
    //                      5
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    root->right->right->right = new TreeNode(4);
    root->right->right->right->right = new TreeNode(5);

    // Тест для minDepth
    std::cout << "Minimum Depth (кривое дерево): " << minDepth(root) << std::endl;

    // Тесты для hasPathSum
    std::cout << "Has path sum (15): " << (hasPathSum(root, 15) ? "Yes" : "No") << std::endl; // 1 + 2 + 3 + 4 + 5
    std::cout << "Has path sum (10): " << (hasPathSum(root, 10) ? "Yes" : "No") << std::endl; // Нет пути

    // Освобождение памяти
    delete root->right->right->right->right;
    delete root->right->right->right;
    delete root->right->right;
    delete root->right;
    delete root;

    return 0;
}
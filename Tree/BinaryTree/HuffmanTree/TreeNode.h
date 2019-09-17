#include <cstddef>

using namespace std;

struct TreeNode
{
	TreeNode(int _val=0):val(_val),left(NULL),right(NULL)
	{
	}

	int val;
	TreeNode *left;
	TreeNode *right;
};

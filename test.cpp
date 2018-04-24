#include <iostream>
#include <fstream>
#include <string>
#include "title.h"

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() {};
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution 
{
public:
	int temp = -1;
	int final = -1;
	int count = 0;

	int rob(TreeNode* root) 
	{
		vector<int> res = dfs(root);
		return max(res[0], res[1]);
	}
	vector<int> dfs(TreeNode *root) 
	{
		if (!root) return vector<int>(2, 0);
		vector<int> left = dfs(root->left);
		vector<int> right = dfs(root->right);
		vector<int> res(2, 0);
		res[0] = max(left[0], left[1]) + max(right[0], right[1]);
		res[1] = left[0] + right[0] + root->val;

		temp = max(res[0], res[1]);
		final = max(final, temp);
		count++;
		return res;
	}
};


int main()
{
	Json::Reader reader;
	Json::Value root;

	TreeNode tree[MAX];
	int i = -1;

	ifstream is(filename, ios::binary);//read

	if (!is.is_open())
	{
		cout << "Error opening file\n";
		return -1;
	}	

	if (reader.parse(is, root))
	{
		while (!root[to_string(++i)].isNull())//访问节点
		{
			if (!root[to_string(i)]["left"].isNull())//left
			{
				string num1 = root[to_string(i)]["left"].asString();
				std::string::size_type sz;
				int num = std::stoi(num1, &sz);

				if (num <= i)
				{
					cerr << "map error" << endl;
					getchar();
					return -1;
				}
				else
					tree[i].left = &tree[num];
			}
			else
				tree[i].left = NULL;
			if (!root[to_string(i)]["right"].isNull())//right
			{
				string num1 = root[to_string(i)]["right"].asString();
				std::string::size_type sz;
				int num = std::stoi(num1, &sz);

				if (num <= i)
				{
					cerr << "map error" << endl;
					getchar();
					return -1;
				}
				else
					tree[i].right = &tree[num];
			}
			else
				tree[i].right = NULL;
			if (!root[to_string(i)]["value"].isNull())//val
			{
				tree[i].val = root[to_string(i)]["value"].asInt();
			}
			else
			{
				cerr << "lack value error" << endl;
				getchar();
				return -1;
			}
		}

	}
	else
	{
		cerr << "blank error" << endl;
		getchar();
		return -1;
	}
	is.close();

	//print
		
	Solution solution;
	solution.rob(&(tree[0]));

	cout <<"对于该二叉树地图，最大价值为："<< solution.final << endl;
	cout << "读取节点的次数为：" << solution.count << endl;

	getchar();
	return 0;
}
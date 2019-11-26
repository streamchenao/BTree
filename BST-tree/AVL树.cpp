#include<iostream>
using namespace std;
#if 0
template<typename T>
class AVLTree
{
public:
	AVLTree() :root(nullptr) {}
	~AVLTree() {}
	// 递归的插入操作
	void insert(const T& val)
	{
		root = insert(root, val);
	}
	// 递归的删除操作
	void remove(const T& val);
private:
	struct AVLnode
	{
		AVLnode(T dat = T()) :data(dat), left(nullptr), right(nullptr), height(0) {}
		T data;
		AVLnode* left;
		AVLnode* right;
		int height;//记录节点在树中所处的高度值
	};
	AVLnode* root;
	//返回节点所处的高度值
	int getheight(AVLnode *node)
	{
		return node == nullptr ? 0 : node->height;
	}
	//获取左右孩子中高度大的那一个
	int maxHeight(AVLnode* left, AVLnode* right)
	{
		return getheight(left) > getheight(right) ? getheight(left) : getheight(right);
	}

	//插入操作的递归接口    插入就是找到空的地方，再插入。递归的时候找地方插入节点 。。 回溯的时候判断是否失衡
	AVLnode* insert(AVLnode* node, const T& val)    // 因此回溯的时候判断的语句应该写在递归函数的后面
	{
		if (node == nullptr)
		{
			return new AVLnode(val);
		}
		if (node->data > val)
		{
			node->left = insert(node->left, val);

			if (getheight(node->left) - getheight(node->right) > 1)//往左子树中插导致的失衡
			{
				if (getheight(node->left->left) >= getheight(node->left->right)) //左子树的左边太高导致的失衡
				{
					node = rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}

		else if (node->data < val)
		{
			node->right = insert(node->right, val);
		//想要在递归代码的回溯过程中做的操作，都应当写在递归代码的后面。
			if (getheight(node->right) - getheight(node->left) > 1)//往右子树中插导致的失衡
			{
				if (getheight(node->right->right) >= getheight(node->right->left)) //右子树的右边太高导致的失衡
				{
					node = leftRotate(node);
				}
				else // 右子树的左边太高导致的失衡
				{
					node = rightBalance(node);
				}
			}
		}
		//在递归回溯的过程中更新对应节点的高度值
		node->height = maxHeight(node->left, node->right) + 1;
		return node;
	}
	//接下来封装平衡操作的接口，因为用户只会接触到insert。所以将平衡操作封装在private中

	//左旋转操作   返回值是 旋转完后的新的树的根的地址。供后续递归继续使用。
	AVLnode* leftRotate(AVLnode* node)
	{
		//记着不光光是要做旋转操作，还要更新child和parents的高度值
		AVLnode* child = node->right;
		node->right = child->left;
		child->left = node;

		node->height = maxHeight(node->left, node->right)+1;
		child->height = maxHeight(child->left, child->right)+1;
		return child;
	}
	//右旋转操作
	AVLnode* rightRotate(AVLnode* node)
	{
		//记着不光光是要做旋转操作，还要更新child和parents的高度值
		AVLnode* child = node->left;
		node->left = child->right;
		child->right = node;

		node->height = maxHeight(node->left, node->right)+1;
		child->height = maxHeight(child->left, child->right)+1;
		return child;
	}
	//左平衡操作   左-右旋
	AVLnode* leftBalance(AVLnode* node)
	{
		//记着不光光是要做旋转操作，还要更新child和parents的高度值
		AVLnode* child = node->left;		
		leftRotate(child);
		rightRotate(node);
		return child;
	}
	//右平衡操作 右-左旋
	AVLnode* rightBalance(AVLnode* node)
	{
		//记着不光光是要做旋转操作，还要更新child和parents的高度值
		AVLnode* child = node->right;
		rightRotate(child);
		leftRotate(node);
		return child;
	}

	//AVL树 删除指定节点的递归接口
	AVLnode* remove(AVLnode* node, const T& val)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->data > val)
		{
			node->left = remove(node->left, val);
			// #1
			if (getheight(node->right) - getheight(node->left) > 1)
			{
				if (getheight(node->right->right) >= getheight(node->right->left))
				{
					node = leftRotate(node); // 右孩子  -   右子树
				}
				else
				{
					node = rightBalance(node); // 右孩子   -   左子树
				}
			}
		}
		else if (node->data < val)
		{
			node->right = remove(node->right, val);
			// #2
			if (height(node->left) - height(node->right) > 1)
			{
				if (getheight(node->left->left) >= getheight(node->left->right))
				{
					node = rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}
		else
		{
			if (node->left != nullptr && node->right != nullptr)
			{
				if (getheight(node->left) >= getheight(node->right))
				{  // 删前驱节点
					AVLNode* pre = node->left;
					while (pre->right != nullptr)
						pre = pre->right;
					node->data = pre->data;
					node->left = remove(node->left, pre->data);
				}
				else
				{
					// 删除后继节点
					AVLNode* post = node->right;
					while (post->left != nullptr)
						post = post->left;
					node->data = post->data;
					node->right = remove(node->right, post->data);
				}
			}
			else
			{
				if (node->left != nullptr)
				{
					AVLNode* left = node->left;
					delete node;
					return left;
				}
				else if (node->right != nullptr)
				{
					AVLNode* right = node->right;
					delete node;
					return right;
				}
				else
				{
					delete node;
					return nullptr;
				}
			}
		}

		// #3 从叶子节点向根节点回溯的过程中，更新节点的高度值
		node->height = maxHeight(node->left, node->right) + 1;
		return node;
	}

};
int main()
{
	AVLTree<int> AVL;
	for(int i=1;i<=10;++i)
	{
		AVL.insert(i);
	}
	return 0;
}
#endif
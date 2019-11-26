#include<iostream>
using namespace std;
enum Color { RED, BLACK };
template<typename T>
class RBTree
{
public:
	RBTree() :root(nullptr) {}
	void insert(const T& val)
	{
		//插入和BST树的插入是一样的，不过当遇到连续的两个红色节点时需要调整。
		if (root == nullptr)
		{
			root = new RBNode(val,BLACK);
			return;
		}
		RBNode* parent = nullptr;
		RBNode* cur = root;
		//找对应值应该插入的位置
		while (cur != nullptr)
		{
			if (val > cur->data)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (val < cur->data)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				return;
			}
		}
		RBNode* node = new RBNode(val,RED);
		node->parent = parent;
		//判断应该插入右孩子域还是左孩子域
		if (val > parent->data)
		{
			parent->right = node;		
		}
		else
		{
			parent->left = node;
		}
		if (parent->color == RED)//如果新插入节点的父节点是红色的
		{
			fixAfterInsert(node);//就从当前节点开始调整
		}	
	}

	//删除指定值为val的节点
	void earse(const T& val)
	{
		RBNode* node = find(val);
		if (node == nullptr)
		{
			return;
		}
		//要删除的节点在这颗RB树中
		//情况一:待删除节点是红色的，修改对应的指针域就ok了
		if (node->color == RED)
		{

		}
		else
		{

		}



	}


private:
	struct RBNode
	{
		RBNode(T da, Color col):
			data(da),
			color(col),
			left(nullptr),
			right(nullptr),
			parent(nullptr) 
		{}
		T data;
		Color color;
		RBNode *left;
		RBNode *right;
		RBNode *parent;
	};
	RBNode* root;
	Color color(RBNode *node)
	{
		return node == nullptr ? BLACK : node->color;
	}
	void setColor(RBNode* node, Color color) { node->color = color; }
	RBNode* left(RBNode* node) { return node->left; }
	RBNode* right(RBNode* node) { return node->right; }
	RBNode* parent(RBNode* node) { return node->parent; }
	// 	color(parent(parent(node)))
	//以node为根节点进行左旋
	void leftRotate(RBNode* node)
	{	
		/*总共要修改六个指针域。结合图来看*/
		RBNode* child = node->right;
		child->parent = node->parent;
		if (node->parent == nullptr)
		{
			root = child;
		}
		else if (node->parent->left == node)
		{
			node->parent->left = child;
		}
		else if(node->parent->right == node)
		{
			node->parent->right = child;
		}

		node->right = child->left;
		child->left = node;
		if (child->left != nullptr)
		{
			child->left->parent = node;
		}
		node->parent = child;
	}
	void rightRotate(RBNode* node)
	{
		RBNode* child = node->left;
		child->parent = node->parent;
		if (node->parent == nullptr)
		{
			root = child;
		}
		else if(node->parent->right == node)
		{
			node->parent->right = child;
		}
		else if (node->parent->left == node)
		{
			node->parent->left = child;
		}
		node->parent = child;
		node->left = child->right;
		if (child->right != nullptr)
		{
			child->right->parent = node;
		}
		child->right = node;
	}
	//RB树插入调整接口,从当前节点node开始调整，这里node指的就是新插入节点
	void fixAfterInsert(RBNode *node)
	{
		//父节点的颜色一直为红色，就得一直向上调整
		while ( color(parent(node)) == RED )
		{ 
			//首先分新插入节点在爷爷节点的左侧还是右侧(这对叔叔节点是哪一个有影响)
			if (parent(node) == left(parent(parent(node))))
			{
				//如果待插入节点在祖先节点的左边
				RBNode* un = right(parent(parent(node)));
				if (color(un) == RED)// 解决情况一的情形
				{
					setColor(un, BLACK);
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					//别忘了向上回溯，此时node指向的应该是当前节点的爷爷节点
					node = parent(parent(node));
				}
				else //叔叔节点为黑色，即处理情况二
				{
					//这里记着还有情况三的后半部分也和情况二一样
					if (right(parent(node)) == node)//如果新插入的节点在父节点的右边
					{
						node = node->parent;   //这里要求Node指向的是位于最下边的那个节点
						leftRotate(node);
					}
					//下面是统一处理情况二
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;//这样本次调整完成以后，局部就是满足RB树性质的了，不用在往上回溯了
				}
			}
			else if (parent(node) == right(parent(parent(node))))//新插入节点在爷爷节点的右侧
			{
				RBNode* un = left(parent(parent(node)));
				if (color(un) == RED)
				{
					setColor(un, BLACK);
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					//别忘了向上回溯，此时node指向的应该是当前节点的爷爷节点
					node = parent(parent(node));
				}
				else //叔叔节点为黑色，即处理情况二
				{
					//这里记着还有情况三的后半部分也和情况二一样
					if (left(parent(node)) == node)//如果新插入的节点在父节点的左边
					{
						node = node->parent;   //这里要求Node指向的是位于最下边的那个节点
						rightRotate(node);
					}
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break;
				}
			}
		}
		/*如果一直向上调整，一直到了根节点。那么根节点的父节点为nullptr，nullptr默认为黑色。
		然后跳出循环，表示当前node节点的父节点颜色为黑，
		很可能当前节点已经是根节点了，根节点的父节点为空，当然也算黑色了。
		所以当前节点可能被置成红色了，最后要强制置为黑色*/
		setColor(root, BLACK);
	}
	//提供query接口，供earse函数使用
	bool query(RBNode* node, const T& val, RBNode* &find)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (node->data == val)
		{
			find = node;
			return true;
		}
		return query(node->left,val,find) || query(node->right, val,find); // 以VLR前序遍历的方式来访问整颗RB树
	}
	
	RBNode* find(const T& val)
	{
		RBNode* find = nullptr;
		if (query(root, val, find))
		{
			return find;
		}
	}


};

int main()
{
	RBTree<int> rbtree;
	for (int i = 1; i <= 10; ++i)
	{
		rbtree.insert(i);
	}	

	return 0;
}





/*ctrl+F10 debug到光标所在处
再按F5,debug到下一个断点处
*/
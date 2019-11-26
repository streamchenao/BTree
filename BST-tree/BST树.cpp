
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;
#if 0
template<typename T>
class BSTree
{
public:
	BSTree() :root(nullptr) {}
	// BST树的插入操作
	void insert(const T& val)
	{
		if (root == nullptr)
		{
			root = new BSTnode(val);
				return ;
		}
		BSTnode* old_node = nullptr;
		BSTnode* cur_node = root;
			//找对应值应该插入的位置
		while(cur_node != nullptr)
		{
		   if (val >= cur_node->data)
			{
				old_node = cur_node;
				cur_node = cur_node->right;
			}
			else if (val < cur_node->data)
			{
				old_node = cur_node;
				cur_node = cur_node->left;
			}
			else
			{
				return;
			}
		}
			BSTnode* node = new BSTnode(val);
			//判断应该插入右孩子域还是左孩子域
			if (val > old_node->data)
			{
				old_node->right = node;
			}
			else
			{
				old_node->left = node;
			}
	}


	/*
		没有孩子节点，直接删
		有一个子节点，删除它本身后，往它的父节点的相应的地址域写
		有两个子节点，用它前驱和后继，
	
	明确代码逻辑:
	首先应该找到你要删除的那个节点
	找到之后再按情况分类进行处理
	
	*/
	//关联容器：有序(映射表map和集合set底层数据结构都是红黑树，调用sort()，就是做的红黑树的中序遍历)/无序(链式哈希，迭代器遍历也是无序)
	void earse(const T&val)
	{
		BSTnode* cur_node = root;
		BSTnode* parent = nullptr;
	
		while (cur_node->data != val)
		{
			if (val > cur_node->data)
			{
				parent = cur_node;
				cur_node = cur_node->right;
			}
			else if (val < cur_node->data)
			{
				parent = cur_node;
				cur_node = cur_node->left;
			}
			else
			{
				break;
			}
		}

		BSTnode* old_node = cur_node;
		if (cur_node->left != nullptr && cur_node->right != nullptr)
		{
			cur_node = cur_node->left;
			/*while (cur_node != nullptr)
			{
				parent = cur_node;
				cur_node = cur_node->right;
			}*/
			while (cur_node->right != nullptr)
			{
				parent = cur_node;
				cur_node = cur_node->right;
			}
			 old_node->data = cur_node->data;
		}
		BSTnode* child = cur_node->left;
		if (child == nullptr)
		{
			child = cur_node->right;
		}
		//把child的地址域写到parent的相应的地址域中
		if (parent != nullptr)//父节点不为空，说明不是root节点
		{
			if (parent->left == cur_node)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}
		}
		else
		{
			root = child;
		}
		delete cur_node;
		/*

		BSTnode* child = cur_node->left;
		if (child == nullptr)
		{
			child = cur_node->right;
		}

		else if (cur_node->left == nullptr )
		{
			if(parent->right == cur_node)
			{
				parent->right = cur_node->right;
			}
			else
			{
				parent->left = cur_node->right;
			}
		}
		else if (cur_node->right == nullptr)
		{
			if(parent->right == cur_node)
			{
				parent->right = cur_node->left;
			}
			else
			{
				parent->left = cur_node->left;
			}
		}
		delete cur_node;
		*/
}

	//删除节点，并返回被删除节点的孩子
	void earse_r(const T& val)
	{
		root = earse_r(root, val);
	}
	



	void preOrder()
	{
			cout << "BST的前序遍历" << endl;
			preOrder(root);
	}
	void inOrder()
	{
			cout << "BST的中序遍历" << endl;
			inOrder(root);
	}
	void postOrder()
	{
			cout << "BST的后序遍历" << endl;
			postOrder(root);
	}
	void levelOrder()
	{
		cout << "BST的层序遍历" << endl;
		//获取层数
		int level = levels(root);
		//层序遍历，需要通过树的层数来控制递归的次数，每一次递归，打印这一层的值。
		for (int i = 0; i < level; ++i)
		{
			levelOrder(root, i);
		}
	}
	//获取BST树的层数
	int levels()
	{
		level(root);
	}
	//二叉树的镜像
	void mirror_tree()
	{
		mirror_tree(root);
	}

	bool isBSTtree() 
	{
		return isBSTtree(root,nullptr);
	}

	//找出两个指定元素的LCA公共祖先节点
	int getLCA(int a, int b)
	{
		
		return getLCA(root, a, b)->data;
	}

	//判断一颗BST树是否为平衡树。
	bool isBlance()
	{
		int level = 0;
		return isBalance(root,0,true);
	}
	
	//判断给定的一棵树是否为该二叉树的子树
	bool isChildtree(BSTree<T> tree)
	{
		BSTnode* p = root;
		while (p != nullptr)
		{
			if (p->data > tree.root->data)
			{
				p = p->left;
			}
			else if (p->data < tree.root->data)
			{
				p = p->right;
			}
			else
			{
				break;
			}
		}
		if (p == nullptr)
		{
			return false;
		}
		//先遍历母树，找到母树中 子树的根节点所处的位置。
		isChildtree(p,tree);
	}
	
	//找BST树中的第K小的元素
	int getTopKValue(int k)
	{

		

	}



private:
	struct BSTnode
	{
		BSTnode(T val = T()) :data(val), left(nullptr), right(nullptr) {}
		T data;
		BSTnode* left;
		BSTnode* right;
	};
	BSTnode* root;
	void preOrder(BSTnode* node)
	{
		if (node != nullptr)
		{
			cout <<node->data<<" ";
			preOrder(node->left);
			preOrder(node->right);
		}
		//cout<<endl;
	}
	void inOrder(BSTnode* node)
	{
		if (node != nullptr)
		{	
			inOrder(node->left);
			cout << node->data << " ";
			inOrder(node->right);
		}
	}
	void postOrder(BSTnode* node)
	{
		if (node != nullptr)
		{
			postOrder(node->left);     //站在当前层来考虑，剩下的节点的遍历方式与当前层一样
			postOrder(node->right);
			cout << node->data << " ";
		}
	}
	//二叉树高度的递归接口。该递归接口的含义是:以当前node为起始节点，求树的层数
	int levels(BSTnode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left_tree = levels(node->left);
		int right_tree = levels(node->right);
		return  left_tree > right_tree ? left_tree + 1 : right_tree + 1;
	}

	//考虑问题的方式，，只考虑当前节点和它左右子树之间的关系，它的左右子树也有自己的左右子树，它们之间的关系也是一样的
	//因此可以采用递归的方式
	//定义一个这样的递归接口，它所完成的任务是，计算以它为根节点，二叉树上的节点个数。
	//二叉树节点个数的递归接口
	int cal_num(BSTnode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left_num = cal_num(node->left);   //这样的一个递归的代码，实现的是每经过一个节点，都将它往总数里面加1。
		int right_num = cal_nun(node->right);
		return left_num + right_num + 1;
	}

	//层序遍历递归接口，以当前节点为根节点，打印其对应第height层的节点
	void levelOrder(BSTnode* node ,int height)
	{
		if (node == nullptr)
		{
			return;
		}
		if(height == 0)   //把height变为0，就当作递归已经走到要输出的这一层来了。
		{
			cout << node->data << " ";
			return;
		}
		levelOrder(node->left, height - 1);
		levelOrder(node->right, height - 1);
	}

	void exchange(BSTnode* node)
	{
		BSTnode* tmp = nullptr;
		tmp = node->right;
		node->right = node->left;
		node->left = tmp;
	}
	//镜像递归接口。思想和前序遍历是一样的。
	void mirror_tree(BSTnode* node)
	{
		if (node == nullptr)
		{
			return;
		}
		exchange(node);
		mirror_tree(node->left);
		mirror_tree(node->right);
	}

	//判断这棵树是否为一颗BST树的递归接口。参照中序遍历是升序思想，如果遍历出来的不是升序就说明不是一颗BST树
	//保存当前节点的前驱节点以用作比较是否为升序关系。
	BSTnode* pre_node=nullptr;
	bool isBSTtree(BSTnode* node)
	{
		if (node == nullptr)
		{
			return true;
		}
		if (!isBSTtree(node->left))
		{
			return false;
		}
		//isBSTtree(node->left，pre_node);
		if (pre_node != nullptr)
		{
			if (pre_node->data > node->data)
			{
				return false;
			}
			else
			{
				pre_node = node;
				return isBSTtree(node->right，pre_node);
			}
		}
		

		/*从反向角度出发，只要有不满足条件的情况就返回false。
		if (node->left != nullptr && node->left->data > node->data)
		{
			return false;
		}
		if (node->left != nullptr && node->right->data < node->data)
		{
			return false;
		}
		return isBSTtree(node->left)&&isBSTtree(node->right);
				
		if (node->left != nullptr && node->right != nullptr)
		{
			if (node->left->data > val && val < node->right->data)
			{
				isBSTtree(node->left, node->left->data);
				isBSTtree(node->right, node->right->data);
			}
		}
			else
				return false;
		
		这样从整天上来看思路是大致正确的，但是具有判断的局部性。

		       40
			  /   \
			 30    50
			     /  \
                20  60
		*/
	}

	//找出指定区间[i,j]中的元素
	void findValue(BSTnode* node,vector<int> &vec, int i, int j) {}

	//这个递归函数的语义是 以node为根节点，找出a，b的公共祖先节点。
	BSTnode* getLCA(BSTnode* node, int a, int b)
	{
		//先判断参数的合法性
		if (!query(root, a) || !query(root, b))
		{
			return nullptr;
		}
		if (node == nullptr) //连根节点都没有的情况
		{
			throw "NOT FOUND!!";
		}
		if (node->data >= a && node->data <= b)//如果当前遍历到的节点值大于a小于b，说明当前节点就是公共祖先节点
		{
			return node;
		}
		if (node->data > a && node->data > b)  //如果当前值比a，b都大，说明a，b的公共祖先节一定在当前节点的左子树中
		{
			return getLCA(node->left, a, b);
		}
		if (node->data < a && node->data < b)//反之则在右子树中。
		{
			return getLCA(node->right, a, b);
		}

	}
	//查找给定的值是否在当前的树中
	BSTnode* query(BSTnode* node,int a)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->data > a)
		{
			return query(node->left, a);
		}
		else if (node->data < a)
		{
			return query(node->right, a);
		}
		else
		{
			return node;
		}
	}

	//这里返回值指的是当前节点所在的层数。
	int isBalance(BSTnode* node,int level,bool result)
	{
		if (node == nullptr)
		{
			return level;
		}
		//当前节点所在的层数
		int left = isBalance(node->left,level+1,result);
		if (!result)
		{
			return left;
		}
		int right = isBalance(node->right, level + 1，result);
		if(!result)
		{
			return right;
		}
		
		if (abs(left - right) >= 2)
		{
			result = false;
		}

		return max(left,right);
	}

	bool isChildtree(BSTnode *mother_node,BSTnode *child_node)
	{
		if(mother_node == nullptr)   //总共分三种情况,同时为空说明是子树，
									//若子树节点先为空也说明是子树，若母树的节点先为空说明不是子树


		return isChildtree(p, tree);
	}

	//获取第K小的元素的递归接口        其中i是用来记录当前的中序遍历，遍历到了第几个元素
	BSTnode* getTopKValue(BSTnode* node,int k,int &i)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (++i == k)
		{
			return node;
		}
		BSTnode* node1=getTopKValue(node->left, k, i);
		if (node1 != nullptr)
		{
			return node1;
		}
		return getTopKValue(node->right, k, i);

	}

	//查询BST树中是否存在某一元素的递归接口
	bool query(BSTnode* node, const T& val)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (node->data > val)
		{
			return query(node->left, val);
		}
		else if (node->data < val)
		{
			return query(node->right, val);
		}
		else
		{
			return true;
		}


	}
	
	//插入新节点的递归接口。  生成新节点，将新节点的地址写到父节点的相应的地址域中。因为会回溯，也就是说递归的时候是从父节点到子节点，回溯的时候就反着来了。所以可以直接将函数的返回值写到本次递归前的节点的相应的地址域中
	BSTnode* insert_r(BSTnode* node, const T& val)
	{
		if (node == nullptr)
		{
			return new BSTnode(val);
		}
		if (node->data > val)
		{
			//node->left = insert_r(node->left, val);  //这样做有一个弊端，会将树中已存在的节点的地址继续回写。虽然没错，但是并没有必要做多余的事情。所以可以加一个逻辑判断
			if (node->left != nullptr)
			{
				insert_r(node->left, val);
			}
			else
			{
				node->left = insert_r(node->left, val);
			}
		
		}
		else if (node->data < val)
		{
			node->right = insert_r(node->right, val);
		}
		else
		{
			;   //这一部分在优化代码的时候，可以去掉
		}
		return node;   
	}

	BSTnode* earse_r(BSTnode* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data > val)
		{
			node->left = earse_r(node->left, val);//如果当前节点的值大于所要删除的val，说明要删除的节点如果能找到，一定在左子树中，所以向左递归下去。
		}													//递归返回的值写到父节点的相应的地址域中
		else if (node->data < val)
		{
			node->right = earse_r(node->right, val);//如果当前节点的值小于所要删除的val，说明要删除的节点如果能找到，一定在右子树中，所以向右递归下去。
		}                                           //然后将递归返回的值写到父节点相应的地址域中
		else
		{
			// 这里的else就表示找到当前要删除的节点了
			if (node->left != nullptr && node->right != nullptr)
			{
				BSTnode* pre = node->left;
				while (pre->right != nullptr)
					pre = pre->right;
				node->data = pre->data;
				// 删除前驱节点
				node->left = earse_r(node->left, pre->data);
			}
			else
			{
				if (node->left != nullptr)
				{
					// node被删除，把node的左孩子返回
					BSTnode* left = node->left;
					delete node;
					return left;
				}
				else if (node->right != nullptr)
				{
					// node被删除，把node的右孩子返回
					BSTnode* right = node->right;
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
		return node;
	}

	//广度优先搜索用队列
	//深度优先搜索用栈

	//非递归实现层序遍历接口recursion
	void levelOrder_nr()
	{
		queue<BSTNode*> que;
		que.push(root);
		while (!que.empty())
		{
			BSTNode* front = que.front();
			if (front->left != nullptr)
				que.push(front->left);
			if (front->right != nullptr)
				que.push(front->right);
			cout << front->data << " ";
			que.pop();
		}
		cout << endl;
	}

	//非递归的深度遍历结构
	void deeporder_nr()
	{
		stack<BSTnode* > sta;
		BSTnode* root = root;
		sta.push(root);
		while (!sta.empty())
		{
			BSTnode* top = sta.top();
			sta.pop();
			if (top->right != nullptr)
			{
				sta.push(top->right);
			}
			if (top->left != nullptr)
			{
				sta.push(top->left);
			}
			cout << top->data << " ";
		}
		cout << endl;
	}

	//非递归前序遍历接口 VLR
	void preOrder_nr()
	{
		stack<BSTnode*>s;
		s.push(root);
		while(!s.empty())
		{
			BSTnode* top = s.top();
			s.pop();
			cout << top->data<<" ";
			if (top->right != nullptr)
			{
				s.push(top->right);
			}
			if (top->left != nullptr)
			{
				s.push(top->left);
			}
		}

	}

	//非递归中序遍历接口
	//思想：将当前节点以及左边的所有节点入栈，当为空的时候，pop，打印当前节点，再往右遍历，往右遍历，也是先将左边节点全部入栈，直到为空，再出栈并打印
	void inOrder_nr()
	{
		stack<BSTNode*> s;
		BSTnode* cur = root;
		
		while (cur != nullptr)  // push当前节点左侧的全部节点，直到为空。出栈顶元素并打印。
		{
			s.push(cur);
			cur = cur->left;
		}
		while (!s.empty())
		{
			BSTnode* top = s.top();
			s.pop();
			cout << top->data;

			cur = cur->right;
			while (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left;
			}
		}
			
	


	}

	//非递归后序遍历接口

	void postOrder_nr()
	{
		stack<BSTnode*>s;
		stack<BSTnode*>s2;
		s.push(root);
		while (!s.empty())
		{
			BSTnode* top = s.top();
			s.pop();
			s2.push(top);		
			if (top->left != nullptr)
			{
				s.push(top->left);
			}
			if (top->right != nullptr)
			{
				s.push(top->right);
			}
		}
		while (!s2.empty())
		{
			BSTnode* top2 = s2.top();
			s2.pop();
			cout << top2->data << " ";
		}
		cout << endl;
	}


};

int main()
{
	int arr[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTree<int> bst;
	for (int val : arr)
	{
		bst.insert(val);
	}
	bst.preOrder();
	cout << endl;
	bst.inOrder();
	cout << endl;
	bst.levelOrder();
	cout << endl;
	bst.mirror_tree();
	bst.inOrder();

	int p = bst.getLCA(0, 41);
	cout << p << endl;

	return 0;
}

#endif






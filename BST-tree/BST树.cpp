
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
	// BST���Ĳ������
	void insert(const T& val)
	{
		if (root == nullptr)
		{
			root = new BSTnode(val);
				return ;
		}
		BSTnode* old_node = nullptr;
		BSTnode* cur_node = root;
			//�Ҷ�ӦֵӦ�ò����λ��
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
			//�ж�Ӧ�ò����Һ�������������
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
		û�к��ӽڵ㣬ֱ��ɾ
		��һ���ӽڵ㣬ɾ��������������ĸ��ڵ����Ӧ�ĵ�ַ��д
		�������ӽڵ㣬����ǰ���ͺ�̣�
	
	��ȷ�����߼�:
	����Ӧ���ҵ���Ҫɾ�����Ǹ��ڵ�
	�ҵ�֮���ٰ����������д���
	
	*/
	//��������������(ӳ���map�ͼ���set�ײ����ݽṹ���Ǻ����������sort()���������ĺ�������������)/����(��ʽ��ϣ������������Ҳ������)
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
		//��child�ĵ�ַ��д��parent����Ӧ�ĵ�ַ����
		if (parent != nullptr)//���ڵ㲻Ϊ�գ�˵������root�ڵ�
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

	//ɾ���ڵ㣬�����ر�ɾ���ڵ�ĺ���
	void earse_r(const T& val)
	{
		root = earse_r(root, val);
	}
	



	void preOrder()
	{
			cout << "BST��ǰ�����" << endl;
			preOrder(root);
	}
	void inOrder()
	{
			cout << "BST���������" << endl;
			inOrder(root);
	}
	void postOrder()
	{
			cout << "BST�ĺ������" << endl;
			postOrder(root);
	}
	void levelOrder()
	{
		cout << "BST�Ĳ������" << endl;
		//��ȡ����
		int level = levels(root);
		//�����������Ҫͨ�����Ĳ��������Ƶݹ�Ĵ�����ÿһ�εݹ飬��ӡ��һ���ֵ��
		for (int i = 0; i < level; ++i)
		{
			levelOrder(root, i);
		}
	}
	//��ȡBST���Ĳ���
	int levels()
	{
		level(root);
	}
	//�������ľ���
	void mirror_tree()
	{
		mirror_tree(root);
	}

	bool isBSTtree() 
	{
		return isBSTtree(root,nullptr);
	}

	//�ҳ�����ָ��Ԫ�ص�LCA�������Ƚڵ�
	int getLCA(int a, int b)
	{
		
		return getLCA(root, a, b)->data;
	}

	//�ж�һ��BST���Ƿ�Ϊƽ������
	bool isBlance()
	{
		int level = 0;
		return isBalance(root,0,true);
	}
	
	//�жϸ�����һ�����Ƿ�Ϊ�ö�����������
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
		//�ȱ���ĸ�����ҵ�ĸ���� �����ĸ��ڵ�������λ�á�
		isChildtree(p,tree);
	}
	
	//��BST���еĵ�KС��Ԫ��
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
			postOrder(node->left);     //վ�ڵ�ǰ�������ǣ�ʣ�µĽڵ�ı�����ʽ�뵱ǰ��һ��
			postOrder(node->right);
			cout << node->data << " ";
		}
	}
	//�������߶ȵĵݹ�ӿڡ��õݹ�ӿڵĺ�����:�Ե�ǰnodeΪ��ʼ�ڵ㣬�����Ĳ���
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

	//��������ķ�ʽ����ֻ���ǵ�ǰ�ڵ������������֮��Ĺ�ϵ��������������Ҳ���Լ�����������������֮��Ĺ�ϵҲ��һ����
	//��˿��Բ��õݹ�ķ�ʽ
	//����һ�������ĵݹ�ӿڣ�������ɵ������ǣ���������Ϊ���ڵ㣬�������ϵĽڵ������
	//�������ڵ�����ĵݹ�ӿ�
	int cal_num(BSTnode* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		int left_num = cal_num(node->left);   //������һ���ݹ�Ĵ��룬ʵ�ֵ���ÿ����һ���ڵ㣬�����������������1��
		int right_num = cal_nun(node->right);
		return left_num + right_num + 1;
	}

	//��������ݹ�ӿڣ��Ե�ǰ�ڵ�Ϊ���ڵ㣬��ӡ���Ӧ��height��Ľڵ�
	void levelOrder(BSTnode* node ,int height)
	{
		if (node == nullptr)
		{
			return;
		}
		if(height == 0)   //��height��Ϊ0���͵����ݹ��Ѿ��ߵ�Ҫ�������һ�����ˡ�
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
	//����ݹ�ӿڡ�˼���ǰ�������һ���ġ�
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

	//�ж�������Ƿ�Ϊһ��BST���ĵݹ�ӿڡ������������������˼�룬������������Ĳ��������˵������һ��BST��
	//���浱ǰ�ڵ��ǰ���ڵ��������Ƚ��Ƿ�Ϊ�����ϵ��
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
		//isBSTtree(node->left��pre_node);
		if (pre_node != nullptr)
		{
			if (pre_node->data > node->data)
			{
				return false;
			}
			else
			{
				pre_node = node;
				return isBSTtree(node->right��pre_node);
			}
		}
		

		/*�ӷ���Ƕȳ�����ֻҪ�в���������������ͷ���false��
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
		
		����������������˼·�Ǵ�����ȷ�ģ����Ǿ����жϵľֲ��ԡ�

		       40
			  /   \
			 30    50
			     /  \
                20  60
		*/
	}

	//�ҳ�ָ������[i,j]�е�Ԫ��
	void findValue(BSTnode* node,vector<int> &vec, int i, int j) {}

	//����ݹ麯���������� ��nodeΪ���ڵ㣬�ҳ�a��b�Ĺ������Ƚڵ㡣
	BSTnode* getLCA(BSTnode* node, int a, int b)
	{
		//���жϲ����ĺϷ���
		if (!query(root, a) || !query(root, b))
		{
			return nullptr;
		}
		if (node == nullptr) //�����ڵ㶼û�е����
		{
			throw "NOT FOUND!!";
		}
		if (node->data >= a && node->data <= b)//�����ǰ�������Ľڵ�ֵ����aС��b��˵����ǰ�ڵ���ǹ������Ƚڵ�
		{
			return node;
		}
		if (node->data > a && node->data > b)  //�����ǰֵ��a��b����˵��a��b�Ĺ������Ƚ�һ���ڵ�ǰ�ڵ����������
		{
			return getLCA(node->left, a, b);
		}
		if (node->data < a && node->data < b)//��֮�����������С�
		{
			return getLCA(node->right, a, b);
		}

	}
	//���Ҹ�����ֵ�Ƿ��ڵ�ǰ������
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

	//���ﷵ��ֵָ���ǵ�ǰ�ڵ����ڵĲ�����
	int isBalance(BSTnode* node,int level,bool result)
	{
		if (node == nullptr)
		{
			return level;
		}
		//��ǰ�ڵ����ڵĲ���
		int left = isBalance(node->left,level+1,result);
		if (!result)
		{
			return left;
		}
		int right = isBalance(node->right, level + 1��result);
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
		if(mother_node == nullptr)   //�ܹ����������,ͬʱΪ��˵����������
									//�������ڵ���Ϊ��Ҳ˵������������ĸ���Ľڵ���Ϊ��˵����������


		return isChildtree(p, tree);
	}

	//��ȡ��KС��Ԫ�صĵݹ�ӿ�        ����i��������¼��ǰ������������������˵ڼ���Ԫ��
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

	//��ѯBST�����Ƿ����ĳһԪ�صĵݹ�ӿ�
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
	
	//�����½ڵ�ĵݹ�ӿڡ�  �����½ڵ㣬���½ڵ�ĵ�ַд�����ڵ����Ӧ�ĵ�ַ���С���Ϊ����ݣ�Ҳ����˵�ݹ��ʱ���ǴӸ��ڵ㵽�ӽڵ㣬���ݵ�ʱ��ͷ������ˡ����Կ���ֱ�ӽ������ķ���ֵд�����εݹ�ǰ�Ľڵ����Ӧ�ĵ�ַ����
	BSTnode* insert_r(BSTnode* node, const T& val)
	{
		if (node == nullptr)
		{
			return new BSTnode(val);
		}
		if (node->data > val)
		{
			//node->left = insert_r(node->left, val);  //��������һ���׶ˣ��Ὣ�����Ѵ��ڵĽڵ�ĵ�ַ������д����Ȼû�����ǲ�û�б�Ҫ����������顣���Կ��Լ�һ���߼��ж�
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
			;   //��һ�������Ż������ʱ�򣬿���ȥ��
		}
		return node;   
	}

	BSTnode* earse_r(BSTnode* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data > val)
		{
			node->left = earse_r(node->left, val);//�����ǰ�ڵ��ֵ������Ҫɾ����val��˵��Ҫɾ���Ľڵ�������ҵ���һ�����������У���������ݹ���ȥ��
		}													//�ݹ鷵�ص�ֵд�����ڵ����Ӧ�ĵ�ַ����
		else if (node->data < val)
		{
			node->right = earse_r(node->right, val);//�����ǰ�ڵ��ֵС����Ҫɾ����val��˵��Ҫɾ���Ľڵ�������ҵ���һ�����������У��������ҵݹ���ȥ��
		}                                           //Ȼ�󽫵ݹ鷵�ص�ֵд�����ڵ���Ӧ�ĵ�ַ����
		else
		{
			// �����else�ͱ�ʾ�ҵ���ǰҪɾ���Ľڵ���
			if (node->left != nullptr && node->right != nullptr)
			{
				BSTnode* pre = node->left;
				while (pre->right != nullptr)
					pre = pre->right;
				node->data = pre->data;
				// ɾ��ǰ���ڵ�
				node->left = earse_r(node->left, pre->data);
			}
			else
			{
				if (node->left != nullptr)
				{
					// node��ɾ������node�����ӷ���
					BSTnode* left = node->left;
					delete node;
					return left;
				}
				else if (node->right != nullptr)
				{
					// node��ɾ������node���Һ��ӷ���
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

	//������������ö���
	//�������������ջ

	//�ǵݹ�ʵ�ֲ�������ӿ�recursion
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

	//�ǵݹ����ȱ����ṹ
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

	//�ǵݹ�ǰ������ӿ� VLR
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

	//�ǵݹ���������ӿ�
	//˼�룺����ǰ�ڵ��Լ���ߵ����нڵ���ջ����Ϊ�յ�ʱ��pop����ӡ��ǰ�ڵ㣬�����ұ��������ұ�����Ҳ���Ƚ���߽ڵ�ȫ����ջ��ֱ��Ϊ�գ��ٳ�ջ����ӡ
	void inOrder_nr()
	{
		stack<BSTNode*> s;
		BSTnode* cur = root;
		
		while (cur != nullptr)  // push��ǰ�ڵ�����ȫ���ڵ㣬ֱ��Ϊ�ա���ջ��Ԫ�ز���ӡ��
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

	//�ǵݹ��������ӿ�

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






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
		//�����BST���Ĳ�����һ���ģ�����������������������ɫ�ڵ�ʱ��Ҫ������
		if (root == nullptr)
		{
			root = new RBNode(val,BLACK);
			return;
		}
		RBNode* parent = nullptr;
		RBNode* cur = root;
		//�Ҷ�ӦֵӦ�ò����λ��
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
		//�ж�Ӧ�ò����Һ�������������
		if (val > parent->data)
		{
			parent->right = node;		
		}
		else
		{
			parent->left = node;
		}
		if (parent->color == RED)//����²���ڵ�ĸ��ڵ��Ǻ�ɫ��
		{
			fixAfterInsert(node);//�ʹӵ�ǰ�ڵ㿪ʼ����
		}	
	}

	//ɾ��ָ��ֵΪval�Ľڵ�
	void earse(const T& val)
	{
		RBNode* node = find(val);
		if (node == nullptr)
		{
			return;
		}
		//Ҫɾ���Ľڵ������RB����
		//���һ:��ɾ���ڵ��Ǻ�ɫ�ģ��޸Ķ�Ӧ��ָ�����ok��
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
	//��nodeΪ���ڵ��������
	void leftRotate(RBNode* node)
	{	
		/*�ܹ�Ҫ�޸�����ָ���򡣽��ͼ����*/
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
	//RB����������ӿ�,�ӵ�ǰ�ڵ�node��ʼ����������nodeָ�ľ����²���ڵ�
	void fixAfterInsert(RBNode *node)
	{
		//���ڵ����ɫһֱΪ��ɫ���͵�һֱ���ϵ���
		while ( color(parent(node)) == RED )
		{ 
			//���ȷ��²���ڵ���үү�ڵ����໹���Ҳ�(�������ڵ�����һ����Ӱ��)
			if (parent(node) == left(parent(parent(node))))
			{
				//���������ڵ������Ƚڵ�����
				RBNode* un = right(parent(parent(node)));
				if (color(un) == RED)// ������һ������
				{
					setColor(un, BLACK);
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					//���������ϻ��ݣ���ʱnodeָ���Ӧ���ǵ�ǰ�ڵ��үү�ڵ�
					node = parent(parent(node));
				}
				else //����ڵ�Ϊ��ɫ�������������
				{
					//������Ż���������ĺ�벿��Ҳ�������һ��
					if (right(parent(node)) == node)//����²���Ľڵ��ڸ��ڵ���ұ�
					{
						node = node->parent;   //����Ҫ��Nodeָ�����λ�����±ߵ��Ǹ��ڵ�
						leftRotate(node);
					}
					//������ͳһ���������
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;//�������ε�������Ժ󣬾ֲ���������RB�����ʵ��ˣ����������ϻ�����
				}
			}
			else if (parent(node) == right(parent(parent(node))))//�²���ڵ���үү�ڵ���Ҳ�
			{
				RBNode* un = left(parent(parent(node)));
				if (color(un) == RED)
				{
					setColor(un, BLACK);
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					//���������ϻ��ݣ���ʱnodeָ���Ӧ���ǵ�ǰ�ڵ��үү�ڵ�
					node = parent(parent(node));
				}
				else //����ڵ�Ϊ��ɫ�������������
				{
					//������Ż���������ĺ�벿��Ҳ�������һ��
					if (left(parent(node)) == node)//����²���Ľڵ��ڸ��ڵ�����
					{
						node = node->parent;   //����Ҫ��Nodeָ�����λ�����±ߵ��Ǹ��ڵ�
						rightRotate(node);
					}
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break;
				}
			}
		}
		/*���һֱ���ϵ�����һֱ���˸��ڵ㡣��ô���ڵ�ĸ��ڵ�Ϊnullptr��nullptrĬ��Ϊ��ɫ��
		Ȼ������ѭ������ʾ��ǰnode�ڵ�ĸ��ڵ���ɫΪ�ڣ�
		�ܿ��ܵ�ǰ�ڵ��Ѿ��Ǹ��ڵ��ˣ����ڵ�ĸ��ڵ�Ϊ�գ���ȻҲ���ɫ�ˡ�
		���Ե�ǰ�ڵ���ܱ��óɺ�ɫ�ˣ����Ҫǿ����Ϊ��ɫ*/
		setColor(root, BLACK);
	}
	//�ṩquery�ӿڣ���earse����ʹ��
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
		return query(node->left,val,find) || query(node->right, val,find); // ��VLRǰ������ķ�ʽ����������RB��
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





/*ctrl+F10 debug��������ڴ�
�ٰ�F5,debug����һ���ϵ㴦
*/
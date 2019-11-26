#include<iostream>
using namespace std;
#if 0
template<typename T>
class AVLTree
{
public:
	AVLTree() :root(nullptr) {}
	~AVLTree() {}
	// �ݹ�Ĳ������
	void insert(const T& val)
	{
		root = insert(root, val);
	}
	// �ݹ��ɾ������
	void remove(const T& val);
private:
	struct AVLnode
	{
		AVLnode(T dat = T()) :data(dat), left(nullptr), right(nullptr), height(0) {}
		T data;
		AVLnode* left;
		AVLnode* right;
		int height;//��¼�ڵ������������ĸ߶�ֵ
	};
	AVLnode* root;
	//���ؽڵ������ĸ߶�ֵ
	int getheight(AVLnode *node)
	{
		return node == nullptr ? 0 : node->height;
	}
	//��ȡ���Һ����и߶ȴ����һ��
	int maxHeight(AVLnode* left, AVLnode* right)
	{
		return getheight(left) > getheight(right) ? getheight(left) : getheight(right);
	}

	//��������ĵݹ�ӿ�    ��������ҵ��յĵط����ٲ��롣�ݹ��ʱ���ҵط�����ڵ� ���� ���ݵ�ʱ���ж��Ƿ�ʧ��
	AVLnode* insert(AVLnode* node, const T& val)    // ��˻��ݵ�ʱ���жϵ����Ӧ��д�ڵݹ麯���ĺ���
	{
		if (node == nullptr)
		{
			return new AVLnode(val);
		}
		if (node->data > val)
		{
			node->left = insert(node->left, val);

			if (getheight(node->left) - getheight(node->right) > 1)//���������в嵼�µ�ʧ��
			{
				if (getheight(node->left->left) >= getheight(node->left->right)) //�����������̫�ߵ��µ�ʧ��
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
		//��Ҫ�ڵݹ����Ļ��ݹ��������Ĳ�������Ӧ��д�ڵݹ����ĺ��档
			if (getheight(node->right) - getheight(node->left) > 1)//���������в嵼�µ�ʧ��
			{
				if (getheight(node->right->right) >= getheight(node->right->left)) //���������ұ�̫�ߵ��µ�ʧ��
				{
					node = leftRotate(node);
				}
				else // �����������̫�ߵ��µ�ʧ��
				{
					node = rightBalance(node);
				}
			}
		}
		//�ڵݹ���ݵĹ����и��¶�Ӧ�ڵ�ĸ߶�ֵ
		node->height = maxHeight(node->left, node->right) + 1;
		return node;
	}
	//��������װƽ������Ľӿڣ���Ϊ�û�ֻ��Ӵ���insert�����Խ�ƽ�������װ��private��

	//����ת����   ����ֵ�� ��ת�����µ����ĸ��ĵ�ַ���������ݹ����ʹ�á�
	AVLnode* leftRotate(AVLnode* node)
	{
		//���Ų������Ҫ����ת��������Ҫ����child��parents�ĸ߶�ֵ
		AVLnode* child = node->right;
		node->right = child->left;
		child->left = node;

		node->height = maxHeight(node->left, node->right)+1;
		child->height = maxHeight(child->left, child->right)+1;
		return child;
	}
	//����ת����
	AVLnode* rightRotate(AVLnode* node)
	{
		//���Ų������Ҫ����ת��������Ҫ����child��parents�ĸ߶�ֵ
		AVLnode* child = node->left;
		node->left = child->right;
		child->right = node;

		node->height = maxHeight(node->left, node->right)+1;
		child->height = maxHeight(child->left, child->right)+1;
		return child;
	}
	//��ƽ�����   ��-����
	AVLnode* leftBalance(AVLnode* node)
	{
		//���Ų������Ҫ����ת��������Ҫ����child��parents�ĸ߶�ֵ
		AVLnode* child = node->left;		
		leftRotate(child);
		rightRotate(node);
		return child;
	}
	//��ƽ����� ��-����
	AVLnode* rightBalance(AVLnode* node)
	{
		//���Ų������Ҫ����ת��������Ҫ����child��parents�ĸ߶�ֵ
		AVLnode* child = node->right;
		rightRotate(child);
		leftRotate(node);
		return child;
	}

	//AVL�� ɾ��ָ���ڵ�ĵݹ�ӿ�
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
					node = leftRotate(node); // �Һ���  -   ������
				}
				else
				{
					node = rightBalance(node); // �Һ���   -   ������
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
				{  // ɾǰ���ڵ�
					AVLNode* pre = node->left;
					while (pre->right != nullptr)
						pre = pre->right;
					node->data = pre->data;
					node->left = remove(node->left, pre->data);
				}
				else
				{
					// ɾ����̽ڵ�
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

		// #3 ��Ҷ�ӽڵ�����ڵ���ݵĹ����У����½ڵ�ĸ߶�ֵ
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
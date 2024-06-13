#pragma once
// ��ģ��ʵ�ֺ�����Ĳ���--ע�⣺Ϊ�˺����װmap��set��������ʵ��ʱ���������������һ��ͷ���
using namespace std;
enum color {
	RED,
	BLACK
};
template<class T>
struct RBTreeNode
{
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;
	color _color;
	T _data;

	RBTreeNode(T val) :
		_left(nullptr), _right(nullptr), _parent(nullptr), _color(RED), _data(val)
	{}
};

template<class T,class Ref,class Ptr>
struct _RBTreeIterater{
	typedef RBTreeNode<T> Node;
	typedef _RBTreeIterater<T, Ref, Ptr> Self;
	Node* _node;
	_RBTreeIterater(Node* tmp):
		_node(tmp) {

	}
	Ptr operator *() {
		return _node->_data;
	}
	Ref operator ->() {
		return &_node->_data;
	}
	Self operator++() {
		Node* cur= _node;
		
			if (cur->_right == nullptr) {
				while (cur->_parent->_left != cur) {
					cur = cur->_parent;
					if (cur->_parent == nullptr) {
						return nullptr;
					}
				}
				
			}
			else if (cur->_right != nullptr) {
				cur = cur->_right;
				while (cur->_left != nullptr) {
					cur = cur->_left;
				}
				
			}
			return cur;
		
	}
	Self operator--() {
		Node* cur = _node;
		if (cur->_left == nullptr) {
			while (cur->_parent->_right != cur) {
				cur = cur->_parent;
				if (cur->_parent == nullptr) {
					return nullptr;
				}
			}
		}
		else if (cur->_left) {
			cur = cur->_left;
		}
		return cur;
	}
	bool operator==(const Self& tmp) {
		return this == tmp._node;
	}
	bool operator!=(const Self& tmp) {
		return this != tmp._node;
	}
};
//template<class T>
//struct keyofT {
//	T& operater()(const T& key){
//		return key;
//	}
//};

template<class K,class T,class keyofT/*= keyofT<K>*/>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef _RBTreeIterater<T,T*,T&> iterator;
	
public:
	RBTree() {
		_root = nullptr;
	}
	iterator begin() {
		Node* cur = _root;
		if (_root->_left) {
			cur = cur->_left;
		}
		return iterator(cur);
	}
	iterator end() {
		return iterator(nullptr);
	}
	// �ں�����в���ֵΪdata�Ľڵ㣬����ɹ�����true�����򷵻�false
	// ע�⣺Ϊ�˼����������ʵ�ֺ�������洢�ظ���Ԫ��
	pair <iterator,bool> Insert(const T& data) {
		Node* parent = nullptr;
		Node* cur = _root;
		keyofT kot;
		if (_root == nullptr) {
			_root = new Node(data);
			_root->_color = BLACK;
		}
		else {						//Ĭ���������Ϊ���򣬱Ƚڵ�С�������ߣ��Ƚڵ�С��������
			
			while (cur) {
				if (kot(cur->_data) > kot(data)) {
					parent = cur;
					cur = cur->_left;
				}
				else if (kot(cur->_data) < kot(data)) {
					parent = cur;
					cur = cur->_right;
				}
				else {
					return make_pair(iterator(cur), false);
				}
			}
			cur = new Node(data);
			if (kot(parent->_data) > kot(data)) {
				parent->_left = cur;
				cur->_parent = parent;
			}
			else if (kot(parent->_data) < kot(data)) {
				parent->_right = cur;
				cur->_parent = parent;
			}



			//�����½ڵ�󣬶Խڵ������ɫ����
			while (parent && parent->_color == RED) {

				Node* grandf = parent->_parent;
				Node* uncle = nullptr;
				if (parent == grandf->_left) {
					uncle = grandf->_right;
				}
				else {
					uncle = grandf->_left;
				}

				if (uncle != nullptr && uncle->_color == RED) {
					uncle->_color = BLACK;
					parent->_color = BLACK;
					grandf->_color = RED;
					cur = grandf;
					parent = cur->_parent;
				}
				else if ((parent->_color == RED && uncle == nullptr) || (parent->_color == RED && uncle->_color == BLACK)) {
					if (grandf->_left == parent && parent->_left == cur) {
						RotateR(grandf);
						//��ת��Խڵ��ɫ
						parent->_color = BLACK;
						grandf->_color = RED;
						cur->_color = RED;
						break;
					}
					else if (grandf->_left == parent && parent->_right == cur) {
						RotateLR(grandf);
						parent->_color = RED;
						grandf->_color = RED;
						cur->_color = BLACK;
						break;
					}
					else if (grandf->_right == parent && parent->_right == cur) {
						RotateL(grandf);
						//��ת��Խڵ��ɫ
						parent->_color = BLACK;
						grandf->_color = RED;
						cur->_color = RED;
						break;
					}
					else if (grandf->_right == parent && parent->_left == cur) {
						RotateRL(grandf);
						parent->_color = RED;
						grandf->_color = RED;
						cur->_color = BLACK;
						break;
					}
				}

			}
			_root->_color = BLACK;
		}
		return make_pair(iterator(cur), true);
	}
	// ����������Ƿ����ֵΪdata�Ľڵ㣬���ڷ��ظýڵ�ĵ�ַ�����򷵻�nullptr
	Node* Find(const T& data) {
		Node* cur = _root;
		while (cur) {
			if (kot(cur->_data) > kot(data)) {
				cur = cur->_left;
			}
			else if (kot(cur->_data) < kot(data)) {
				cur = cur->_right;
			}
			else if (kot(cur->_data) == kot(data)) {
				return cur;
			}
		}
		return nullptr;
	}



	// ��������Ƿ�Ϊ��Ч�ĺ������ע�⣺���ڲ���Ҫ����_IsValidRBTRee�������
	bool IsValidRBTRee() {
		if (_root == nullptr) {
			return true;
		}
		if (_root->_color == RED) {
			return false;
		}
		//����ο�ֵ������_IsValidRBTRee������ο�ֵ���бȽϣ�����ͬ�򷵻�false
		size_t rval = 0;
		Node* cur = _root;
		while (cur) {
			if (cur->_color == BLACK) {
				rval++;
			}
			cur = cur->_left;
		}
		return _IsValidRBTRee(_root, 0, rval);
	}
private:
	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, const size_t rval) {

		if (pRoot == nullptr) {
			if (blackCount == rval) {
				return true;
			}
			else {
				cout << "��ɫ�ڵ��������һ��" << endl;
				return false;
			}
		}
		if (pRoot->_color == RED && pRoot->_parent->_color == RED) {
			cout << "������ڵ�" <<"cur"<<pRoot->_data << "  parent"<<pRoot->_parent->_data << endl;
			return false;
		}
		if (pRoot->_color == BLACK) {
			blackCount++;
		}
		return _IsValidRBTRee(pRoot->_left, blackCount,rval) && _IsValidRBTRee(pRoot->_right, blackCount, rval);

	}
	// ����
	void RotateL(Node* grandf) {
		Node* parent = grandf->_right;
		Node* pL = parent->_left;
		grandf->_right = pL;
		if (pL) {
			pL->_parent = grandf;
		}
		parent->_left = grandf;

		if (grandf == _root) {
			_root = parent;
			parent->_parent = nullptr;
		}
		else {
			parent->_parent = grandf->_parent;
			if (grandf->_parent->_left == grandf) {
				grandf->_parent->_left = parent;
			}
			else if (grandf->_parent->_right == grandf) {
				grandf->_parent->_right = parent;
			}
		}
		grandf->_parent = parent;

	}
	// �ҵ���
	void RotateR(Node* grandf) {
		Node* parent = grandf->_left;
		Node* pR = parent->_right;
		grandf->_left = pR;
		if (pR) {
			pR->_parent = grandf;
		}
		parent->_right = grandf;

		if (grandf == _root) {
			_root = parent;
			parent->_parent = nullptr;
		}
		else {
			parent->_parent = grandf->_parent;
			if (grandf->_parent->_left == grandf) {
				grandf->_parent->_left = parent;
			}
			else if (grandf->_parent->_right == grandf) {
				grandf->_parent->_right = parent;
			}
			
		}
		grandf->_parent = parent;

	}
	void RotateLR(Node* grandf) {
		Node* uncle = nullptr;
		Node* parent = grandf->_left;
		if (parent == grandf->_left) {
			Node* uncle = grandf->_right;
		}
		else {
			Node* uncle = grandf->_left;
		}
		Node* cur = parent->_right;
		//Node* curL = cur->_left;
		RotateL(parent);
		RotateR(grandf);

	}
	void RotateRL(Node* grandf) {
		Node* uncle = nullptr;
		Node* parent = grandf->_right;
		if (parent == grandf->_left) {
			Node* uncle = grandf->_right;
		}
		else {
			Node* uncle = grandf->_left;
		}
		Node* cur = parent->_left;
		//Node* curR = cur->_right;
		RotateR(parent);
		RotateL(grandf);

	}
private:
	Node* _root;
};
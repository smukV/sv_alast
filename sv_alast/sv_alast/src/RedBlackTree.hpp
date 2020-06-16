#pragma once
#include <utility>

namespace sv_alast {
	template<class Key, class Value>
	class RedBlackTree
	{
	private:
		enum Color {
			BLACK,
			RED
		};
		template<class Key, class Value>
		struct Node {
			std::pair<Key, Value> *m_data;
			Color m_color;
			Node *m_parent, *m_left, *m_right;
			Node() {
				m_data = nullptr;
				m_color = BLACK;
				m_parent = nullptr;
				m_left = nullptr;
				m_right = nullptr;
			}
			Node(const std::pair<Key, Value> data, Node<Key, Value> *parent = nullptr, Color color = BLACK) {
				m_data = new std::pair<Key, Value>(data);
				m_color = color;
				m_parent = parent;
				m_left = nullptr;
				m_right = nullptr;
			}
			Node(const Key key, Value value, Node<Key, Value> *parent = nullptr, Color color = BLACK) {
				m_data = new std::pair<Key, Value>(key, value);
				m_color = color;
				m_parent = parent;
				m_left = nullptr;
				m_right = nullptr;
			}
			~Node() {
				if (m_data != nullptr)
					delete m_data;
			}
		};

		Node<Key, Value> *m_root;
		Node<Key, Value> *m_nil; //empty leaf

		void Rebalance(Node<Key, Value> *node) {
			//case 0 node is a root
			if (node == m_root) {
				node->m_color = BLACK;
				return;
			}
			Node<Key, Value> *parent = node->m_parent;
			Node<Key, Value> *grandParent = parent->m_parent;
			Node<Key, Value> *uncle;
			bool isParentLeftChild = (parent == grandParent->m_left);
			bool isNodeLeftChild = (node == parent->m_left);
			if (isParentLeftChild)
				uncle = grandParent->m_right;
			else
				uncle = grandParent->m_left;
			// case 1 uncle is red 
			if (uncle->m_color == RED) {
				parent->m_color = BLACK;
				uncle->m_color = BLACK;
				grandParent->m_color = RED;
				if (grandParent->m_parent == m_root)
					return;
				Rebalance(grandParent);
				return;
			}
			//case 2 uncle is black (triangle)
			if (isNodeLeftChild ^ isParentLeftChild) {
				if (isNodeLeftChild) {
					RotateRight(node->m_parent);
					Rebalance(parent);
					return;
				}
				else {
					RotateLeft(node->m_parent);
					Rebalance(parent);
					return;
				}
			}
			//case 3 uncle is black (line)
			if (isNodeLeftChild)
				RotateRight(grandParent);
			else
				RotateLeft(grandParent);
			grandParent->m_color = RED;
			parent->m_color = BLACK;
		}
		void RotateRight(Node<Key, Value> *node) {
			if (node->m_left == m_nil)
				return;
			Node<Key, Value> *child = node->m_left;
			if (child->m_right != m_nil) {
				node->m_left = child->m_right;
				child->m_right->m_parent = node;
			}
			else
				node->m_left = m_nil;
			if (node == m_root) {
				m_root = child;
				child->m_parent = nullptr;
			}
			else {
				child->m_parent = node->m_parent;
				if (node == node->m_parent->m_left)
					node->m_parent->m_left = child;
				else
					node->m_parent->m_right = child;
			}
			child->m_right = node;
			node->m_parent = child;
		}
		void RotateLeft(Node<Key, Value> *node) {
			if (node->m_right == m_nil)
				return;
			Node<Key, Value> *child = node->m_right;
			if (child->m_left != m_nil) {
				node->m_right = child->m_left;
				child->m_left->m_parent = node;
			}
			else
				node->m_right = m_nil;
			if (node == m_root) {
				m_root = child;
				child->m_parent = nullptr;
			}
			else {
				child->m_parent = node->m_parent;
				if (node == node->m_parent->m_left)
					node->m_parent->m_left = child;
				else
					node->m_parent->m_right = child;
			}
			child->m_left = node;
			node->m_parent = child;
		}

		void DestroySubTree(Node<Key, Value> *node) {
			if (node->m_left != m_nil)
				DestroySubTree(node->m_left);
			if (node->m_right != m_nil)
				DestroySubTree(node->m_right);
			delete node;
		}

		void DeleteNode(Node<Key, Value> *node) {
			bool isNodeLeftChild = (node != m_root) ? node == node->m_parent->m_left : false;
			//case 0 node dont have childs
			if (node->m_left == m_nil & node->m_right == m_nil) {
				if (node->m_color == BLACK)
					ResolveDoubleBlack(node);
				if (node != m_root) {
					if (isNodeLeftChild)
						node->m_parent->m_left = m_nil;
					else
						node->m_parent->m_right = m_nil;
				}
				delete node;
				return;
			}
			//case 1 node has one child	
			else if (node->m_left != m_nil ^ node->m_right != m_nil) {
				Node<Key, Value> *child = (node->m_left != m_nil) ? node->m_left : node->m_right;
				node->m_data = child->m_data;
				child->m_data = nullptr;
				node->m_left = (node->m_right = m_nil);
				delete child;
				return;
			}
			//case 2 node has two childs
			else if (node->m_left != m_nil & node->m_right != m_nil) {
				Node<Key, Value> *rightMostInLeftSubTree = node->m_left;
				while (rightMostInLeftSubTree->m_right != m_nil)
					rightMostInLeftSubTree = rightMostInLeftSubTree->m_right;
				node->m_data = rightMostInLeftSubTree->m_data;
				rightMostInLeftSubTree->m_data = nullptr;
				DeleteNode(rightMostInLeftSubTree);
			}
		}
		void ResolveDoubleBlack(Node<Key, Value> *node) {
			if (node == m_root)
				return;

			bool isNodeLeftChild = node == node->m_parent->m_left;
			Node<Key, Value> *parent = node->m_parent;
			Node<Key, Value> *sibling = (!isNodeLeftChild) ? parent->m_left : parent->m_right;
			Node<Key, Value> *nephew;
			if (isNodeLeftChild) //finding red nephew starting from opposit side of node, will be black if not found
				nephew = (sibling->m_right->m_color == RED) ? sibling->m_right : sibling->m_left;
			else
				nephew = (sibling->m_left->m_color == RED) ? sibling->m_left : sibling->m_right;
			bool isNephewLeftChild = nephew == sibling->m_left;
			//case 0 red sibling
			if (sibling->m_color == RED) {
				if (isNodeLeftChild)
					RotateLeft(parent);
				else
					RotateRight(parent);
				ResolveDoubleBlack(node);
			}
			//case 1 black sibling and at least one red nephew
			else if (nephew->m_color == RED) {
				//case 1.1 red nephew, sibling and parent making line
				if (isNodeLeftChild != isNephewLeftChild) {
					nephew->m_color = BLACK;
					sibling->m_color = parent->m_color;
					parent->m_color = BLACK;
					if (isNodeLeftChild)
						RotateLeft(parent);
					else
						RotateRight(parent);
				}
				//case 1.2 red nephew, sibling and parent making triangle
				else {
					sibling->m_color = RED;
					nephew->m_color = BLACK;
					if (isNephewLeftChild)
						RotateRight(sibling);
					else
						RotateLeft(sibling);
					ResolveDoubleBlack(node);
				}
			}
			//case 2 no red nephews
			else if (nephew->m_color == BLACK) {
				sibling->m_color = RED;
				if (parent->m_color == RED) {
					parent->m_color = BLACK;
					return;
				}
				else if (parent == m_root)
					return;
				else
					ResolveDoubleBlack(parent);
			}
		}

		Node<Key, Value>* GetNode(const Key& key) const {
			Node<Key, Value> *descendant = m_root;
			while (descendant != m_nil) {
				if (key < (descendant->m_data->first))
					descendant = descendant->m_left;
				else if (key > (descendant->m_data->first))
					descendant = descendant->m_right;
				else
					return descendant;
			}
			return m_nil;
		}
	public:
		RedBlackTree() {
			m_nil = new Node<Key, Value>();
			m_root = m_nil;
		}
		RedBlackTree(const std::pair<Key, Value> &data) {
			m_root = new Node<Key, Value>(data);
			m_nil = new Node<Key, Value>();
			m_root->m_left = m_nil;
			m_root->m_right = m_nil;
		}
		RedBlackTree(const Key key, const Value value) {
			m_root = new Node<Key, Value>(key, value);
			m_nil = new Node<Key, Value>();
			m_root->m_left = m_nil;
			m_root->m_right = m_nil;
		}
		~RedBlackTree() {
			if (m_root != m_nil)
				DestroySubTree(m_root);
			delete m_nil;
		}

		void Insert(const Key& key, const Value& value) {
			this->Insert(std::pair<Key, Value>(key, value));
		}
		void Insert(const std::pair<Key, Value> &data) {
			if (m_root == m_nil) {
				m_root = new Node<Key, Value>(data);
				m_root->m_left = m_nil;
				m_root->m_right = m_nil;
				return;
			}
			bool isDescendantLeft = (data.first) < (m_root->m_data->first);
			Node<Key, Value> *descendant = ((isDescendantLeft) ? m_root->m_left : m_root->m_right);
			Node<Key, Value> *ancestor = m_root;

			while (descendant != m_nil) {
				ancestor = descendant;
				descendant = (data.first < (descendant->m_data->first) ? descendant->m_left : descendant->m_right);
			}
			descendant = new Node<Key, Value>(data, ancestor, RED);
			descendant->m_left = m_nil;
			descendant->m_right = m_nil;

			isDescendantLeft = data.first < (ancestor->m_data->first);
			if (isDescendantLeft)
				ancestor->m_left = descendant;
			else
				ancestor->m_right = descendant;
			if (ancestor->m_color == RED)
				Rebalance(descendant);
		}

		void Delete(const Key& key) {
			if (m_root == nullptr)
				return;
			Node<Key, Value> *node = m_root;
			while (node != m_nil) {
				if (key < *(node->m_data->first))
					node = node->m_left;
				else if (key > *(node->m_data->first))
					node = node->m_right;
				else
					break;
			}
			if (node == m_nil) //return if not found
				return;
			DeleteNode(node);
		}

		const Value& Get(const Key key) const {
			Node<Key, Value> *descendant = m_root;
			while (descendant != m_nil) {
				if (key < (descendant->m_data->first))
					descendant = descendant->m_left;
				else if (key > (descendant->m_data->first))
					descendant = descendant->m_right;
				else
					return descendant->m_data->second;
			}
		}
		void Set(const Key& key, const Value& value) {
			Node<Key, Value> *node = GetNode(key);
			if (node == m_nil)
				Insert(key, value);
			else {
				node->m_data->second = value;
			}
		}
		bool isSet(const Key& key) const {
			const Node<Key, Value> *node = GetNode(key);
			if (node == m_nil)
				return false;
			else
				return true;
		}
	};
}
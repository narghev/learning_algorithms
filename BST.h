#include <memory>
#include <iterator>

template<class T>
class BinarySearchTree {
public:
	class Node; // Declaration of a class.

	class iterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::ptrdiff_t difference_type;

		friend class BinarySearchTree;
		// ++iter
		iterator& operator++() {
			if (this->node->right_child != nullptr) {
				*this = tree.begin(this->node->right_child.get());
				return *this;
			}
			// Go up until you went up from a left child.
			while (true) {
				Node* parent = node->parent;
				if (parent == nullptr) {
					*this = tree.end();
					return *this;
				}
				if (parent->left_child.get() == this->node) {
					this->node = parent;
					return *this;
				}
				node = parent;
			}
		}

		// iter++
		iterator operator++(int) {
			iterator copy = *this;
			++(*this);
			return copy;
		}

		// --iter
		iterator& operator--(){
			if (this->node->left_child != nullptr) {
				*this = tree.rbegin(this->node->left_child.get());
				return *this;
			}
			// Go up until you went up from a right child.
			while (true) {
				Node* parent = node->parent;
				if (parent == nullptr) {
					*this = tree.end();
					return *this;
				}
				if (parent->right_child.get() == this->node) {
					this->node = parent;
					return *this;
				}
				node = parent;
			}
		}

		// iter--
		iterator operator--(int) {
			iterator copy = *this;
			--(*this);
			return copy;
		}

		// Dereferencing the iterator to get the value inside.
		// (*iter)
		const T& operator*() {
			return node->get();
		}

		// Compare to another iterator
		// iter1 == iter2.
		bool operator==(const iterator& other) {
			return node == other.node;
		}

		bool operator!=(const iterator& other) {
			return node != other.node;
		}
		// Copy the current iterator.
		iterator& operator=(const iterator& other) {
			node = other.node;
			return *this;
		}

	private:
		iterator(BinarySearchTree& tree, Node * node)
			: node(node)
			, tree(tree) {

		}
	private:
		Node* node;
		BinarySearchTree& tree;

	};

	BinarySearchTree() 
		: size_(0) {
		
	}

	// Iterator to the start of container.
	iterator begin() {
		return begin(head.get());
	}

	// Iterator to the element AFT`ER the last element of container.
	iterator end() {
		return iterator(*this, nullptr);
	}

	// Iterator to the start of container.
	iterator rbegin(){
		return rbegin(head.get());
	} // 0.5 points

	// Iterator to the element AFTER the last element of container.
	iterator rend() {
		return end();
	}

	// Returns the size of the container.
	int size() const {
		return size_;
	}

	// Inserts the new value.
	void insert(const T& value) {
		++size_;
		if (size_ == 1) {
			head = std::make_shared<Node>(
				value, 
				std::shared_ptr<Node>(),
				std::shared_ptr<Node>(),
				nullptr);
			return;
		}
		insert(head, value);
	}

	bool is_empty() const {
		return size_ == 0;
	}

	// Search for exact matches.
	iterator find(const T& value) {
		if (is_empty())
			return end();
		return find(head, value);
	}

	// Search for set member <= value.
	iterator lower_bound(const T& value){
		if (is_empty())
			return end();
		return lower_bound(head, value);
	} // 1 point

	// Search for set member > value.
	iterator upper_bound(const T& value){
		if (is_empty())
			return end();
		return upper_bound(head, value);
	}; // 1 point

	// Erases element at given location.
	void erase(const iterator& iter){
		if (iter.node->left_child == nullptr && iter.node->right_child == nullptr){
			delete_node(iter);
			return;
		}

		if (iter.node->left_child == nullptr){
			if (left_node(iter.node))
				iter.node->parent->left_child = iter.node->right_child;
			else
				iter.node->parent->right_child = iter.node->right_child;
			return;
		}

		if (iter.node->right_child == nullptr){
			if (left_node(iter.node))
				iter.node->parent->left_child = iter.node->left_child;
			else
				iter.node->parent->right_child = iter.node->left_child;
			return;
		}

		auto new_iter = iter;
		new_iter++;
		iter.node->value = new_iter.node->value;
		erase(new_iter);

	} // 2 extra points.

	class Node {
	public:
		Node(const T& value,
			std::shared_ptr<Node> left_child = nullptr,
			std::shared_ptr<Node> right_child = nullptr,
			Node* parent = nullptr)
			: value(value)
			, left_child(left_child)
			, right_child(right_child)
			, parent(parent) {

		}

		const T& get() const {
			return value;
		}
		
		T value;
		std::shared_ptr<Node> left_child;
		std::shared_ptr<Node> right_child;

		// We don't OWN this parent pointer;
		Node* parent;
	};

private:
	iterator begin(Node* current) {
		if (is_empty())
			return end();
		while (current->left_child != nullptr) {
			current = current->left_child.get();
		}
		return iterator(*this, current);
	}

	iterator rbegin(Node* current){
		if (is_empty())
			return end();
		while (current->right_child != nullptr) {
			current = current->right_child.get();
		}
		return iterator(*this, current);
	}

	iterator lower_bound(std::shared_ptr<Node>& current_node, const T& search_value) {
		if (current_node->get() < search_value) {
			if (current_node->right_child == nullptr) 
				return iterator(*this, current_node.get()); 
			iterator lb = lower_bound(current_node->right_child, search_value);
			if (lb == end())
				return iterator(*this, current_node.get());
			return lb;
		}
		if (current_node->left_child == nullptr)
			return end();
		return lower_bound(current_node->left_child, search_value);
	}

	iterator upper_bound(std::shared_ptr<Node>& current_node, const T& search_value) {
		if (current_node->get() > search_value) {
			if (current_node->left_child == nullptr) 
				return iterator(*this, current_node.get());
			iterator ub = upper_bound(current_node->left_child, search_value);
			if (ub == end())
				return iterator(*this, current_node.get());
			return ub;
		}
		if (current_node->right_child == nullptr)
			return end();
		return upper_bound(current_node->right_child, search_value);
	}

	bool left_node(Node* node){
		if (node->parent->left_child->value == node->value)
			return true;
		return false;
	}

	void delete_node(const iterator& iter) {
			if (iter.node->parent->left_child->value == iter.node->value)
				iter.node->parent->left_child = nullptr;
			else
				iter.node->parent->right_child = nullptr;
			--size_;
	}

	void insert(std::shared_ptr<Node>& current_node, const T& value) {
		if (current_node->get() == value)
			return;
		if (current_node->get() < value) {
			if (!current_node->right_child) {
				current_node->right_child = std::make_shared<Node>(value);
				current_node->right_child->parent = current_node.get();
			}
			else {
				insert(current_node->right_child, value);
			}
		}
		else {
			if (!current_node->left_child) {
				current_node->left_child = std::make_shared<Node>(value);
				current_node->left_child->parent = current_node.get();
			}
			else {
				insert(current_node->left_child, value);
			}
		}
	}

	iterator find(std::shared_ptr<Node>& current_node, const T& search_value) {
		if (current_node->get() == search_value)
			return iterator(*this, current_node.get());
		if (current_node->get() < search_value) {
			if (!current_node->right_child) {
				return end();
			}
			else {
				return find(current_node->right_child, search_value);
			}
		}
		else {
			if (!current_node->left_child) {
				return end();
			}
			else {
				return find(current_node->left_child, search_value);
			}
		}
	}

private:
	// The head of the tree.
	std::shared_ptr<Node> head;

	int size_;
};

// Node * my_node = new Node();
// CODE throw
// delete my_node;

// {
// unique_ptr<Node> 
// shared_ptr<Node> my_node = std::make_shared<Node>(15);
// foo(std::move(my_node));
// my_node.get() // crash.
// Node* inside_ptr = my_node.get();
// CODE.
// }

// class shared_ptr {
//
//
// int counter; = 0
// T* ptr;
//}
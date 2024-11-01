#include <stdexcept>
#include <utility>

template <typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;

        Node(const K& key, const V& value) : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t tree_size;


    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key, node->value);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* find(Node* node, const K& key) const {
        if (!node) return nullptr;
        if (key < node->key) return find(node->left, key);
        else if (key > node->key) return find(node->right, key);
        else return node;
    }

    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);
        if (key < node->key) node->left = insert(node->left, key, value);
        else if (key > node->key) node->right = insert(node->right, key, value);
        else throw std::runtime_error("Element with key already exists");
        return node;
    }

    Node* erase(Node* node, const K& key, bool& erased) {
        if (!node) return nullptr;
        if (key < node->key) node->left = erase(node->left, key, erased);
        else if (key > node->key) node->right = erase(node->right, key, erased);
        else {
            erased = true;
            if (!node->left) {
                Node* rightNode = node->right;
                delete node;
                return rightNode;
            } else if (!node->right) {
                Node* leftNode = node->left;
                delete node;
                return leftNode;
            } else {
                Node* successor = node->right;
                while (successor->left) successor = successor->left;
                node->key = successor->key;
                node->value = successor->value;
                node->right = erase(node->right, successor->key, erased);
            }
        }
        return node;
    }

public:
    Map() : root(nullptr), tree_size(0) {}

    Map(const Map& other) : root(copy(other.root)), tree_size(other.tree_size) {}

    Map(Map&& other) noexcept : root(other.root), tree_size(other.tree_size) {
        other.root = nullptr;
        other.tree_size = 0;
    }

    Map& operator=(const Map& other) {
        if (this != &other) {
            clear();
            root = copy(other.root);
            tree_size = other.tree_size;
        }
        return *this;
    }

    Map& operator=(Map&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            tree_size = other.tree_size;
            other.root = nullptr;
            other.tree_size = 0;
        }
        return *this;
    }

    ~Map() {
        clear(root);
    }

    bool empty() const {
        return tree_size == 0;
    }

    size_t size() const {
        return tree_size;
    }

    V& at(const K& key) {
        Node* node = find(root, key);
        if (!node) throw std::out_of_range("Key not found");
        return node->value;
    }

    const V& at(const K& key) const {
        Node* node = find(root, key);
        if (!node) throw std::out_of_range("Key not found");
        return node->value;
    }

    V* find(const K& key) {
        Node* node = find(root, key);
        if (!node) return nullptr;
        return &(node->value);
    }

    const V* find(const K& key) const {
        Node* node = find(root, key);
        if (!node) return nullptr;
        return &(node->value);
    }

    V& operator[](const K& key) {
        Node* node = find(root, key);
        if (!node) {
            root = insert(root, key, V());
            ++tree_size;
            node = find(root, key);
        }
        return node->value;
    }

    template <typename F>
    void insert(const K& key, F&& value) {
        if (find(root, key)) throw std::runtime_error("Element with key already exists");
        root = insert(root, key, std::forward<F>(value));
        ++tree_size;
    }

    bool erase(const K& key) {
        bool erased = false;
        root = erase(root, key, erased);
        if (erased) --tree_size;
        return erased;
    }

    void clear() {
        clear(root);
        root = nullptr;
        tree_size = 0;
    }
};

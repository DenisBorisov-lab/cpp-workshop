#include <iostream>
#include <fstream>
#include <cstring>

template<typename K, typename T>
class AVL {
private:

    struct Node {
        K Key;
        T Value;
        Node *Left, *Right;
        short Height;

        Node(const K &k, const T &v) {
            Key = k;
            Value = v;
            Left = Right = nullptr;
            Height = 1;
        }
    };

    Node *Root;

    Node *findTree(Node *tree, const K &k) {
        while (tree != nullptr) {
            if (k > tree->Key) {
                tree = tree->Right;
            } else if (k < tree->Key) {
                tree = tree->Left;
            } else {
                return tree;
            }
        }
        return tree;
    }

    Node *insertNode(Node *tree, Node *node) {
        if (tree == nullptr) {
            return node;
        }
        if (node->Key < tree->Key) {
            Node *temp = insertNode(tree->Left, node);
            if (temp == nullptr)
                return nullptr;
            tree->Left = temp;
        } else if (node->Key > tree->Key) {
            Node *temp = insertNode(tree->Right, node);
            if (temp == nullptr)
                return nullptr;
            tree->Right = temp;
        } else {
            return nullptr;
        }
        updateHeight(tree);
        return balance(tree);
    }

    Node *removeNode(Node *tree, const K &key) {
        if (tree == nullptr) {
            return nullptr;
        }
        if (key < tree->Key) {
            Node *temp = removeNode(tree->Left, key);
            tree->Left = temp;
        } else if (key > tree->Key) {
            Node *temp = removeNode(tree->Right, key);
            tree->Right = temp;
        } else {
            if (tree->Right == nullptr) {
                Node *temp = tree->Left;
                delete tree;
                return temp;
            } else if (tree->Left == nullptr) {
                Node *temp = tree->Right;
                delete tree;
                return temp;
            } else {
                Node *m = min(tree->Right);
                tree->Key = m->Key;
                tree->Value = m->Value;
                tree->Right = removeMin(tree->Right);
                delete m;
            }
        }
        updateHeight(tree);
        return balance(tree);
    }

    Node *min(Node *tree) {
        while (tree->Left != nullptr) {
            tree = tree->Left;
        }
        return tree;
    }

    Node *removeMin(Node *tree) {
        if (tree->Left == nullptr) {
            return tree->Right;
        }
        tree->Left = removeMin(tree->Left);
        return balance(tree);
    }

    Node *rightRotate(Node *tree) {
        Node *temp = tree->Left;
        tree->Left = temp->Right;
        temp->Right = tree;
        updateHeight(tree);
        updateHeight(temp);
        return temp;
    }

    Node *leftRotate(Node *tree) {
        Node *temp = tree->Right;
        tree->Right = temp->Left;
        temp->Left = tree;
        updateHeight(tree);
        updateHeight(temp);
        return temp;
    }

    Node *balance(Node *tree) {
        short bf = BFactor(tree);
        if (bf < -1) {
            if (BFactor(tree->Left) > 0) {
                tree->Left = leftRotate(tree->Left);
            }
            tree = rightRotate(tree);
        } else if (bf > 1) {
            if (BFactor(tree->Right) < 0) {
                tree->Right = rightRotate(tree->Right);
            }
            tree = leftRotate(tree);
        }
        updateHeight(tree);
        return tree;
    }

    inline short max(short a, short b) {
        return a > b ? a : b;
    }

    inline short getHeight(Node *tree) {
        return tree == nullptr ? 0 : tree->Height;
    }

    void updateHeight(Node *tree) {
        tree->Height = max(getHeight(tree->Left), getHeight(tree->Right)) + 1;
    }

    inline short BFactor(Node *tree) {
        return getHeight(tree->Right) - getHeight(tree->Left);
    }

    void deleteTree(Node *tree) {
        if (tree == nullptr)
            return;
        deleteTree(tree->Left);
        deleteTree(tree->Right);
        delete tree;
    }


    void serializeRecursive(Node* node, std::ofstream& ofs) {
        bool hasNode = (node != nullptr);
        ofs.write(reinterpret_cast<char*>(&hasNode), sizeof(bool));


        if (!hasNode) {
            return;
        }

        size_t keySize = node->Key.size();
        ofs.write(reinterpret_cast<char*>(&keySize), sizeof(size_t));

        ofs.write(node->Key.data(), keySize);

        ofs.write(reinterpret_cast<char*>(&node->Value), sizeof(T));

        ofs.write(reinterpret_cast<char*>(&node->Height), sizeof(short));

        serializeRecursive(node->Left, ofs);
        serializeRecursive(node->Right, ofs);
    }

    Node* deserializeRecursive(std::ifstream& ifs) {
        bool hasNode;
        ifs.read(reinterpret_cast<char*>(&hasNode), sizeof(bool));

        if (!hasNode) {
            return nullptr;
        }

        size_t keySize;
        ifs.read(reinterpret_cast<char*>(&keySize), sizeof(size_t));

        std::string key(keySize, '\0');
        ifs.read(key.data(), keySize);

        T value;
        ifs.read(reinterpret_cast<char*>(&value), sizeof(T));

        short height;
        ifs.read(reinterpret_cast<char*>(&height), sizeof(short));

        Node* newNode = new Node(key, value);
        newNode->Height = height;

        newNode->Left = deserializeRecursive(ifs);
        newNode->Right = deserializeRecursive(ifs);

        return newNode;
    }

public:

    void deserialize(std::ifstream &is) {
        Root = deserializeRecursive(is);
    }

    void serialize(std::ofstream &ofs) {
        serializeRecursive(Root, ofs);
    }

    T *find(const K &k) {
        Node *temp = findTree(Root, k);
        return temp == nullptr ? nullptr : &(temp->Value);
    }

    AVL() {
        Root = nullptr;
    }

    ~AVL() {
        deleteTree(Root);
    }

    int insert(const K &k, const T &v) {
        if (findTree(Root, k) != nullptr) {
            return 0;
        }
        Root = insertNode(Root, new Node(k, v));
        return 1;
    }

    int remove(const K &k) {
        if (findTree(Root, k) == nullptr) {
            return 0;
        }
        Root = removeNode(Root, k);
        return 1;
    }

    int empty() {
        return Root == nullptr;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    AVL<std::string, unsigned long long> tree;
    std::string command, key;
    unsigned long long value;

    while (true) {
        std::cin >> std::ws;
        if (std::cin.eof()) {
            break;
        }
        std::cin >> command;
        if (command == "+") {
            std::cin >> key;
            for (auto &x: key) {
                x = (char) tolower(x);
            }
            std::cin >> value;
            if (tree.insert(key, value)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "Exist" << std::endl;
            }
        } else if (command == "-") {
            std::cin >> key;
            for (auto &x: key) {
                x = (char) tolower(x);
            }
            if (tree.remove(key)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        } else if (command == "!") {
            std::cin >> key;
            if (key == "Save") {
                std::cin >> command;
                std::ofstream ofs(command.c_str(), std::ios::binary);
                tree.serialize(ofs);
                std::cout << "OK" << std::endl;
            } else if (key == "Load") {
                std::cin >> command;
                std::ifstream ifs(command.c_str(), std::ios::binary);
                tree.deserialize(ifs);
                std::cout << "OK" << std::endl;
            }
        } else {
            unsigned long long *tempValue;
            for (auto &x: command) {
                x = (char) tolower(x);
            }
            if ((tempValue = tree.find(command)) != nullptr) {
                std::cout << "OK: " << *tempValue << std::endl;
            } else {
                std::cout << "NoSuchWord" << std::endl;
            }
        }
    }
    return 0;
}
#include <list>

template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::Default() : root(0), size(0)
{
}

template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::~Default()
{
    if (root) traversePostOrder(root, [](Node* node){ delete node; });
}

template <typename Key, typename Value>
typename Rt::Tree::RB::Default<Key, Value>::Node*
Rt::Tree::RB::Default<Key, Value>::search(Key key) const
{
    if (root)
    {
        auto currentNode = root;
        while (currentNode)
        {
            if (currentNode->key == key)
                return currentNode;
            else
            {
                if (currentNode->key > key)
                    currentNode = currentNode->children[0];
                else
                    currentNode = currentNode->children[1];
            }
        }
    }

    return 0;
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traversePreOrder(Node* node, std::function<void (Node*)> f)
{
    f(node);
    if (node->children[0]) traverseInOrder(node->children[0], f);
    if (node->children[1]) traverseInOrder(node->children[1], f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traversePreOrder(std::function<void (Node*)> f)
{
    if (root) traversePreOrder(root, f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traverseInOrder(Node* node, std::function<void (Node*)> f)
{
    if (node->children[0]) traverseInOrder(node->children[0], f);
    f(node);
    if (node->children[1]) traverseInOrder(node->children[1], f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traverseInOrder(std::function<void (Node*)> f)
{
    if (root) traverseInOrder(root, f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traverseInReverseOrder(Node* node, std::function<void (Node*)> f)
{
    if (node->children[0]) traverseInReverseOrder(node->children[0], f);
    f(node);
    if (node->children[1]) traverseInReverseOrder(node->children[1], f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traverseInReverseOrder(std::function<void (Node*)> f)
{
    if (root) traverseInReverseOrder(root, f);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traversePostOrder(Node* node, std::function<void (Node*)> f)
{
    for (int i = 0; i < 2; i++)
        if (node->children[i])
            traversePostOrder(node->children[i], f);
    f(node);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::traversePostOrder(std::function<void (Node*)> f)
{
    if (root) traversePostOrder(root, f);
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::search(Key key, Value* valuePtr) const
{
    auto node = search(key);
    if (node)
    {
        *valuePtr = node->value;
        return true;
    }

    return false;
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::rotate(Node* node, u1 direction)
{
    if (node->rotate(direction))
        if (root == node)
            root = node->parent;
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::isConsistent() const
{
    std::list<Node*> inconsistentNodes;

    if (root && root->parent) return false;

    traversePreOrder([&](Node* node)
                     {
                         if (node->children[0])
                             if (node->children[0]->parent != node || node->children[0]->directionToParent != 0)
                                 inconsistentNodes.push_back(node->children[0]);

                         if (node->children[1])
                             if (node->children[1]->parent != node || node->children[1]->directionToParent != 1)
                                 inconsistentNodes.push_back(node->children[1]);
                     });

    return inconsistentNodes.empty();
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::insertCase1(Node* node, Node* parentNode)
{
    if (parentNode)
        insertCase2(node);
    else
    {
        node->color = Node::Color::Black;
        root = node;
    }
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::insertCase2(Node* node)
{
    if (node->parent && node->parent->color == Node::Color::Red)
        insertCase3(node);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::insertCase3(Node* node)
{
    Node* grandparent;
    Node* uncle;

    node->getGrandparentAndUncle(&grandparent, &uncle);
    if (uncle && uncle->color == Node::Color::Red)
//        && node->parent->color == Node::Color::Red)
    {
        node->parent->color = uncle->color = Node::Color::Black;
        grandparent->color = Node::Color::Red;

        insertCase1(grandparent, grandparent->parent);
    }
    else
    {
        insertCase4(node, grandparent);
    }
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::insertCase4(Node* node, Node* grandparent)
{
    if (node->directionToParent == 1 && node->parent->directionToParent == 0)
    {
        rotate(node->parent, 1);
        node = node->children[0];
    }
    else
    {
        if (node->directionToParent == 0 && node->parent->directionToParent == 1)
        {
            rotate(node->parent, 0);
            node = node->children[1];
        }
    }

    insertCase5(node);
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::insertCase5(Node* node)
{
    auto grandparent = node->getGrandparent();

    node->parent->color = Node::Color::Black;
    grandparent->color = Node::Color::Red;

    if (node->directionToParent == node->parent->directionToParent)
        rotate(grandparent, node->parent->directionToParent);
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::insert(Key key, Value value)
{
    Node* parentNode = 0;
    Node* currentNode = root;
    bool found = false;
    u1 directionToParent = 0;

    while (currentNode)
    {
        if (currentNode->key != key)
        {
            directionToParent = currentNode->key > key ? 0 : 1;
            parentNode = currentNode;
            currentNode = currentNode->children[directionToParent];
        }
        else
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        auto newNode = new Node(key, value, Node::Color::Red, parentNode, 0, 0, directionToParent);
        if (newNode)
        {
            if (parentNode) parentNode->children[directionToParent] = newNode;
            insertCase1(newNode, parentNode);
        }

        size++;

        return true;
    }

    return false;
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::insert(std::pair<Key, Value> pair)
{
    return insert(pair.first, pair.second);
}
/*
void delete_one_child(struct node *n)
{
        struct node *child = is_leaf(n->right) ? n->left : n->right;
 
        replace_node(n, child);
        if (n->color == BLACK) {
                if (child->color == RED)
                        child->color = BLACK;
                else
                        delete_case1(child);
        }
        free(n);
}
*/
template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::erase(Key key)
{
    auto node = search(key);
    if (node)
    {
        
        
        size--;

        return true;
    }

    return false;
}

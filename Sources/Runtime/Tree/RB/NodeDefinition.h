template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::Node::Node()
{
    parent = children[0] = children[1] = 0;
}

template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::Node::Node(Key key, Value value, Color color)
{
    this->key = key;
    this->value = value;
    this->color = color;
}

template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::Node::Node(Key key, Value value, Color color, Node* parent) : Node(key, value, color)
{
    this->parent = parent;
    children[0] = children[1] = 0;
    directionToParent = 0;
}

template <typename Key, typename Value>
Rt::Tree::RB::Default<Key, Value>::Node::Node(Key key, Value value, Color color,
                                              Node* parent, Node* leftChild, Node* rightChild,
                                              u1 directionToParent) : Node(key, value, color)
{
    this->key = key;
    this->value = value;
    this->color = color;
    this->parent = parent;
    this->children[0] = leftChild;
    this->children[1] = rightChild;
    this->directionToParent = directionToParent;
}

template <typename Key, typename Value>
typename Rt::Tree::RB::Default<Key, Value>::Node*
Rt::Tree::RB::Default<Key, Value>::Node::getGrandparent() const
{
    return parent ? parent->parent : 0;
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::Node::getGrandparentAndUncle(Node** grandparent, Node** uncle) const
{
    auto localGrandparent = getGrandparent();

    if (localGrandparent && uncle)
        *uncle = localGrandparent->children[!parent->directionToParent];

    if (grandparent) *grandparent = localGrandparent;
}

template <typename Key, typename Value>
typename Rt::Tree::RB::Default<Key, Value>::Node*
Rt::Tree::RB::Default<Key, Value>::Node::getBrother() const
{
    return parent ? parent->children[!directionToParent] : 0;
}

template <typename Key, typename Value>
void Rt::Tree::RB::Default<Key, Value>::Node::attachToAnotherParent(Node* newParent, u1 directionToParent)
{
    parent = newParent;
    if (newParent) newParent->children[directionToParent] = this;
    this->directionToParent = directionToParent;
}

template <typename Key, typename Value>
bool Rt::Tree::RB::Default<Key, Value>::Node::rotate(u1 directionToChild)
{
    if (children[directionToChild])
    {
        auto N = children[directionToChild];
        auto M = N->children[1 - directionToChild];

        N->attachToAnotherParent(parent, directionToParent);
        attachToAnotherParent(N, 1 - directionToChild);

        if (M)
            M->attachToAnotherParent(this, directionToChild);
        else
            children[directionToChild] = 0;

        return true;
    }

    return false;
}

template <typename Key, typename Value>
std::pair<Key, Value> Rt::Tree::RB::Default<Key, Value>::Node::getStdPair() const
{
    return std::pair<Key, Value>(key, value);
}

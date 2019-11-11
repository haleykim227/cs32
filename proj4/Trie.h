#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
using namespace std;

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node
    {
        Node() : m_label(' ') {}
        Node(char label) : m_label(label) {}
        ~Node() {}
        vector<ValueType> m_value;
        vector<Node*> m_children;
        char m_label;
    };
    Node* m_root;
    void freeTrie(Node* current);
    void findHelper(vector<ValueType>& vector, const string& key, int index, bool exactMatchOnly, Node* current) const;
};

template<typename ValueType>
Trie<ValueType>::Trie()
: m_root(new Node()) {}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    freeTrie(m_root);
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    freeTrie(m_root);
    Trie();
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    Node* current = m_root;
    for (int i = 0; i < key.size(); i++)
    {
        if (current->m_children.size() == 0)
        {
            current->m_children.push_back(new Node(key[i]));
            current = current->m_children.back();
            if (i == key.size() - 1)
                current->m_value.push_back(value);
        }
        else
        {
            for (int j = 0; j < current->m_children.size(); j++)
            {
                if (key[i] == current->m_children[j]->m_label)
                {
                    current = current->m_children[j];
                    if (i == key.size() - 1)
                        current->m_value.push_back(value);
                    break;
                }
                else if ((j == current->m_children.size() - 1) && (key[i] != current->m_children[j]->m_label))
                {
                    current->m_children.push_back(new Node(key[i]));
                    current = current->m_children.back();
                    if (i == key.size() - 1)
                        current->m_value.push_back(value);
                }
            }
        }
    }
}

template<typename ValueType>
vector<ValueType> Trie<ValueType>::find(const string& key, bool exactMatchOnly) const
{
    vector<ValueType> test;
    if (key == "")
        return test;
    for (int j = 0; j < m_root->m_children.size(); j++)
    {
        if (key[0] == m_root->m_children[j]->m_label)
            findHelper(test, key, 1, exactMatchOnly, m_root->m_children[j]);
    }
    return test;
}

//==============================================Helper functions===================================================

template<typename ValueType>
void Trie<ValueType>::freeTrie(Node* current)
{
    if (current == nullptr)
        return;
    for (int i = 0; i < current->m_children.size(); i++)
    {
        freeTrie(current->m_children[i]);
    }
    delete current;
}


template<typename ValueType>
void Trie<ValueType>::findHelper(vector<ValueType>& vector, const string& key, int index, bool exactMatchOnly, Node* current) const
{
    if (current == nullptr)
        return;
    if (index == key.size())
    {
        vector.insert(vector.end(), current->m_value.begin(), current->m_value.end());
    }
    if (exactMatchOnly == true)
    {
        for (int j = 0; j < current->m_children.size(); j++)
        {
            if (key[index] == current->m_children[j]->m_label)
                findHelper(vector, key, index + 1, true, current->m_children[j]);
        }
    }
    else
    {
        for (int j = 0; j < current->m_children.size(); j++)
        {
            if (key[index] == current->m_children[j]->m_label)
                findHelper(vector, key, index + 1, false, current->m_children[j]);
            else
                findHelper(vector, key, index + 1, true, current->m_children[j]);
        }
    }
}

#endif // TRIE_INCLUDED

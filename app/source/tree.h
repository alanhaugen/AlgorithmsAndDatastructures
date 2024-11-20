#ifndef TREE_H
#define TREE_H

#include <core/containers/linkedlist.h>

template<class Datatype>
class Tree
{
public:
    class Node
    {
    public:
        Datatype* data;
        Node* parent;

        Node()
        {
            data   = NULL;
            parent = NULL;
        }

        ~Node()
        {
            if (data != NULL)
            {
                delete data;
            }
        }
    };

    LinkedList<Node> nodes;
    Node* root;

public:
    Tree()
    {
        root = NULL;
    }

    void Clear()
    {
        nodes.Clear();
    }

    void AddNode(Datatype* data, Node* parent = nullptr)
    {
        Node newNode;
        newNode.data   = data;
        newNode.parent = parent;

        nodes.Append(newNode);

        if (root == NULL)
        {
            root = (*nodes.Begin()).parent;
        }
    }
};

#endif // TREE_H

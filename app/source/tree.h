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

public:
    Tree()
    {
    }

    void Clear()
    {
        nodes.Clear();
    }

    void AddNode(Datatype* data)
    {
        Node newNode;
        newNode.data = data;
        nodes.Append(newNode);
    }
};

#endif // TREE_H

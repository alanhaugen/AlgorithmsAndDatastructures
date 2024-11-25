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
        Datatype data;
        Node* parent;

        LinkedList<Node*> children;

        Node()
        {
            data   = NULL;
            parent = NULL;
        }

        ~Node()
        {
        }
    };

    LinkedList<Node*> nodes;

public:
    LinkedList<Node*> rootChildren;

    Tree()
    {
    }

    void Clear()
    {
        nodes.Clear();
    }

    Node* AddNode(Datatype data)
    {
        Node* newNode = new Node();
        newNode->data = data;

        nodes.Append(newNode);

        return newNode;
    }
};

#endif // TREE_H

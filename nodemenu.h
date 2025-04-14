#pragma once

#include "nodelist.h"
#include "node.h"

class NodeMenu {
private:
    Node* m_Node;
    NodeList* m_Graph;
public:
    NodeMenu(Node* node, NodeList* graph); //only allow node menu to be used with a node, its necessary
    ~NodeMenu() = default;

    void Run();

};

enum NodeMenuOptions{
    INPUT_DESTINATION = 1,
    ADD_CONNECTION,
    REMOVE_CONNECTION,
    NODE_EXIT,
};

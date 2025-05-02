#pragma once

#include <iostream>
#include <string>

#include "core.h"
#include "node.h"
#include "graph.h"

class NodeMenu {
private:
    Node* m_Node;
    Graph* m_Graph;
public:
    NodeMenu(Node* node, Graph* graph); //only allow node menu to be used with a node, its necessary
    ~NodeMenu() = default;

    void Run();

};

enum NodeMenuOptions{
    INPUT_DESTINATION = 1,
    ADD_CONNECTION,
    REMOVE_CONNECTION,
    NODE_EXIT,
};

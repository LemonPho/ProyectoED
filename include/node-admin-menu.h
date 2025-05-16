#include <iostream>
#include "node.h"
#include "core.h"

class NodeAdminMenu{
private:
    Node* m_Node;
    Graph* m_Graph;
public:
    NodeAdminMenu(Node* node, Graph* graph);
    void Run();
};

enum NodeAdminMenuOptions{
    ADD_CONNECTION = 1,
    REMOVE_CONNECTION,
    CHANGE_NAME,
    PRINT_NODE,
    NODE_ADMIN_EXIT,
};
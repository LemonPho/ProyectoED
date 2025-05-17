#pragma once

#include <iostream>
#include "graph.h"
#include "node.h"
#include "core.h"
#include "util.h"
#include "node-admin-menu.h"

class GraphAdminMenu{
private:
    Graph* m_Graph;
public:
    GraphAdminMenu(Graph* graph);
    void Run();
};

//Menu constants
enum GraphAdminMenuOptions {
    ADD_NODE = 1,
    EDIT_NODE,
    DELETE_NODE,
    SHOW_NODES,
    ADMIN_EXIT,
};
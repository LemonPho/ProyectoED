#pragma once

#include <iostream>
#include "graph.h"
#include "core.h"
#include "util.h"

class AdminMenu{
private:
    Graph* m_Graph;
public:
    AdminMenu(Graph* graph);
    void Run();
};

//Menu constants
enum AdminMenuOptions {
    ADD_NODE = 1,
    EDIT_NODE,
    DELETE_NODE,
    SHOW_NODES,
    ADMIN_EXIT,
};
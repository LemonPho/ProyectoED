#pragma once

#include <iostream>

#include "graph.h"
#include "nodemenu.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

class Core {
private:
    Graph* m_Graph = new Graph();
public:
    Core();
    void Run();
    ~Core();

};

enum MainMenuOptions {
    INPUT_LOCATION = 1,
    ADD_NODE,
    EDIT_NODE,
    DELETE_NODE,
    CORE_EXIT,
};

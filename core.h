#pragma once

#include <iostream>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include "graph.h"

class Core {
private:
    Graph* m_Graph;
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

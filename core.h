#pragma once

#include <iostream>

#include "nodelist.h"
#include "nodemenu.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

class Core {
private:
    NodeList* m_Graph = new NodeList();
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
    EXIT,
};

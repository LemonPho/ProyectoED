#include "core.h"
#include "nodemenu.h"
#include "graph.h"
#include "admin-menu.h"

Core::Core() {
    m_Graph = new Graph();
}

void Core::Run(){
    bool exit = false;

    std::string buildingInput;
    Node* selectedNode;
    do{
        system(CLEAR);
        std::cout << "Mapa CUCEI" << std::endl;
        m_Graph->PrintList();
        std::cout << "Ingresa su ubicacion (0. menu de admin, 1. Salir): ";
        std::getline(std::cin, buildingInput);
        if(buildingInput == "0"){
            AdminMenu adminMenu = AdminMenu(m_Graph);
            adminMenu.Run();
        } else if(buildingInput == "1"){
            exit = true;
        } else {
            selectedNode = m_Graph->GetNodeFromString(buildingInput);
            while(!selectedNode){
                std::cout << "No se encontro el edificio buscado (" << buildingInput << "), intenta de nuevo: ";
                std::getline(std::cin, buildingInput);
                selectedNode = m_Graph->GetNodeFromString(buildingInput);
            }

            NodeMenu nodeMenu = NodeMenu(selectedNode, m_Graph);
            nodeMenu.Run();
        }
    } while(!exit);
}


Core::~Core() {

}

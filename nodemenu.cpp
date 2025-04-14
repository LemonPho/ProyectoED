// SPDX-FileCopyrightText: 2025 <copyright holder> <email>
// SPDX-License-Identifier: Apache-2.0

#include "nodemenu.h"
#include "core.h"

NodeMenu::NodeMenu(Node* node, Graph* graph) {
    m_Node = node;
    m_Graph = graph;
}

void NodeMenu::Run() {
    int option;
    bool exit = false;

    do{
        system(CLEAR);
        std::cout << m_Node->GetName() << " menu" << std::endl;
        std::cout << "Edificios Cercanos: " << std::endl;
        m_Node->PrintConnections();
        std::cout << "1. Ingresar Destino" << std::endl;
        std::cout << "2. Agregar Conexion" << std::endl;
        std::cout << "3. Quitar Conexion" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cin >> option;
        switch(option){
            case INPUT_DESTINATION: {
                system(CLEAR);

                std::string destinationInput;
                Node* destinationNode;

                std::cout << "Ingresar Destino" << std::endl;
                m_Graph->PrintList();
                std::cout << "Ingresa el nombre del edificio destino: ";
                std::getline(std::cin, destinationInput);
                destinationNode = m_Graph->GetNodeFromString(destinationInput);
                while(!destinationNode){
                    std::cout << "No se encontro un edificio con el nombre: " << destinationInput << ", intenta de nuevo: ";
                    std::getline(std::cin, destinationInput);
                    destinationNode = m_Graph->GetNodeFromString(destinationInput);
                }

                // array of connections to save the path from origin node (m_Node) to destinationNode
                Connection *path = m_Graph->MakeShortestPath(m_Node, destinationNode);
                break;
            }
        }
    } while(!exit);
}


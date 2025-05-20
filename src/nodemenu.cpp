#include "nodemenu.h"
#include "connection-list.h"

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
        if(m_Node->GetConnectionList().GetAmountConnections() > 0){
            std::cout << "Edificios Cercanos: " << std::endl;
            m_Node->GetConnectionList().PrintNearby();
        } else {
            std::cout << "Este edificio no tiene conexiones" << std::endl;
        }
        
        std::cout << "1. Ingresar Destino" << std::endl;
        std::cout << "2. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        util::ClearBuffer();
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
                ConnectionList path = m_Graph->FindShortestPath(m_Node, destinationNode);
                system(CLEAR);
                path.PrintPath();
                util::EnterToContinue();
                break;
            }

            case NODE_EXIT: {
                exit = true;
                break;
            }

            default: {
                std::cout << "Opcion invalida" << std::endl;
                util::EnterToContinue();
                break;
            }
        }
    } while(!exit);
}


#include "node-admin-menu.h"

NodeAdminMenu::NodeAdminMenu(Node *node, Graph *graph){
    m_Node = node;
    m_Graph = graph;
}

void NodeAdminMenu::Run(){
    bool exit = false;
    int option;

    do{
        system(CLEAR);
        std::cout << "MENU EDIFICIOS ADMIN: " << m_Node->GetName() << std::endl;
        std::cout << "1. Agregar Conexion" << std::endl;
        std::cout << "2. Quitar Conexion" << std::endl;
        std::cout << "3. Cambiar Nombre" << std::endl;
        std::cout << "4. Mostrar Edificio" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;

        switch(option){
            case ADD_CONNECTION: {
                system(CLEAR);
                std::cout << "AGREGAR CONEXION: " << m_Node->GetName() << std::endl;
                
                m_Node->AddConnection(m_Graph);
                break;
            }

            case REMOVE_CONNECTION: {
                system(CLEAR);

                std::cout << "QUTIAR CONEXION: " << m_Node->GetName() << std::endl;
                if(m_Node->GetConnectionList().GetAmountConnections() == 0){
                    std::cout << "El edificio no tiene conexiones" << std::endl;
                    util::EnterToContinue();
                    break;
                }

                int index;

                m_Node->PrintConnectionsIndexed();
                std::cout << "Ingresa el indice del conexion que quiere eliminar: ";
                std::cin >> index;
                index--; //decrement because the connections list starts at 0 and they are printed from 1-n
                while(index < 0 || index > m_Node->GetConnectionList().GetAmountConnections()-1){
                    std::cout << "Ingresa un indice valido: ";
                    std::cin >> index;
                }
                m_Node->DeleteConnectionIndex(index);
                break;
            }

            case CHANGE_NAME: {
                system(CLEAR);
                std::cout << "CAMBIAR NOMBRE: " << m_Node->GetName() << std::endl;

                std::string newName;
                Node* searchNode;
                
                util::ClearBuffer(); //getline doens't work without this
                std::cout << "Ingresa el nuevo nombre: ";
                std::getline(std::cin, newName);

                //verify name is unique
                searchNode = m_Graph->GetNodeFromString(newName);
                while(searchNode){
                    std::cout << "Un edificio ya existe con ese nombre, ingresa otro nombre: ";
                    std::getline(std::cin, newName);
                    searchNode = m_Graph->GetNodeFromString(newName);
                }
                
                m_Node->SetName(newName);
                break;
            }

            case PRINT_NODE:{
                m_Node->PrintFull();
                util::EnterToContinue();
                break;
            }

            case NODE_ADMIN_EXIT:{
                exit = true;
                break;
            }

            default: {
                util::EnterToContinue();
                break;
            }
        }
    } while(!exit);
}

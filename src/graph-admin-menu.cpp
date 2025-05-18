#include "graph-admin-menu.h"

GraphAdminMenu::GraphAdminMenu(Graph* graph) {
    m_Graph = graph;
}

void GraphAdminMenu::Run() {
    system(CLEAR);

    std::string username, password;

    std::cout << "LOGIN" << std::endl;
    std::cout << "Usuario: ";
    std::cin >> username;
    std::cout << "Contrasena: ";
    std::cin >> password;
    while(username != "admin" && password != "admin"){
        std::cout << "Datos invalidos, intenta de nuevo" << std::endl;
        std::cout << "Usuario: ";
        std::cin >> username;
        std::cout << "Contrasena: ";
        std::cin >> password;
    }

    bool exit = false;
    int option;
    do{
        system(CLEAR);
        std::cout << "Menu Admin" << std::endl;
        std::cout << "1. Agregar Edificio" << std::endl;
        std::cout << "2. Editar Edificio" << std::endl;
        std::cout << "3. Eliminar Edificio" << std::endl;
        std::cout << "4. Mostrar Edificios" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        util::ClearBuffer();
        switch(option){
            case ADD_NODE: {
                Node* newNode = new Node();
                newNode->Create(m_Graph);
                m_Graph->InsertNode(newNode);
                m_Graph->WriteToDisk();
                break;
            }

            case EDIT_NODE: {
                system(CLEAR);
                int index;
                Node* node;

                m_Graph->PrintListIndex();
                std::cout << "Ingresa el indice del nodo que quiere modificar: ";
                std::cin >> index;
                //no need to decrement index because in Graph::GetNodeFromIndex it starts at 1
                while(index < 1 && index > m_Graph->NodeCount()){
                    std::cout << "Ingrese un valor valido (es menor a 0 o mayor que el indice maximo): ";
                    std::cin >> index;
                }

                node = m_Graph->GetNodeFromIndex(index);
                if(!node){
                    std::cout << "Hubo un error al intentar cargar la informacion del nodo";
                    util::EnterToContinue();
                    break;
                }
                
                NodeAdminMenu nodeAdminMenu = NodeAdminMenu(node, m_Graph);
                nodeAdminMenu.Run();
                m_Graph->WriteToDisk();
                break;
            }

            case DELETE_NODE: {
                system(CLEAR);
                std::cout << "ELIMINAR EDIFICIO" << std::endl;

                int index;
                m_Graph->PrintListIndex();
                std::cout << "Ingresa el indice del edificio que quiere eliminar: ";
                std::cin >> index;
                m_Graph->DeleteNode(index);
                m_Graph->WriteToDisk();
                break;
            }

            case SHOW_NODES: {
                m_Graph->PrintGraph();
                util::EnterToContinue();
                break;
            }

            case ADMIN_EXIT: {
                exit = true;
                break;
            }

            default: {
                std::cout << "Opcion invalida" << std::endl;
                util::EnterToContinue();
            }
        }
    } while(!exit);
}

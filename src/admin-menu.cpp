#include "admin-menu.h"

AdminMenu::AdminMenu(Graph* graph) {
    m_Graph = graph;
}

void AdminMenu::Run() {
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
                m_Graph->CreateNode();
                break;
            }

            case EDIT_NODE: {
                m_Graph->EditNode();
                break;
            }

            case DELETE_NODE: {
                m_Graph->DeleteNode();
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

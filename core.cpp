#include "core.h"

Core::Core() {

}

void Core::Run(){
    int option;
    bool exit = false;

    do{
        system(CLEAR);
        std::cout << "Mapa CUCEI" << std::endl;
        std::cout << "1. Ingresar Ubicacion" << std::endl;
        std::cout << "2. Agregar Edificio" << std::endl;
        std::cout << "3. Editar Edificio" << std::endl;
        std::cout << "4. Eliminar Edificio" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> option;
        switch(option){
            case INPUT_LOCATION: {
                std::string locationInput;
                Node* selectedNode;

                system(CLEAR);
                std::cout << "Ingresa Ubicacion" << std::endl;
                m_Graph->PrintList();
                std::cout << "Ingresa el nombre del edificio en donde esta: ";
                std::getline(std::cin, locationInput);
                selectedNode = m_Graph->GetNodeFromString(locationInput);
                while(selectedNode == nullptr){
                    std::cout << "No se encontro un edificio con el nombre: " << locationInput << ", intenta de nuevo: ";
                    std::getline(std::cin, locationInput);
                    selectedNode = m_Graph->GetNodeFromString(locationInput);
                }

                NodeMenu nodeMenu(selectedNode, m_Graph);
                nodeMenu.Run(); //Node menu
                break;
            }
        }

    } while(!exit);
}


Core::~Core() {

}

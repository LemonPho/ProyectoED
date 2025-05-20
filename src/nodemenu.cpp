#include "nodemenu.h"
#include "util.h"
#include "connection-list.h"

NodeMenu::NodeMenu(Node* node, Graph* graph) {
    m_Node = node;
    m_Graph = graph;
}


void NodeMenu::Run() {
    int option;
    bool exit = false;

    do {
        system(CLEAR);

        std::cout << "=============================\n";
        std::cout << "   Menú para " << m_Node->GetName() << "\n";
        std::cout << "=============================\n";

        if (m_Node->GetConnectionList().GetAmountConnections() > 0) {
            std::cout << "Edificios Cercanos: " << std::endl;
            m_Node->GetConnectionList().PrintNearby();
        } else {
            std::cout << "Este edificio no tiene conexiones" << std::endl;
        }

        std::cout << "[1] Ingresar Destino" << std::endl;
        std::cout << "[2] Salir" << std::endl;
        std::cout << "Opcion: ";

        // Validar entrada numérica para option
        while (!(std::cin >> option)) {
            std::cin.clear(); // Limpia el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
            std::cout << "Entrada inválida. Por favor ingresa un número: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer para getline

        switch(option) {
            case INPUT_DESTINATION: {
                system(CLEAR);

                // 1. Mostrar mapa de la región actual del nodo origen (m_Node)
                int regionId = m_Node->GetRegion();
                m_Graph->displayMapForRegion(regionId);

                // 2. Pedir destino al usuario
                std::string destinationInput;
                Node* destinationNode = nullptr;

                std::cout << "Ingresar Destino\n";
                m_Graph->PrintList();  // Lista de todos los edificios disponibles

                std::cout << "Ingresa el nombre del edificio destino: ";
                std::getline(std::cin, destinationInput);

                // Validar que el nodo exista
                destinationNode = m_Graph->GetNodeFromString(destinationInput);

                while (!destinationNode) {
                    std::cout << "No se encontró un edificio con el nombre: " << destinationInput << ", intenta de nuevo: ";
                    std::getline(std::cin, destinationInput);
                    destinationNode = m_Graph->GetNodeFromString(destinationInput);
                }

                // 3. Obtener ruta más corta entre m_Node (origen) y destinationNode (destino)
                ConnectionList path = m_Graph->FindShortestPath(m_Node, destinationNode);

                // 4. Preguntar cómo quiere ver la ruta el usuario
                int pathOption = 0;
                std::cout << "\nOpciones de visualización:\n";
                std::cout << "[1] Ver ruta completa\n";
                std::cout << "[2] Ver paso por paso\n";
                std::cout << "Opción: ";

                // Validar entrada numérica para pathOption
                while (!(std::cin >> pathOption)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Entrada inválida. Por favor ingresa un número: ";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

                system(CLEAR);

                // 5. Mostrar ruta según opción
                if (pathOption == 1) {
                    path.PrintPath();
                    util::EnterToContinue();
                } else if (pathOption == 2) {
                    m_Graph->showStepByStepPath(path);
                } else {
                    std::cout << "Opción no válida. Mostrando ruta completa por defecto.\n";
                    path.PrintPath();
                    util::EnterToContinue();
                }
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

    } while (!exit);
}



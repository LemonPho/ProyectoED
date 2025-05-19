#include "core.h"
#include "nodemenu.h"
#include "graph.h"
#include "graph-admin-menu.h"

Core::Core() {
    m_Graph = new Graph();
}

void Core::Run(){
    //read the graph from the disk
    m_Graph->ReadFromDisk();

    bool exit = false;
    std::string buildingInput;
    Node* selectedNode;
    
    do{
        system(CLEAR);
        std::cout << "CUCEI MAPS" << std::endl;
        Map();
        m_Graph->PrintErrorMessages();
        m_Graph->PrintList();
        std::cout << "Ingresa su ubicacion (0. menu de admin, 1. Salir): ";
        std::getline(std::cin, buildingInput);

        if(buildingInput == "0"){
            //open admin menu
            GraphAdminMenu graphAdminMenu = GraphAdminMenu(m_Graph);
            graphAdminMenu.Run();
        } else if(buildingInput == "1"){
            //exit program
            exit = true;
        } else {
            //open node menu
            bool cancelSearch = false;
            selectedNode = m_Graph->GetNodeFromString(buildingInput);
            while(!selectedNode && !cancelSearch){
                //node not found
                std::cout << "No se encontro el edificio buscado (" << buildingInput << "), intenta de nuevo (0 para cancelar): ";
                std::getline(std::cin, buildingInput);
                if(buildingInput == "0"){
                    cancelSearch = true;
                } else {
                    selectedNode = m_Graph->GetNodeFromString(buildingInput);
                }
            }

            if(!cancelSearch){
                NodeMenu nodeMenu = NodeMenu(selectedNode, m_Graph);
                nodeMenu.Run();    
            }
        }
    } while(!exit);
}


Core::~Core() {
    delete m_Graph;
}

void Core::Map() {
    std::ifstream mapaFile("mapAscii.txt", std::ios::in);
    if (!mapaFile.is_open()) {
        m_ErrorMessages += "No se pudo abrir el archivo del mapa (mapAscii.txt)\n";
        return;
    }
    std::string linea;
    while (std::getline(mapaFile, linea)) {
        std::cout << linea << std::endl;
    }
    mapaFile.close();
}
int busquedaBinaria(int arr[], int n, int valor) {
    int inicio = 0, fin = n - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (arr[medio] == valor)
            return medio;
        else if (arr[medio] < valor)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }
    return -1;
}

void QuickSort::ordenar(int arreglo[],int start,int end){
    if (end <= start) {
        return ;
    }
    int pivot=partir(arreglo, start, end);
    ordenar(arreglo, start, pivot-1);
    ordenar(arreglo, pivot+1, end);
    
}
int QuickSort::partir(int arreglo[], int start, int end){

    int pivot=arreglo[end];
    int i=start-1, aux=0;
    
    for (int j=start; j < end; j++) {
        if(arreglo[j]<=pivot){
            i++;
            aux= arreglo[i];
            arreglo[i]=arreglo[j];
            arreglo[j]=aux;
            est++;
        }
    }
    i++;
    aux= arreglo[i];
    arreglo[i]=arreglo[end];
    arreglo[end]=aux;
    est++;
    
    return i;
}

#include "graph.h"
#include "node.h"
#include "connection-list.h"
#include "core.h"

Graph::Graph(){
    m_Header = nullptr;
}

void Graph::AddNode(){
    system(CLEAR);

    Node* newNode = new Node();
    std::string tempName;
    int tempDistance;

    std::cout << "Ingresa el nombre del edificio: ";
    std::getline(std::cin, tempName);

    Connection tempConnection;
    Node* selectedNode;
    bool exitAddConnection = false;
    int index;
    while(!exitAddConnection){
        system(CLEAR);
        std::cout << "AGREGAR CONEXIONES" << std::endl;
        PrintListIndex();
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingresa el indice del edificio que quiere agregar como conexion: ";
        std::cin >> index;
        if(!index){
            exitAddConnection = true;
        } else {
            selectedNode = GetNodeFromIndex(index);
            while(!selectedNode){
                std::cout << "No se encontro un edificio con el indice " << index << ", intenta de nuevo: ";
                std::cin >> index;
                selectedNode = GetNodeFromIndex(index);
            }
            std::cout << "Ingresa la distancia: ";
            std::cin >> tempDistance;
            tempConnection = Connection(selectedNode, tempDistance);
            newNode->InsertConnection(tempConnection);
        }
    }

    newNode->SetName(tempName);
    Node* temp = m_Header;
    if(!temp){
        m_Header = newNode;        
    } else {
        while(temp->GetNext()){
            temp = temp->GetNext();
        }
    
        temp->SetNext(newNode);
        newNode->SetPrev(temp);
    }

    std::cout << "Edificio registrado" << std::endl;
    util::EnterToContinue();
}

void Graph::EditNode(){

}

void Graph::DeleteNode(){
}

Node* Graph::GetNodeFromString(const std::string& nodeName) {
    Node* temp = m_Header;
    while(temp){
        if(temp->GetName() == nodeName) return temp;
        temp = temp->GetNext();
    }

    return nullptr;
}

Node *Graph::GetNodeFromIndex(const int index) {
    Node* temp = m_Header;
    int i = 1;
    while(temp && i != index){
        temp = temp->GetNext();
    }
    return temp;
}

ConnectionList Graph::MakeShortestPath(Node* originNode, Node* destinationNode) {

}


void Graph::PrintGraph(){
    Node* temp = m_Header;

    if(!temp){
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    while(temp){
        temp->PrintFull();
        temp = temp->GetNext();
    }
}

void Graph::PrintList(){
    Node* temp = m_Header;

    if(!temp){
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    while(temp){
        temp->PrintSimple();
        temp = temp->GetNext();
    }
}

void Graph::PrintListIndex() {
    Node* temp = m_Header;

    if(!temp) {
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    int i = 1;
    while(temp){
        temp->PrintSimpleIndex(i);
        temp = temp->GetNext();
    }
}

Graph::~Graph(){
}






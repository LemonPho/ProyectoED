#include "graph.h"
#include "node.h"
#include "connection-list.h"
#include "core.h"

Graph::Graph(){
    m_Header = nullptr;
}

void Graph::CreateNode(){
    system(CLEAR);

    Node* newNode = new Node(); //Node used for creating the new node
    Node* searchNode = new Node(); //Node used for making sure the name is unique
    std::string tempName;
    double tempDistance;

    std::cout << "Ingresa el nombre del edificio: ";
    std::getline(std::cin, tempName);

    //Make sure the name is unique
    searchNode = GetNodeFromString(tempName);
    while(searchNode){
        std::cout << "Un edificio ya existe con ese nombre (" << tempName << "), ingrese un nombre diferente: ";
        std::getline(std::cin, tempName);
        searchNode = GetNodeFromString(tempName);
    }

    Connection tempConnection;
    Node* selectedNode;
    bool exitAddConnection = NodeCount() == 0; //If there aren't nodes, then the node is saved without connections
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
            while(!selectedNode && exitAddConnection){
                std::cout << "No se encontro un edificio con el indice " << index << ", intenta de nuevo: ";
                std::cin >> index;
                //if -> user tries to cancel
                if(!index) exitAddConnection = true;
                selectedNode = GetNodeFromIndex(index);
            }

            //if to make sure user didn't cancel
            if(!exitAddConnection){
                std::cout << "Ingresa la distancia: ";
                std::cin >> tempDistance;
                tempConnection = Connection(selectedNode, tempDistance);
                newNode->InsertConnection(tempConnection);
            }
        }
    }

    newNode->SetName(tempName);
    InsertNode(newNode);
    std::cout << "Edificio registrado" << std::endl;
    util::EnterToContinue();
}

void Graph::InsertNode(Node* newNode){
    //insert node at the end
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
        i++;
    }
    return temp;
}

//TODO
ConnectionList Graph::FindShortestPath(Node* originNode, Node* destinationNode) {
    //destination node or origin node is not connected in any way to the other nodes
    if(destinationNode->GetConnectionList().GetAmountConnections() == 0 || originNode->GetConnectionList().GetAmountConnections() == 0) return ConnectionList();

    return ConnectionList();
}


void Graph::PrintGraph(){
    Node* temp = m_Header;

    if(!temp){
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    while(temp){
        temp->PrintFull();
        std::cout << "|" << std::endl;
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
        i++;
    }
}

void Graph::PrintErrorMessages(){
    std::cout << m_ErrorMessages;
    m_ErrorMessages = "";
}

Graph::~Graph(){
    //delete graph, although this is only used for when the program is closed, so either way the operating system deletes everything associated
    Node* temp = m_Header;
    m_Header = m_Header->GetNext();
    while(temp){
        delete temp;
        temp = m_Header;
        m_Header = m_Header->GetNext();
    }
}

int Graph::NodeCount() {
    if(!m_Header){
        return 0;
    }

    Node* temp = m_Header;
    int i=0;
    while(temp){
        i++;
        temp = temp->GetNext();
    }

    return i;
}

void Graph::ReadFromDisk(){
    std::ifstream buildings(BUILDINGS_FILE, std::ios::in);
    std::ifstream connections(CONNECTIONS_FILE, std::ios::in);

    if(!buildings.is_open() || !connections.is_open()){
        m_ErrorMessages += "El archivo con la informacion de los edificios no se pudo abrir\n";
        return;
    }

    std::string line;
    Node* newNode;
    while(std::getline(buildings, line)){
        newNode = new Node();
        newNode->SetName(line);
        InsertNode(newNode);
    }

    Connection connection;
    Node* originNode;
    Node* destinationNode;
    double distance;
    std::string distanceStr;
    std::string originName;
    std::string destinationName;

    while(std::getline(connections, line)){
        //string stream so that we can use getline on the line
        std::istringstream liness(line);
        connection = Connection();
        
        //getting the name of the origin node
        std::getline(liness, originName, '|');
        originNode = GetNodeFromString(originName);

        //getting the name of the destination node
        std::getline(liness, destinationName, '|');
        destinationNode = GetNodeFromString(destinationName);

        //getting distance then converting to double
        std::getline(liness, distanceStr);
        distance = std::stof(distanceStr);

        //one or both of the buildings was not found
        if(!originNode || !destinationNode){
            m_ErrorMessages += "No se pudo hacer la conexion entre " + originName + " y " + destinationName + " porque no se encontro: ";
            if(!originNode && !destinationNode){
                m_ErrorMessages += "ambos edificios\n";
            } else if (!originNode){
                m_ErrorMessages += "el edificio " + originName + "\n";
            } else if (!destinationNode){
                m_ErrorMessages += "el edificio " + destinationName + "\n";
            }
        } else {
            connection.SetNode(destinationNode);
            connection.SetDistance(distance);
            originNode->InsertConnection(connection);
        }
    }
}

void Graph::WriteToDisk(){

}
#include "node.h"

Node::Node() {
    m_Next = nullptr;
    m_Prev = nullptr;
    m_ConnectionList = ConnectionList();
}

Node::~Node() {
}

Node::Node(const std::string& name) : m_Name(name) {}

void Node::Create(Graph *graph){
    Node* searchNode = new Node(); //Node used for making sure the name is unique
    std::string tempName;

    std::cout << "Ingresa el nombre del edificio: ";
    std::getline(std::cin, tempName);

    //Make sure the name is unique
    searchNode = graph->GetNodeFromString(tempName);
    while(searchNode){
        std::cout << "Un edificio ya existe con ese nombre (" << tempName << "), ingrese un nombre diferente: ";
        std::getline(std::cin, tempName);
        searchNode = graph->GetNodeFromString(tempName);
    }

    SetName(tempName);
    graph->InsertNode(this);
    std::cout << "Edificio registrado" << std::endl;
    util::EnterToContinue();
}

void Node::AddConnection(Graph* graph){
    Connection tempConnection;
    Node* selectedNode;
    bool exit = graph->NodeCount() == 0; //If there aren't nodes, then the node is saved without connections
    int index;
    double tempDistance;

    while(!exit){
        system(CLEAR);
        std::cout << "AGREGAR CONEXIONES" << std::endl;
        graph->PrintListIndex();
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingresa el indice del edificio que quiere agregar como conexion: ";
        std::cin >> index;
        //there is no need to decrement index by 1, because in Graph::GetNodeFromIndex it uses 1 as the starting point
        if(!index){
            exit = true;
        } else {
            selectedNode = graph->GetNodeFromIndex(index);
            while(!selectedNode && exit){
                std::cout << "No se encontro un edificio con el indice " << index << ", intenta de nuevo: ";
                std::cin >> index;
                //if -> user tries to cancel
                if(!index) exit = true;
                selectedNode = graph->GetNodeFromIndex(index);
            }

            //if to make sure user didn't cancel
            if(!exit){
                std::cout << "Ingresa la distancia: ";
                std::cin >> tempDistance;
                tempConnection = Connection(selectedNode, tempDistance);
                InsertConnection(tempConnection);
            }
        }
    }
}

void Node::SetName(const std::string &name) {
    m_Name = name;
}

void Node::InsertConnection(Connection connection) {
    m_ConnectionList.AddConnection(connection);
}

void Node::DeleteConnectionIndex(int index) {
    m_ConnectionList.DeleteConnectionIndex(index);
}

void Node::DeleteConnectionNode(Node* node) {
    m_ConnectionList.DeleteConnectionNode(node);
}

void Node::SetNext(Node *next) {
    m_Next = next;
}

void Node::SetPrev(Node *prev){
    m_Prev = prev;
}

const std::string Node::GetName() {
    return m_Name;
}

ConnectionList& Node::GetConnectionList() {
    if(m_ConnectionList.GetAmountConnections() > 0) m_ConnectionList.QuickSort(0, m_ConnectionList.GetAmountConnections()-1);
    return m_ConnectionList;
}

Node* Node::GetNext() {
    return m_Next;
}

Node* Node::GetPrev() {
    return m_Prev;
}

void Node::PrintFull() {
    std::cout << m_Name;
    m_ConnectionList.Print();
    std::cout << std::endl;
}

void Node::PrintConnectionsIndexed(){
    m_ConnectionList.PrintIndexed();
}

void Node::PrintSimple(){
    std::cout << m_Name << std::endl;
}

void Node::PrintSimpleIndex(int index){
    std::cout << index << ". " << m_Name << std::endl;
}

void Node::WriteToDisk(std::ofstream &file) {
    if (!file.is_open()) return;

    file << m_Name << std::endl;
}

Node& Node::operator=(const Node& other) {
    return *this;
}

bool Node::operator==(const Node& other) const {
    return false;
}

bool Node::operator!=(const Node& other) const {
    return false;
}

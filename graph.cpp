#include "graph.h"

Graph::Graph(){
}

void Graph::AddNode(Node* newNode){
}

void Graph::EditNode(Node* node){

}

void Graph::RemoveNode(const std::string& nodeName){
}

Node* Graph::GetNodeFromString(const std::string& nodeName) {
    Node* temp = m_Header;
    while(temp != nullptr){
        if(temp->GetName() == nodeName) return temp;
        temp = temp->GetNext();
    }

    return nullptr;
}

Connection * Graph::MakeShortestPath(Node* originNode, Node* destinationNode) {

}



void Graph::PrintGraph(){
}

void Graph::PrintList(){
    Node* temp = m_Header;

    while(temp != nullptr){
        std::cout << temp->GetName() << std::endl;
        temp = temp->GetNext();
    }
}

Graph::~Graph(){
}






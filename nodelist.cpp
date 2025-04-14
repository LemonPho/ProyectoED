#include "nodelist.h"

NodeList::NodeList(){
}

void NodeList::AddNode(Node* newNode){
}

void NodeList::EditNode(Node* node){

}

void NodeList::RemoveNode(const std::string& nodeName){
}

Node* NodeList::GetNodeFromString(const std::string& nodeName) {
    Node* temp = m_Header;
    while(temp != nullptr){
        if(temp->GetName() == nodeName) return temp;
        temp = temp->GetNext();
    }

    return nullptr;
}

Connection * NodeList::MakeShortestPath(Node* originNode, Node* destinationNode) {

}



void NodeList::PrintGraph(){
}

void NodeList::PrintList(){
    Node* temp = m_Header;

    while(temp != nullptr){
        std::cout << temp->GetName() << std::endl;
        temp = temp->GetNext();
    }
}

NodeList::~NodeList(){
}






#include "node.h"

Node::Node() {

}

Node::Node(const std::string& name) {

}

Node::~Node() {

}

const std::string & Node::GetName() {
    return m_Name;
}

int Node::GetAmountConnections() {
    return m_AmountConnections;
}

Connection* Node::GetConnections() {
    return m_Connections;
}

Node* Node::GetNext() {
    return m_Next;
}

Node* Node::GetPrev() {
    return m_Prev;
}

void Node::PrintConnections(){
    for(int i=0; i < MAX_CONNECTIONS; i++){
        std::cout << m_Connections[i].GetNode()->GetName() << " - " << m_Connections[i].GetDistance() << std::endl;
    }
}

Node& Node::operator=(const Node& other) {

}

bool Node::operator==(const Node& other) const {

}

bool Node::operator!=(const Node& other) const {

}

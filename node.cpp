#include "node.h"

Node::Node() {

}

Node::Node(const std::string& name) {

}

Node::~Node() {

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

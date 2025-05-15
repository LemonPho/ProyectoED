#include "connection.h"
#include "node.h"
#include "util.h"

Connection::Connection() {
    m_Node = nullptr;
    m_Distance = 0.0;
}

Connection::Connection(Node* node, double distance) {
    if(distance < 0){
        std::cout << "No se puede ingresar una distancia menor a 0, operacion cancelada" << std::endl;
        util::EnterToContinue();
        return;
    }

    m_Node = node;
    m_Distance = distance;
}

void Connection::SetNode(Node* node) {
    m_Node = node;
}

void Connection::SetDistance(double distance){
    if(distance < 0){
        std::cout << "No se puede ingresar una distancia menor a 0, operacion cancelada" << std::endl;
        util::EnterToContinue();
        return;
    }

    m_Distance = distance;
}

double Connection::GetDistance() {
    return m_Distance;
}

bool Connection::operator<(Connection &connection){
    return this->GetDistance() < connection.GetDistance();
}

Node* Connection::GetNode() {
    return m_Node;
}

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

bool Connection::operator==(Connection &connection){
    return this->GetNode() == connection.GetNode();
}

Node* Connection::GetNode() {
    return m_Node;
}

void Connection::WriteToDisk(std::ofstream& file, const std::string &originString) {
    if (!file.is_open()) return;

    std::cout << "\t" << originString << "->" << m_Node->GetName() << std::endl;
    file << originString << "|" << m_Node->GetName() << "|" << m_Distance << std::endl;
}

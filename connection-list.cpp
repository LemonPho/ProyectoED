#include "connection-list.h"
#include "node.h"

ConnectionList::ConnectionList() {
    for(int i=0; i < MAX_CONNECTIONS; i++){
        m_Connections[i] = Connection();
    }
}

void ConnectionList::AddConnection(Connection connection){
    if(m_AmountConnections == MAX_CONNECTIONS){
        std::cout << "No se pueden agregar mas conexiones" << std::endl;
        util::EnterToContinue();
        return;
    }

    m_Connections[m_AmountConnections] = connection;
    m_AmountConnections++;
}

void ConnectionList::DeleteConnection(int index) {

}

void ConnectionList::Print() {
    if(m_AmountConnections == 0) return;
    std::cout << " -> ";
    for(int i=0; i < m_AmountConnections; i++){
        std::cout << m_Connections[i].GetNode()->GetName() << "(" << m_Connections[i].GetDistance() << "m)";
        if(i != m_AmountConnections-1) std::cout << " -> ";
    }
}
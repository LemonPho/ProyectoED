#include "connection-list.h"
#include "node.h"

ConnectionList::ConnectionList() {
    for(int i=0; i < MAX_CONNECTIONS; i++){
        m_Connections[i] = Connection();
    }
}

int ConnectionList::GetAmountConnections() {
    return m_AmountConnections;
}

Connection ConnectionList::GetConnection(int index) {
    //out of bounds
    if(index < 0 || index >= m_AmountConnections) return Connection();

    return m_Connections[index];
}

ConnectionList ConnectionList::QuickSort(int start, int end) {
    if(start < end){
        int partition = Partition(start, end);

        QuickSort(start, partition-1);
        QuickSort(partition+1, end);
    }
}

int ConnectionList::Partition(int start, int end){
    Connection pivot = m_Connections[end];
    Connection temp;
    int i = start - 1;

    for(int j=start; j <= end; j++){
        if(m_Connections[j] < pivot){
            temp = m_Connections[j];
            m_Connections[j] = m_Connections[i];
            m_Connections[i] = temp;
        }
    }

    temp = m_Connections[i+1];
    m_Connections[i+1] = m_Connections[end];
    m_Connections[end] = temp;

    return i+1;
}

void ConnectionList::AddConnection(Connection connection) {
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
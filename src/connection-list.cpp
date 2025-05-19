#include "connection-list.h"
#include "node.h"

ConnectionList::ConnectionList() {
    for(int i=0; i < MAX_CONNECTIONS; i++){
        m_Connections[i] = Connection();
    }
}

bool ConnectionList::IsEmpty() {
    return m_AmountConnections == 0;
}

int ConnectionList::GetAmountConnections() {
    return m_AmountConnections;
}

Connection ConnectionList::GetConnection(int index) {
    //out of bounds
    if(index < 0 || index >= m_AmountConnections) return Connection();

    return m_Connections[index];
}

void ConnectionList::QuickSort(int start, int end) {
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
            i++;
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

void ConnectionList::DeleteConnectionIndex(int index) {
    //return if index is out of range
    if(index < 0 || index > m_AmountConnections-1) return;

    //delete the connection
    m_Connections[index] = Connection();
    RemoveEmptySpaces();
}

void ConnectionList::DeleteConnectionNode(Node* node) {
    bool connectionDeleted = false;
    for (size_t i = 0; i < m_AmountConnections; i++) {
        if (m_Connections[i].GetNode() == node) {
            m_Connections[i] = Connection();
            connectionDeleted = true;
        }
    }

    if (connectionDeleted) RemoveEmptySpaces();
}

//function used after deleting elements from the array, this shifts the elements ahead to fill the empty spaces
//it is necessary to run after using any of the delete functions, because they dont decrement the amountConnections variable
void ConnectionList::RemoveEmptySpaces(){
    //if we dont do this the for never runs so the decrement never happens
    if (m_AmountConnections == 1) {
        m_AmountConnections--;
        return;
    }

    Connection emptyConnection = Connection();
    for(int i=0; i < m_AmountConnections-1; i++){
        //connection is either a deleted node or just empty
        if(m_Connections[i] == emptyConnection){
            //shift all the connections ahead one spot behind
            for(size_t j=i+1; j < m_AmountConnections; j++){
                m_Connections[j-1] = m_Connections[j];
                m_Connections[j] = Connection();
            }
            m_AmountConnections--;
            i--;
        }
    }
}

Connection ConnectionList::PopSmallest() {
    //no connections
    if (m_AmountConnections == 0) return Connection();

    //use first connection as the default
    double minDistance = m_Connections[0].GetDistance();
    size_t minIndex = 0;
    
    //find connection with smallest distance
    for (size_t i = 1; i < m_AmountConnections; i++) {
        if (m_Connections[i].GetDistance() < minDistance && !m_Connections[i].IsEmpty()) {
            minDistance = m_Connections[i].GetDistance();
            minIndex = i;
        }
    }

    Connection result = m_Connections[minIndex]; //save copy of the connection to return
    m_Connections[minIndex] = Connection(); //"erase" connection
    RemoveEmptySpaces(); //removes fills the empty space by shifting array

    return result;
}

void ConnectionList::UpdateDistance(Node* node, double newDistance) {
    Connection newConnection;
    bool found = false;

    for (size_t i = 0; i < m_AmountConnections; i++) {
        if (m_Connections[i].GetNode() == node) {
            m_Connections[i].SetDistance(newDistance);
            found = true;
            break;
        }
    }

    if (!found) {
        newConnection.SetNode(node);
        newConnection.SetDistance(newDistance);
        AddConnection(newConnection);
    }
}

//prints the nearby buildings (limits to 5), and they are ordered by distance
void ConnectionList::PrintNearby(){
    if(m_AmountConnections == 0) return;

    int limit = (m_AmountConnections > 5) ? 5 : m_AmountConnections;

    for(int i=0; i < limit; i++){
        std::cout << m_Connections[i].GetNode()->GetName() << "(" << m_Connections[i].GetDistance() << "m)" << std::endl;
    }
    std::cout << std::endl;
}

//prints all the connections, also ordered
void ConnectionList::Print() {
    if(m_AmountConnections == 0) std::cout << " (sin conexiones)";
    for(int i=0; i < m_AmountConnections; i++){
        std::cout << "-> " << m_Connections[i].GetNode()->GetName() << "(" << m_Connections[i].GetDistance() << "m)";
    }
}

void ConnectionList::PrintIndexed(){
    if(m_AmountConnections == 0) std::cout << " (sin conexiones)";
    for(int i=0; i < m_AmountConnections; i++){
        std::cout << i+1 << ". " << m_Connections[i].GetNode()->GetName() << std::endl;
    }
}

void ConnectionList::PrintPath() {
    if (IsEmpty()) {
        std::cout << "No se encontro un camino";
        return;
    }

    double totalDistance = 0;
    std::string timeWalked;

    for (int i = m_AmountConnections - 1; i >= 0; i--) {
        std::cout << m_Connections[i].GetNode()->GetName() << ": " << m_Connections[i].GetDistance() << "m" << std::endl;
        totalDistance += m_Connections[i].GetDistance();
    }

    timeWalked = util::MetersToWalkingTime(totalDistance);
    std::cout << "Distancia total: " << totalDistance << "m, tiempo de caminata aprox (mm:ss): " << timeWalked << std::endl;
}

void ConnectionList::WriteToDisk(std::ofstream &file, const std::string& originName) {
    if (!file.is_open()) return;

    std::cout << originName << std::endl;
    for (size_t i = 0; i < m_AmountConnections; i++) {
        m_Connections[i].WriteToDisk(file, originName);
    }
}

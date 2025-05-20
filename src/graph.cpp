#include "graph.h"
#include "node.h"
#include "connection-list.h"
#include "core.h"

Graph::Graph(){
    m_Header = nullptr;
}

void Graph::InsertNode(Node* newNode){
    //insert node at the end
    Node* temp = m_Header;
    if(!temp){
        m_Header = newNode;        
    } else {
        while(temp->GetNext()){
            temp = temp->GetNext();
        }
    
        temp->SetNext(newNode);
        newNode->SetPrev(temp);
    }
}

void Graph::DeleteNode(int index){
    Node* deleteNode = GetNodeFromIndex(index);

    if (!deleteNode) {
        m_ErrorMessages += "No se encontró ningún nodo con ese índice.\n";
        return;
    }

    // Reasignar punteros
    if (deleteNode == m_Header) {
        m_Header = m_Header->GetNext();
        if (m_Header) {
            m_Header->SetPrev(nullptr);
        }
    } else {
        if (deleteNode->GetPrev()) {
            deleteNode->GetPrev()->SetNext(deleteNode->GetNext());
        }
        if (deleteNode->GetNext()) {
            deleteNode->GetNext()->SetPrev(deleteNode->GetPrev());
        }
    }

    // Eliminar conexiones desde otros nodos hacia este
    Node* temp = m_Header;
    while (temp) {
        temp->DeleteConnectionNode(deleteNode);
        temp = temp->GetNext();
    }

    delete deleteNode;
}


Node* Graph::GetNodeFromString(const std::string& nodeName) {
    Node* temp = m_Header;
    while(temp){
        if(temp->GetName() == nodeName) return temp;
        temp = temp->GetNext();
    }

    return nullptr;
}

Node *Graph::GetNodeFromIndex(const int index) {
    Node* temp = m_Header;
    int i = 1;
    while(temp && i != index){
        temp = temp->GetNext();
        i++;
    }
    return temp;
}

int Graph::GetIndexFromNode(Node* node) {
    Node* temp = m_Header;
    int i = 1;
    while (temp != node) {
        temp = temp->GetNext();
        i++;
    }

    //node not found
    if (temp == nullptr) {
        return -1;
    } else {
        return i;
    }
}

//Dijkstra method
ConnectionList Graph::FindShortestPath(Node* originNode, Node* destinationNode) {
    if (!originNode || !destinationNode) return ConnectionList();

    int nodeCount = NodeCount();
    double* distances = new double[nodeCount];
    Node** previous = new Node*[nodeCount];

    for (int i = 0; i < nodeCount; ++i) {
        distances[i] = std::numeric_limits<double>::infinity();
        previous[i] = nullptr;
    }

    int originIndex = GetIndexFromNode(originNode);
    if (originIndex == -1) return ConnectionList();

    distances[originIndex] = 0.0;

    ConnectionList queue;
    queue.AddConnection(Connection(originNode, 0.0));

    while (!queue.IsEmpty()) {
        Connection current = queue.PopSmallest();
        Node* currentNode = current.GetNode();
        int currentIndex = GetIndexFromNode(currentNode);

        if (currentNode == destinationNode) break;

        ConnectionList neighbors = currentNode->GetConnectionList();
        for (int i = 0; i < neighbors.GetAmountConnections(); ++i) {
            Connection edge = neighbors.GetConnection(i);
            Node* neighbor = edge.GetNode();
            int neighborIndex = GetIndexFromNode(neighbor);
            if (neighborIndex == -1) continue;

            double alt = distances[currentIndex] + edge.GetDistance();
            if (alt < distances[neighborIndex]) {
                distances[neighborIndex] = alt;
                previous[neighborIndex] = currentNode;
                queue.UpdateDistance(neighbor, alt);
            }
        }
    }

    ConnectionList path;
    int destIndex = GetIndexFromNode(destinationNode);
    if (distances[destIndex] != std::numeric_limits<double>::infinity()) {
        Node* current = destinationNode;
        while (current) {
            int idx = GetIndexFromNode(current);
            if (idx == -1) break;
            path.AddConnection(Connection(current, distances[idx]));
            current = previous[idx];
        }

        path.Reverse();  //
    }

    delete[] distances;
    delete[] previous;
    return path;
}



void Graph::PrintGraph(){
    Node* temp = m_Header;

    if(!temp){
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    while(temp){
        temp->PrintFull();
        std::cout << "|" << std::endl;
        temp = temp->GetNext();
    }
}

void Graph::PrintList(){
    Node* temp = m_Header;

    if(!temp){
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    while(temp){
        temp->PrintSimple();
        temp = temp->GetNext();
    }
}

void Graph::PrintListIndex() {
    Node* temp = m_Header;

    if(!temp) {
        std::cout << "No hay edificios registrados" << std::endl;
        return;
    }

    int i = 1;
    while(temp){
        temp->PrintSimpleIndex(i);
        temp = temp->GetNext();
        i++;
    }
}

void Graph::PrintErrorMessages(){
    std::cout << m_ErrorMessages;
    m_ErrorMessages = "";
}

Graph::~Graph(){
    //delete graph, although this is only used for when the program is closed, so either way the operating system deletes everything associated
    Node* temp = m_Header;
    m_Header = m_Header->GetNext();
    while(m_Header){
        delete temp;
        temp = m_Header;
        m_Header = m_Header->GetNext();
    }

    delete temp;
}

int Graph::NodeCount() {
    if(!m_Header){
        return 0;
    }

    Node* temp = m_Header;
    int i=0;
    while(temp){
        i++;
        temp = temp->GetNext();
    }

    return i;
}

void Graph::ReadFromDisk(){
    std::ifstream buildings(BUILDINGS_FILE, std::ios::in);
    std::ifstream connections(CONNECTIONS_FILE, std::ios::in);

    if(!buildings.is_open() || !connections.is_open()){
        m_ErrorMessages += "El archivo con la informacion de los edificios no se pudo abrir\n";
        return;
    }

    //read from buildings.txt
    std::string line;
    Node* newNode;
    while(std::getline(buildings, line)){
        newNode = new Node();
        newNode->SetName(line);
        InsertNode(newNode);
    }
    buildings.close();
    
    std::ifstream regionsFile(BUILDINGS_REGION_FILE, std::ios::in);
    if (regionsFile.is_open()) {
        std::string regionLine;
        while (std::getline(regionsFile, regionLine)) {
            std::istringstream linestream(regionLine);
            std::string name;
            std::string regionStr;

            std::getline(linestream, name, ',');
            std::getline(linestream, regionStr);

            Node* node = GetNodeFromString(name);
            if (node) {
                int region = std::stoi(regionStr);
                node->SetRegion(region);
            } else {
                m_ErrorMessages += "No se encontró el edificio \"" + name + "\" al intentar asignar su región\n";
            }
        }
        regionsFile.close();
    } else {
        m_ErrorMessages += "No se pudo abrir el archivo de regiones (buildingsRegion.csv)\n";
    }


    //read from connections.txt
    Connection connection;
    Node* originNode;
    Node* destinationNode;
    double distance;
    std::string distanceStr;
    std::string originName;
    std::string destinationName;

    //should look into moving this logic to connection or somethign but not sure if possible
    while(std::getline(connections, line)){
        //string stream so that we can use getline on the line
        std::istringstream liness(line);
        connection = Connection();
        
        //getting the name of the origin node
        std::getline(liness, originName, '|');
        originNode = GetNodeFromString(originName);

        //getting the name of the destination node
        std::getline(liness, destinationName, '|');
        destinationNode = GetNodeFromString(destinationName);

        //getting distance then converting to double
        std::getline(liness, distanceStr);
        distance = std::stof(distanceStr);

        //one or both of the buildings was not found
        if(!originNode || !destinationNode){
            m_ErrorMessages += "No se pudo hacer la conexion entre " + originName + " y " + destinationName + " porque no se encontro: ";
            if(!originNode && !destinationNode){
                m_ErrorMessages += "ambos edificios\n";
            } else if (!originNode){
                m_ErrorMessages += "el edificio " + originName + "\n";
            } else if (!destinationNode){
                m_ErrorMessages += "el edificio " + destinationName + "\n";
            }
        } else {
            connection.SetNode(destinationNode);
            connection.SetDistance(distance);
            originNode->InsertConnection(connection);
        }
    }

    connections.close();
}

void Graph::WriteToDisk(){
    std::ofstream buildings(BUILDINGS_FILE, std::ios::in);
    std::ofstream connections(CONNECTIONS_FILE, std::ios::in);

    if (!buildings.is_open() || !connections.is_open()) {
        m_ErrorMessages += "El archivo con la informacion de los edificios no se pudo abrir\n";
        return;
    }


    //write to buildings.txt
    std::string line;
    Node* temp = m_Header;
    while (temp) {
        temp->WriteToDisk(buildings);
        temp = temp->GetNext();
    }
    buildings.close();
    
    //write to connections.txt
    temp = m_Header;
    while (temp) {
        temp->GetConnectionList().WriteToDisk(connections, temp->GetName());
        temp = temp->GetNext();
    }

    util::EnterToContinue();
    connections.close();
}

void Graph::displayMapForRegion(int regionId) {
    std::string filename;
    switch(regionId) {
        case 1: filename = "mapNorthEast(1).txt"; break;
        case 2: filename = "mapNorthWest(2).txt"; break;
        case 3: filename = "mapSouthEast(3).txt"; break;
        case 4: filename = "mapSouthWest(4).txt"; break;
        default:
            std::cout << "Región desconocida.\n";
            return;
    }

    std::ifstream file("data/" + filename);
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo del mapa: data/" << filename << std::endl;
        return;
    }

    std::cout << "\n=== Mapa de la región " << regionId << " ===\n\n";

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

#include <limits> // para std::numeric_limits

void Graph::showStepByStepPath(const ConnectionList& path) {
    if (path.GetAmountConnections() == 0) {
        std::cout << "No se encontró un camino.\n";
        return;
    }

    int previousRegion = -1;

    for (int i = 0; i < path.GetAmountConnections(); ++i) {
        Node* current = path.GetConnection(i).GetNode();
        int currentRegion = current->GetRegion();

        if (currentRegion != previousRegion) {
            std::cout << "\nCambio de región detectado. Mostrando nuevo mapa...\n\n";
            displayMapForRegion(currentRegion);
            previousRegion = currentRegion;
        }

        std::cout << "Paso " << i + 1 << ": Ahora ve al edificio: ";
        current->PrintSimple();
        util::EnterToContinue();
    }

    std::cout << "\n¡Has llegado a tu destino!\n";
}


void Graph::LoadBuildingsWithRegions(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Saltar header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, regionStr;

        std::getline(ss, name, ',');
        std::getline(ss, regionStr, ',');

        if (name.empty() || regionStr.empty()) continue;

        Node* node = FindNode(name);
        if (!node) {
            node = new Node(name);
            AddNode(node);
        }

        try {
            int region = std::stoi(regionStr);
            node->SetRegion(region);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Valor inválido para región en línea: " << line << std::endl;
        }
    }
}

void Graph::AddNode(Node* node) {
    if (!m_Header) {
        // Lista vacía: el nuevo nodo es la cabeza
        m_Header = node;
        node->SetNext(nullptr);
        node->SetPrev(nullptr);
    } else {
        // Insertar al final de la lista
        Node* current = m_Header;
        while (current->GetNext() != nullptr) {
            current = current->GetNext();
        }
        current->SetNext(node);
        node->SetPrev(current);
        node->SetNext(nullptr);
    }
}

Node* Graph::FindNode(const std::string& name) {
    Node* current = m_Header;
    while (current != nullptr) {
        if (current->GetName() == name) {
            return current;
        }
        current = current->GetNext();
    }
    return nullptr;
}

#pragma once

#include <iostream>
#include "connection.h"
#include "util.h"

const int MAX_CONNECTIONS = 20;

class ConnectionList{
private:
    int m_AmountConnections = 0;
    Connection m_Connections[MAX_CONNECTIONS];
public:
    ConnectionList();

    bool IsEmpty();

    //get
    int GetAmountConnections();
    Connection GetConnection(int index);

    //sorting
    void QuickSort(int start, int end);
    int Partition(int start, int end);
    
    //management
    void AddConnection(Connection connection);
    void DeleteConnectionIndex(int index);
    void DeleteConnectionNode(Node* node);
    void RemoveEmptySpaces();
    Connection PopSmallest();
    void UpdateDistance(Node* node, double newDistance);
    void Reverse();


    //print
    void PrintNearby();
    void Print();
    void PrintIndexed();
    void PrintPath();

    //disk
    void WriteToDisk(std::ofstream& file, const std::string &originName); //sending by reference to avoid stream issues
};

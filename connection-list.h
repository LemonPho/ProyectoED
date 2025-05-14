#pragma once

#include <iostream>
#include "connection.h"
#include "util.h"

const int MAX_CONNECTIONS = 10;

class ConnectionList{
private:
    int m_AmountConnections = 0;
    Connection m_Connections[MAX_CONNECTIONS];
public:
    ConnectionList();

    //get
    int GetAmountConnections();
    Connection GetConnection(int index);

    //sorting
    void QuickSort(int start, int end);
    int Partition(int start, int end);
    
    //management
    void AddConnection(Connection connection);
    void DeleteConnection(int index);

    //print
    void PrintNearby();
    void Print();
};
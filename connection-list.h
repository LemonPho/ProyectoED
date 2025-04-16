#pragma once

#include <iostream>
#include "connection.h"
#include "util.h"

const int MAX_CONNECTIONS = 5;

class ConnectionList{
private:
    int m_AmountConnections = 0;
    Connection m_Connections[MAX_CONNECTIONS];
public:
    ConnectionList();

    int GetAmountConnections();
    Connection GetConnection(int index);

    ConnectionList QuickSort(int start, int end);
    int Partition(int start, int end);
    
    void AddConnection(Connection connection);
    void DeleteConnection(int index);
    void Print();
};
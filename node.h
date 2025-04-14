#pragma once

#include <iostream>
#include "connection.h"

const int MAX_CONNECTIONS = 5;

class Node {
private:
    std::string m_Name; // each "building" has to have a unique name

    //TODO: this should be made an object, where it has the amount connections there, so that when the list
    //is requested from GetConnections(), it would include the amount of connections
    int m_AmountConnections = 0;
    Connection m_Connections[MAX_CONNECTIONS]; //arbitrary for now, array for easier sorting

    Node* m_Next;
    Node* m_Prev;
public:
    Node();
    Node(const std::string& name);
    ~Node();

    void SetName(const std::string& name);
    void InsertConnection(Node* newConnection);
    void DeleteConnection(const std::string& name);
    void SetNext(Node* next);
    void SetPrev(Node* prev);

    const std::string& GetName();
    int GetAmountConnections();
    Connection* GetConnections();
    Node* GetNext();
    Node* GetPrev();

    void Print();
    void PrintConnections();

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

};

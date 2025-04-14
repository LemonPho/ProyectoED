#pragma once

#include <iostream>
#include "connection.h"

class Node {
private:
    std::string m_Name; // each "building" has to have a unique name
    Connection* m_Connection;
    Node* m_Next;
    Node* m_Prev;
public:
    Node();
    Node(const std::string& name, Connection* connection, Node* next);
    ~Node();

    void SetName(const std::string& name);
    void InsertConnection(Node* newConnection);
    void DeleteConnection(const std::string& name);
    void SetNext(Node* next);
    void SetPrev(Node* prev);

    const std::string& GetName();
    Connection* GetConnection();
    Node* GetNext();
    Node* GetPrev();

    void Print();

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

};

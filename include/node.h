#pragma once

#include <iostream>

#include "connection-list.h"

class Node {
private:
    std::string m_Name; // each "building" has to have a unique name

    ConnectionList m_ConnectionList;
    
    Node* m_Next;
    Node* m_Prev;
public:
    Node();
    ~Node();

    void SetName(const std::string& name);
    void InsertConnection(Connection connection);
    void DeleteConnection(int index);
    void SetNext(Node* next);
    void SetPrev(Node* prev);

    const std::string GetName();
    ConnectionList& GetConnectionList();
    Node* GetNext();
    Node* GetPrev();

    void PrintFull();
    void PrintSimple();
    void PrintSimpleIndex(int index);

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

};

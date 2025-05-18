#pragma once

#include <iostream>

#include "connection-list.h"
#include "graph.h"
#include "core.h"

class Node {
private:
    std::string m_Name; // each "building" has to have a unique name

    ConnectionList m_ConnectionList;
    
    Node* m_Next;
    Node* m_Prev;
public:
    Node();
    ~Node();

    void Create(Graph* graph);

    void AddConnection(Graph* graph);

    void SetName(const std::string& name);
    void InsertConnection(Connection connection);
    void DeleteConnectionIndex(int index);
    void DeleteConnectionNode(Node* node);
    void SetNext(Node* next);
    void SetPrev(Node* prev);

    const std::string GetName();
    ConnectionList& GetConnectionList();
    Node* GetNext();
    Node* GetPrev();

    void PrintFull();
    void PrintConnectionsIndexed();
    void PrintSimple();
    void PrintSimpleIndex(int index);

    void WriteToDisk(std::ofstream &file);

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

};

#pragma once

#include <iostream>
#include "nodelist.h"

class Node {
private:
    std::string m_Name; // each "building" has to have a unique name
    NodeList* m_Connections;
    Node* next;
public:
    Node();
    Node(const std::string& name, NodeList* connections, Node* next);
    ~Node();

    void SetName(const std::string& name);
    void InsertConnection(Node* newConnection);
    void DeleteConnection(const std::string& name);
    void SetNext(Node* next);

    const std::string& GetName();
    NodeList* GetConnections();
    Node* GetNext();

    Node& operator=(const Node& other);
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

};

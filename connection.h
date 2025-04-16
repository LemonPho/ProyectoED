#pragma once

#include <iostream>

class Node;

class Connection {
private:
    Node* m_Node;
    float m_Distance;
public:
    Connection();
    Connection(Node* node, float distance);

    void SetNode(Node* node);
    void SetDistance(float distance);

    Node* GetNode();
    float GetDistance();

    bool operator<(Connection& connection);
};


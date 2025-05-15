#pragma once

#include <iostream>

class Node;

class Connection {
private:
    Node* m_Node;
    double m_Distance;
public:
    Connection();
    Connection(Node* node, double distance);

    void SetNode(Node* node);
    void SetDistance(double distance);

    Node* GetNode();
    double GetDistance();

    bool operator<(Connection& connection);
};


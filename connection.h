#pragma once

#include <iostream>

//can't include node.h, because node.h includes connection.h, so it would infinitely include itself
//in connection.cpp node.h is included
class Node;

class Connection {
private:
    Node* m_Node;
    float m_Distance;
public:
    Connection();
    Connection(Node* node, float distance);
    ~Connection();

    void SetNode(Node* node);
    void SetDistance(float distance);

    Node* GetNode();
    float GetDistance();


};


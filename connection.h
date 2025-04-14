#pragma once

//can't include node.h, because node.h includes connection.h, so it would infinitely include itself
//in connection.cpp node.h is included
class Node;

class Connection {
private:
    Node* m_Node;
    float m_Distance;

    Connection* m_Next;
public:
    Connection();
    Connection(Node* node, float distance);

    void SetNode(Node* node);
    void SetDistance(float distance);
    void SetConnection(Connection* connection);

    Connection* GetConnection();
    Node* GetNode();
    float GetDistance();

    ~Connection();

};


#pragma once

class Node; //If we include node.h, node.h will include nodelist.h which will then include node.h, infinite.

class NodeList {
private:
    Node* m_Header;
public:
    NodeList();

    void Add(Node* newNode);
    void Remove(const std::string& nodeName);
    void Print();

    ~NodeList();
};

#include "connection-list.h"
#include "node.h"

Node::Node() {
    m_Next = nullptr;
    m_Prev = nullptr;
    m_ConnectionList = ConnectionList();
}

Node::~Node() {
}

void Node::SetName(const std::string &name) {
    m_Name = name;
}

void Node::InsertConnection(Connection connection) {
    m_ConnectionList.AddConnection(connection);
}

void Node::DeleteConnection(int index) {
    m_ConnectionList.DeleteConnection(index);
}

void Node::SetNext(Node *next) {
    m_Next = next;
}

void Node::SetPrev(Node *prev){
    m_Prev = prev;
}

const std::string & Node::GetName() {
    return m_Name;
}

ConnectionList& Node::GetConnectionList() {
    m_ConnectionList.QuickSort(0, m_ConnectionList.GetAmountConnections()-1);
    return m_ConnectionList;
}

Node* Node::GetNext() {
    return m_Next;
}

Node* Node::GetPrev() {
    return m_Prev;
}

void Node::PrintFull() {
    std::cout << m_Name;
    m_ConnectionList.Print();
    std::cout << std::endl;
}

void Node::PrintSimple(){
    std::cout << m_Name << std::endl;
}

void Node::PrintSimpleIndex(int index){
    std::cout << index << ". " << m_Name << std::endl;
}

Node& Node::operator=(const Node& other) {

}

bool Node::operator==(const Node& other) const {

}

bool Node::operator!=(const Node& other) const {

}

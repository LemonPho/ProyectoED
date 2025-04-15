#include "util.h"

void util::EnterToContinue(){
    ClearBuffer();
    std::cout << "Presione enter para continuar..." << std::endl;
    getchar();
}

void util::ClearBuffer(){
    while((getchar()) != '\n');
}
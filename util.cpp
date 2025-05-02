#include "util.h"

void util::EnterToContinue(){
    std::cout << "Presione enter para continuar..." << std::endl;
    ClearBuffer();
    getchar();
}

void util::ClearBuffer(){
    while((getchar()) != '\n');
}
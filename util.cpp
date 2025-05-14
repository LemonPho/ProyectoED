#include "util.h"

void util::EnterToContinue(){
    std::cout << "Presione enter para continuar..." << std::endl;
    ClearBuffer();
    getchar();
}

//https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
void util::ClearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
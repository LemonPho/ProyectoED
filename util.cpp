#include "util.h"

void util::EnterToContinue(){
    while ((getchar()) != '\n');
    std::cout << "Presione enter para continuar" << std::endl;
    getchar();
}
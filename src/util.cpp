#include "util.h"
/*
void util::EnterToContinue(){
    std::cout << "Presione enter para continuar..." << std::endl;
    ClearBuffer();
    getchar();
}

//https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
void util::ClearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}*/
void util::ClearBuffer() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

void util::EnterToContinue() {
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpia buffer
    std::cin.get(); // espera ENTER
}
std::string util::MetersToWalkingTime(double meters) {
    double walkingSpeed = 1.4; // meters per second
    int totalSeconds = static_cast<int>(std::ceil(meters / walkingSpeed));

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[]){
    std::cout << "Seond window works!" << std::endl;
    std::cout << "Command Line: " << GetCommandLine() << std::endl;
    std::cin.get();
    return 0;
}
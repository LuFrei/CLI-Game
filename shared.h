#pragma once

#include <string>
namespace Shared{

#define CAPACITY 50

struct Data {
    int size = 0;
    int Data[CAPACITY];
    std::string Message[CAPACITY];
    void AddData(std::string msg, int data){
        Message[size] = msg;
        Data[size] = data;
        size++;
    };
};

} // end namespace
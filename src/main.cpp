#include<iostream>
#include "Wrapper.h"
#include "Subject.h"

int main(){
    std::cout << "Hello Wrapper!\n";
    std::cout << "Hello Engine!\n";

    Subject* subject = new Subject("test.txt");

    subject->capitalizeWords();

    Wrapper wrapper(subject, &Subject::replaceWord, { {"Arg1", "First"}, {"Arg2", "SSSSSSSSSS"} });

    wrapper.call("First", "SSSSSSSSSS");

    return 0; 
}
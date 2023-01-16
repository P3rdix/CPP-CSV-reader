#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>


class Frame{
    column* a;
    column* read(std::string);
}

Frame::Frame(std::string){
    
}

class column{
    public:

    private:
        std::string name;


}

struct init{
    std::string name;
    vector<int>;
    vector<float>;
    vector<std::string>;
    struct column* next;
};

column* Frame::read(std::string FILENAME){

}

Frame::Frame(std::string FILENAME){
    a = read(FILENAME);

}

column::column(std::string n,int* series){
    auto series = series;
    name = n;

}

#endif
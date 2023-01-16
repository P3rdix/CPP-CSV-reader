#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

class WrongFileTypeException : public exception{
    public:
        const char* what() const throw(){
            return "\n";
        }
};

class Frame{
    public:
        column* read(std::string);
    private:
        column* a;
        std::String* col_names;
        int dim[2];


}

Frame::Frame(std::string FILENAME){
    if(FILENAME.substring(FILENAME.length()-4,4) != ".csv"){
        WrongFileTypeException w;
        throw w;
    }
    ifstream fin;
    fin.open(FILENAME);
    std::String names;
    getline(fin,names);
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
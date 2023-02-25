#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class column{
    int x;
};

std::vector<std::string> adv_tokenizer(std::string s, char del){
    std::stringstream l{s};
    std::string word;
    std::vector<std::string> ret;
    while (!l.eof()) {
        getline(l, word, del);
        ret.push_back(word);
    }
    return ret;
}

class WrongFileTypeException{
    public:
        WrongFileTypeException(std::string name, std::string end){
            name = name;
            end = end;
        }
        void printmsg(){
            std::cout<<std::endl<<name<<" does not end with .csv";
            std::cout<<std::endl<<"File ends with ";
            std::cout<<std::endl<<"Required File Type is comma separated value file (.csv)";
            std::cout<<std::endl;
        }
    private:
        std::string name,end;
};

class Frame{
    public:
        column* read(std::string);
        Frame(std::string,int);
    private:
        column* a;
        std::string* col_names;
        int dim[2];


};

Frame::Frame(std::string FILENAME, int awk = 0){
    if(awk == 0){
        try{
            if(FILENAME.substr(FILENAME.length()-4,4) != ".csv"){
                WrongFileTypeException w = WrongFileTypeException(FILENAME, FILENAME.substr(FILENAME.length()-4,4));
                throw w;
            }
            std::ifstream fin;
            if(fin.fail()){
                std::cout<<"File Not Found";
            }
            std::string names;
            getline(fin,names);
            std::vector<std::string> c = adv_tokenizer(names,',');
            for(int i=0;i<c.size();i++){
                std::cout<<c.at(i)<<std::endl;
            }
            dim[0] = c.size();
        }
        catch(WrongFileTypeException e){
            e.printmsg();
        }
    }
    else{
        
    }
}

#endif
#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int to_Int(std::string);

class column{
    int x;
};

std::vector<std::string> breakup(std::string s, char del){
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
        WrongFileTypeException(std::string a, std::string b){
            name = a;
            end = b;
            std::cout<<name<<"   "<<end<<std::endl; 
        }
        void printmsg(){
            std::cout<<name<<"   "<<end<<std::endl; 
            std::cerr<<std::endl<<name<<" does not end with .csv";
            std::cerr<<std::endl<<"File ends with "<<end;
            std::cerr<<std::endl<<"Required File Type is comma separated value file (.csv)";
            std::cerr<<std::endl;
        }
    private:
        std::string name,end;
};

class FileNotFoundException{
    public:
        FileNotFoundException(std::string a){
            name = a;
        }
        void printmsg(){
            std::cerr<<std::endl<<name<<" does not exist";
            return;
        }
    private:
        std::string name,end;
};



class Frame{
    public:
        column* read(std::string);
        Frame(std::string);
        Frame(std::string,int);
    private:
        column* a;
        std::string* col_names;
        int dim[2];


};

Frame::Frame(std::string FILENAME){
    try{
        if(FILENAME.substr(FILENAME.length()-4,4) != ".csv"){
            WrongFileTypeException w = WrongFileTypeException(FILENAME, FILENAME.substr(FILENAME.length()-4,4));
            throw w;
        }
        std::ifstream fin;
        fin.open(FILENAME);
        if(fin.fail()){
            FileNotFoundException f(FILENAME);
            throw f;
        }
        std::cout<<"BYRRRRRR";
        std::string names;
        getline(fin,names);
        std::vector<std::string> c = breakup(names,',');
        for(int i=0;i<c.size();i++){
            std::cout<<c.at(i)<<std::endl;
        }
        dim[0] = c.size();
    }
    catch(WrongFileTypeException e){
        e.printmsg();
    }
    catch(FileNotFoundException e){
        e.printmsg();
    }

}

int to_Int(std::string a){
    int n = 0;
    if(a.length()==0){
        return 0;
    }
    if(a.at(0) == '-'){
        for(int i=1;i<a.length();i++){
            n = n*10 - (a.at(i)-48);
        }
        return n;
    }
    for(int i=0;i<a.length();i++){
        n = n*10 + (a.at(i)-48);
    }
    return n;
}

double toFloat(std::string a){
    double n = 0;
    if(a.length()==0){
        return 0;
    }
    int i = 0;
    int l = a.length();
    while(i < l){
        if(a.at(i) == '.'){
            break;
        }
        n = (a.at(0) == '-')?(n*10 - (a.at(i)-48)):(n*10 + (a.at(i)-48));
        i++;
    }
    if(i == l){
        return n;
    }
    double m = 0;
    i++;
    int f = i;
    while(i != a.length()){
        m = m*10 + (a.at(i)-48);
        i++;
    }
    while(f < l){
        m/=10.0;
        f++;
    }
    return n+m;
}

#endif
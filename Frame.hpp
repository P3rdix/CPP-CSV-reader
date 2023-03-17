#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

struct column{
    int*i;
    float* f;
    char** s;
    std::string name;
    struct column* next;
};


struct column* create_col(struct column*, std::vector<std::string>, int, int, std::string);

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

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || *it == '-')) ++it;
    return !s.empty() && it == s.end();
}

class Frame{
    public:
        Frame(std::string);
        Frame(std::string,int);
        void print();
    protected:
        int dim[2];
        int success;
        struct column* x;
};


bool isFloat( std::string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail(); 
}

Frame::Frame(std::string FILENAME){
    try{
        x = NULL;
        if(FILENAME.substr(FILENAME.length()-4,4) != ".csv"){
            throw FILENAME+"T";
        }
        std::ifstream fin;
        fin.open(FILENAME);
        if(fin.fail()){
            throw FILENAME+"E";
        }
        std::string n;
        getline(fin,n);
        std::vector<std::string> c = breakup(n,',');
        std::vector<std::string> names = c;
        dim[0] = c.size();
        std::vector<std::string> b[dim[0]];
        int r[dim[0]]={0};
        getline(fin,n);
        while(!fin.eof()){
            std::cout<<n<<std::endl;
            c = breakup(n,',');
            for(int i=0;i<dim[0];i++){
                if(r[i] == 0 && !is_number(c.at(i)) && c.at(i)!=""){
                    if(isFloat(c.at(i))){
                        r[i]+=1;
                    }
                    else{
                        r[i]+=2;
                    }
                }
                else if(r[i] == 1 && !isFloat(c.at(i)) && c.at(i)!=""){
                    r[i]+=1;
                }
                b[i].push_back(c.at(i));
            }
            getline(fin,n);
        }
        
        dim[1] = b[0].size();
        struct column* q;
        for(int i=0;i<dim[0];i++){
            struct column* t = new struct column;
            if(x == NULL){
                x = create_col(t,b[i],r[i],dim[1], names.at(i));
                q = x;
            }
            else{
                q->next = create_col(t,b[i],r[i],dim[1], names.at(i));
                q = q->next;
            }
        }
    }
    catch(std::string e){
        if(e == FILENAME+"T"){
            std::cerr<<FILENAME<<" does not end with .csv";
            std::cerr<<std::endl<<"File ends with "<<FILENAME.substr(FILENAME.length()-4,4);
            std::cerr<<std::endl<<"Required File Type is comma separated value file (.csv)"<<std::endl;
        }
        else if(e == FILENAME+"E"){
            std::cerr<<FILENAME<<" file does not exist"<<std::endl;
        }
        success = -1;
    }
}

struct column* create_col(struct column* x, std::vector<std::string> y, int a, int dim, std::string name){
    x->name = name;
    if(a == 0){
        x->i = new int[dim];
        for(int j=0;j<dim;j++){
            *(x->i + j) = std::stoi(y.at(j));
        }  
        x->s = NULL;
        x->f = NULL;
    }
    else if(a == 1){
        x->f = new float[dim];
        for(int j=0;j<dim;j++){
            *(x->f + j) = std::stof(y.at(j));
        }
        x->i = NULL;
        x->s = NULL;
    }
    else{
        x->s = (char**)malloc(sizeof(char*)*dim);
        for(int j=0;j<dim;j++){
            *(x->s+j) = (char*)malloc(sizeof(char)*y.at(j).length());
            for(int k=0;k<y.at(j).length();k++){
                *(*(x->s+j)+k) = y.at(j).at(k);
            }
        }
        x->i = NULL;
        x->f = NULL;
    }
    x->next = NULL;
    return x;
}

#endif
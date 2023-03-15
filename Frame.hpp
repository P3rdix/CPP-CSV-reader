#ifndef CSV
#define CSV

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

int to_Int(std::string);

struct column{
    int*i;
    float* f;
    char** s;
    std::string name;
    struct column* next;
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

class Frame{
    public:
        Frame(std::string);
        Frame(std::string,int);
    private:
        ** col_names;
        int dim[2];
        int success;
        struct column* x;
};

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
        dim[0] = c.size();
        std::string a[dim[0]];
        std::vector<std::string> b[dim[0]];
        int r[dim[0]]={0};
        while(!fin.eof()){
            getline(fin,n);
            c = breakup(n,',');
            for(int i=0;i<dim[0];i++){
                if(r[i] == 0 && !is_number(c.at(i))){
                    if(isFloat(c.at(i))){
                        r[i]+=1;
                    }
                    else{
                        r[i]+=2;
                    }
                }
                else if(r[i] == 1 && !isFloat(c.at(i))){
                    r[i]+=1;
                }
                b[i].push_back(c.at(i));
            }
        }
        dim[1] = b[0].size();
        struct column* q=x;
        for(int i=0;i<dim[0];i++){
            struct column* t = new struct column;
            if(x == NULL){
                x = 
            }
        }
    }
    catch(std::string e){
        if(e == FILENAME+"T"){
            std::cerr<<std::endl<<FILENAME<<" does not end with .csv";
            std::cerr<<std::endl<<"File ends with "<<FILENAME.substr(FILENAME.length()-4,4);
            std::cerr<<std::endl<<"Required File Type is comma separated value file (.csv)"<<std::endl;
        }
        else if(e == FILENAME+"E"){
            std::cerr<<FILENAME<<" file does not exist";
        }
        success = -1;
    }
}

struct column* create_col(struct column* x, std::vector<std::string> y, int a, int dim){
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
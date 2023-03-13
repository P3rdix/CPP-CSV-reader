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

class Frame{
    public:
        Frame(std::string);
        Frame(std::string,int);
    private:
        std::string* col_names;
        int dim[2];
        int success;
};

Frame::Frame(std::string FILENAME){
    try{
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
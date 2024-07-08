#ifndef _OPCODE_H_
#define _OPCODE_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include <sstream>
#pragma warning(disable:4996);
using namespace std;


class QuadCode{
    public:
    string OP1;
    string OP2;
    string OP3;
    string OP4;

    QuadCode(string op1) {
       OP1 = op1;
    }

    QuadCode(string op1,string op2) {
       OP1 = op1;
       OP2 = op2;
    }

    QuadCode(string op1,string op2,string op3) {
       OP1 = op1;
       OP2 = op2;
       OP3 = op3;
    }

    QuadCode(string op1,string op2,string op3,string op4) {
       OP1 = op1;
       OP2 = op2;
       OP3 = op3;
       OP4 = op4;
    }

    QuadCode(const QuadCode& q){
        OP1 = q.OP1;
        OP2 = q.OP2;
        OP3 = q.OP3;
        OP4 = q.OP4;
        
    }

    void Print_QUAD_CODE(){
        if(!OP1.empty())
        cout<<OP1;
        if(!OP2.empty())
        cout<<"   "<<OP2;
        if(!OP3.empty())
        cout<<"   "<<OP3;
        if(!OP4.empty())
        cout<<"   "<<OP4;
        cout<<endl;
    }
};


class OpTokens {
public:
    std::string token1;
    std::string token2;
    std::string token3;
    std::string token4;
    std::string token5;
    std::string token6;

    OpTokens(std::string str) {
        std::vector<std::string> tokens = tokenize(str);
        if (tokens.size() >= 1) token1 = tokens[0];
        if (tokens.size() >= 2) token2 = tokens[1];
        if (tokens.size() >= 3) token3 = tokens[2];
        if (tokens.size() >= 4) token4 = tokens[3];
        if (tokens.size() >= 5) token5 = tokens[4];
        if (tokens.size() >= 6) token6 = tokens[5];
    }


    vector<string> tokenize(string str)
    {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }
        return tokens;
    }

    void Print_OpTokens(){

        if(!token1.empty()){
            cout<<token1;
        }
        if(!token2.empty()){
            cout<<" | "<<token2;
        }
        if(!token3.empty()){
            cout<<" | "<<token3;
        }
        if(!token4.empty()){
            cout<<" | "<<token4;
        }
        if(!token5.empty()){
            cout<<" | "<<token5;
        }
        if(!token6.empty()){
            cout<<" | "<<token6;
        }
       cout<<endl;
    }
};


class OpCode{
    private:
   
    public:
    vector<OpTokens> _opTokens;
    vector<string> lines;
    vector<QuadCode> _quadCode;
    void load_code_in_stream(const char filename[]);
    void convert_code_into_tokens();
    void clean_the_code();
    void Print_the_lines();
    string convertSpaces(string str);
    std::string replaceSpaces(std::string str);
    string removeBrackets(string);
    void translate_code_into_machine_code();

    void Single_Assignment_Translation(OpTokens t);
    void Selection_Translation(OpTokens t);
    void Operational_Transaltion(OpTokens t);
    void Function_Call_Transaltion(OpTokens t);
    string translateRelationalOperator(const std::string& op);




};
#endif
#ifndef _VM_H_
#define _VM_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include "Opcode.h"
#include "Opcode.cpp"
#pragma warning(disable:4996);
using namespace std;

enum class OperationCode {
    MOV = 1,
    ADD  = 2,
    SUB = 3,
    GOTO = 4,
    DIV = 5,
    MOD= 6,
    IF =7,
    COLON=8,
    LT=9,
    GT=10,
    GE=11,
    NE=12,
    EQ=13,
    LE=14,
    OUT=15,
    IN=16,
    RET=17,
    PARAM=18,
    CALL=19,
    MUL =20,

};

class Symbol_Table{
    public:
    vector<string> symbols;
    vector<int> addr;
    vector<int> initial_value;
    vector<string> context;
    vector<string> type;
    void add_Entry(string symbol, int size, int i_value, string context_, string type_){
        symbols.push_back(symbol);
        addr.push_back(size);
        initial_value.push_back(i_value);
        context.push_back(context_);
        type.push_back(type_);
    }

    void Print_Symbol_Table(){
        cout<<"----------------------------------------"<<endl;
        cout<<"IV       ADR       CNTXT       TYPE      SYM"<<endl;
        for(int i=0;i<symbols.size();i++){
            cout<<initial_value[i]<<"        "<<addr[i]<<"        "<<context[i]<<"          "<<type[i]<<"         "<<symbols[i]<<"             "<<endl;
           
        }
        cout<<"----------------------------------------"<<endl;
    }


    // void Print_Symbol_Table(vector<string> cntxt){
    //     cout<<"----------------------------------------"<<endl;
    //     cout<<"IV       ADR     CTX      SYM"<<endl;
    //     for(int i=0;i<symbols.size();i++){
    //         cout<<initial_value[i]<<"        "<<addr[i]<<"       "<<cntxt[i]<<"        "<<symbols[i]<<endl;
           
    //     }
    //     cout<<"----------------------------------------"<<endl;
    // }

    vector<string> lookup_table(string var,vector<string> cntxt ){

        for(int i=0;i<symbols.size();i++){
           if(symbols[i]==var && cntxt[i]=="var"){
                vector<string> ReturnIt;
                ReturnIt.push_back(var);
                ReturnIt.push_back(to_string(addr[i]));
                ReturnIt.push_back(to_string(initial_value[i]));
                return ReturnIt;
           }
        }
        vector<string> ReturnIt;
        return ReturnIt;
    }

     vector<string> lookup_table(string var){
        // cout<<"Var -- "<<var<<endl;
        for(int i=0;i<symbols.size();i++){
            // cout<<"Cmparing "<<symbols[i]<<" with "<<var<<endl;
            if(symbols[i]==var){
                vector<string> ReturnIt;
                ReturnIt.push_back(var);
                ReturnIt.push_back(to_string(addr[i]));
                ReturnIt.push_back(to_string(initial_value[i]));
                return ReturnIt;
            }
        }
        vector<string> ReturnIt;
        return ReturnIt;
    }
};

class DataSegment{
    public:
    vector<int> addresses;
    vector<string> variables; 
    int addr=0;
    int seed=1000000;
    int add_variable(string var){
        for(int i=0;i<variables.size();i++){
            if(variables[i]==var){
                return (i) + seed;
            }
        }
        addresses.push_back(addr);
        variables.push_back(var);
        addr++;
        return (addr-1)+ seed;
    }

    void Print_Data_Segment(){
        for(int i=0;i<addresses.size();i++){
            cout<<i+seed<<"          ~"<<i<<"             "<<addresses[i]<<"       -->"<<variables[i]<<endl;
        }
    }

    int get_address_by_var(string var){
        for(int i=0;i<addresses.size();i++){
            if(variables[i]==var){
                return i+seed;
            }
        }
    }

    void ds_clear(){
        addresses.clear();
        variables.clear();
        addr =0;
        seed=1000000;
    }
    
};


class StackSegment{
    public:
    vector<int> Stack;
    int num_of_params =0;
    bool return_value =  false;
    int return_line = 0;
    string function_name;

    void Print_Stack_Segment(){
        cout<<"-------------Stack Segment-----------------"<<endl;
        cout<<"Params = "<<num_of_params<<endl;
        cout<<"Return Line = "<<return_line<<endl;
        cout<<"Function Name = "<<function_name<<endl;
        cout<<"Return_Value = "<<return_value<<endl;
        for(int i=0;i<Stack.size();i++){
            if(i<num_of_params)
            cout<<"Parameter"<<i+1<<" = "<<Stack[i]<<endl;
            if(i>=num_of_params)
            cout<<"Output Variable Address = "<<Stack[i]<<endl;
        }
         cout<<"---------------------------------------"<<endl;

    }

    void clear_Segement(){
        Stack.clear();
        num_of_params=0;
        return_value=0;
        function_name.clear();
        return_line=0;
    }
};


class VM{

    private:
    vector<DataSegment> DS;  // Basically an Array of DataSegment every function has Different Data Segment so implemented using a structure
    //DS 0    0[  ]  where  [] is the container to store variable
    //        1[  ]
    //DS 1    0[  ]
    //        1[  ]
    //DS 2    0[  ]
    //        1[  ]
    vector<StackSegment> SS;
    vector<QuadCode> CS;    // Basically a 2D  but implemented using a Structur
    Symbol_Table global_ST;
    vector<string> global_ST_Context;
    vector<Symbol_Table> local_ST;
    const char* filename;
    public:
    OpCode _opCode;
    vector<QuadCode> quad; 

    VM(const char filename[]){
      start(filename);
    }

    //CODE COMPILATION
    void start(const char filename[]);
    void initialize_OpCode_and_CodeSegment(const char filename[]);
    void initialize_symbol_tables();
    void initialize_data_segmant();
    bool lookup_global_symbol_table(string var);
    void initialize_data_segmant_local();
    bool lookup_local_table(string var, int i);
    OperationCode convert_condition_to_enum(string Operand1);
    string lookup_variable(string var, int func, DataSegment* ds);
    string clean_the_string(string my_string);
    int get_ds(string op);
    int get_ind(string op);
    int get_ds_2(string op);
    int updatePC(string label);
    void functionCall(int,string);

    //CODE EXECUTION
    void Executer_VM();


};
#endif
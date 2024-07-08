#include "OpCode.h"
#include<iostream>
#include<string.h>
#include<fstream>
#include<string>
#pragma warning(disable:4996)
using namespace std;


void OpCode::Print_the_lines(){
    for(int i=0;i<lines.size();i++){
        cout<<lines[i]<<endl;
    }
}

std::string OpCode::replaceSpaces(std::string str) {
    bool inQuotes = false;
    for (std::size_t i = 0; i < str.length(); i++) {
        if (str[i] == '"' && (i == 0 || str[i-1] != '\\')) { // Check for start or end of quotes
            inQuotes = !inQuotes;
        } else if (inQuotes && str[i] == ' ') {
            str[i] = '$';
        }
    }
    return str;
}


std::string OpCode::convertSpaces(std::string str) {
     bool inSpace = false;
    std::string result;
    for (char c : str) {
        if (std::isspace(c)) {
            if (!inSpace) {
                result += ' ';
                inSpace = true;
            }
        } else {
            result += c;
            inSpace = false;
        }
    }

    // Trim leading spaces
    const auto firstNonSpace = result.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos) {
        // String is all spaces
        return "";
    }
    result.erase(0, firstNonSpace);

    // Trim trailing spaces
    const auto lastNonSpace = result.find_last_not_of(' ');
    const auto lastNonSpaceIndex = lastNonSpace != std::string::npos ? lastNonSpace : result.size();
    result.erase(lastNonSpaceIndex + 1, result.size() - lastNonSpaceIndex - 1);

    return result;
}


string OpCode::removeBrackets(string str) {
    string result;
    for (char c : str) {
        if (c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}') {
            result += c;
        }
    }
    return result;
}


void OpCode::load_code_in_stream(const char filename[]){
    ifstream file;
    file.open(filename);
    if(file.is_open()){
        int it= 0;
        std::string line;
        while(std::getline(file, line)){
        lines.push_back(line);}
        file.close();
    }else{
        cout<<"error";
    }

    cout<<"-----------------------------------------------"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"OpCode Running"<<endl;
    cout<<"-----------------------------------------------"<<endl;
    cout<<"-----------------------------------------------"<<endl;

    // Print_the_lines();
    clean_the_code();
    convert_code_into_tokens();
    translate_code_into_machine_code();
}




void OpCode:: clean_the_code()
{
    // cout<<"--------Brackets Removing---------"<<endl;
    for(int i=0;i<lines.size();i++){
        lines[i] = removeBrackets(lines[i]);
    }
    // Print_the_lines();


    // cout<<"--------Spaces Converting---------"<<endl;
    for(int i=0;i<lines.size();i++){
        lines[i] = convertSpaces(lines[i]);
    }

    // Print_the_lines();

    // cout<<"--------Spaces Replacing in Strings---------"<<endl;
    for(int i=0;i<lines.size();i++){
        lines[i] = replaceSpaces(lines[i]);
    }
    // Print_the_lines();

    
}

void OpCode:: convert_code_into_tokens(){

    // cout<<"-------Tokenizing-------"<<endl;

    for(int i =0 ;i<lines.size();i++){
        OpTokens t(lines[i]);
        // t.Print_OpTokens();
        _opTokens.push_back(t);

    }
}


bool isNotOperator(const std::string& str) {
    for (char c : str) {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            return false;
        }
    }
    return true;
}

void OpCode::Single_Assignment_Translation(OpTokens t){
    string move = "mov";
    QuadCode Q(move,t.token1, t.token3);
    _quadCode.push_back(Q);
}

string OpCode::translateRelationalOperator(const std::string& op) {
    if (op == "<") {
        return "LT";
    } else if (op == "<=") {
        return "LE";
    } else if (op == ">") {
        return "GT";
    } else if (op == ">=") {
        return "GE";
    } else if (op == "=") {
        return "EQ";
    } else if (op == "!=") {
        return "NE";
    } else {
        // handle unrecognized operator as an error or a different operator, as desired
        return op;
    }
}


void OpCode::Selection_Translation(OpTokens t){
  QuadCode Q(translateRelationalOperator(t.token3), t.token2, t.token4, t.token6);
  _quadCode.push_back(Q);
}

void OpCode::Operational_Transaltion(OpTokens t){
    if(t.token4=="+")
    {QuadCode Q("add", t.token3, t.token5, t.token1); _quadCode.push_back(Q);}
    else if(t.token4=="-")
   { QuadCode Q("sub", t.token3, t.token5, t.token1); _quadCode.push_back(Q);}
     else if(t.token4=="/")
   { QuadCode Q("div", t.token3, t.token5, t.token1); _quadCode.push_back(Q);}
     else if(t.token4=="%")
   { QuadCode Q("mod", t.token3, t.token5, t.token1); _quadCode.push_back(Q);}
     else if(t.token4=="*")
   { QuadCode Q("mul", t.token3, t.token5, t.token1); _quadCode.push_back(Q);}
   

}

void OpCode::Function_Call_Transaltion(OpTokens t){
   QuadCode Q(t.token1, t.token2, t.token3, t.token5);
  _quadCode.push_back(Q);
}

void OpCode::translate_code_into_machine_code(){

    for(int i=0;i<_opTokens.size();i++){

        if(_opTokens[i].token2=="=" && _opTokens[i].token4.empty() && isNotOperator(_opTokens[i].token4)){
            Single_Assignment_Translation(_opTokens[i]);
        }
        else if(_opTokens[i].token2=="=" && !_opTokens[i].token4.empty() && !isNotOperator(_opTokens[i].token4)){
            Operational_Transaltion(_opTokens[i]);
        }
        else if(_opTokens[i].token1=="if"){
            Selection_Translation(_opTokens[i]);
        }
        else if(_opTokens[i].token1=="call"){
            Function_Call_Transaltion(_opTokens[i]);
        }
        else if(_opTokens[i].token3.empty()){
            QuadCode Q(_opTokens[i].token1, _opTokens[i].token2);
             _quadCode.push_back(Q);
        }
        else if(_opTokens[i].token2.empty()){
            QuadCode Q(_opTokens[i].token1);
             _quadCode.push_back(Q);
        }
    }

    

}
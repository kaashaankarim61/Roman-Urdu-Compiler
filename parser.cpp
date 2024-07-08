#include "parser.h"
#include<iostream>
#include<string.h>
#include<string>
#pragma warning(disable:4996)
using namespace std;

int n_line = 1;
int s_nxt = 0;
int BET = 0;
int BEF = 0;
bool Check_Phir = false;
int argCount=0;

vector<int> BEF_v;
vector<int> BET_v;


vector<std::string> Code_Lines;
vector<int> elses;

string Lexemes[] = {
    "END_OF_FILE",
    "NL",
    "INT",
    ";",
    "ID",
    "RELOP",
    "COMMENT",
    "IO",
    ":=",
    "(",
	")",
	"|",
	":",
	"@",
	"`",
	"+",
	"-",
	"*",
	"/",
	"%",
    "STRING",  
	"markazi",
	"kaam",
	"karo",
	"rakho",
	"jab",
	"tak",
	"bas",
	"agar",
	"to",
	"warna",
	"phir",
	"dekhao",
	"lo",
	"chalao",
	"bhaijo",
	"adad",
	"khali",
	"khatam",
    "wapas",
    "error",
    "temp"
	};


void parser::syntax_error()
{
    cout << "SYNTAX ERROR AT LINE  " << countLines()+1 <<endl;;
    exit(1);
}

void fillblank(int At, int What){
    ifstream file;
    file.open("TAC.txt");
    if(file.is_open()){
        int it= 0;
        std::string line;
        while(std::getline(file, line)){
        Code_Lines.push_back(line);}
        file.close();
    }else{
        cout<<"error";
    }


    int u = Code_Lines[At-1].length()-2;
    string str_num =to_string(What);
    int str_num_len = str_num.size();

    // char line_num = What + '0';
    for(int i=0;i<str_num_len;i++){
        Code_Lines[At-1][u++]=str_num[i];
    }


    const char* filename = "TAC.txt";
    int result = std::remove(filename);


    ofstream file_out;
    file_out.open("TAC.txt");
    if(file_out.is_open()){
        for(int i=0; i<Code_Lines.size();i++)
        {file_out << Code_Lines[i];
        file_out <<'\n';}
        file_out.close();
    }

    Code_Lines.clear();


}

void parser::write_TAC(string lexeme, bool nl){

    
    ofstream myfile;
    myfile.open("TAC.txt",ios::app);
    if (myfile.is_open())
    {
        myfile <<string(lexeme)<<" ";
        if(nl){ myfile<<"\n"; n_line++;}
        myfile.close();
    }
    else cout << "Unable to open file";
}

void parser::write_TAC_NS(string lexeme, bool nl){

    ofstream myfile;
    myfile.open("TAC.txt",ios::app);
    if (myfile.is_open())
    {
        myfile <<string(lexeme);
        if(nl){ myfile<<"\n"; n_line++;}
        myfile.close();
    }
    else cout << "Unable to open file";
}







void parser::write_symbol_table(){
    ofstream myfile ("symbol_table.txt");
    if (myfile.is_open())
    {
        myfile <<"TYPE        Initial_Value      Address      Id_Type        ID\n";
        for(int i=0;i<symbols.size();i++)
        {
           
           if(S_type[i]==1)
           myfile<<"adad ";
           else
           myfile<<"khali";

           myfile<<'\t'<<'\t'<<'\t'<<'\t';

           myfile<<S_initial_value[i];
           myfile<<'\t'<<'\t'<<'\t';
           myfile<<symbols_address[i];

           myfile<<'\t'<<'\t'<<'\t';

           if(S_id_type[i]==0)
           myfile<<"func";
           else if(S_id_type[i]==1)
           myfile<<"var ";
           else if(S_id_type[i]==2)
           myfile<<"param";

           myfile<<'\t'<<'\t'<<'\t';

           if(symbols[i].tokenType!=TokenType::MARKAZI)
           myfile<<symbols[i].lexeme;
           else 
           myfile<<"Markazi";
           
            myfile<<'\n';
            
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

void parser::print_tabs(){
    // for(int i=0;i<tabs;i++)
    // {
    //     cout<<'\t';
    // }
    for(int i=0;i<tabs;i++)
    {
        cout<<"    ";
    }
}

token parser::expect(TokenType expected_type)
{
    //cout<<"I";
    token t = _lexer.getNextToken();
    print_tabs();
    t.Print(); 
     //t.PrintOnlyToken();

    if (t.tokenType != expected_type){
        cout<<"Mismatched Token  = ";t.Print();
        syntax_error();
    }
    else {
        ;
    }
    //cout<<"O";
    return t;
}



parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    readAndPrintAllInput();
    cout<<"-------------<PARSING>---------------"<<endl<<endl;

    Program();


    while(_lexer.peek(1).tokenType == TokenType::NL)
       _lexer.getNextToken();

    if (_lexer.peek(1).tokenType != TokenType::END_OF_FILE)
    {
       syntax_error();
    }

    write_symbol_table();
   
}



void parser::readAndPrintAllInput() //read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }


}



void parser::resetPointer()
{
    _lexer.resetPointer();
}



//this function is for sample purposes only

// void parser::T()
// {
//     resetPointer();
//     cout<<"T"<<endl;
//     tabs++;
//     F();T_();
// }

// void parser::T_(){
//     print_tabs();
//     cout<<"T_"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::PLUS)
//     {
//         expect(TokenType::PLUS); F(); T_(); 
//     }
//     else{
//      ;
//     }
//     tabs--;
// }

// void parser::F(){

//     print_tabs();
//     cout<<"F"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::ID)
//     {
//         expect(TokenType::ID);
//     }
//     else if(_lexer.peek(1).tokenType == TokenType::INT)
//     {
//      expect(TokenType::INT);   
//     }
//     else{
//        ;
//     }
//     tabs--;
// }

// void parser::Statement_List(){
//     resetPointer();
//     cout<<"SL"<<endl;
//     tabs++;

//     if (_lexer.peek(1).tokenType == TokenType::KAAM || _lexer.peek(1).tokenType == TokenType::RAKHO)
//     {
//        Decleration();
//     }

//     tabs--;
// }


// void parser::Decleration(){
    
//     print_tabs();
//     cout<<"D"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::KAAM)
//     {
//        Funtion_Decleration();
//     }
//     else if(_lexer.peek(1).tokenType == TokenType::RAKHO){

//         Variable_Decleration();
//     }

//     tabs--;
// }

// void parser::Variable_Decleration()
// {
//     print_tabs();
//     cout<<"VD"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::RAKHO)
//     {
//        expect(TokenType::RAKHO);
//        expect(TokenType::ID);
//        expect(TokenType::AT); 
//         expect(TokenType::ADAD); 
//        VD_Specifier();
//     }

//     tabs--;

// }

// void parser::VD_Specifier(){

//     print_tabs();
//     cout<<"VD_S"<<endl;
//     tabs++;
 
//     if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP)
//     {
//        expect(TokenType::ASSIGNOP);
//         F();T_();
//     }

//     tabs--;

// }

// void parser::Funtion_Decleration(){

// }





///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////



int  parser::countStatementsInBlock(int pos, int btype){
    //cout<<"Pos = "<<pos<<endl;
    //cout<<"idmeodi = "<< _lexer.getStatementCount(pos,btype);
    return _lexer.getStatementCount(pos,btype);

 }

  void parser::countDecleration(){
     functionCount =  _lexer.getDecCount();
  }







///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////




void parser::Program(){

    const char* filename = "TAC.txt";
    int result = std::remove(filename);
    //removeNL();
    print_tabs();
    resetPointer();
    countDecleration();
    removeNL();
    cout<<"P"<<endl;
    tabs++;

    if (_lexer.peek(1).tokenType == TokenType::KAAM || _lexer.peek(1).tokenType == TokenType::RAKHO)
    {
       DeclarationList();
       write_TAC("HALT",1);
    }
    else if(_lexer.peek(1).tokenType == TokenType::END_OF_FILE){
        ;
    }
    else{
        syntax_error();
    }
    tabs--;
    cout<<"PROGRAM COMPILED SUCCESSFULLY"<<endl;
    //removeNL();

}

void parser::DeclarationList(){
    //removeNL();
    print_tabs();
    cout<<"DL"<<endl;
    tabs++;
    if( ( _lexer.FunctionDecCount(_lexer.getCurrentPointer()) + _lexer.globalVariablesCount(_lexer.getCurrentPointer())) ==1){
    Declaration();
    }
    else if((_lexer.FunctionDecCount(_lexer.getCurrentPointer()) + _lexer.globalVariablesCount(_lexer.getCurrentPointer())) > 1) {
     Declaration(); removeNL(); DeclarationList(); 
    }
    else{
        ;
    }
    tabs--;
    //removeNL();
}




void parser::Declaration(){
    //removeNL();
    print_tabs();
    cout<<"D"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KAAM)
    {
        FunctionDeclaration();
    }
    else if(_lexer.peek(1).tokenType == TokenType::RAKHO){
      
        VariableDeclaration();  
    }
    else
    {
        syntax_error();
    }

    tabs--;
   // removeNL();
   
}




void parser::TypeF(){
   // removeNL();
    print_tabs();
    cout<<"TypeF"<<endl;
    tabs++;
  

 
    if (_lexer.peek(1).tokenType == TokenType::ADAD)
    {
       expect(TokenType::ADAD); 
    }
    else if(_lexer.peek(1).tokenType == TokenType::KHALI){
       expect(TokenType::KHALI); 
    }
    else{
        syntax_error();
    }

    tabs--;
   // removeNL();

}




void parser::TypeID(){
    removeNL();
    print_tabs();
    cout<<"TypeID"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ADAD)
    {
       expect(TokenType::ADAD); 
    }
    else{
        syntax_error();
    }

    tabs--;
    //removeNL();
}


void parser::Parameter(){
    //Parameter → id @ typeV
    //removeNL();
    print_tabs();
    cout<<"P"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
        ADDTOTABLE(_lexer.getCurrentToken(_lexer.getCurrentPointer()),1,2);
        ADD_Initial_Value("0");
        expect(TokenType::AT);
        TypeID();
          
    }else{
        syntax_error();
    }

    tabs--;
  // removeNL();


}




void parser::ParameterList(){
  /// removeNL();
    //ParameterList → Parameter | Parameter `|`  ParameterList 
    print_tabs();
    cout<<"PL"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ID && _lexer.peek(4).tokenType != TokenType::PIPE)
    {
        Parameter();     
    }
    else if(_lexer.peek(4).tokenType == TokenType::PIPE){
        Parameter();
        expect(TokenType::PIPE);
        ParameterList();
    }
    else
    {
       ;
    }

    tabs--;
  /// removeNL();

}

void parser::FunctionDeclaration(){
   ///removeNL();
    //FunctionDeclaration → “kaam” id “@” typeF "(" ParameterList ")" BlockF

    print_tabs();
    cout<<"FD"<<endl;
    tabs++;

    
 
    if (_lexer.peek(1).tokenType == TokenType::KAAM && _lexer.peek(2).tokenType != TokenType::MARKAZI)
    {
       addr=0;
       expect(TokenType::KAAM);
    //    write_TAC(_lexer.peek(1).lexeme,0);
    //    write_TAC(":",1);
       expect(TokenType::ID);
       if (_lexer.peek(2).tokenType == TokenType::ADAD){
        ADD_Initial_Value(to_string(n_line));
        ADDTOTABLE(_lexer.getCurrentToken(_lexer.getCurrentPointer()),1,0); 
        }
        else{
             ADD_Initial_Value("0");
         ADDTOTABLE(_lexer.getCurrentToken(_lexer.getCurrentPointer()),0,0);
         }
       expect(TokenType::AT);
       TypeF(); 
       expect(TokenType::LPAREN);
       ParameterList();
       expect(TokenType::RPAREN);
       BlockF();

    }
    else if (_lexer.peek(1).tokenType == TokenType::KAAM && _lexer.peek(2).tokenType == TokenType::MARKAZI )
    {
       addr=0;
       expect(TokenType::KAAM);
       expect(TokenType::MARKAZI);
    //    write_TAC("markazi",0);
    //    write_TAC(":",1);
       ADDTOTABLE(_lexer.getCurrentToken(_lexer.getCurrentPointer()),0,0);
       ADD_Initial_Value(to_string(n_line));
       expect(TokenType::AT);
       TypeF(); 
       expect(TokenType::LPAREN);
       ParameterList();
       expect(TokenType::RPAREN);
       BlockF();
    }
    else{
        syntax_error();
    }


    tabs--;
    //removeNL();


}




void parser::VariableDeclaration(){
    print_tabs();
    cout<<"VD"<<endl;
    token VDSpecifier_i;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::RAKHO )
    {
       expect(TokenType::RAKHO);

       if (_lexer.peek(1).tokenType == TokenType::ID )
       VDSpecifier_i = _lexer.peek(1);

       expect(TokenType::ID);
       ADDTOTABLE(_lexer.getCurrentToken(_lexer.getCurrentPointer()),1,1);
       expect(TokenType::AT); 
       TypeID(); 
       VDSpecifier(VDSpecifier_i);
    }
    else{
        ;
    }

    tabs--;
  // removeNL();
}


token parser::VariableAssignment(){
    print_tabs();
    cout<<"VA"<<endl;
    tabs++;
    token Expression_v;
    token ID_v;
 
    if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(4).tokenType != TokenType::NL &&  _lexer.peek(4).tokenType != TokenType::CHALAO)
    {
       expect(TokenType::RAKHO);
       if (_lexer.peek(1).tokenType == TokenType::ID) ID_v=_lexer.peek(1);
       expect(TokenType::ID);
       expect(TokenType::ASSIGNOP);
       Expression_v = Expression();

       write_TAC(ID_v.lexeme,0);
       write_TAC("=",0);
       write_TAC(Expression_v.lexeme,1);
       tabs--;
       return ID_v;
    }
     else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(4).tokenType == TokenType::CHALAO ){
       expect(TokenType::RAKHO);
       if (_lexer.peek(1).tokenType == TokenType::ID) ID_v=_lexer.peek(1);
       expect(TokenType::ID);
       expect(TokenType::ASSIGNOP);
       Expression_v =FunctionCall();

       write_TAC(ID_v.lexeme,0);
       write_TAC("=",0);
       write_TAC(Expression_v.lexeme,1);
       tabs--;
       return ID_v;
    }

    else{
        syntax_error();
    }
   
    tabs--;
    return ID_v;
}

void parser::VDSpecifier(token VDSpecifier_i){
    //removeNL();
    print_tabs();
    cout<<"VD_S"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP  && _lexer.peek(2).tokenType != TokenType::NL && _lexer.peek(2).tokenType != TokenType::CHALAO ) 
    {
       expect(TokenType::ASSIGNOP);
       token Expression_v = Expression();
       write_TAC(VDSpecifier_i.lexeme,0);
       write_TAC("=",0);
       write_TAC(Expression_v.lexeme,1);
       string str = Expression_v.lexeme;
       ADD_Initial_Value(str);
    }
    else if (_lexer.peek(1).tokenType == TokenType::ASSIGNOP  && _lexer.peek(2).tokenType == TokenType::CHALAO ) 
    {
       expect(TokenType::ASSIGNOP);
       token Expression_v = FunctionCall();
       write_TAC(VDSpecifier_i.lexeme,0);
       write_TAC("=",0);
       write_TAC(Expression_v.lexeme,1);
       string str = Expression_v.lexeme;
       ADD_Initial_Value("0");
    }
    else if(_lexer.peek(1).tokenType == TokenType::NL) {
         expect(TokenType::NL);
         ADD_Initial_Value("0");
    }
    else{
        syntax_error();
    }

    tabs--;
   //removeNL();

}


void parser::Block(){
    //removeNL();
    print_tabs();
    cout<<"BLOCK"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       expect(TokenType::NL);
       StatementList();
       expect(TokenType::BAS); 
       expect(TokenType::KARO);
       expect(TokenType::NL);
    }else{
        syntax_error();
    }

    tabs--;
    //removeNL();

}
void parser::BlockF(){
    //removeNL();
    int Statement =0;
    print_tabs();
    cout<<"BLOCKF"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       expect(TokenType::NL);
       StatementList();
       expect(TokenType::KAAM); 
       expect(TokenType::KHATAM);
       if (_lexer.peek(1).tokenType == TokenType::NL)
       expect(TokenType::NL);
       else if (_lexer.peek(1).tokenType == TokenType::END_OF_FILE)
       expect(TokenType::END_OF_FILE);
    }
    else{
        syntax_error();
    }

    tabs--;
   // removeNL();

}




void parser::BlockIF(){

    print_tabs();
    cout<<"BLOCKIF"<<endl;
    tabs++;
 
    if (_lexer.peek(1).tokenType == TokenType::KARO)
    {
       expect(TokenType::KARO);
       expect(TokenType::NL);
       IFStatementList();

       if(Check_Phir==false){
       BEF = BEF_v.back();
       BEF_v.pop_back();
       fillblank(BEF,n_line);
       }

       for(int i=0;i<elses.size();i++)
       {
         fillblank(elses[i],n_line);
       }

       elses.clear();
       expect(TokenType::BAS); 
       expect(TokenType::KARO);
       expect(TokenType::NL);

       Check_Phir=false;


    }else{
        syntax_error();
    }

    tabs--;


}
void parser::IFStatementList(){

    print_tabs();
    cout<<"ISL"<<endl;
    tabs++;

    if(_lexer.CheckLast(_lexer.getCurrentPointer())==1){
      IFStatement();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==0) {
      IFStatement(); IFStatementList();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==-1) {
        tabs--;
        return;
    }
    else{
        tabs--;
        return;
    }

    tabs--;
    

}
void parser::IFStatement(){

    print_tabs();
    cout<<"IF"<<endl;
    tabs++;

    


    if (_lexer.peek(1).tokenType == TokenType::AGAR)
    {
        SelectionStatement();
    }
    else if( _lexer.peek(1).tokenType == TokenType::WARNA){
        write_TAC("goto",0);
        elses.push_back(n_line);
        write_TAC("_",1);
        BEF = BEF_v.back();
        BEF_v.pop_back();
        fillblank(BEF,n_line);
        WarnaStatement();
        
    }
    else if (_lexer.peek(1).tokenType == TokenType::JAB){
        IterativeStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::WAPAS){
        ReturnStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::AT){
        VariableDeclaration();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::ASSIGNOP){
        VariableAssignment();
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHALAO){
        FunctionCall();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LO  || _lexer.peek(1).tokenType == TokenType::DEKHAO){
        IOStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID || _lexer.peek(1).tokenType == TokenType::INT){
        Expression();
    }
    else if((_lexer.EmptyStatements(_lexer.getCurrentPointer())==1)){
        ;
    }
    else{
         syntax_error();
    }

    tabs--;
    removeNL();

}


void parser::StatementList(){
  // removeNL();
    print_tabs();
    cout<<"SL"<<endl;
    tabs++;
    // cout<<"Call "<<_lexer.CheckLast(_lexer.getCurrentPointer())<<endl;

    if(_lexer.CheckLast(_lexer.getCurrentPointer())==1){
    Statement();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==0) {
     Statement();StatementList();
    }
    else if(_lexer.CheckLast(_lexer.getCurrentPointer())==-1) {
        tabs--;
        return;
    }
    else{
        tabs--;
        return;
    }

    tabs--;
   //removeNL();
   
}

void parser::Statement(){
    //removeNL();
    print_tabs();
    cout<<"S"<<endl;
    tabs++;
    //cout<<"TOKEN"; _lexer.peek(1).Print();


    if (_lexer.peek(1).tokenType == TokenType::AGAR)
    {
        SelectionStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::JAB){
        IterativeStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::WARNA){
       syntax_error();
    }
    else if (_lexer.peek(1).tokenType == TokenType::WAPAS){
        ReturnStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::AT){
        VariableDeclaration();
    }
    else if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::ASSIGNOP){
        VariableAssignment();
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHALAO){
        FunctionCall();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LO  || _lexer.peek(1).tokenType == TokenType::DEKHAO){
        IOStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::ID || _lexer.peek(1).tokenType == TokenType::INT){
        Expression();
    }
    else if((_lexer.EmptyStatements(_lexer.getCurrentPointer())==1)){
        ;
    }
    else{
        syntax_error();
    }
   


    // if (_lexer.peek(1).tokenType == TokenType::NL){
    //     Expression();
    // }
    // expect(TokenType::NL);
    tabs--;
    //statementCount--;
    removeNL();

}


token parser::Expression(){

     //removeNL();
    print_tabs();
    cout<<"Ex"<<endl;
    tabs++;
    token Expression_v;

    if (_lexer.peek(1).tokenType == TokenType::RAKHO && _lexer.peek(3).tokenType == TokenType::ASSIGNOP  ){
        Expression_v =  VariableAssignment(); 
    }

    else {
       Expression_v  = ComparisonExpression();
    }

    
    tabs--;
    return Expression_v;
     
}


void parser::SelectionStatement(){

     // SelectionStatement → "agar" "(" Expression ")" "to phir" Block WarnaStatement
    print_tabs();
    cout<<"SS"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::AGAR)
    {
       expect(TokenType::AGAR);
       expect(TokenType::LPAREN); 
       Expression();
       BET= BET_v.back();
       BET_v.pop_back();
       fillblank(BET,n_line);
       expect(TokenType::RPAREN);
       expect(TokenType::TO);
       expect(TokenType::PHIR);
       BlockIF();
       
       

    }
    else if(_lexer.peek(1).tokenType == TokenType::WARNA )
    {

        expect(TokenType::WARNA);
        PhirStatement();

    }
    else {
      syntax_error();
    }

    tabs--;



}
void parser::IterativeStatement(){
    //IterativeStatement → "jab tak" "(" Expression ")" Block
    print_tabs();
    cout<<"Iter S"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::JAB)
    {
       expect(TokenType::JAB);
       expect(TokenType::TAK);
       expect(TokenType::LPAREN); 
       BET_v.push_back(n_line);
       Expression();
       BET = BET_v.back();
       BET_v.pop_back();
       fillblank(BET,n_line);
       expect(TokenType::RPAREN);
       Block();
       write_TAC("goto",0);
       BET  =BET_v.back();
       BET_v.pop_back();
       write_TAC(to_string(BET),1);
       BEF = BEF_v.back();
       BEF_v.pop_back();
       fillblank(BEF,n_line);
    }
    else {
      syntax_error();
    }

    tabs--;


}
void parser::ReturnStatement(){
    //ReturnStatement → "wapas bhaijo" Expression 

     print_tabs();
    cout<<"RET"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::WAPAS)
    {
       expect(TokenType::WAPAS);
       expect(TokenType::BHAIJO);
       token t = Expression();
       write_TAC("ret",0);
       write_TAC(t.lexeme,1);
       expect(TokenType::NL);
    }
    else {
      syntax_error();
    }

    tabs--;

}

token parser::FunctionCall(){

    print_tabs();
    cout<<"FC"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::CHALAO)
    {
       
       expect(TokenType::CHALAO);
       string id = _lexer.peek(1).lexeme;
       expect(TokenType::ID);
       expect(TokenType::LPAREN); 
       ArgumentList();
       expect(TokenType::RPAREN);
       write_TAC("call", 0);
       write_TAC(id, 0);
       write_TAC(to_string(argCount), 0);
       write_TAC(",",0);
       token t = tempVAR();
       ADDTOTABLE(t,1,1);
       ADD_Initial_Value("0");

       write_TAC(t.lexeme,1);
       expect(TokenType::NL);
       argCount=0;
       return t;
    }
    else {
      syntax_error();
    }

    tabs--;


}
void parser::IOStatement(){
    print_tabs();
    cout<<"IO"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::LO)
    {
      InputStatement();
    }
    else if (_lexer.peek(1).tokenType == TokenType::DEKHAO)
    {
      PrintStatement();
    }
    else {
      syntax_error();
    }

    tabs--;

}


void parser:: ArgumentList(){

    print_tabs();
    cout<<"AL"<<endl;
    tabs++;
   
    if (_lexer.countArgs(_lexer.getCurrentPointer())<=1)
    {
       Argument(); 
    }
    else if (_lexer.countArgs(_lexer.getCurrentPointer())>1)
    {
       Argument();  expect(TokenType::PIPE); ArgumentList(); 
    }
    else {
      syntax_error();
    }

    tabs--;

}

//Argument → id | int | "(" Expression ")" | ^

void parser::Argument(){
    argCount++;
    print_tabs();
    cout<<"A"<<endl;
    tabs++;
   
    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
       write_TAC("param", 0);
       write_TAC(_lexer.peek(1).lexeme,1);
       expect(TokenType::ID);
    }
    else if (_lexer.peek(1).tokenType == TokenType::INT)
    {
       write_TAC("param", 0);
       write_TAC(_lexer.peek(1).lexeme,1);
       expect(TokenType::INT);
    }
    else if (_lexer.peek(1).tokenType == TokenType::LPAREN)
    {
       expect(TokenType::LPAREN);
       token Argument_v = Expression();
       expect(TokenType::RPAREN);
       write_TAC("param", 0);
       write_TAC(Argument_v.lexeme,1);
    }
    else {
     ;
    }

    tabs--;

}





void parser::T_(){
   // removeNL();
    print_tabs();
    cout<<"T_"<<endl;
    tabs++;

    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        expect(TokenType::PLUS); F(); T_();
    }
    else{
     ;
    }
    tabs--;
   // removeNL();
}

void parser::F(){
   // removeNL();
    print_tabs();
    cout<<"F"<<endl;
    tabs++;

    if (_lexer.peek(1).tokenType == TokenType::ID)
    {
        expect(TokenType::ID);
    }
    else if(_lexer.peek(1).tokenType == TokenType::INT)
    {
        expect(TokenType::INT);   
    }
    else{
       ;
    }
    tabs--;
    //removeNL();

}


 // IOStatement → InputStatement | PrintStatement
 
    // InputStatement → "lo" PS1 | IS1

    // IS1 → “>>” id | IS1

    // PrintStatement → "dekhao"  PS1

    // PS1 →  “<<” string PS1 | Expression PS1 | int PS1 | id PS1 | ^



    void parser::InputStatement(){
        print_tabs();
        cout<<"IState"<<endl;
        tabs++;

        if (_lexer.peek(1).tokenType == TokenType::LO)
        {
            expect(TokenType::LO);
            InputSpecifier();
        }
        else{
        ;
        }
        tabs--;

    }

    void parser::InputSpecifier(){

        print_tabs();
        cout<<"ISpeci"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        // cout<<"lexeme";
        // cout<<str<<endl;
        if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "I")==0)
        {
           IS1();
        }
        else if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "O")==0)
        {
           InOutStatement();
        }
        else{
        ;
        }
        tabs--;

    }

    void parser::PrintStatement(){
       
       
        print_tabs();
        cout<<"PState"<<endl;
        tabs++;

        if (_lexer.peek(1).tokenType == TokenType::DEKHAO)
        {
            expect(TokenType::DEKHAO);
            PS1();
        }
        else{
        ;
        }
        tabs--;

    }
    void parser::PS1(){

        print_tabs();
        cout<<"PS1"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "O")==0)
        {
           expect(TokenType::IO);
           PrintVar();
        }
        else{
        syntax_error();
        }
        tabs--;

    }


    void parser::InOutStatement(){

        print_tabs();
        cout<<"IOS"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "O")==0)
        {
           expect(TokenType::IO);
           PrintArg();
        }
        else{
        syntax_error();
        }
        tabs--;

    }

    void parser::PrintVar(){
        print_tabs();
        cout<<"PrintVar"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        
        if (_lexer.peek(1).tokenType == TokenType::STRING)
        {
         
           write_TAC("out",0);
           write_TAC_NS("\"",0);
           write_TAC_NS(_lexer.peek(1).lexeme,0);
           write_TAC("\"",1);
           expect(TokenType::STRING);
           PrintTer();
        }
        else if (_lexer.peek(1).tokenType == TokenType::INT || _lexer.peek(1).tokenType == TokenType::ID)
        {
           
           token PrintVar_v= Expression();

           write_TAC("out",0); 
           write_TAC(PrintVar_v.lexeme,1); 
           PrintTer();

        }
        else{
        syntax_error();
        }
        tabs--;


    }


    void parser::PrintArg(){
        print_tabs();
        cout<<"PrintArg"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        
        if (_lexer.peek(1).tokenType == TokenType::STRING)
        {
           write_TAC("out",0);
           write_TAC_NS("\"",0);
           write_TAC_NS(_lexer.peek(1).lexeme,0);
           write_TAC("\"",1);
           expect(TokenType::STRING); 
          
           PrintCont();
        }
        else if (_lexer.peek(1).tokenType == TokenType::INT || _lexer.peek(1).tokenType == TokenType::ID)
        {
           token t = Expression(); 
           write_TAC("out",0); 
           write_TAC(t.lexeme,1);


           PrintCont();
        }
        else{
        syntax_error();
        }
        tabs--;


    }





    void parser::PrintTer(){

         print_tabs();
        cout<<"PrintTER"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        

        if (_lexer.peek(1).tokenType == TokenType::NL)
        {
           expect(TokenType::NL);
        }
        else if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "O")==0)
        {
          PS1();
        }
        else{
        syntax_error();
        }
        tabs--;


    }


    void parser::PrintCont(){

         print_tabs();
        cout<<"PrintCont"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        

        if (_lexer.peek(1).tokenType == TokenType::NL)
        {
           expect(TokenType::NL);
        }
        else if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "O")==0)
        {
          InOutStatement();
        }
        else if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "I")==0)
        {
          IS1();
        }
        else{
        syntax_error();
        }
        tabs--;


    }

    void parser:: InputVAR(){

        print_tabs();
        cout<<"IVAR"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        

        if (_lexer.peek(1).tokenType == TokenType::NL)
        {
           expect(TokenType::NL);
        }
        else if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "I")==0)
        {
          IS1();
        }
        else{
        syntax_error();
        }
        tabs--;

    }

    void parser::IS1(){
        print_tabs();
        cout<<"IS1"<<endl;
        tabs++;

        const char* str = _lexer.peek(1).lexeme.c_str();
        if (_lexer.peek(1).tokenType == TokenType::IO && strcmp(str, "I")==0)
        {
          
           
           expect(TokenType::IO);
           write_TAC("in",0);
           write_TAC(_lexer.peek(1).lexeme,1);
           expect(TokenType::ID);
           InputVAR();
        }
        else{
        syntax_error();
        }
        tabs--;
        
    }



    void parser::WarnaStatement(){
        print_tabs();
        cout<<"WS"<<endl;
        tabs++;
    
        if (_lexer.peek(1).tokenType == TokenType::WARNA)
        {
        expect(TokenType::WARNA);
        PhirStatement();
        }
        else {
        ;
        }

        tabs--;

    }

    void parser::PhirStatement(){
        //PhirStatement →  "agar" Block WarnaStatement |  “phir" Block | ^
        print_tabs();
        cout<<"PhirS"<<endl;
        tabs++;
    
        if (_lexer.peek(1).tokenType == TokenType::AGAR)
        {
        expect(TokenType::AGAR);
        expect(TokenType::LPAREN);
        Expression();
        BET= BET_v.back();
        BET_v.pop_back();
        fillblank(BET,n_line);
        expect(TokenType::RPAREN);
        expect(TokenType::TO);
        expect(TokenType::PHIR);
        expect(TokenType::NL);
        IFStatementList();
        }

        else if (_lexer.peek(1).tokenType == TokenType::PHIR)
        {
        expect(TokenType::PHIR);
        expect(TokenType::NL);
        // BEF = BEF_v.back();
        // cout<<"HERE IS "<<BEF<<endl;
        // BEF_v.pop_back();
        // fillblank(BEF,n_line);
        Check_Phir=true;
        StatementList();
        }

        else {
        ;
        }

        tabs--;

    }


    // Expression → AssignmentExpression | ComparisonExpression | ASExprssion

    // AssignmentExpression → “rakho” id ":=" Expression 

    // ComparisonExpression → ASExpression REExpression

    // REExpression →  RELOP ASExpression |  ASExpression

    // ASExpression →  + T ASExpression  | - T ASExpression  | ^

    // T → Terminal MDExpression

    // MDExpression → * Terminal MDExpression | / Terminal  MDExpression | %F MDExpression| ^

    token parser::ComparisonExpression(){

        print_tabs();
        cout<<"CE"<<endl;
        tabs++;
        token ComparisonExpression_v;
        token RELOPExpression_i;
    
        if(_lexer.CheckForRELOP(_lexer.getCurrentPointer())==1)
        {
           RELOPExpression_i = E();  
           RELOPExpression(RELOPExpression_i);
        }
        else if(_lexer.CheckForRELOP(_lexer.getCurrentPointer())==0)
        {
           ComparisonExpression_v = E(); 
        }

        else {
        syntax_error();
        }

        tabs--;
        return ComparisonExpression_v;        

    }

    token parser::E(){
    //E → T E’ \n
        print_tabs();
        cout<<"E"<<endl;
        tabs++;
        token E_v;
        token ASExpression_i;
        ASExpression_i = TT(); 
        E_v = ASExpression(ASExpression_i);
        tabs--;
        return E_v;

    }

    token parser::ASExpression(token ASExpression_i){
        // + T ASExpression  | - T ASExpression  | ^
        print_tabs();
        cout<<"ASExp"<<endl;
        tabs++;
        token tmp;

    
        if (_lexer.peek(1).tokenType == TokenType::PLUS)
        {
          expect(TokenType::PLUS);
          token ID_v = TT();
          tmp  =tempVAR();
          ADDTOTABLE(tmp,1,1); 
          ADD_Initial_Value("0");
          write_TAC(tmp.lexeme,0);
          write_TAC(string("="),0);
          write_TAC(ASExpression_i.lexeme,0);
          write_TAC(Lexemes[int(TokenType::PLUS)],0);
          write_TAC(ID_v.lexeme,1);
          tmp = ASExpression(tmp);
        }


        else if (_lexer.peek(1).tokenType == TokenType::MINUS)
        { 
          expect(TokenType::MINUS);
          token ID_v = TT();
          tmp  =tempVAR();
          ADDTOTABLE(tmp,1,1); 
          ADD_Initial_Value("0");
          write_TAC(tmp.lexeme,0);
          write_TAC(string("="),0);
          write_TAC(ASExpression_i.lexeme,0);
          write_TAC(Lexemes[int(TokenType::MINUS)],0);
          
          write_TAC(ID_v.lexeme,1);
          tmp = ASExpression(tmp);
        }

        else {
        tabs--;
        return ASExpression_i;
        }

        tabs--;
        return tmp;

    }



    token parser::MDExpression(token MDExpression_i){
        print_tabs();
        cout<<"MDE"<<endl;
        tabs++;
        token tmp ;

    
        if (_lexer.peek(1).tokenType == TokenType::MULTIPLY)
        {
          expect(TokenType::MULTIPLY);
          token ID_v = Terminal();
          tmp  =tempVAR();
           ADDTOTABLE(tmp,1,1); 
          ADD_Initial_Value("0");
          write_TAC(tmp.lexeme,0);
          write_TAC(string("="),0);
          write_TAC(MDExpression_i.lexeme,0);
          write_TAC(string("*"),0);
        
          write_TAC(ID_v.lexeme,1);
          tmp = MDExpression(tmp);

        }
        else if (_lexer.peek(1).tokenType == TokenType::DIVIDE)
        {
          expect(TokenType::DIVIDE);
          token ID_v = Terminal();

          tmp  =tempVAR();
          ADDTOTABLE(tmp,1,1); 
          ADD_Initial_Value("0");
          write_TAC(tmp.lexeme,0);
          write_TAC(string("="),0);
          write_TAC(MDExpression_i.lexeme,0);
          write_TAC(string("/"),0);
          write_TAC(ID_v.lexeme,1);
          tmp = MDExpression(tmp);
        }
        else if (_lexer.peek(1).tokenType == TokenType::MODOLUS)
        {
          expect(TokenType::MODOLUS);
          token ID_v = Terminal();
            
          tmp  =tempVAR();
           ADDTOTABLE(tmp,1,1); 
          ADD_Initial_Value("0");
          write_TAC(tmp.lexeme,0);
          write_TAC(string("="),0);
          write_TAC(MDExpression_i.lexeme,0);
          write_TAC(string("%"),0);
         
          write_TAC(ID_v.lexeme,1);
          tmp = MDExpression(tmp);
        }
        else {

        tabs--;
        return MDExpression_i;
        }

        tabs--;
        return tmp;

    }
    token parser::Terminal(){
        print_tabs();
        cout<<"Terminal"<<endl;
        tabs++;
        token Terminal_v;

        if (_lexer.peek(1).tokenType == TokenType::ID)
        {
            Terminal_v=_lexer.peek(1);
            expect(TokenType::ID);
        }
        else if(_lexer.peek(1).tokenType == TokenType::INT)
        {
            Terminal_v=_lexer.peek(1);
            expect(TokenType::INT);   
        }
          else if(_lexer.peek(1).tokenType == TokenType::STRING)
        {
            Terminal_v=_lexer.peek(1);
            expect(TokenType::STRING);   
        }
        else if(_lexer.peek(1).tokenType == TokenType::LPAREN)
        {
            expect(TokenType::LPAREN);
            Terminal_v = Expression();   
            // cout<<"Terminal_v = ";Terminal_v.Print();
            expect(TokenType::RPAREN);
        }
        else{
        ;
        }


        tabs--;
        return Terminal_v;
      
    }
    void parser::RELOPExpression(token RELOPExpression_i){

        print_tabs();
        cout<<"RELOPEXP"<<endl;
        tabs++;
        token E_v;
    
       if (_lexer.peek(1).tokenType == TokenType::RELOP)
        {
         
        
        token RO = _lexer.peek(1);
        expect(TokenType::RELOP);
        E_v = E();

        BET_v.push_back(n_line);
        // BET = n_line ;

        write_TAC("if",0);
        write_TAC("(",0);
        write_TAC(RELOPExpression_i.lexeme,0);
        write_TAC(RO.lexeme,0);
        write_TAC(E_v.lexeme,0);
        write_TAC(")",0);
        write_TAC("goto",0);
        write_TAC("_",1);


        BEF_v.push_back(n_line);
        // BEF = n_line;

        write_TAC("goto",0); 
        write_TAC("_",1);

        }
        else {
         syntax_error();
        }

        tabs--;

    }

    token parser::TT(){
      
        print_tabs();
        cout<<"TT"<<endl;
        tabs++;

        token TT_v;
        token MD_i;
    
        MD_i = Terminal();
        TT_v = MDExpression(MD_i);

        tabs--;
        return TT_v;
    }

 void parser::removeNL(){
    while(_lexer.peek(1).tokenType == TokenType::NL)
     _lexer.getNextToken();
 }


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////







































    // //statements-- > COLON LPAREN start RPAREN
    // if (_lexer.peek(1).tokenType == TokenType::PLUS)
    // {
    //     expect(TokenType::PLUS);
    //     if (_lexer.peek(1).tokenType == TokenType::LPAREN)
    //     {
    //         expect(TokenType::LPAREN);
    //         start();
    //         if (_lexer.peek(1).tokenType == TokenType::RPAREN)
    //         {
    //             expect(TokenType::RPAREN);
    //             return true;
    //         }
    //     }
    // }
    // return false;
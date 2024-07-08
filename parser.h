#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    vector<token> symbols;
    vector<int> symbols_address;
    vector<int> S_type;
    vector<string> S_initial_value;
    vector<int> S_id_type;

public:
    int tabs = 0;
    int addr = 0;
    int line = 0;
    int functionCount =0;
    int globalVarCount =0;
    int statementCount = 0;
    int IFCLICK = 0;


    void write_symbol_table();
    void print_tabs();

    token tempVAR() {
    static int count = 1;
    std::string result = "t" + std::to_string(count);
    count++;
    token R(result,TokenType::TEMP);
    return R;
    }

    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    void write_TAC(string lexeme, bool nl);
    void write_TAC_NS(string lexeme, bool nl);


    int countLines(){ return _lexer.lineCount(_lexer.getCurrentPointer());}
    int countStatementsInBlock(int pos, int btype);
    void countDecleration();
    void Program();
    void DeclarationList();
    void Declaration();
    void VariableDeclaration();
    token VariableAssignment();
    void FunctionDeclaration();

    void VDSpecifier(token);

    void TypeF();
    void TypeID();
    void ParameterList();
    void Parameter();
    void Block();
    void BlockF();
    void StatementList();
    void Statement();
    void removeNL();



    void BlockIF();
    void IFStatementList();
    void IFStatement();


    token Expression();
    void SelectionStatement();
    void IterativeStatement();
    void ReturnStatement();
    token FunctionCall();
    void IOStatement();

    
    void ArgumentList();
    void Argument();


    void InputStatement();
    void PrintStatement();
    void InputSpecifier();
    void InputVAR();

    void PrintArg();
    void PrintCont();
    void InOutStatement();

    void PrintVar();
    void PrintTer();
    void PS1();
    void IS1();



    void WarnaStatement();
    void PhirStatement();



    token ComparisonExpression();
    token ASExpression(token);
    token MDExpression(token);
    token Terminal();
    void RELOPExpression(token);
    token E();


    void ADDTOTABLE(token t, int type, int id_type){
        symbols.push_back(t);
        symbols_address.push_back(addr);
        S_id_type.push_back(id_type);
        if(type==1){S_type.push_back(1); addr = addr + 4;}
        else {S_type.push_back(0);addr=addr+4;}
    }

    void ADD_Initial_Value(string initial_value){
         S_initial_value.push_back(initial_value);
    }


    token TT();
    void T_();
    void F();
};
#endif

#include "lexer.h"
#include<string>
#include<iostream>
#include<string.h>
#pragma warning(disable:4996)
using namespace std;
//for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
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




token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}




token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}



void token::Print()
{
    cout << "{" << lexeme << " , "
        << reserved[(int)tokenType] << "}\n";
}


void token::PrintOnlyToken()
{
    cout << reserved[(int)tokenType]<<"\n";
}


void Print_Single_Token(token t){
     cout << "{" << t.lexeme << " , "
        << reserved[(int)t.tokenType] << "}\n";
}


int lexer::getCurrentPointer()
{
    return index;
}


void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}

void printVec(vector<char> stream) {
    ///this for printing whatwever is in the file
    vector<char>::iterator ptr;
    // Displaying vector elements using begin() and end()
    cout << "The vector elements  in printing are : ";
    for (ptr = stream.begin(); ptr < stream.end(); ptr++)
        cout << *ptr;
    cout<<endl;
}



void lexer::Tokenize()//function that tokenizes your input stream
{
    vector<char>::iterator it = stream.begin();

    vector<char> toks;
   

	//your implementation goes here
    int state = 1;
   
    for(int i =0; i< stream.size(); i++ ){

        switch(state)
        {

            //Intial State
            case 1:

            //FOR TOKEN (INT) -->DIGIT
            if( isdigit(stream[i]))
            {
                state = 2;
                toks.push_back(stream[i]);
                
                
            }


            //FOR IDENTIFIERS AND KEYWORDS
            else if(isalpha(stream[i]) || char(stream[i])=='_')
            {
                state = 4;
                toks.push_back(stream[i]);   
            }



            // //FOR TOKEN (SEMICOLON) --> ;
            // else if(char(stream[i])==';' && stream[i+1]=='\n')
            // {

            //     toks.push_back(stream[i]);
            //     state=6;
            //     i++;
            //     tokens.push_back(token(string(""), TokenType::NL));
            //     nooflines.push_back(1);
            //     toks.clear();

            // }

            //FOR TOKEN (SEMICOLON) --> ;
            else if(char(stream[i])==';' )
            {

                
                toks.push_back(stream[i]);
                state=9;
                //printVec(toks);
                //tokens.push_back(token(string(""), TokenType::SEMICOLON));
                toks.clear();
            }



            //FOR TOKEN (RELOP) --> [ < ] : LT
            else if(char(stream[i])=='<')
            {
                toks.push_back(stream[i]);
                state=5;
            }



             //FOR TOKEN (RELOP) --> [ > ] : GT
            else if(char(stream[i])=='>')
            {
                toks.push_back(stream[i]);
                state=7;
            }


            //FOR TOKEN (RELOP) --> [ = ] : EQ
            else if(char(stream[i])=='=')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string("="), TokenType::RELOP));
                nooflines.push_back(2);
                toks.clear();
            }


            //FOR TOKEN (AO) --> [ + ] : PLUS
            else if(char(stream[i])=='+')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::PLUS));
                nooflines.push_back(2);
                toks.clear();
            }

            else if(char(stream[i])=='-')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::MINUS));
                nooflines.push_back(2);
                toks.clear();
            }


            //FOR TOKEN (AO) -->  [ * ] : MULTIPLY
            else if(char(stream[i])=='*')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::MULTIPLY));
                nooflines.push_back(2);
                toks.clear();
            }

            //FOR TOKEN (AO) -->  [ / ] : DIVIDE
            else if(char(stream[i])=='/')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::DIVIDE));
                nooflines.push_back(2);
                toks.clear();
            }



            //FOR TOKEN (AO) -->  [ % ] : MODULUS
            else if(char(stream[i])=='%')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::MODOLUS));
                nooflines.push_back(2);
                toks.clear();
            }


            //FOR TOKEN (AO) --> [ | ] : PIPE
            else if(char(stream[i])=='|')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::PIPE));
                nooflines.push_back(2);
                toks.clear();
            }

              //FOR TOKEN (SC) --> [ ( ] : LPAREN
            else if(char(stream[i])=='(')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::LPAREN));
                nooflines.push_back(2);
                toks.clear();
            }

              //FOR TOKEN (SC) --> [ ) ] : RPAREN
            else if(char(stream[i])==')')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::RPAREN));
                nooflines.push_back(2);
                toks.clear();
            }


            //FOR TOKEN (SC) --> [ ) ] : RPAREN
            else if(char(stream[i])=='\n')
            {
                //toks.push_back(stream[i]);
                state=10;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::NL));
                toks.clear();
            }



            //FOR TOKEN (SC) --> [ @ ] : AT
            else if(char(stream[i])=='@')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::AT));
                nooflines.push_back(2);
                toks.clear();
            }



            //FOR TOKEN (assignment operator) --> [ : ][ = ] : ASSIGNOP
            else if(char(stream[i])==':' && stream[i + 1]=='=')
            {
                toks.push_back(stream[i]);
                toks.push_back(stream[i + 1]);
                i++;
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(""), TokenType::ASSIGNOP));
                nooflines.push_back(2);
                toks.clear();
            }



            //FOR TOKEN STRING 
            //BACK TICK
            else if(char(stream[i])=='`')
            {
                toks.push_back(stream[i]);
                state=8;
                //printVec(toks);
                //tokens.push_back(token(string(""), TokenType::BACKTICK));
                toks.clear();
            }


            break;
            //FOR DIGITS ONLY
            case 2:
            if(isdigit(stream[i]))
            {
                state = 2;
                toks.push_back(stream[i]);
            }
            else
            {         
                //printVec(toks);
                string str(toks.begin(),toks.end());
                tokens.push_back(token(string(str), TokenType::INT));
                nooflines.push_back(2);
                toks.clear();
                state = 3;
            }    
            break;    

            case 4:
            if(isalnum(stream[i]) || char(stream[i])=='_')
            {
                state = 4;
                toks.push_back(stream[i]);
            }
            else
            {     

                //printVec(toks);
                string str1(toks.begin(),toks.end());
                const char* str = str1.c_str();
                if(strcmp(str,"markazi")==0)
                {
                    tokens.push_back(token(string(""), TokenType::MARKAZI));nooflines.push_back(2);
                }
                else if(strcmp(str,"kaam")==0)
                {
                    tokens.push_back(token(string(""), TokenType::KAAM));nooflines.push_back(2);
                }
               
                else if(strcmp(str,"karo")==0)
                {
                    tokens.push_back(token(string(""), TokenType::KARO));nooflines.push_back(2);
                }
                else if(strcmp(str,"rakho")==0)
                {
                    tokens.push_back(token(string(""), TokenType::RAKHO));nooflines.push_back(2);
                }
                else if(strcmp(str,"jab")==0)
                {
                    tokens.push_back(token(string(""), TokenType::JAB));nooflines.push_back(2);
                }
                else if(strcmp(str,"tak")==0)
                {
                    tokens.push_back(token(string(""), TokenType::TAK));nooflines.push_back(2);
                }
                else if(strcmp(str,"bas")==0)
                {
                    tokens.push_back(token(string(""), TokenType::BAS));nooflines.push_back(2);
                }
                else if(strcmp(str,"agar")==0)
                {
                    tokens.push_back(token(string(""), TokenType::AGAR));nooflines.push_back(2);
                }
                else if(strcmp(str,"to")==0)
                {
                    tokens.push_back(token(string(""), TokenType::TO));nooflines.push_back(2);
                }
                else if(strcmp(str,"warna")==0)
                {
                    tokens.push_back(token(string(""), TokenType::WARNA));nooflines.push_back(2);
                }
                else if(strcmp(str,"phir")==0)
                {
                    tokens.push_back(token(string(""), TokenType::PHIR));nooflines.push_back(2);
                }
                else if(strcmp(str,"dekhao")==0)
                {
                    tokens.push_back(token(string(""), TokenType::DEKHAO));nooflines.push_back(2);
                }
                else if(strcmp(str,"lo")==0)
                {
                    tokens.push_back(token(string(""), TokenType::LO));nooflines.push_back(2);
                }
                else if(strcmp(str,"chalao")==0)
                {
                    tokens.push_back(token(string(""), TokenType::CHALAO));nooflines.push_back(2);
                }
                else if(strcmp(str,"bhaijo")==0)
                {
                    tokens.push_back(token(string(""), TokenType::BHAIJO));nooflines.push_back(2);
                }
                else if(strcmp(str,"adad")==0)
                {
                    tokens.push_back(token(string(""), TokenType::ADAD));nooflines.push_back(2);
                }
                else if(strcmp(str,"khali")==0)
                {
                    tokens.push_back(token(string(""), TokenType::KHALI));nooflines.push_back(2);
                }
                else if(strcmp(str,"wapas")==0)
                {
                    tokens.push_back(token(string(""), TokenType::WAPAS));nooflines.push_back(2);
                }
                else if(strcmp(str,"khatam")==0)
                {
                    tokens.push_back(token(string(""), TokenType::KHATAM));nooflines.push_back(2);
                }
                else
                {
                    string str2(toks.begin(),toks.end());
                    tokens.push_back(token(string(str2), TokenType::ID));nooflines.push_back(2);
                }

                toks.clear();
                state = 3;

            }    
            break;


            // FOR
            // RELATIONAL
            // OPERATORS
            // STATE 5 and 7

            // LESS THAN ONWARDS
            case 5:
            //FOR TOKEN (RELOP) --> = ;
            if(char(stream[i])=='=')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string("<="), TokenType::RELOP));nooflines.push_back(2);
                toks.clear();
            }

             //FOR TOKEN (RELOP) --> > ;
            else if(char(stream[i])=='>')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string("!="), TokenType::RELOP));nooflines.push_back(2);
                toks.clear();
            }

            else if(char(stream[i])=='<')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string("O"), TokenType::IO));nooflines.push_back(2);
                toks.clear();
            }

            else{
                state=3;
                //printVec(toks);
                tokens.push_back(token(string("<"), TokenType::RELOP));nooflines.push_back(2);
                toks.clear();
            }
            break;

            //GREATER THAN ONWARDS
            case 7:
            //FOR TOKEN (RELOP) --> = ;
            if(char(stream[i])=='=')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string(">="), TokenType::RELOP));nooflines.push_back(2);
                toks.clear();
            }
            else if(char(stream[i])=='>')
            {
                toks.push_back(stream[i]);
                state=6;
                //printVec(toks);
                tokens.push_back(token(string("I"), TokenType::IO));nooflines.push_back(2);
                toks.clear();
            }
            else{

                state=3;
                //printVec(toks);
                tokens.push_back(token(string("GT"), TokenType::RELOP));nooflines.push_back(2);
                toks.clear();

            }
            break;


            case 8:
            //STRING FINISH ENDING BACKTICKS
            if(stream[i]!='`')
            {
                toks.push_back(stream[i]);
                state=8;
            }
            else if(stream[i]=='`')
            {
                //printVec(toks);
                string str(toks.begin(),toks.end());
                tokens.push_back(token(string(str), TokenType::STRING));nooflines.push_back(2);
                toks.clear();
                //tokens.push_back(token(string(""), TokenType::BACKTICK));
                //toks.clear();
                state = 6;
            }
            break;




            case 9:
            //COMMENTS 
            if(stream[i]!='\n')
            {
                toks.push_back(stream[i]);nooflines.push_back(1);
                state=9;
            }
            else if(stream[i]=='\n')
            {
                string stri(toks.begin(),toks.end());
               // if(tokens.back().tokenType!=TokenType::NL)
                tokens.push_back(token(string(""), TokenType::NL));
                nooflines.push_back(1);
                toks.clear();
                state = 6;
            }
            break;


            case 10:
            if(stream[i]=='\n')
            {
                tokens.push_back(token(string(""), TokenType::NL));
                state=10;nooflines.push_back(1);
            }
            else if(stream[i]!='\n')
            {
                //string stri(toks.begin(),toks.end());
                // cout<<"Them = ";
                // tokens.back().Print();
                //if(tokens.back().tokenType!=TokenType::NL)
                //tokens.push_back(token(string(""), TokenType::NL));
                nooflines.push_back(1);
                toks.clear();
                state = 3;
            }
            break;


            //--i represent that the element on which we have arrive must be checked again
            //Final State (  )
            case 6:
            // //printVec(toks);
            // toks.clear();
            i--;
            state=1;
            break;




            //Final State  ( * )
            case 3:
            i=i-2;
            state=1;
            break;

        }
        
    }

	//push_back EOF token at end to identify End of File
     tokens.push_back(token(string(""), TokenType::END_OF_FILE));

    //cout<<"TOKEN LENGHT = "<<tokens.size()<<endl;
}



lexer::lexer(const char filename[])
{
    //constructors: takes file name as an argument and store all
    //the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) //if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { //store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' ');//dummy spaces appended at the end
        stream.push_back(' ');
        //Tokenize function to get all the (token,lexeme) pairs
        
        
        
        ///this for printing whatwever is in the file
        vector<char>::iterator ptr;
        
        Tokenize();
        //assigning tokens to iterator::pointer
        index = 0;
    }
}



lexer::lexer()
{
    index = -1;
}




void lexer::printRaw()
{
    //helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;

}





token lexer::getNextToken()
{
    //this function will return single (token,lexeme) pair on each call
    //this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}




void lexer::resetPointer()
{
    index = 0;
}





token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                                 // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}

#include <iostream>
#include "parser.h"
#include "parser.cpp"
#include "lexer.cpp"
#include "lexer.h"
#include "VM.h"
#include "VM.cpp"
using namespace std;


//HI TA, OF YOU ARE RUNNING IT ON LINUX KINDLY COMMENT LINE 3 ,4 ,7  all  #include "--.cpp" waly header

// GIVE THREE CMD ARGS    ./main.exe  sample_code.ru  TAC.txt


int main(int argc, char* argv[])
{
	//asking for file name as command line arguments
	if (argc == 3)
	{

		parser _parser(argv[1]);
		VM vm(argv[2]);

        //Lexer is in Parser
        // lexer _lexer(argv[1]);
		// token t;
		// t = _lexer.getNextToken();

		// while (t.tokenType != TokenType::END_OF_FILE)
		// {
		// 	t.Print();
		// 	t = _lexer.getNextToken();
		// }

	}
	else if (argc > 3)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}

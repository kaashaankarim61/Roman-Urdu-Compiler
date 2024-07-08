Assignment 1:

First, we created a single DFA for identifiers, integers, strings, comments, relational operators, and IO operators. Then, we moved on to write the regular definitions of these by consulting the DFA. Lastly, we did the coding part by writing a program that identifies tokens and their respective lexemes for keywords, relational operators, special characters, arithmetic operators, other constructs, strings, comments, assignment operators, starting blocks, closing blocks, and IO operators. We followed both the DFA (i.e., its states represent cases) and the regular definitions (i.e., for token names) while coding for identifiers, integers, strings, comments, relational operators, and IO operators, while the others were done independently. We did not encounter any problems while doing the assignment and were able to complete it without any hassle.

Assignment 2:

First, we created a CFG for the Roman Urdu language and then converted it into LL(1) grammar by setting operator precedence and association, removing left recursion and ambiguity, and left factoring. After that, we wrote the code to implement the parser by following the LL(1) grammar. Next, we generated a parse tree as well. We did not encounter any problems while doing the assignment and were able to complete it without any hassle.

Assignment 3:

First, we created a rough translation scheme for the Roman Urdu language and then used it to test three-address code. After that, we finalized our output actions and included these actions in our grammar file. We created a symbol table and three-address code using output actions, which include the use of vectors and variables. In the three-address code, we used temporary variables for computation. Due to an update in the assignment, we faced a huge problem and panicked. We had completed the assignment long before as per the requirements. On the due date, when we were about to submit the assignment, we saw an update in the three-address code example and symbol table, which required us to commit a lot of changes to our assignment.

Assignment 4:

I have done the following steps:

1. Read TAC.txt line by line into a vector\<string\>.
2. Cleaned it by removing more than one empty space.
3. Removed unnecessary things.
4. Tokenized the strings of each line based on space (but replaced `$` with space in our string).
5. Stored it in an Opcode class, which contains 6 tokens of type string.
6. From the symbol table file, I made a multi-level symbol table for every function.
7. Based on these tokens, translated the code into QUAD OPCODE, which also is a structure containing 4 OPs of type string.
8. Made a data segment for every function and mapped the addresses in the quad.
9. Executed the code based on operations and Operand1.
10. Function calls are done using the stack segment; every function has a different stack segment.
11. The code runs fine, and everything is fine.
12. As function calls were optional, bonus marks should be given.
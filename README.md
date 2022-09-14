
# Lexical Analyzer in CPP
A c++ program that takes input a `.c` or `.cpp` program file and writes the **tokens** present in it in a file. It also creates a **symbol table** for the program.

 - **Lexical Analysis** is the process of converting a sequence of characters into a sequence of **Lexical Tokens** 
 - A program that performs lexical analysis is  termed as **Lexical Analyzer**
 
## System requirements
 
C++ 11  or higher to compile the code
Unix users can run the following command to install latest version of C++ compiler
```bash
sudo apt-get install g++
```

## How to run?
1. `cd` to this project

2. Compile  with C++ 11
	- Run the following command in terminal `g++ -std=c++11 FSM.cpp -o FSM`
OR
	- Run `make` command if MakeFile is supported in your system
3. Run the executable with input the input file as follows
```
./FSM < inputProgram
```

4. Following two files will be generated:
	1.	`pa_1.out`
	This file contains description of tokens in the following format 
	```<token> <token_id>```
	2. `symbol_table_1.out`
	 This file contains identifiers and keywords in the following format 
	```<token> 1``` if token is an identifier
	```<token> 0``` if token is a keyword
	**The tokens are identified as defined in `def.h` file**


## Flow of the code
1. The input file is read character by character and stored in buffer string.
2. The string is preprocessed using `removeComments()` routine to remove comments enclosed between `/*` and `*/`.
3. The `lexicalAnalysis` is function then performs the tokenization.
4. We make use of `lexemeBegin` and `forwardPtr` which keeps track of the index we have to start scannnig from and the end index of token we are currently considering respectively.
5. In each iteration, we find the maximum length token we can get that starts from index pointed by `lexemeBegin`. We skip the iteration if the character pointed by `lexemeBegin` is a white space, which is checked using `isWhiteSpace()` routine.
6. If a token is found, we write it in the required format in the `pa_1.out` file and update the `symbol_table_1.out` if the token found is an identifer or keyword.
7. If no token is found, then we `exit(1)` denoting a failure in analysing the code.

## Functions used
```cpp
int isKeyword(const string&);
int isIdentifier(const string&);
int isIntegerConstant(const string&);
int isFloatingConstant(const string&);
int isArithmeticOperator(const string&);
int isAssignmentOperator(const string&);
int isRelationalOperator(const string&);
int isSpecialSymbol(const string&);
int matchToken(int, int); // returns token_id if token is found in the substring [L,R] else return -1 
bool isWhiteSpace(char);
void lexicalAnalysis();
void removeComments();
```
All the functions are self-explanatory.
### Finite State Machine of some tokens
1. **Identifier**
![identifier](https://raw.githubusercontent.com/prajapati-sumit/images/main/identifier.jpg)

2. **Integer Constant**
![integer](https://raw.githubusercontent.com/prajapati-sumit/images/main/integer.jpg)

3. **Floating Constant**
![floating](https://raw.githubusercontent.com/prajapati-sumit/images/main/floating.jpg)
## Sample
For the given `input.in` file, the analyzer generates following two files

1. **`symbol_table_1.out`**
```cpp
int 0
main 1
x 1
i 1
ans 1
for 0
return 0
n 1
 ```
2.  **`pa_1.out`**
```py
423 int
300 main
418 (
419 )
416 {
423 int
300 x
311 =
301 4
420 ,
300 i
311 =
301 0
420 ,
300 ans
311 =
301 0
421 ;
430 for
418 (
300 i
311 =
301 0
421 ;
300 i
307 <
300 x
421 ;
300 i
304 ++
419 )
300 ans
316 +=
301 4
421 ;
433 return
300 ans
421 ;
417 }
430 for
418 (
423 int
300 i
311 =
301 0
421 ;
300 i
307 <
300 n
421 ;
300 i
304 ++
419 )
```
## Authors

* **Sumit Kumar Prajapati (B20CS074)**  - [prajapati.3@iitj.ac.in](prajapati.3@iitj.ac.in)
* **Pratul Singh (B20CS095)**  - [singh.142@iitj.ac.in](singh.142@iitj.ac.in)

## References 
- https://web.stanford.edu/class/cs143/
- https://app.diagrams.net/

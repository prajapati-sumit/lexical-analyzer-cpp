#include "def.h"
#include <map>
#include <set>
#include <string>
using namespace std;
const map<string, int> KEYWORDS {
    {"short", SHORT},
    {"int", INT},
    {"float", FLOAT},
    {"double", DOUBLE},
    {"bool", BOOL},
    {"char", CHAR},
    {"signed", SIGNED},
    {"unsigned", UNSIGNED},
    {"for", FOR},
    {"while", WHILE},
    {"do", DO},
    {"return", RETURN},
    {"void", VOID},
    {"switch", SWITCH},
    {"break", BREAK},
    {"case" , CASE},
    {"continue", CONTINUE},
    {"goto", GOTO},
    {"long", LONG},
    {"static", STATIC},
    {"union", UNION},
    {"default", DEFAULT},
    {"if", IF},
    {"else", ELSE},
};
const map<string, int> ARITHMETIC_OPERATORS{
    {"+", PLUS},
    {"-", MINUS},
    {"*", MULT},
    {"/", DIV},
    {"%", PERCENT},
    {"++", PLUS_PLUS},
    {"--", MINUS_MINUS}
};
const map<string, int>ASSIGNMENT_OPERATORS{
    {"=", EQ},
    {"+=", PLUS_EQ},
    {"-=", MINUS_EQ},
    {"*=", MULT_EQ},
    {"/=", DIV_EQ}
};
const map<string, int>RELATIONAL_OPERATORS{
    {"<", LESSER},
    {">", GREATER},
    {"<=", LESS_EQ},
    {">=", GREAT_EQ},
    {"==", EQ_EQ}
};

const map<string, int>SPECIAL_SYMBOLS{
    {"(", L_CBRACE},
    {")", R_CBRACE} ,
    {",", COMMA},
    {"[", L_SQUARE},
    {"]", R_SQUARE},
    {"{", L_PARAEN},
    {"}", R_PARAEN},
    {";", SEMICOL}
};
set<string>symbols;
string buffer;
int bufferLen;

int isKeyword(const string&);
int isIdentifier(const string&);
int isIntegerConstant(const string&);
int isFloatingConstant(const string&);
int isArithmeticOperator(const string&);
int isAssignmentOperator(const string&);
int isRelationalOperator(const string&);
int isSpecialSymbol(const string&);
int matchToken(int, int);
bool isWhiteSpace(char);
void lexicalAnalysis();
void removeComments();
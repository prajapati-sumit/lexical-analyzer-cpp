#include <iostream>
#include <ctype.h>
#include "def.h"
#include "util.h"
using namespace std;


int isKeyword(const string& token) {
    if (KEYWORDS.find(token) != KEYWORDS.end())
        return KEYWORDS.at(token);
    return NOTOK;
}
int isIdentifier(const string& token) {
    int n = token.length();
    if (n == 0)
        return NOTOK;
    int i = 0;
    if (token[i] != '_' && !isalpha(token[i]))
        return NOTOK;
    if (n >= 2 && token[0] == '_' && token[1] == '_')
        return NOTOK;
    for (; i < n; i++)
        if (token[i] != '_' && !isalpha(token[i]))
            return NOTOK;
    return IDNTIFIER;
}
int isIntegerConstant(const string& token) {
    int n = token.length();
    if (n == 0)
        return NOTOK;
    int i = 0;
    if (token[i] == '-')
        i++;
    for (; i < n; i++) {
        if (!isdigit(token[i]))
            return NOTOK;
    }
    return INT_CONST;

}
int isFloatingConstant(const string& token) {
    int n = token.length();
    if (n == 0)
        return NOTOK;
    int i = 0;
    if (token[i] == '-')
        i++;
    int cnt = 0;
    for (; i < n; i++) {
        if (token[i] == '.')
            cnt++;
        else if (!isdigit(token[i]))
            return NOTOK;
    }
    return cnt == 1 ? FLO_CONST : NOTOK;
}
int isArithmeticOperator(const string& token) {
    if (ARITHMETIC_OPERATORS.find(token) != ARITHMETIC_OPERATORS.end())
        return ARITHMETIC_OPERATORS.at(token);
    return NOTOK;
}
int isAssignmentOperator(const string& token) {
    if (ASSIGNMENT_OPERATORS.find(token) != ASSIGNMENT_OPERATORS.end())
        return ASSIGNMENT_OPERATORS.at(token);
    return NOTOK;
}
int isRelationalOperator(const string& token) {
    if (RELATIONAL_OPERATORS.find(token) != RELATIONAL_OPERATORS.end())
        return RELATIONAL_OPERATORS.at(token);
    return NOTOK;
}
int isSpecialSymbol(const string& token) {
    if (SPECIAL_SYMBOLS.find(token) != SPECIAL_SYMBOLS.end())
        return SPECIAL_SYMBOLS.at(token);
    return NOTOK;
}
int matchToken(int L, int R) {

    string token = buffer.substr(L, R - L + 1);
    int tokenCode = NOTOK;
    if ((tokenCode = isKeyword(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isIdentifier(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isIntegerConstant(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isFloatingConstant(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isArithmeticOperator(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isAssignmentOperator(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isRelationalOperator(token)) != NOTOK)
        return tokenCode;
    if ((tokenCode = isSpecialSymbol(token)) != NOTOK)
        return tokenCode;
    return tokenCode;
}
bool isWhiteSpace(char c) {
    return c == ' ' || c == '\n' || c == '\r';
}
// utility function that performs lexical analysis
void lexicalAnalysis() {

    FILE* pa_1 = fopen("pa_1.out", "w");
    FILE* symbol_table_1 = fopen("symbol_table_1.out", "w");

    int lexemeBegin = 0;
    int forwardPtr = 0;
    int validTokenEndIndex;
    int validTokenCode;

    while (lexemeBegin < bufferLen) {
        // ignore whitespaces
        if (isWhiteSpace(buffer[lexemeBegin])) {
            lexemeBegin++;
            continue;
        }
        for (forwardPtr = lexemeBegin, validTokenCode = NOTOK, validTokenEndIndex = -1; forwardPtr < bufferLen; forwardPtr++) {
            int code = matchToken(lexemeBegin, forwardPtr);
            // if found a valid token
            if (code != NOTOK) {
                validTokenEndIndex = forwardPtr;
                validTokenCode = code;
            }
        }
        // no valid token found
        if (validTokenCode == NOTOK) {
            fprintf(stderr, "Error analysing the code starting from character %c (character %d)\n", buffer[lexemeBegin], lexemeBegin);
            exit(1);
        }

        // filling token file
        int tokenLength = validTokenEndIndex - lexemeBegin + 1;
        string token = buffer.substr(lexemeBegin, tokenLength);
        fprintf(pa_1, "%d %s\n", validTokenCode, token.c_str());

        // filling symbol table
        int keywordOrIdentifier = -1;
        if (validTokenCode == IDNTIFIER) {
            keywordOrIdentifier = 1;
        }
        else if (isKeyword(token) != NOTOK) {
            keywordOrIdentifier = 0;
        }
        if (keywordOrIdentifier != -1 && !symbols.count(token)) {
            symbols.insert(token);
            fprintf(symbol_table_1, "%s %d\n", token.c_str(), keywordOrIdentifier);
        }

        lexemeBegin = validTokenEndIndex + 1;
    }
    fprintf(stdout, "Lexical Analsis Completed Successfully\npa_1.out and symbol_table_1.out written\n");
}
// removes comment from the given input file enclosed between /* and */
void removeComments() {
    string tmp;
    bool startOfComment = false;

    for (int i = 0; i < bufferLen; i++) {
        // start of comment
        if (i + 1 < bufferLen && buffer[i] == '/'  && buffer[i + 1] == '*')
            startOfComment = true;
        if (!startOfComment) {
            tmp.push_back(buffer[i]);
        }
        // end of comment
        if (i - 1 >= 0 && buffer[i - 1] == '*' && buffer[i] == '/')
            startOfComment = false;

    }
    buffer = tmp;
}
int main() {
    // reading entire content of file as single string
    char c;
    while (cin.get(c))
        buffer.push_back(c);
    bufferLen = buffer.length();
    removeComments();
    lexicalAnalysis();
    return 0;
}
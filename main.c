#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    char type[30];
    char lexeme[50];
    int line;
    int column;
} Token;

Token getNextToken(FILE *inputFile, int *line, int *column)
{
    Token token;
    
    char c = fgetc(inputFile);

    while (isspace(c) || c == '\n')
    {
        if (c == '\n')
        {
            *line = (*line) + 1;
            *column = 1;
            c = ' ';
        }
        else
        {
            c = getc(inputFile);
        }
    }

    token.line = *line;
    token.column = *column;
    token.lexeme[0] = c;
    if (isalpha(c) || c == '_')
    {
        int i = 0;
        while (isalnum(c) || c == '_')
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            if (c == '\n')
            {
                *line = (*line) + 1;
                *column = 0;
            }
            i++;
        }
        token.lexeme[i] = '\0';
        if (c != '\n' && c != ' ')
        {
            ungetc(c, inputFile);
        }

        if (strncmp(token.lexeme, "int", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_INT");
        }
        else if (strncmp(token.lexeme, "float", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_FLOAT");
        }
        else if (strncmp(token.lexeme, "char", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_CHAR");
        }
        else if (strncmp(token.lexeme, "double", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DOUBLE");
        }
        else if (strncmp(token.lexeme, "struct", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_STRUCT");
        }
        else if (strncmp(token.lexeme, "while", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_WHILE");
        }
        else if (strncmp(token.lexeme, "do", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DO");
        }
        else if (strncmp(token.lexeme, "for", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_FOR");
        }
        else if (strncmp(token.lexeme, "if", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_IF");
        }
        else if (strncmp(token.lexeme, "else", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_ELSE");
        }
        else if (strncmp(token.lexeme, "switch", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_SWITCH");
        }
        else if (strncmp(token.lexeme, "case", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_CASE");
        }
        else if (strncmp(token.lexeme, "default", strlen(token.lexeme)) == 0)
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_DEFAULT");
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_IDENTIFIER");
        }
    }
    else if (isdigit(c))
    {
        int i = 0;
        while (isdigit(c))
        {
            token.lexeme[i] = c;
            c = getc(inputFile);
            if (c == '\n')
            {
                *line = (*line) + 1;
                *column = 0;
            }
            i++;
        }
        token.lexeme[i] = '\0';
        if (c != '\n' && c != ' ')
        {
            ungetc(c, inputFile);
        }
        *column = (*column) + 1;
        strcpy(token.type, "TK_NUMBER");
    }
    else if (c == '+')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_PLUS");
    }
    else if (c == '-')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_MINUS");
    }
    else if (c == '*')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_MULTIPLY");
    }
    else if (c == '/')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_DIVIDE");
    }
    else if (c == '%')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_MODULO");
    }
    else if (c == '=')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_EQUAL");
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_ASSIGN");
            ungetc(c, inputFile);
        }
    }
    else if (c == '<')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LESS_THAN_EQUAL");
            token.lexeme[1] = '=';
        }
        else if (c == '<')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_LEFT_SHIFT");
            token.lexeme[1] = '<';
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LESS_THAN");
            ungetc(c, inputFile);
        }
    }
    else if (c == '>')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_GREATER_THAN_EQUAL");
            token.lexeme[1] = '=';
        }
        else if (c == '>')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_RIGHT_SHIFT");
            token.lexeme[1] = '>';
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_GREATER_THAN");
            ungetc(c, inputFile);
        }
    }
    else if (c == '!')
    {
        c = getc(inputFile);
        if (c == '=')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_NOT_EQUAL");
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_NOT");
            ungetc(c, inputFile);
        }
    }
    else if (c == '&')
    {
        c = getc(inputFile);
        if (c == '&')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LOGICAL_AND");
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_AND");
            ungetc(c, inputFile);
        }
    }
    else if (c == '|')
    {
        c = getc(inputFile);
        if (c == '|')
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_LOGICAL_OR");
            token.lexeme[1] = c;
        }
        else
        {
            *column = (*column) + 1;
            strcpy(token.type, "TK_BITWISE_OR");
            ungetc(c, inputFile);
        }
    }
    else if (c == '^')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_BITWISE_XOR");
    }
    else if (c == '(')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LPAREN");
    }
    else if (c == ')')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RPAREN");
    }
    else if (c == '{')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LBRACE");
    }
    else if (c == '}')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RBRACE");
    }
    else if (c == '[')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_LBRACKET");
    }
    else if (c == ']')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_RBRACKET");
    }
    else if (c == ';')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_SEMICOLON");
    }
    else if (c == '~')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_~");
    }
    else if (c == '.')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_DOT");
    }
    else if (c == ':')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_DOUBLE_DOT");
    }
    else if (c == ',')
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_COMMA");
    }
    else if (c == EOF)
    {
        *column = (*column) + 1;
        strcpy(token.type, "TK_EOF");
        token.lexeme[0]='|';
        token.lexeme[1]='n';
        
    }
    else
    {
        // Error handling for unrecognized characters
        printf("Error: Unrecognized character '%c' at line %d, column %d\n", c, *line, *column);
        *column = (*column) + 1;
        strcpy(token.type, "TK_EOF");
    }
    return token;
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening input or output file.\n");
        return 1;
    }

    Token token;

    int lineCount = 1, columnCount = 1;
    int tokenCount = 0;
    printf("| Linha \t | Coluna: \t | Lexeme: \t | Token \t |\n");
    fprintf(outputFile, "| Linha \t | Coluna: \t | Lexeme: \t | Token \t |\n");
    do
    {
        token = getNextToken(inputFile, &lineCount, &columnCount);
        printf("| %d \t\t | %d \t\t | %s \t\t | %s \t \n", token.line, token.column, token.lexeme, token.type);
        fprintf(outputFile, "| %d \t\t | %d \t\t | %s \t\t| %s \t \n", token.line, token.column, token.lexeme, token.type);
        tokenCount++;
    } while (strcmp(token.type, "TK_EOF") != 0);

    printf("Total tokens: %d\n", tokenCount);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                         "do", "double", "else", "enum", "extern", "float", "for", "goto",
                         "if", "int", "long", "register", "return", "short", "signed",
                         "sizeof", "static", "struct", "switch", "typedef", "union",
                         "unsigned", "void", "volatile", "while"};

char operators[] = "-+=*%/";
char symbols[11] = {'(', ')', '[', ']', ',', ';', ':', '"', '\'', '{', '}'};
int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

char error_messages[100][5];
int error_messages_top_index = 0;

char prev_symbol = ' ';
char current_symbol = ' ';

int is_keyword(char buffer[])
{
    int flag = 0;
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(buffer, keywords[i]) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int is_identifier(char buffer[])
{
    int flag = 0;
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (i == 0)
        {
            if (buffer[i] != '_' && isalpha(buffer[i]) == 0)
            {
                flag = 1;
                break;
            }
        }
        else
        {
            if (buffer[i] != '_' && isalpha(buffer[i]) == 0 && isdigit(buffer[i]) == 0)
            {

                flag = 1;
                break;
            }
        }
    }

    if (flag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int is_operator(char ch)
{
    int flag = 0;
    for (int i = 0; i < strlen(operators); i++)
    {
        if (ch == operators[i])
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int is_constant(char buffer[])
{
    int flag = 0;
    if (prev_symbol == '"' || prev_symbol == '\'')
    {
        if (current_symbol == '"' || current_symbol == '\'')
        {
            if (current_symbol == prev_symbol)
            {
                prev_symbol = ' ';

                return 1;
            }
        }
    }
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (isdigit(buffer[i]) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int is_symbol(char ch)
{
    int flag = 0;
    for (int i = 0; i < strlen(symbols); i++)
    {

        if (ch == symbols[i])
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void main()
{
    char ch, buffer[32];
    FILE *fprogram;
    int buffer_top_index = 0;
    int lexeme_end_flag = 0;
    int flag = 0;

    fprogram = fopen("program.txt", "r");
    if (fprogram == NULL)
    {

        printf("Unable to open file.");
        exit(0);
    }

    while ((ch = fgetc(fprogram)) != EOF)
    {

        current_symbol = ch;

        if (isalnum(ch) || ch == '_')
        {
            buffer[buffer_top_index++] = ch;
        }

        else if (((is_symbol(ch) || is_operator(ch) || ch == ' ') && (prev_symbol != '"' && prev_symbol != '\'')) || ((prev_symbol == '"' && current_symbol == '"') || (prev_symbol == '\'' || current_symbol == '\'')))
        {
            buffer[buffer_top_index++] = '\0';
            lexeme_end_flag = 1;
            buffer_top_index = 0;
        }
        else if ((prev_symbol == '"' && current_symbol != '"') || (prev_symbol == '\'' && current_symbol != '\''))
        {
            buffer[buffer_top_index++] = ch;
        }

        if (lexeme_end_flag == 1)
        {
            if (strlen(buffer) > 0)
            {

                if (is_keyword(buffer))
                {
                    printf("< %s , keyword >\n", buffer);
                    lexeme_end_flag = 0;
                    buffer[0] = '\0';
                }
                else if (is_constant(buffer))
                {
                    printf("< %s , constant >\n", buffer);
                    lexeme_end_flag = 0;
                    buffer[0] = '\0';
                    prev_symbol = ' ';
                }
                else if (is_identifier(buffer) && prev_symbol != '"' && prev_symbol != '\'')
                {
                    printf("< %s , identifier >\n", buffer);
                    lexeme_end_flag = 0;
                    buffer[0] = '\0';
                }
            }
        }

        if (is_operator(ch))
        {
            printf("< %c , operator >\n", ch);
            lexeme_end_flag = 1;
        }
        else if (is_symbol(ch) && (prev_symbol != '"' || prev_symbol != '\''))
        {
            printf("< %c >\n", ch);
            prev_symbol = ch;
        }

        if (lexeme_end_flag == 1)
        {
            lexeme_end_flag = 0;
            buffer[0] = '\0';
        }
    }
}

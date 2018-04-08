#include "Lexer.h"

namespace
{
    void PushWord(std::vector<std::string> &expr, std::string &word)
    {
        if (!word.empty())
        {
            expr.push_back(word);
            word.clear();
        }
    }

    void JumpIter(
        std::string_view::const_iterator &i,
        const std::string_view::const_iterator &j,
        std::vector<std::string> &expr,
        std::string &word)
    {
        PushWord(expr, word);
        word += *i;
        word += *j;
        PushWord(expr, word);
        i = j;
    }
}

std::vector<std::string> Lexer::Split(const std::string_view &line)
{
    std::vector<std::string> result;
    std::string word;
    bool isStr = false;
    char str = ' ';
    for (auto i = line.cbegin(); i < line.cend(); ++i)
    {
        if (*i == '\'' || *i == '"')
        {
            if (isStr && *i == str)
            {
                word += *i;
                PushWord(result, word);
                isStr = false;
                continue;
            }
            if (!isStr)
            {
                str = *i;
                isStr = true;
            }
        }
        if (isStr)
        {
            word += *i;
            continue;
        }
        switch (*i)
        {
        case '!':
        case '+':
        case '-':
        case '*':
        case '/':
        case '>':
        case '<':
        case '=':
        case '^':
            if (*(i + 1) == '=')
            {
                JumpIter(i, i + 1, result, word);
                continue;
            }
            if (!*(i + 1))
            {
                auto j = i;
                while (!(*++j))
                    ;
                if (*j == '=')
                {
                    JumpIter(i, j, result, word);
                    continue;
                }
            }
        case '&':
        case '|':
        case ':':
        case '[':
        case ']':
        case '{':
        case '}':
        case '(':
        case ')':
            //case '.':
        case ',':
            PushWord(result, word);
            word += *i;
            PushWord(result, word);
            continue;
        case '\n':
        case ' ':
            PushWord(result, word);
            continue;
        }
        word += *i;
    }
    PushWord(result, word);
    return result;
}


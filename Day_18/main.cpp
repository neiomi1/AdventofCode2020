#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

void consume(std::stack<int64_t>& operands, std::stack<char>& operators)
{
    char op = operators.top();
    if (op == '(')
        return;

    operators.pop();

    int64_t a = operands.top();
    operands.pop();
    int64_t b = operands.top();
    operands.pop();

    switch (op) {
    case '*':
        operands.push(a * b);
        break;
    case '+':
        operands.push(a + b);
        break;
    }
}

int64_t evaluate(const char* expression, const std::unordered_map<char, int>& precedence)
{
    std::stack<int64_t> operands;
    std::stack<char> operators;

    while (*expression) {
        while (*expression == ' ')
            ++expression;

        switch (*expression) {
        case '+':
        case '*':
            if (operators.size() && precedence.at(operators.top()) >= precedence.at(*expression)) {
                consume(operands, operators);
            }
        case '(':
            operators.push(*expression);
            break;
        case ')':
            while (operators.top() != '(') {
                consume(operands, operators);
            }
            operators.pop();
            break;
        default:
            int n = *expression - '0';
            while (std::isdigit(expression[1])) {
                ++expression;
                n = n * 10 + (*expression - '0');
            }
            operands.push(n);
            break;
        }

        ++expression;
    }

    while (operators.size()) {
        consume(operands, operators);
    }

    return operands.top();
}

int main()
{
    std::fstream file("../../../../Day_18/input.txt");
    std::string line;
    int64_t sum1 = 0, sum2 = 0;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
        if (!line[0])
            continue;
        sum1 += evaluate(line.c_str(), { { '*', 1 }, { '+', 1 }, { '(', 3 } });
        sum2 += evaluate(line.c_str(), { { '*', 1 }, { '+', 2 }, { '(', 3 } });
    }

    std::cout << "1: " << sum1 << std::endl;
    std::cout << "2: " << sum2 << std::endl;

    return 0;
}
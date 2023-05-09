#include <iostream>
#include <stack>

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &rpn)
{
    *this = rpn;
}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &rpn)
{
    (void)rpn;
    return (*this);
}

t_operation_type RPN::charToOperator(char op)
{
    switch (op)
    {
    case '+':
        return OP_ADD;
        break;
    case '-':
        return OP_SUB;
        break;
    case '*':
        return OP_MULTIPLY;
        break;
    case '/':
        return OP_DIVIDE;
        break;
    }
    return OP_NONE;
}

int RPN::applyOperation(t_operation_type op, int a, int b)
{
    switch (op)
    {
    case OP_ADD:
        return a + b;
    case OP_SUB:
        return a - b;
    case OP_MULTIPLY:
        return a * b;
    case OP_DIVIDE:
        if (b == 0)
        {
            std::cerr << "Error: division by zero" << std::endl;
            return 0;
        }
        return a / b;
    default:
        std::cerr << "Error: unknown operator " << op << std::endl;
        return 0;
    }
}

void RPN::reversePolishNotation(std::string expression)
{
    std::stack<int> operands;
    t_operation_type operation = OP_NONE;

    // Removes all spaces
    expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());

    std::string::const_iterator token = expression.begin();
    while (token != expression.end())
    {
        if (isdigit(*token))
        {
            if (operands.size() <= 1)
            {
                operands.push(atoi(std::string(token, token + 1).c_str()));
            }
            else
            {
                std::cerr << "Error: too many operands" << std::endl;
                return;
            }
        }
        else if (charToOperator(*token) != OP_NONE)
        {
            if (operation == OP_NONE)
            {
                operation = charToOperator(*token);
            }
            else
            {
                std::cerr << "Error: Multiple operators. Not enough operands." << std::endl;
                return;
            }
        }
        else
        {
            std::cerr << "Error: Unknown token found: " << *token << std::endl;
            return;
        }

        if (operation && operands.size() == 2)
        {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            operands.push(applyOperation(operation, operand1, operand2));
            operation = OP_NONE;
        }
        token++;
    }

    if (operands.size() != 1)
    {
        std::cerr << "Error: Invalid number of operands." << std::endl;
        return;
    }

    if (operation != OP_NONE)
    {
        std::cerr << "Error: Not enough operands. Operation pending..." << std::endl;
        return;
    }

    std::cout << operands.top() << std::endl;
}

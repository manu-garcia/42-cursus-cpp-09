#ifndef RPN_HPP
#define RPN_HPP

typedef enum e_operation_type
{
    OP_NONE = 0,
    OP_ADD = 1,
    OP_SUB = 2,
    OP_MULTIPLY = 3,
    OP_DIVIDE = 4
} t_operation_type;

class RPN
{
private:
    t_operation_type charToOperator(char op);
    int applyOperation(t_operation_type op, int b, int a);

public:
    RPN();
    RPN(const RPN &rpn);

    RPN &operator=(const RPN &rpn);

    ~RPN();

    void reversePolishNotation(std::string expression);
};

#endif

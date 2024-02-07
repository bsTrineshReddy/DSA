#include <iostream>
#include <vector>
#include <string>

class Solution {
private:
    std::vector<std::string> answer;
    std::string digits;
    long target;

    void recurse(int index, long previousOperand, long currentOperand, long value, std::vector<std::string> ops) {
        std::string nums = this->digits;

        // Done processing all the digits in num
        if (index == nums.length()) {

            // If the final value == target expected AND
            // no operand is left unprocessed
            if (value == this->target && currentOperand == 0) {
                std::string expression;
                for (const std::string& op : ops) {
                    expression += op;
                }
                this->answer.push_back(expression);
            }
            return;
        }

        // Extending the current operand by one digit
        currentOperand = currentOperand * 10 + nums[index] - '0';
        std::string current_val_rep = std::to_string(currentOperand);
        int length = nums.length();

        // To avoid cases where we have 1 + 05 or 1 * 05 since 05 won't be a
        // valid operand. Hence this check
        if (currentOperand > 0) {

            // NO OP recursion
            recurse(index + 1, previousOperand, currentOperand, value, ops);
        }

        // ADDITION
        ops.push_back("+");
        ops.push_back(current_val_rep);
        recurse(index + 1, currentOperand, 0, value + currentOperand, ops);
        ops.pop_back();
        ops.pop_back();

        if (!ops.empty()) {

            // SUBTRACTION
            ops.push_back("-");
            ops.push_back(current_val_rep);
            recurse(index + 1, -currentOperand, 0, value - currentOperand, ops);
            ops.pop_back();
            ops.pop_back();

            // MULTIPLICATION
            ops.push_back("*");
            ops.push_back(current_val_rep);
            recurse(
                index + 1,
                currentOperand * previousOperand,
                0,
                value - previousOperand + (currentOperand * previousOperand),
                ops);
            ops.pop_back();
            ops.pop_back();
        }
    }
public:
    std::vector<std::string> addOperators(std::string num, int target) {
        if (num.empty()) {
            return {};
        }

        this->target = target;
        this->digits = num;
        this->answer.clear();
        this->recurse(0, 0, 0, 0, {});
        return this->answer;
    }


};

int main() {
    Solution solution;
    std::string num = "123";
    int target = 6;
    std::vector<std::string> result = solution.addOperators(num, target);

    std::cout << "Expressions: ";
    for (const std::string& expr : result) {
        std::cout << expr << " ";
    }
    std::cout << std::endl;

    return 0;
}

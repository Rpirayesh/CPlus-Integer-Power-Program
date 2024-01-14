#include <iostream>
#include <algorithm>
#include <vector>

// BigInteger Class
class BigInteger {
private:
    std::string value; // Stores the value of BigInteger as a string

public:
    // Constructor to initialize BigInteger with a string
    BigInteger(const std::string& val): value(val) {}

    // Overloading multiplication operator to multiply two BigInteger
    BigInteger operator*(const BigInteger& b) {
        int n1 = value.size(); // size of first BigInteger
        int n2 = b.value.size(); // size of second BigInteger

        // If either of them is zero
        if (n1 == 0 || n2 == 0)
           return BigInteger("0");

        // Will keep the result number in vector in reverse order
        std::vector<int> result(n1 + n2, 0);

        // Below two indexes are used to find positions in result
        int i_n1 = 0;
        int i_n2 = 0;

        // Go from right to left in first number
        for (int i = n1 - 1; i >= 0; i--) {
            int carry = 0;
            int n1 = value[i] - '0';

            i_n2 = 0;

            // Go from right to left in second number
            for (int j = n2 - 1; j >= 0; j--) {
                int n2 = b.value[j] - '0';

                int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

                // Carry for next iteration
                carry = sum / 10;

                // Store result
                result[i_n1 + i_n2] = sum % 10;

                i_n2++;
            }

            // Store carry
            if (carry > 0)
                result[i_n1 + i_n2] += carry;

            // To shift position to left after every multiplication of a digit
            i_n1++;
        }

        // Remove leading zeros
        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0)
            i--;

        // If all digits are zero
        if (i == -1)
            return BigInteger("0");

        // Generate the result string
        std::string s = "";
        while (i >= 0)
            s += std::to_string(result[i--]);

        return BigInteger(s);
    }

    // Function to return value of BigInteger
    std::string getValue() const {
        return value;
    }
};

// Function to calculate base to the power exponent
BigInteger power(int base, int exponent) {
    BigInteger result = BigInteger("1");
    BigInteger b = BigInteger(std::to_string(base));

    for(int i = 0; i < exponent; i++) {
        result = result * b;
    }

    return result;
}

// Function to reverse a number
std::string reverseNum(int num) {
    std::string str_num = std::to_string(num);
    std::reverse(str_num.begin(), str_num.end());
    return str_num;
}

// Main Function
int main() {
    int number;

    // Prompt the user to enter a number
    std::cout << "Enter a number (0-99999): ";
    std::cin >> number;

    // Check for number bounds
    if (number < 0 || number > 99999) {
        std::cout << "Invalid input!\n";
        return 1;
    }

    // Reverse the number and convert back to integer
    int reversed = std::stoi(reverseNum(number));

    // Calculate the power of the original number to its reversed form
    BigInteger result = power(number, reversed);

    // Print the result
    std::cout << "Result: " << number << "^" << reversed << " is " << result.getValue() << "\n";
    return 0;
}


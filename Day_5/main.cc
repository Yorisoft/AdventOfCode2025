/* https://adventofcode.com/2024/day/5 */ 

#include "load_input_utils.cc"
#include "algorithm"
#include<iomanip>

class Solution {
public:
    Solution() {};
    ~Solution() {};

    double taskOne(std::vector<std::pair<int, int>>* input_1, std::vector<std::vector<int>>* input_2) {
        double result = 0;
        for (std::vector<int>& pages : *input_2) {
            bool isValid = true;
            for (auto& rule : *input_1) {
                std::vector<int>::iterator ruleOne = std::find(pages.begin(), pages.end(), rule.first);
                std::vector<int>::iterator ruleTwo = std::find(pages.begin(), pages.end(), rule.second);
                
                if ((ruleOne != pages.end() && ruleTwo != pages.end()) && !(ruleOne < ruleTwo)) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                result += pages[pages.size()/2];  
            } 
        }
        return result;
    }

    double taskTwo(std::vector<std::pair<int, int>>* input_1, std::vector<std::vector<int>>* input_2) {
        double result = 0;
        for (auto& pages : *input_2) {
            bool swapped = true, everSwapped = false;
            while (swapped) {
                swapped = false;
                for (auto& rule : *input_1) {
                    std::vector<int>::iterator ruleOne = std::find(pages.begin(), pages.end(), rule.first);
                    std::vector<int>::iterator ruleTwo = std::find(pages.begin(), pages.end(), rule.second);
                    
                    if ((ruleOne != pages.end() && ruleTwo != pages.end()) && !(ruleOne < ruleTwo)) {
                        swapped = true;

                        int indexOne = std::distance(pages.begin(), ruleOne);
                        int indexTwo = std::distance(pages.begin(), ruleTwo);

                        std::swap(pages[indexOne], pages[indexTwo]);
                    }
                }
                everSwapped |= swapped;
            }

            if (everSwapped) {
                result += pages[pages.size()/2];  
            } 
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::pair<int, int>>* input_1;
    std::vector<std::vector<int>>* input_2;
    Input* data = new Input();
    Solution* solution = new Solution();

    std::string
        fileName_1 = "input_1.txt",
        fileName_2 = "input_2.txt";

    input_1 = data->getInput_1(fileName_1);
    input_2 = data->getInput_2(fileName_2);

    data->printInput(input_1);
    data->printInput(input_2);
    
    std::cout << std::fixed << std::setprecision(0) << std::endl;

    int answer = solution->taskOne(input_1, input_2);
    std::cout << "We calculate the answer to Day 5, Task 1 to be: " << answer << std::endl;
    std::cin.get();

    answer = solution->taskTwo(input_1, input_2);
    std::cout << "We calculate the answer to Day 5, Task 2 to be: " << answer << std::endl;
    std::cin.get();

    delete data;
    data = nullptr;
    delete solution;
    solution = nullptr;

    return 0;
}
#include<iostream>
#include "load_input_utils.cpp"
#include<regex>
#include<iomanip>

double taskOne(std::vector<std::string>*);
double taskTwo(std::vector<std::string>*);

int main() {

	std::vector<std::string>* input;
	Input *data = new Input();

	std::string fileName = "input.txt";
	input = data->getInput(fileName);
	data->printInput(input);
	std::cin.get();

	double answer = taskOne(input); 
	std::cout << std::fixed << std::setprecision(0);
	std::cout << "We calculate the answer for Day 3, Task 1 to be: " << answer << std::endl;
	std::cin.get();
	
	answer = taskTwo(input);
	std::cout << std::fixed << std::setprecision(0);
	std::cout << "We calculate the answer for Day 3, Task 2 to be: " << answer << std::endl;
	std::cin.get();

	return 0;
}
double taskOne(std::vector<std::string>* input) {

	// ------------------------------- TASK 2 --------------------------------- //

	// create a regex expression that matches what we're searching for 
	// for each string in input, 
	// search for regex in string and save it in matches
	// for each match 
	// get num1 in mul by skipping the first 4 chars and including everything upto not including ' , '
	// get num2 by skipping 1 after num1 and upto not including ' ) '
	// multiply num1 * num2, save in answer
	// return answer

	std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
	double answer = 0;
	for (std::string line : *input) {
		auto matchStart = std::sregex_iterator(line.begin(), line.end(), pattern);
		auto matchEnd= std::sregex_iterator();
		for (auto i = matchStart; i != matchEnd; i++) {
			std::smatch match = *i;
			std::string match_str = match.str();
			
			std::cout << match_str << std::endl;

			size_t start1 = match_str.find("(") + 1;
			size_t end1 = match_str.find(",");
			size_t start2 = end1 + 1;
			size_t end2 = match_str.find(")");
			
			// more readable
			int num1 = std::stoi(match_str.substr(start1, end1 - start1));
			int num2 = std::stoi(match_str.substr(start2, end2 - start2));

			// if I want code to be short, it would be like this 
			//int num1 = std::stoi(match.substr(4, (match.find(",")) - 4));
			//int num2 = std::stoi(match.substr((match.find(",") + 1), (match.find(")")) - match.find(",") - 1));

			answer += (num1 * num2);

		}
	}
	return answer;
}

double taskTwo(std::vector<std::string>* input) {

	// ------------------------------- TASK 2 --------------------------------- //
	// clean up the data by removing anything between a don't and a do by:
	// for each string in vector, find the substring up to but not including don't, 
	// store in string add to new vector of string. once done, at last vector to vector of vector of strings. 
	// move pos 5 steps forward and search again
	// when done, for each vector string in vector of vector string, add all string together.
	// return clean vector of strings
	//

	std::regex pattern(R"(do\(\)|don't\(\))");
	std::vector<std::string> newInput;

	for (std::string line : *input) {
		std::sregex_iterator rit = std::sregex_iterator(line.begin(), line.end(), pattern);
		std::sregex_iterator ritEnd = std::sregex_iterator();

		bool mode = true;
		size_t pos = 0;
		std::string cleanSubStr;

		for (auto i = rit; i != ritEnd; i++) {
			if (mode) {
				cleanSubStr += line.substr(pos, i->position() - pos);
			}

			if (i->str() == "do()") {
				mode = true;
			}
			else if (i->str() == "don't()"){
				mode = false;
			}
			pos = i->position();
		}
		if( pos < line.size() && mode) {
			// If "do" is not found, skip to the end of the line
			cleanSubStr += line.substr(pos);

		}	
		newInput.push_back(cleanSubStr);
	} 
	Input data;
	data.printInput(&newInput);

	double answer = taskOne(&newInput);
	return answer;
}

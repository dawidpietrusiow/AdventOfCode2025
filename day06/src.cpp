#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

void part1(vector<string>& lines) {

	// Parse math
	vector<vector<long long>> numbers;
	vector<char> operators;
	for (int i = 0; i < lines.size(); i++) {
		istringstream ss(lines[i]);
		string token;

		if (i == lines.size() - 1) {
		vector<long long> tokensLine; 
			while (ss >> token) {
				operators.push_back(token[0]);
			}
		}
		else {
			vector<long long> numbersLine;
			while (ss >> token) {
				numbersLine.push_back(stoll(token));
			}
			numbers.push_back(numbersLine);
		}
	}

	// Calculate result
	long long result = 0;

	for (int col = 0; col < operators.size(); col++) {
		if (operators[col] == '+') {
			long long sum = 0;
			for (int row = 0; row < numbers.size(); row++) {
				sum += numbers[row][col];
			}
			result += sum;
		}
		else {
			long long prod = 1;
			for (int row = 0; row < numbers.size(); row++) {
				prod *= numbers[row][col];
			}
			result += prod;
		}
	}

	cout << result << endl;
}

void part2(vector<string>& lines) {
	long long result = 0;

	// Get max line length
	int maxLineSize = 0;
	for (string line : lines) {
		if (line.size() > maxLineSize)
			maxLineSize = line.size();
	}

	// Parse lines
	char op = lines[lines.size() - 1][0];
	vector<long long> numbers;
	for (int x = 0; x < maxLineSize; x++) {

		// Build numbers with vertical split
		string numBuilder;
		for (int row = 0; row < lines.size() - 1; row++) {
			if (x >= lines[row].size())
				continue;
			char digit = lines[row][x];
			if (digit >= '0' && digit <= '9')
				numBuilder.push_back(digit);
		}

		// Column is completed
		if (numBuilder.empty()) {
			if (op == '+') {
				long long sum = 0;
				for (long long num : numbers)
					sum += num;
				result += sum;
			}
			else {
				long long prod = 1;
				for (long long num : numbers)
					prod *= num;
				result += prod;
			}
			numbers.clear();
			op = lines[lines.size() - 1][x + 1];
		}

		// Add new number to list
		else {
			numbers.push_back(stoll(numBuilder));
		}
	}

	// Add last column left in buffer
	if (op == '+') {
		long long sum = 0;
		for (long long num : numbers)
			sum += num;
		result += sum;
	}
	else {
		long long prod = 1;
		for (long long num : numbers)
			prod *= num;
		result += prod;
	}

	cout << result << endl;
}


// BOILERPLATE ------------------------
vector<string> readLines(fs::path dataPath) {
    vector<string> lines;
    string line;

    ifstream data(dataPath);
    if (!data) {
        cout << string("File not found at:") + string(dataPath) + "\n";
        exit(1);
    }

    while(getline(data, line))
        lines.push_back(line);
    data.close();

    return lines;
}

int main(int argc, char *argv[]) {
    // Get part number
    int part;
    if (argc >= 2)
        part = stoi(argv[1]);
    else {
        cout << "Enter part number\n>";
        cin >> part;
    }

    // Get data filepath
    fs::path exePath = fs::absolute(argv[0]);                                
    fs::path dayPath = exePath.parent_path();
    fs::path dataPath = dayPath / "data.txt";

    vector<string> lines = readLines(dataPath);

    // Run part
    switch(part) {
        case 1:
            part1(lines);
            break;
        case 2:
            part2(lines);
            break;
        default: 
            cout << "Invalid argument\n";
    }
}



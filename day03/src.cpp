#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

void part1(vector<string>& lines) {
	int result = 0;

    for (int i = 0; i < lines.size(); i++) {
		string bank = lines[i];

		int left = 0, right = bank.size() - 1;
		// First digit
		for (int j = left; j < right; j++) {
			if (bank[j] > bank[left])
				left = j;
		}
		// Second digit 
		for (int j = right; j > left; j--) {
			if (bank[j] > bank[right])
				right = j;
		}
		result += (bank[left] - '0') * 10 + (bank[right] - '0');
	}
	cout << result << endl;
}

void part2(vector<string>& lines) {
	long long result = 0;

    for (int i = 0; i < lines.size(); i++) {
		string bank = lines[i];

		long long joltage = 0;
		int left = 0;
		// Loop through digits, most significant first
		for (int dx = 12; dx >= 1; dx--) {
			for (int pos = left; pos <= bank.size() - dx; pos++) {
				if (bank[pos] > bank[left])
					left = pos;
			}
			joltage = joltage * 10 + (bank[left] - '0');
			left++;
		}
		result += joltage;
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



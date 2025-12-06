#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

bool isAccessible(vector<string>& lines, int row, int col) {
	int rolls = 0;
	for (int drow = -1; drow <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
			int resRow = row + drow;
			int resCol = col + dcol;
			if ((drow == 0 && dcol == 0) || 
					resRow < 0 || resRow >= lines.size() ||
					resCol < 0 || resCol >= lines[resRow].size()) {
				continue;
			}
			if (lines[resRow][resCol] == '@') {
				rolls++;
			}
		}
	}
	return rolls < 4;
}

void part1(vector<string>& lines) {
	int accessibleRolls = 0;
	for (int row = 0; row < lines.size(); row++) {
		for (int col = 0; col < lines[row].size(); col++) {
			if (lines[row][col] == '@' && isAccessible(lines, row, col)) 
				accessibleRolls++;
		}
	}
	cout << accessibleRolls << endl;
}

void part2(vector<string>& lines) {
	vector<string> newState = lines;
	int rollsRemoved = 0;
	int accessibleRolls = 0;
	do {
		accessibleRolls = 0;
		for (int row = 0; row < lines.size(); row++) {
			for (int col = 0; col < lines[row].size(); col++) {
				if (lines[row][col] == '@' && isAccessible(lines, row, col)) {
					accessibleRolls++;
					rollsRemoved++;
					newState[row][col] = '.';
				}
			}
		}
		lines = newState;
	}
	while (accessibleRolls > 0);

	cout << rollsRemoved << endl;
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



#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

void part1(vector<string>& lines) {
	int pos = 50;
	int password = 0;
	for (int i = 0; i < lines.size(); i++) {
		string line = lines[i];
		int rotDir = line[0] == 'L' ? -1 : 1;
		int rotAbs = stoi(line.substr(1, line.size()));

		pos += rotDir * rotAbs;
		while (pos < 0) {
			pos += 100;
		}
		while (pos >= 100) {
			pos -= 100;
		}
		if (pos == 0)
			password++;
	}	
	cout << password << endl;
}

void part2(vector<string>& lines) {
	int pos = 50;
	int password = 0;
	for (int i = 0; i < lines.size(); i++) {
		string line = lines[i];
		int rotDir = line[0] == 'L' ? -1 : 1;
		int rotAbs = stoi(line.substr(1, line.size()));

		password += rotAbs / 100;	// Full rotations
		int newPos = pos + rotDir * (rotAbs % 100);	// Add non-full rotation

		if (newPos == 0) {
			password++;
		}
		if (newPos < 0) {
			if (pos > 0)
				password++;
			newPos += 100;
		}
		if (newPos >= 100) {
			password++;
			newPos -= 100;
		}
		pos = newPos;

	}	
	cout << password << endl;
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



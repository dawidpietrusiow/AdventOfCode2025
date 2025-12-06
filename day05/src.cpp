#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

void part1(vector<string>& lines) {
	// Initialize ranges
	vector<array<long long, 2>> freshIdRanges;
	int i = 0;
	while (!lines[i].empty()) {
		int splitIndex = lines[i].find('-');
		long long start = stoll(lines[i].substr(0, splitIndex));
		long long end = stoll(lines[i].substr(splitIndex + 1));	
		freshIdRanges.push_back({start, end});
		i++;
	}
	i++;	// Skip blank line
			
	// Validate ingredients
	int freshCount = 0;
	while (i < lines.size()) {
		long long id = stoll(lines[i]);
		for (auto [start, end] : freshIdRanges) {
			if (id >= start && id <= end) {
				freshCount++;
				break;
			}
		}
		i++;
	}
	
	cout << freshCount << endl;
}

void part2(vector<string>& lines) {
	// Initialize ranges
	vector<array<long long, 2>> freshIdRanges;
	int i = 0;
	while (!lines[i].empty()) {
		int splitIndex = lines[i].find('-');
		long long start = stoll(lines[i].substr(0, splitIndex));
		long long end = stoll(lines[i].substr(splitIndex + 1));	

		bool isUniqueRange = true;
		for (int j = 0; j < freshIdRanges.size(); j++) {
			auto [cmpStart, cmpEnd] = freshIdRanges[j];
			if (start >= cmpStart && start <= cmpEnd)	// newRange intersects on upper end of cmpRange
				start = cmpEnd + 1;
			if (end >= cmpStart && end <= cmpEnd)		// newRange intersects on lower end of cmpRange
				end = cmpStart - 1;
			if (start <= cmpStart && end >= cmpEnd) {	// cmpRange subset of newRange (delete cmpRange)
				freshIdRanges.erase(freshIdRanges.begin() + j);
				j--;	// Compensate for vector shrink
			}
			if (start > end) {
				isUniqueRange = false;
				break;
			}
		}
		if (isUniqueRange)
			freshIdRanges.push_back({start, end});
		i++;
	}

	// Calculate total amount of ids
	long long freshIds = 0;
	for (auto [start, end] : freshIdRanges) {
		freshIds += end - start + 1;	// inclusive
	}

	cout << freshIds << endl;
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



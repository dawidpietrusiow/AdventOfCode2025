#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

long long getResults(vector<string>& lines, bool (*isInvalidFunc)(long long)) {
	long long result = 0;

	string data = lines[0];		// Just one line this day
	stringstream dataStream(data);
	string idRange;
	while (getline(dataStream, idRange, ',')) {
		int splitIndex = idRange.find('-');
		long long start = stoll(idRange.substr(0, splitIndex));
		long long end = stoll(idRange.substr(splitIndex + 1, idRange.size()));

		int invalidIds = 0;
		for(long long i = start; i <= end; i++) {
			if (isInvalidFunc(i)) {
				result += i;
			}
		}
	}
	return result;
}

bool isInvalid1(long long i) {
	string id = to_string(i);
	int n = id.size();
	if (n % 2 == 0) {
		string id1 = id.substr(0, n / 2);
		string id2 = id.substr(n / 2);
		if (id1.compare(id2) == 0) {
			return true;
		}
	}
	return false;
}

bool isInvalid2(long long i) {
	string id = to_string(i);
	int n = id.size();
	for (int len = 1; len <= n / 2; len++) {	

		if (n % len != 0) 	//Invalid id only possible when size is multiple of block length
			continue;

		bool isInvalid = true;
		string block = id.substr(0, len);

		for (int pos = len; pos < n; pos += len) {
			string currBlock = id.substr(pos, len);
			if (block.compare(currBlock) != 0) {
				isInvalid = false;
				break;
			}
		}
		if (isInvalid) 
			return true;
	}
	return false;
}
void part1(vector<string>& lines) {
	long long result = getResults(lines, &isInvalid1);
	cout << result << endl;
}
void part2(vector<string>& lines) {
	long long result = getResults(lines, &isInvalid2);
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



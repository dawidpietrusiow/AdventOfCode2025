#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// SOLUTIONS -------------------------

int alreadyExists(vector<int>& list, int num) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == num)
			return true;
	}
	return false;
}

void part1(vector<string>& lines) {
	int result = 0;

	vector<int> beams = { static_cast<int>(lines[0].find('S')) };
	for (int y = 1; y < lines.size(); y++) {
		vector<int> newBeams;
		for (int i = 0; i < beams.size(); i++) {
			int beam = beams[i];
			if (lines[y][beam] == '^') {
				if (beam < lines[0].size() - 1 && !alreadyExists(newBeams, beam + 1)) {
					newBeams.push_back(beam + 1);
				}
				if (beam > 0 && !alreadyExists(newBeams, beam - 1)) {
					newBeams.push_back(beam - 1);
				}
				result++;
			}
			else {
				if (!alreadyExists(newBeams, beam))
					newBeams.push_back(beam);
			}
		}
		beams = newBeams;
	}
	cout << result << endl;
}


void part2(vector<string>& lines) {
	int H = lines.size();
	int W = lines[0].size();
	vector<long long> beamCount(W, 0);
	int startX = lines[0].find('S');
	beamCount[startX] = 1;

	for (int y = 1; y < H; y++) {
		vector<long long> newCount(W, 0);
		for (int x = 0; x < W; x++) {
			if (beamCount[x] == 0) 
				continue;
			if (lines[y][x] == '^') {
				if (x > 0) 
					newCount[x - 1] += beamCount[x];
				if (x < W - 1) 
					newCount[x + 1] += beamCount[x];
			} else {
				newCount[x] += beamCount[x];
			}
		}
		beamCount = newCount;
	}

	long long result = 0;
	for (long long c : beamCount)
		result += c;
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



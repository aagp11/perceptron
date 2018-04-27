#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

pair<map<vector<float>, float>, multimap<float, vector<float>>> read_Input() {
	map<vector<float>, float> data_Set;
	multimap<float, vector<float>> test_Set;
	int m, n;
	float num_f;
	string input;
	string::size_type sz;
	vector<float> temp_in;
	pair<map<vector<float>, float>, multimap<float, vector<float>>> sets;
	cin >> m;
	cin >> n;
	cin.ignore();
	cin.clear();
	for (int i = 0; i < m; i++) {
		getline(cin, input);
		while (input.find(',') != string::npos) {
			sz = input.find(',');
			num_f = stof(input, &sz);
			input = input.substr(sz + 1);
			temp_in.push_back(num_f);
		}
		num_f = stof(input, &sz);
		data_Set.insert(pair<vector<float>, float>(temp_in, num_f));
		temp_in.clear();
	}
	for (int i = 0; i < n; i++) {
		getline(cin, input);
		while (input.find(',') != string::npos) {
			sz = input.find(',');
			num_f = stof(input, &sz);
			input = input.substr(sz + 1);
			temp_in.push_back(num_f);
		}
		num_f = stof(input, &sz);
		temp_in.push_back(num_f);
		test_Set.insert(pair<float, vector<float>>(0, temp_in));
		temp_in.clear();
	}
	sets.first = data_Set;
	sets.second = test_Set;
	return sets;
}

float calc_output(vector<float> weights, vector<float>input) {
	float res = 0;
	for (int i = 0; i < weights.size(); i++) {
		res += weights.at(i) * input.at(i);
	}
	if (res > 1)res = 1;
	else res = 0;
	return res;
}

int main()
{
	int d;
	bool linear;
	vector<float> weights;
	float threshold = 0.5, y;
	map<vector<float>, float> data_Set;
	multimap<float, vector<float>> test_Set;
	pair<map<vector<float>, float>, multimap<float, vector<float>>> sets;
	cin >> d;
	sets = read_Input();
	data_Set = sets.first;
	test_Set = sets.second;
	for (int i = 0; i < d; i++)weights.push_back(1);
	for (int i = 0; i < data_Set.size() * 9; i++) {
		for (auto& x : data_Set) {
			y = calc_output(weights, x.first);
			for (int j = 0; j < weights.size(); j++) {
				weights.at(j) += (.99 * (x.second - y) * x.first.at(j));
			}
		}
	}
	linear = true;
	for (auto& x : data_Set) {
		y = calc_output(weights, x.first);
		if (y != x.second)linear = false;
	}
	if (linear) {
		for (auto& x : test_Set) cout << calc_output(weights, x.second) << "\n";
	}
	else cout << "no solution found\n";
    return 0;
}

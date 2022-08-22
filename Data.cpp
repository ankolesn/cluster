//
// Created by ankoles on 17.08.22.
//

#include "Data.h"

int Data::cpu_gpu(string n) {
    string s;
    int value = 0;
    ifstream file(n);
    if (!file.is_open()) {
        throw std::invalid_argument("There is no such file");
    }
    getline(file, s);
    value = stoi(s) / 1000;
    return value;
}

int Data::cpu_load(string ss) {
    int strs1[4];
    int strs2[4];
    string s;

    for (int j = 0; j < 2; ++j) {
        ifstream file(ss);
        getline(file, s);
        auto pos2 = 4;
        for (int i = 0; i < 4; ++i) {
            auto pos1 = s.find(' ', pos2);
            pos2 = s.find(' ', pos1 + 1);
            if (j == 0)
                strs1[i] = stoi(s.substr(pos1, pos2));
            else strs2[i] = stoi(s.substr(pos1, pos2));
        }
        sleep(1);
        file.close();
    }

    int razn_strs[4];
    for (int i = 0; i < 4; ++i) {
        razn_strs[i] = strs2[i] - strs1[i];
    }
    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        sum += razn_strs[i];
    }
    return ((razn_strs[0] + razn_strs[1] + razn_strs[2]) * 100 / sum);
}

pair<double, double> Data::memory_load(string n) {
    string s;
    ifstream file(n);
    string mem[2];
    int j = 0;
    while (!file.eof()) {
        for (int i = 0; i < 3; ++i) {
            getline(file, s);
            j++;
            if (j == 1) {
                mem[0] = s.substr(17, 7);
            }
            else if(j == 3) {
                mem[1] = s.substr(17, 7);
            }
        }
    }
    return make_pair<int, int> ( stoi(mem[0]) / 1000000, (stoi(mem[0]) - stoi(mem[1])) / 1000000);
}

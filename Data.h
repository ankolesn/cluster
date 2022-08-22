//
// Created by ankoles on 17.08.22.
//


#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <iomanip>

#ifndef CLUSTER_DATA_H
#define CLUSTER_DATA_H


using namespace std;

class Data {
public:
    int cpu_gpu(string n);
    int cpu_load(string ss);
    pair<double, double> memory_load(string n);
};


#endif //CLUSTER_DATA_H


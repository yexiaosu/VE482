//
// Created by lanwang on 11/4/21.
//

#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#define MAX_RESOURCE_NUM 10

using namespace std;

class process {
private:
    int pid;
    int typeNum;

public:
    vector<int> allocated, maximum, need;

    process(int pid, int typeNum) : pid(pid), typeNum(typeNum) {
        for (int i = 0; i < typeNum; i++) {
            int tmp1 = rand() % (MAX_RESOURCE_NUM - 1) + 1;
            int tmp2 = rand() % (MAX_RESOURCE_NUM - 1) + 1;
            if (tmp1 >= tmp2) {
                maximum.emplace_back(tmp1);
                allocated.emplace_back(tmp2);
                need.emplace_back(tmp1 - tmp2);
            } else {
                maximum.emplace_back(tmp2);
                allocated.emplace_back(tmp1);
                need.emplace_back(tmp2 - tmp1);
            }
        }
    }

    void print() {
        cout << pid << "  |";
        for (int i = 0; i < typeNum; i++) {
            cout << "  " << allocated[i];
        }
        cout << "  |";
        for (int i = 0; i < typeNum; i++) {
            cout << "  " << maximum[i];
        }
        cout << endl;
        cout << "-------------------------" << endl;
    }
};

class banker {
private:
    vector<int> work;
    vector<bool> finish;
    vector<process> *processes;
    int numProcess;
    int numResource;
public:
    banker(int numProcess, int numResource, vector<int> available, vector<process> &processes) : numProcess(numProcess),
                                                                                                 numResource(
                                                                                                         numResource),
                                                                                                 work(std::move(
                                                                                                         available)),
                                                                                                 processes(&processes) {
        finish.reserve(numProcess);
        for (int i = 0; i < numProcess; ++i) {
            finish[i] = false;
        }
    }

    int find() {
        for (int i = 0; i < numProcess; ++i) {
            if (!finish[i]) {
                int flag = 0;
                for (int j = 0; j < numResource; ++j) {
                    if (processes->at(i).need[j] <= work[j]) {
                        continue;
                    } else {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    return i;
                }
            }
        }
        return -1;
    }

    bool check() {
        int pos = find();
        if (pos == -1) {
            for (int i = 0; i < numProcess; ++i) {
                if (!finish[i]) {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = 0; i < numResource; ++i) {
                work[i] = work[i] + processes->at(pos).allocated.at(i);
            }
            finish[pos] = true;
            return check();
        }
    }
};

int main() {
    srand(time(nullptr));
    int numProcess, numResource;
    cout << "Input the number of process:" << endl;
    cin >> numProcess;
    cout << "Input the number of type resources:" << endl;
    cin >> numResource;
    vector<int> available;
    available.reserve(numResource);
    cout << "**************************" << endl;
    cout << "Available";
    for (int i = 0; i < numResource; ++i) {
        int tmp = rand() % (MAX_RESOURCE_NUM - 1) + 1;
        available.push_back(tmp);
        cout << "  " << tmp;
    }
    cout << endl;
    vector<process> processes;
    processes.reserve(numProcess);
    cout << "**************************" << endl;
    cout << "Process  Allocated  Maximum" << endl;
    cout << "**************************" << endl;
    for (int i = 0; i < numProcess; ++i) {
        process tmp = process(i, numResource);
        processes.push_back(tmp);
        tmp.print();
    }
    cout << "**************************" << endl;
    banker checkSafe= banker(numProcess,numResource,available,processes);
    if (checkSafe.check()) {
        cout << "Safe state!" << endl;
    }else{
        cout << "Not safe state!" << endl;
    }
    return 0;
}

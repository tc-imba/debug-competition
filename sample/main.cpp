//
// Created by liu on 2019/11/26.
//

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
    unsigned int m, n;
    cin >> n >> m;

    vector<pair<unsigned int, unsigned int>> data_m;
    vector<pair<unsigned int, unsigned int>> data_n;
    unsigned int lines = 0;

    for (unsigned int i = 0; i < n; i++) {
        unsigned int a, b;
        cin >> a >> b;
        lines = max(lines, a);
        lines = max(lines, b);
        data_n.emplace_back(a, b);
    }

    for (unsigned int i = 0; i < m; i++) {
        unsigned int a, b;
        cin >> a >> b;
        lines = max(lines, a);
        lines = max(lines, b);
        data_m.emplace_back(a, b);
    }

    vector<int> vector_max(lines + 1, 0);
    vector<double> vector_avg(lines + 1, 0);

    for (const auto &p:data_n) {
        double avg = 1. / (p.second - p.first + 1);
        for (unsigned int i = p.first; i <= p.second; i++) {
            vector_max[i]++;
            vector_avg[i] += avg;
        }
    }

    for (const auto &p:data_m) {
        int max_bugs = 0;
        double avg_bugs = 0;
        for (unsigned int i = p.first; i <= p.second; i++) {
            max_bugs = max(max_bugs, vector_max[i]);
            avg_bugs += vector_avg[i];
        }
        cout << fixed << setprecision(3) << avg_bugs << " " << max_bugs << endl;
    }

    return 0;
}

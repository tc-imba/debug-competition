//
// Created by liu on 2019/11/25.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

static mt19937 random_engine;

ostream &operator<<(ostream &oss, pair<size_t, size_t> p) {
    return oss << p.first << " " << p.second;
}

double get_random() {
    return double(random_engine()) / mt19937::max();
}

size_t get_random_position(size_t size) {
    return get_random() * size;
}

pair<size_t, size_t> get_random_range(size_t size) {
    auto a = get_random_position(size);
    auto b = get_random_position(size);
    return make_pair(min(a, b), max(a, b));
}

string generate_value(const string &type) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    if (type == "int") {
        int value = int(get_random() * 1000) - 500;
        return to_string(value);
    } else if (type == "double") {
        double value = get_random() * 1000 - 500;
        return to_string(value);
    } else {
        size_t len = get_random_position(20) + 1;
        string value;
        for (size_t i = 0; i < len; i++) {
            value += alphanum[get_random_position(sizeof(alphanum) - 1)];
        }
        return value;
    }
}

void generate_data(const string &filename, const string &type, const string &operation,
                   const string &aggregation, size_t size, size_t query_size) {
    ofstream out(filename);
    out << size << " " << query_size << " " << type << " "
        << operation << " " << aggregation << " " << generate_value(type) << endl;
    for (size_t i = 0; i < query_size; i++) {
        auto query_rand = get_random();
        if (query_rand < 0.25) {
            out << "update " << generate_value(type) << " " << get_random_position(size) << endl;
        } else if (query_rand < 0.5) {
            out << "range " << generate_value(type) << " " << get_random_range(size) << endl;
        } else if (query_rand < 0.75) {
            out << "get " << get_random_position(size) << endl;
        } else {
            out << "aggregate " << get_random_range(size) << endl;
        }
    }
    out.close();
}

void generate_bugs(const string &filename, size_t size, size_t n, size_t m) {
    ofstream out(filename);
    out << n << " " << m << endl;
    for (size_t i = 0; i < n; i++) {
        out << get_random_range(size) << endl;
    }
    for (size_t i = 0; i < m; i++) {
        out << get_random_range(size) << endl;
    }
    out.close();
}

int main(int argc, char *argv[]) {
    // create / clean the directory with fs library
    filesystem::path dir = filesystem::current_path() / "test-cases";
    if (!filesystem::exists(dir)) {
        filesystem::create_directory(dir);
    }
    for (auto &file: filesystem::directory_iterator(dir)) {
        if (file.path().extension() == ".in") {
            filesystem::remove(file);
        }
    }

    size_t seed = 482;
    if (argc > 1) {
        seed = strtoul(argv[1], nullptr, 10);
    }
    random_engine.seed(seed);
    generate_data(dir / "data.0.in", "int", "sum", "sum", 10000, 5000);
    generate_data(dir / "data.1.in", "double", "sum", "max", 10000, 5000);
    generate_data(dir / "data.2.in", "str", "sum", "min", 100, 1000);
    generate_data(dir / "data.3.in", "int", "max", "max", 10000, 5000);
    generate_data(dir / "data.4.in", "double", "max", "min", 10000, 5000);
    generate_data(dir / "data.5.in", "str", "max", "sum", 100, 1000);
    generate_data(dir / "data.6.in", "int", "min", "min", 10000, 5000);
    generate_data(dir / "data.7.in", "double", "min", "sum", 10000, 5000);
    generate_data(dir / "data.8.in", "str", "min", "max", 100, 1000);

    generate_bugs(dir / "bug.0.in", 10, 10, 100);
    generate_bugs(dir / "bug.1.in", 10, 50, 100);
    generate_bugs(dir / "bug.2.in", 100, 10, 1000);
    generate_bugs(dir / "bug.3.in", 100, 50, 1000);
    generate_bugs(dir / "bug.4.in", 100, 100, 1000);
    generate_bugs(dir / "bug.5.in", 1000, 10, 10000);
    generate_bugs(dir / "bug.6.in", 1000, 50, 10000);
    generate_bugs(dir / "bug.7.in", 1000, 100, 10000);
    generate_bugs(dir / "bug.8.in", 1000, 500, 10000);
    generate_bugs(dir / "bug.9.in", 1000, 1000, 10000);
    generate_bugs(dir / "bug.10.in", 1000, 10000, 100000);
    return 0;
}

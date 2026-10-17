#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <iterator>
#include <utility>
#include <cerrno>

using namespace std;

// 存储POJ数据：用户名-做题量
typedef pair<string, int> DataPair;
vector<DataPair> poj_data;


void parse_poj_file() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int rank, ac_count, submit_count;
        string username;
        if (ss >> rank >> username >> ac_count >> submit_count) 
        {
            poj_data.emplace_back(username, ac_count);
        }
    }
    //cerr << "[INFO] 成功解析 " << poj_data.size() << " 条POJ记录" << endl;
}


/**
 * 字符串转整数（带错误处理）
 */
bool str_to_int(const char* str, int& val) {
    char* end;
    errno = 0;
    long num = strtol(str, &end, 10);
    if (errno != 0 || end == str || num < 0 || num > INT_MAX) {
        return false;
    }
    val = static_cast<int>(num);
    return true;
}

int main(int argc, char* argv[]) {
    // 1. 处理命令行参数
    if (argc != 3) {
        cerr << "[Usage] " << argv[0] << " <insert_count> <query_count>" << endl;
        cerr << "[Example] " << argv[0] << " 5000 10000 < poj.txt > test.in" << endl;
        return 1;
    }

    int insert_count, query_count;
    if (!str_to_int(argv[1], insert_count) || !str_to_int(argv[2], query_count)) {
        cerr << "[Error] 插入次数和查询次数必须是非负整数" << endl;
        return 1;
    }

    // 2. 解析POJ数据
    parse_poj_file();
    int max_possible_insert = poj_data.size();
    if (insert_count > max_possible_insert) {
        cerr << "[Warning] 插入次数 " << insert_count << " 超过数据总数 " << max_possible_insert 
             << "，自动调整为 " << max_possible_insert << endl;
        insert_count = max_possible_insert;
    }

    // 3. 初始化随机数生成器（保证每次运行结果不同）
    mt19937 gen(time(0));

    // 4. 生成随机索引，确保插入不重复
    vector<int> indices(max_possible_insert);
    iota(indices.begin(), indices.end(), 0);  // 填充0~max_possible_insert-1
    shuffle(indices.begin(), indices.end(), gen);  // 打乱索引

    // 5. 输出插入操作（类型0）
    vector<string> inserted_usernames;
    inserted_usernames.reserve(insert_count);
    for (int i = 0; i < insert_count; ++i) {
        int idx = indices[i];
        const string& name = poj_data[idx].first;
        int ac = poj_data[idx].second;
        cout << "0 " << name << " " << ac << endl;
        inserted_usernames.push_back(name);
    }

    // 6. 收集未插入的POJ用户名（用于未命中查询）
    vector<string> uninserted_usernames;
    uninserted_usernames.reserve(max_possible_insert - insert_count);
    for (int i = insert_count; i < max_possible_insert; ++i) {
        uninserted_usernames.push_back(poj_data[indices[i]].first);
    }

    // 7. 输出查询操作（类型1）：40%命中，60%未命中（50%POJ未插入+50%随机字符串）
    uniform_int_distribution<> hit_dist(0, 99);  // 用于决定是否命中
    uniform_int_distribution<> choice_dist(0, 1); // 用于选择未命中来源
    for (int i = 0; i < query_count; ++i) {
        string query_name;
        int rand_val = hit_dist(gen);

        if (rand_val < 40 && !inserted_usernames.empty()) {
            // 命中：从已插入用户名中随机选
            uniform_int_distribution<> idx_dist(0, inserted_usernames.size() - 1);
            query_name = inserted_usernames[idx_dist(gen)];
        } else {
            // 未命中：二选一来源
            int choice = choice_dist(gen);
            if (choice == 0 && !uninserted_usernames.empty()) {
                // 来源1：POJ中未插入的用户名
                uniform_int_distribution<> idx_dist(0, uninserted_usernames.size() - 1);
                query_name = uninserted_usernames[idx_dist(gen)];
            } else {
                // 来源2：随机生成字符串
                query_name = generate_random_string(gen);
            }
        }
        cout << "1 " << query_name << endl;
    }

    // 8. 输出结束操作（类型2）
    cout << "2" << endl;

    return 0;
}
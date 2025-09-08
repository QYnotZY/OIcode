#include <bits/stdc++.h>
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> list_files(const std::string& path) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            files.push_back(entry.path().filename().string());
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
    return files;
}
void removeCarriageReturns(const std::string& filename) {
    // 打开原始文件进行读取
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    // 读取文件内容到字符串
    std::string content((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());
    inputFile.close();

    // 移除所有\r字符
    content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());

    // 打开同一文件进行写入（这会清空原文件）
    std::ofstream outputFile(filename, std::ios::binary | std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件进行写入: " << filename << std::endl;
        return;
    }

    // 写入处理后的内容
    outputFile << content;
    outputFile.close();

    std::cout << "已成功移除文件中的所有\\r字符。" << std::endl;
}

int main() {
    std::string directory_path = "./ys";  // 当前目录
    auto file_list = list_files(directory_path);
    
    std::cout << "Files in directory " << directory_path << ":\n";
    for (const auto& file : file_list) {
        removeCarriageReturns("ys/"+file);
        std::cerr<<"File "<<file<<" done."<<std::endl;
    }
    return 0;
}
#include <iostream>
#include <fstream>
#include "person.pb.h" // 生成的 protobuf 头文件

int main() {
    // 创建一个 Person 对象并设置字段值
    Person person;
    person.set_id(123);
    person.set_name("Alice");

    // 序列化 Person 对象
    std::string serialized_data;
    person.SerializeToString(&serialized_data);

    // 将序列化后的数据写入文件
    std::ofstream outfile("person.dat", std::ios::out | std::ios::binary);
    if (outfile.is_open()) {
        outfile.write(serialized_data.c_str(), serialized_data.size());
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing" << std::endl;
        return 1;
    }

    // 从文件中读取数据并反序列化为 Person 对象
    std::ifstream infile("person.dat", std::ios::in | std::ios::binary);
    if (infile.is_open()) {
        std::string serialized_data((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
        Person deserialized_person;
        deserialized_person.ParseFromString(serialized_data);

        // 输出反序列化后的 Person 对象信息
        std::cout << "Deserialized Person: " << std::endl;
        std::cout << "ID: " << deserialized_person.id() << std::endl;
        std::cout << "Name: " << deserialized_person.name() << std::endl;

        infile.close();
    } else {
        std::cerr << "Error opening file for reading" << std::endl;
        return 1;
    }

    return 0;
}

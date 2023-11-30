#include <vector> 
#include <string> 
#include <iostream>
#include <fstream> 


std::vector<std::string> read_and_get_bitacora_info(std::string file_name) {
    std::vector<std::string> bitacora_info;
    std::ifstream bitacora_file(file_name);
    std::string line;
    while (std::getline(bitacora_file, line)) {
        bitacora_info.push_back(line);
    }
    return bitacora_info;
}


std::string get_id(std::string line) {
    // id is the fourth element of the line, separated by spaces
    std::string id;
    int spaces = 0;
    for (char c : line) {
        if (spaces >= 19) {
            id += c;
        }
        spaces++;

    }
    return id;
}

void linear_search_ids(std::string input, std::vector<std::string> vector) {
    for (int i = 0; i < vector.size(); i++) {
        std::string parsed_id = get_id(vector[i]);
        parsed_id = parsed_id.substr(0, 3);
        if (parsed_id == input) {
            std::cout << get_id(vector[i]) << " found at line " << (i + 1) << " (Linear) " << std::endl;
        }
    }
}


std::vector<std::string> get_id_from_bitacora(std::vector<std::string> &bitacora_info) {
    std::vector<std::string> ids;
    for (std::string line : bitacora_info) {
        ids.push_back(get_id(line));
    }
    return ids;
}

void sort_ids(std::vector<std::string> & id) {
    // use bubble sort
    for (int i = 0; i < id.size(); i++) {
        for (int j = 0; j < id.size() - i - 1; j++) {
            if (id[j] > id[j + 1]) {
                std::string temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }
}

void used_main() {
    std::vector<std::string> bitacora_info = read_and_get_bitacora_info("bitacora.txt");
    std::vector<std::string> ids = get_id_from_bitacora(bitacora_info);
    sort_ids(ids);

    for (std::string id : ids) {
        std::cout << id << std::endl;
    }
}

void rearrange_lines(std::vector<std::string> &lines)
{
    int i, j; 
    int vecSize = lines.size();
    for (i = 0; i < vecSize - 1; i++)
    {
        for (j = 0; j < vecSize - i - 1; j++)
        {
            std::string id1 = get_id(lines[j]);
            std::string id2 = get_id(lines[j + 1]);

            if (id1 > id2)
            {
                std::swap(lines[j], lines[j + 1]);
            }
            else if (id1 == id2)
            {
                std::string date1 = lines[j].substr(0, 10);
                std::string date2 = lines[j + 1].substr(0, 10);

                // not so sure about this one, it only compares 
                // the first 10 characters of the line, which are the date


                if (date1 > date2)
                {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
    }
}
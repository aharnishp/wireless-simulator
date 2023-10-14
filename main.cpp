#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
struct node {
    int x;
    int y;
    int z;
    int power;
    int rate;
};

std::vector<node> nodes;
std::map<std::pair<int, int>, float> edge_distance;

int main() {
    // read csv file
    std::ifstream file("input.csv");
    std::string line;
    // remove first line of header = id,x,y,z,power,rate
    std::getline(file, line); 
    // parse each line of csv file with comma separated
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        // create node
        node n;
        n.x = std::stoi(tokens[1]);
        n.y = std::stoi(tokens[2]);
        n.z = std::stoi(tokens[3]);
        n.power = std::stoi(tokens[4]);
        n.rate = std::stoi(tokens[5]);
        nodes.push_back(n);

        // create edge euclidean distance where ni, nj are nodes i < j
        for (int i = 0; i < nodes.size() - 1; i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                std::cout << "calculating for i: " << i << " j: " << j << std::endl;
                float distance = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2) + pow(nodes[i].z - nodes[j].z, 2));
                edge_distance[std::make_pair(i, j)] = distance;
            }
        }
    }

    // print edge distance
    std::cout << "Edge Distance: " << std::endl;
    for (auto e : edge_distance) {
        std::cout << "i:" << e.first.first << " j:" << e.first.second << " distance:" << e.second << std::endl;
    }

    // print nodes
    std::cout << "Input Nodes: " << std::endl;
    for (auto n : nodes) {
        std::cout << n.x << " " << n.y << " " << n.z << " " << n.power << " " << n.rate << std::endl;
    }


    return 0;
}
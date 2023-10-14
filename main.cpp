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
    float radius;
    int send_wait_time;
    long last_packet_sent = 0;
};

std::vector<node> nodes;
// std::map<std::pair<int, int>, float> edge_distance;

std::vector<std::vector<float>> edge_mat; // contains adjacency matrix with +ve distance if they are in range, otherwise -ve.

long timestep = 0;

int simulate(long end_timestep) {
    while (timestep < end_timestep) {
        for(int i = 0; i < nodes.size(); i++){
            // check when was last packet sent
            if(timestep - nodes[i].last_packet_sent >= nodes[i].send_wait_time){
                // send packet
                nodes[i].last_packet_sent = timestep;
                std::cout << "sending packet from node " << i << " at timestep " << timestep << std::endl;
            }
        }
            timestep++;
    }
    return 0;
}

int main() {
    // read csv file
    std::ifstream file("input_nodes.csv");
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
        n.radius = std::stof(tokens[4]);
        n.send_wait_time = std::stoi(tokens[5]);
        nodes.push_back(n);



        // // create edge euclidean distance where ni, nj are nodes i < j
        // for (int i = 0; i < nodes.size() - 1; i++) {
        //     for (int j = i + 1; j < nodes.size(); j++) {
        //         std::cout << "calculating for i: " << i << " j: " << j << std::endl;
        //         float distance = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2) + pow(nodes[i].z - nodes[j].z, 2));
        //         edge_distance[std::make_pair(i, j)] = distance;
        //     }
        // }
    }

    // create lower triangle of adjacency matrix with value = +ve distance which are in range and -ve that are out of range for nodes ni & nj where i > j
    for (int i = 1; i < nodes.size(); i++){
        std::vector<float> row;
        for(int j = 0; j < i; j++){
            float distance = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2) + pow(nodes[i].z - nodes[j].z, 2));
            if()
            std::cout << "calculating for (i: " << i << " j: " << j << ") distance: " << distance << std::endl;
        }
        edge_mat.push_back(row);
    }


    // print edge_mat
    std::cout << "Edge Distance: " << std::endl;
        // print each cell in the format (i,j: distance)
    
    for (int i = 0; i < edge_mat.size(); i++){
        for (int j = 0; j < edge_mat[i].size(); j++){
            std::cout << "(" << i << "," << j+i+1 << ": " << edge_mat[i][j] << ") ";
        }
        std::cout << std::endl;
    }


    // // print edge distance
    // std::cout << "Edge Distance: " << std::endl;
    // for (auto e : edge_distance) {
    //     std::cout << "i:" << e.first.first << " j:" << e.first.second << " distance:" << e.second << std::endl;
    // }



    // print nodes
    std::cout << "Input Nodes: " << std::endl;
    for (auto n : nodes) {
        std::cout << n.x << " " << n.y << " " << n.z << " " << n.radius << " " << n.send_wait_time << std::endl;
    }


    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>

#define pi_val 3.14

#define SINR_THRESHOLD_dB 25

struct node {
    float x;
    float y;
    float z;
    float radius;
    int send_wait_time;
    long last_packet_sent = 0;
};

std::vector<node> nodes;
// std::map<std::pair<int, int>, float> edge_distance;


float get_power_at_distance(float source_power, float distance){
    // assuming uniform medium
    float power_d = source_power/(4*pi_val*distance*distance);
    return power_d;
}

// packet is assumed to be sent from i to j
// the range can be asymmetric 
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
        n.x = std::stof(tokens[1]);
        n.y = std::stof(tokens[2]);
        n.z = std::stof(tokens[3]);
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

    // calculating edge_mat for messages sent from i to j and distance is value at cell, positive if in range, negative if out of range
    for(int i = 0; i < nodes.size(); i++){
        std::vector<float> row;
        row.reserve(nodes.size());
        for(int j = 0; j < nodes.size(); j++){
            if(i == j){
                row.push_back(0);
            }else if(i > j){
                row.push_back(edge_mat[j][i]);
            }else{
                std::cout << "calculating for i: " << i << " j: " << j << std::endl;
                float distance = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2) + pow(nodes[i].z - nodes[j].z, 2));
                row.push_back(distance);
            }
        }
        edge_mat.push_back(row);
    }
    // // print edge_mat
    // std::cout << "Edge Distance: " << std::endl;
    // for (int i = 0; i < edge_mat.size(); i++){
    //     for (int j = 0; j < edge_mat[i].size(); j++){
    //         std::cout << "(" << i << "," << j+i+1 << ": " << edge_mat[i][j] << ") ";
    //     }
    //     std::cout << std::endl;
    // }

    // // fill other triangle of matrix
    // for(int i = 0; i < nodes.size(); i++){
    //     for(int j = 0; j < i; j++){
    //         if(i > j){
    //             // float distance = edge_mat[i][j];
    //             edge_mat[i][j] = edge_mat[j][i];
    //         }
    //     }
    // }

    // print edge_mat
    std::cout << "Edge Distance: " << std::endl;
    for (int i = 0; i < edge_mat.size(); i++){
        for (int j = 0; j < edge_mat[i].size(); j++){
            std::cout << "(" << i << "," << j+i+1 << ": " << edge_mat[i][j] << ") ";
        }
        std::cout << std::endl;
    }

    // print nodes
    std::cout << "Input Nodes: " << std::endl;
    for (auto n : nodes) {
        std::cout << n.x << " " << n.y << " " << n.z << " " << n.radius << " " << n.send_wait_time << std::endl;
    }

    return 0;
}
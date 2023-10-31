#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include <time.h>

#define pi_val 3.14
#define telemetry 1

#define SINR_THRESHOLD_dB 25
#define TTL 0   // 0 is infinite packet

struct packet {
    long id = 0;
    long source;    // storing int of source node array index in nodes[i]
    long target;    // storing int of target node array index in nodes[i]
    long hops = 0;
    long ttl;
    int type = 0;   // 0 = data, 1 = ack
    int reaching_time = 0;
};

struct node {
    float x;
    float y;
    float z;
    float radius;
    int packet_target_node;
    int send_wait_time;
    long next_packet_time = 0;
    std::vector<packet> packet_buffer;
};

std::vector<node> nodes;
// std::map<std::pair<int, int>, float> edge_distance;


float get_power_at_distance(float source_power, float distance){
    // assuming uniform medium
    float power_d = source_power/(4*pi_val*distance*distance);
    return power_d;
}

float get_ideal_attenuation_at_distance(float distance){
    return 1/(4*pi_val*distance*distance);
}


float get_attenuation_at_distance(float distance){
    // simple ideal solution which results in infinite power received at distance 0
    // return 1/(4*pi_val*distance*distance);
    float x = distance*distance + 0.08985;
    float power_d = 1/(4*pi_val*x*x);
    float power_att = sqrt(power_d)/3.14;
    return power_att;
}

void test_attenuation_fn(){
    // test attenuation function
    std::cout << "Testing attenuation function" << std::endl;
    std::cout << "Distance, Attenuation" << std::endl;
    for(float i = 0.01; i < 1; i+=0.01){
        std::cout << i << ", " << get_attenuation_at_distance(i) << std::endl;
    }
}

void test_ideal_attenuation_fn(){
    // test attenuation function
    std::cout << "Testing ideal attenuation function" << std::endl;
    std::cout << "Distance, Attenuation" << std::endl;
    for(float i = 0.01; i < 1; i+=0.01){
        std::cout << i << ", " << get_ideal_attenuation_at_distance(i) << std::endl;
    }
}

// packet is assumed to be sent from i to j
// the range can be asymmetric 
std::vector<std::vector<float>> edge_d_mat; // contains adjacency matrix with +ve distance if they are in range, otherwise -ve.
std::vector<std::vector<float>> edge_power_drop;    // contains the factor of power drop of signal originating at the ni node reaching to nj node.

long timestep = 0;
long next_new_packet_id = 0;

// DEPRECATED live_packets as packets would be stored inside nodes' buffer
// std::vector<packet> live_packets;

int generate_int_between(int min, int max){
    // assuming seed is declared in main()
    return (min + (rand() % (max - min + 1)));
}

// build packets from nodes which have not sent their own packets since last time.
void generate_self_packets(){
    // for every node in nodes
    for(int i = 0; i < nodes.size(); i++){
        // check if this node has to send a packet now or earlier.
        if(nodes[i].next_packet_time >=  timestep){
            // calculate next timestep to send packet
            nodes[i].next_packet_time = timestep + nodes[i].send_wait_time;

            packet new_packet;
            new_packet.id = next_new_packet_id;
            next_new_packet_id++;   // also increment

            new_packet.ttl = TTL;
            new_packet.source = i;
            new_packet.hops = 0;
            // if packet_target_node is -1, then set packet target to random
            if(nodes[i].packet_target_node == -1){
                new_packet.target = generate_int_between(0, nodes.size());
            }else{  // set to actual value
                new_packet.target = nodes[i].packet_target_node;
            }

            // TODO: Check memory management
            // adding packet to it's own packet_buffer
            nodes[i].packet_buffer.push_back(new_packet);
        }

    }
}

int simulate_one_step(){

    // for every node in nodes
    for(int i = 0; i < nodes.size(); i++){
        // get list of packets in buffer
        // send a packet from the top of the buffer.

        //

    }

    return 0;
}

int simulate(long end_timestep) {
    while (timestep < end_timestep) {
        for(int i = 0; i < nodes.size(); i++){
            // check when was last packet sent
            // FIXME: if(timestep - nodes[i].last_packet_sent >= nodes[i].send_wait_time){
                // send packet
                // nodes[i].last_packet_sent = timestep;
                // std::cout << "sending packet from node " << i << " at timestep " << timestep << std::endl;
            // }
        }
            timestep++;
    }
    return 0;
}

int main() {
    srand(time(NULL));
    // read csv file
    std::ifstream file("input_nodes.csv");
    std::string line;
    // remove first line of header = id,x,y,z,power,rate
    std::getline(file, line); 
    // parse each line of csv file with comma separated
    while (std::getline(file, line)) {
    // check in cache file
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
        n.packet_target_node = std::stoi(tokens[6]);
        nodes.push_back(n);
    }

    edge_d_mat.reserve(nodes.size());

    // calculating edge_d_mat for messages sent from i to j and distance is value at cell, positive if in range, negative if out of range
    for(int i = 0; i < nodes.size(); i++){
        std::vector<float> row_d;
        std::vector<float> row_p;
        row_d.reserve(nodes.size());
        row_p.reserve(nodes.size());
        for(int j = 0; j < nodes.size(); j++){
            if(i == j){
                row_d.push_back(0);
                row_p.push_back(1);
                if(telemetry){ std::cout << "c[(" << i << "," << j << ") d=" << 0 <<  " pa=" << 1 << "]  "; }
            }else if(i > j){
                row_d.push_back(edge_d_mat[j][i]);
                row_p.push_back(edge_power_drop[j][i]);
                if(telemetry){ std::cout << "c[(" << i << "," << j << ") d=" << edge_d_mat[j][i] <<  " pa=" << edge_power_drop[j][i] << "]  "; }
            }else{
                float distance = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2) + pow(nodes[i].z - nodes[j].z, 2));
                row_d.push_back(distance);
                row_p.push_back(get_attenuation_at_distance(distance));
                if(telemetry){ std::cout << "c[(" << i << "," << j << ") d=" << distance <<  " pa=" << get_attenuation_at_distance(distance) << "]  "; }
            }
        }
            std::cout << std::endl;
        edge_d_mat.push_back(row_d);
        edge_power_drop.push_back(row_p);
    }


    // print edge_d_mat

    std::cout << "Edge Distance: " << std::endl;
    for (int i = 0; i < edge_d_mat.size(); i++){
        for (int j = 0; j < edge_d_mat[i].size(); j++){
            std::cout << "(" << i << "," << j+i+1 << ": " << edge_d_mat[i][j] << ") ";
        }
        std::cout << std::endl;
    }


    std::cout << "Power Attenuation (not dB): " << std::endl;
    for (int i = 0; i < edge_power_drop.size(); i++){
        for (int j = 0; j < edge_power_drop[i].size(); j++){
            std::cout << "(" << i << "," << j+i+1 << ": " << edge_power_drop[i][j] << ") ";
        }
        std::cout << std::endl;
    }

    // this is to plot graph of attenuation vs distance based on ideal and more realistic fn.
    // print values from ideal attenuation and attenuation function for linspace to see similarity
    std::cout << "Ideal Attenuation: " << std::endl;
    test_ideal_attenuation_fn();
    std::cout << "Modified Attenuation: " << std::endl;
    test_attenuation_fn();



    return 0;
}

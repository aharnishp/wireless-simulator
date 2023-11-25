# wireless-simulator

Environment to test interference in communication between multiple nodes communicating in common medium in ad-hoc network. 

## Code architecture
The main file reads inputs from ```input_nodes.csv``` and stores array of nodes with properties and independent packet buffers. Then a adjacency matrix is calculated storing amplitude attenuation factor between each node to other. Then packets are generated at discrete times based on configuration provided in the input file. At every time step, a packet is transferred from node to node following CSMA. Each node can have different transmission power levels and interference is calculated using the attenuation matrix for each node accounting for transmissions made by all nodes at their power levels.

### Status - In development

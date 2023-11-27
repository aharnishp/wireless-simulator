# wireless-simulator

Environment to test interference in communication between multiple nodes communicating in common medium in ad-hoc network. 

### Status - In development

## Code architecture
The main file reads inputs from ```input_nodes.csv``` and stores array of nodes with properties and independent packet buffers.

<img src="https://github.com/aharnishp/wireless-simulator/assets/69157507/d4962d03-beb8-418e-bf79-74d1182cba80" width="400">

<br><br>

Then a adjacency matrix is calculated storing amplitude attenuation factor between each node to other.

<img src="https://github.com/aharnishp/wireless-simulator/assets/69157507/5cef78c8-5b46-40ca-b5f8-391b177171a7" alt="Adjacency Matrices of Distance from each other and attenuation." height="300">

<br><br>

Then packets are generated at discrete times based on configuration provided in the input file. At every time step, a packet is transferred from node to node following CSMA. Each node can have different transmission power levels and interference is calculated using the attenuation matrix for each node accounting for transmissions made by all nodes at their power levels.

<img src="https://github.com/aharnishp/wireless-simulator/assets/69157507/86859b4b-2c23-4311-8545-cc80c5cdab5f" height="300" alt="Interference when 2 of the nodes are transmitting.">

<br><br>

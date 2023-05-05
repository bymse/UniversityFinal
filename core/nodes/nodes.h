#ifndef UNIVERSITYFINAL_NODES_H
#define UNIVERSITYFINAL_NODES_H
#include <vector>

int* current_node;

void start_nodes_watcher(int node_uid);

std::vector<int> get_nodes_for_task();

int get_node_for_result(int task_uid);

void register_communication(int node_uid);

void handle_connection_request(int node_uid);

#endif //UNIVERSITYFINAL_NODES_H

#ifndef UNIVERSITYFINAL_HOST_COMMUNICATION_H
#define UNIVERSITYFINAL_HOST_COMMUNICATION_H

#include "../tasks/tasks.h"
#include <string>

void load_wasm_module(std::string task_url, int task_uid);
void get_iterations(int task_uid, int offset, int count, TaskData** data);
void calculate(TaskIteration* iteration, TaskResult* data);
void send_to_node(int node_uid, void* data);

#endif //UNIVERSITYFINAL_HOST_COMMUNICATION_H

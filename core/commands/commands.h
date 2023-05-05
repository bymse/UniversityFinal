#ifndef UNIVERSITYFINAL_COMMANDS_H
#define UNIVERSITYFINAL_COMMANDS_H
#include <string>
#include "../tasks/tasks.h"
#include "../storage/storage.h"

void handle_command_with_data(std::string command_type, std::string command_data);

void start_calculate_command(int node_uid, TaskIteration* task_iteration);

void save_calculate_result_command(TaskResult* task_result);

void storage_write_command(StorageWrite *storage_write);

void healthcheck_command(int node_uid);

#endif //UNIVERSITYFINAL_COMMANDS_H

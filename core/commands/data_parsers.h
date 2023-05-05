#ifndef UNIVERSITYFINAL_DATA_PARSERS_H
#define UNIVERSITYFINAL_DATA_PARSERS_H

#include "../tasks/tasks.h"
#include "../storage/storage.h"
#include <string>

TaskIteration parse_task_iteration(std::string command_data);
TaskResult parse_task_result(std::string command_data);
Task parse_task(std::string command_data);
TaskNode parse_task_node(std::string command_data);
Shard parse_shard(std::string command_data);
StorageWrite parse_storage_write(std::string command_data);

#endif //UNIVERSITYFINAL_DATA_PARSERS_H

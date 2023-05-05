#include "data_parsers.h"

TaskIteration parse_task_iteration(std::string command_data) {
    TaskIteration task_iteration;
    memcpy(&task_iteration, command_data.c_str(), sizeof(TaskIteration));
    return task_iteration;
}
TaskResult parse_task_result(std::string command_data) {
    TaskResult task_result;
    memcpy(&task_result, command_data.c_str(), sizeof(TaskResult));
    return task_result;
}
Task parse_task(std::string command_data) {
    Task task;
    memcpy(&task, command_data.c_str(), sizeof(Task));
    return task;
}
TaskNode parse_task_node(std::string command_data) {
    TaskNode task_node;
    memcpy(&task_node, command_data.c_str(), sizeof(TaskNode));
    return task_node;
}
Shard parse_shard(std::string command_data) {
    Shard shard;
    memcpy(&shard, command_data.c_str(), sizeof(Shard));
    return shard;
}
StorageWrite parse_storage_write(std::string command_data) {
    StorageWrite storage_write;
    memcpy(&storage_write, command_data.c_str(), sizeof(StorageWrite));
    return storage_write;
}
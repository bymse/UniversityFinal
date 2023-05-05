#include "commands.h"
#include "data_parsers.h"
#include "../nodes/nodes.h"
#include "../results/results.h"
#include "../logs/logs.h"
#include <string>

#define Calculate "Calculate"
#define SaveResult "SaveResult"
#define RestartCalculate "RestartCalculate"
#define StorageWriteCommand "StorageWrite"
#define NodeConnectedCommand "NodeConnected"
#define NodeConnectionToClusterCommand "NodeConnectionToCluster"

TaskIteration parse_task_iteration(std::string command_data);

void send_command(int node_uid, std::string command_type, std::string command_data);

void handle_command_with_data(std::string command_type, std::string command_data) {
    if (command_type == Calculate) {
        TaskIteration task_iteration = parse_task_iteration(command_data);
        start_calculate(&task_iteration);
    } else if (command_type == SaveResult) {
        TaskResult task_result = parse_task_result(command_data);
        save_calculate_result(&task_result);
    } else if (command_type == "Healthcheck") {
        
    } else if (command_type == RestartCalculate) {
        TaskIteration task_iteration = parse_task_iteration(command_data);
        restart_calculate(&task_iteration);
    } else if (command_type == StorageWriteCommand) {
        StorageWrite storage_write_command = parse_storage_write(command_data);
        storage_write(&storage_write_command);
    } else if (command_type == NodeConnectedCommand) {
        int node_uid = std::stoi(command_data);
        log_node_connected(node_uid);
    } else if (command_type == NodeConnectionToClusterCommand) {
        int node_uid = std::stoi(command_data);
        handle_connection_request(node_uid);
    }
}

void start_calculate_command(int node_uid, TaskIteration *task_iteration) {
    std::string command_data = reinterpret_cast<char *>(task_iteration);
    send_command(node_uid, Calculate, command_data);
}

void save_calculate_result_command(TaskResult *task_result) {
    char *command_data = reinterpret_cast<char *>(task_result);
    int node = get_node_for_result(task_result->task_uid);
    send_command(node, SaveResult, command_data);
}

void storage_write_command(StorageWrite *storage_write) {
    char *command_data = reinterpret_cast<char *>(storage_write);
    send_command(-1, StorageWriteCommand, command_data);
}

void healthcheck_command(int node_uid) {
    send_command(node_uid, "Healthcheck", "");
}
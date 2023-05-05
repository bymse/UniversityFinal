
#include "nodes.h"
#include "../storage/storage.h"
#include "../commands/data_parsers.h"
#include "../commands/commands.h"
#include <map>
#include <thread>
#include "../logs/logs.h"

std::map<int, int> nodes_to_last_communication;

std::vector<int> get_nodes_for_watch();

void recover_cluster(int failed_node);

bool was_safely_disconnected(int node_uid);

void start_nodes_watcher(int node_uid) {
    while (true) {
        std::vector<int> nodes = get_nodes_for_watch();
        for (int i = 0; i < nodes.size(); ++i) {
            int time = nodes_to_last_communication[nodes[i]];
            if (time > 15) {
                healthcheck_command(nodes[i]);
            }

            if (time > 30) {
                log_node_disconnected(nodes[i]);
                if (!was_safely_disconnected(nodes[i])) {
                    log_node_failed(nodes[i]);
                    recover_cluster(nodes[i]);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

std::vector<int> get_nodes_for_task() {
    StorageRead storageRead = {
            .table = TaskNodesTable,
    };

    std::vector<std::string> results = storage_read(&storageRead);
    std::string nodes = "(";
    for (int i = 0; i < results.size(); ++i) {
        nodes += results[i] + ",";
    }

    StorageRead storageRead2 = {
            .table = NodesTable,
            .keys = "NodeUid not in " + nodes + ")",
    };
    results = storage_read(&storageRead2);
    std::vector<int> nodes_uids;
    for (int i = 0; i < results.size(); ++i) {
        nodes_uids.push_back(stoi(results[i]));
    }

    return nodes_uids;
}

int get_node_for_result(int task_uid) {
    StorageRead storageRead = {
            .table = TasksTable,
            .keys = "TaskUid=" + std::to_string(task_uid),
    };

    std::string result = storage_read(&storageRead)[0];
    Task task = parse_task(result);
    return task.node_uid;
}

void recover_cluster(int failed_node) {
    log_cluster_recovery();
    auto tasks = get_tasks(failed_node);
    for (int i = 0; i < tasks.size(); ++i) {
        auto task = tasks[i];
        assign_task(task.task_uid);
        log_node_assigned_for_task(task.node_uid, task.task_uid);
    }
}

void handle_connection_request(int node_uid) {
    log_node_connection_request(node_uid);
    StorageWrite query = {
            .table = NodesTable,
            .keys = "NodeUid=" + std::to_string(node_uid),
    };
    
    storage_write(&query);

    register_communication(node_uid);
    if (node_uid != -1) {
        log_id_returned_to_node(node_uid);
    }
}
#include <thread>
#include "tasks.h"
#include "../commands/commands.h"
#include "../commands/data_parsers.h"
#include "../host_communication/host_communication.h"
#include "../nodes/nodes.h"
#include "../utils/utils.h"

void start_task(int task_uid);

void start_tasks_watcher(int node_uid) {
    while (true) {
        auto tasks = get_tasks(node_uid);
        for (int i = 0; i < tasks.size(); ++i) {
            std::thread thread([&]() {
                start_task(tasks[i].task_uid);
            });
            thread.detach();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void start_calculate(TaskIteration *taskIteration) {
    std::thread thread([&]() {
        TaskResult result;
        calculate(taskIteration, &result);
        save_calculate_result_command(&result);
    });
    thread.detach();
}

void start_task(int task_uid) {
    Task task = get_task(task_uid);
    load_wasm_module(task.generator_url, task_uid);
    while (true) {
        task = get_task(task_uid);
        auto nodes = get_nodes_for_task();
        TaskData *data = new TaskData[nodes.size()];
        get_iterations(task_uid, task.offset, nodes.size(), &data);
        if (data[0].dataLength == 0) {
            break;
        }

        for (int i = 0; i < nodes.size(); ++i) {
            if (data[i].dataLength == 0) {
                break;
            }
            TaskIteration taskIteration = {task_uid, task.offset + i, data[i]};
            start_calculate_command(nodes[i], &taskIteration);
        }

        delete[] data;
    }
}

Task parse_task(std::string result){
    std::vector<std::string> splitted = split(result, ";");
    Task task = {
            .task_uid = stoi(splitted[0]),
            .offset = stoi(splitted[1]),
            .generator_url = splitted[2],
    };

    return task;
}

Task get_task(int task_uid) {
    StorageRead storageRead = {
            .table = TasksTable,
            .keys = "TaskUid=" + std::to_string(task_uid),
    };

    std::string result = storage_read(&storageRead)[0];
    return parse_task(result);
}

std::vector<Task> get_tasks(int node_uid) {
    StorageRead storageRead = {
            .table = TasksTable,
            .keys = "TaskUid=" + std::to_string(node_uid),
    };

    std::string result = storage_read(&storageRead)[0];
    
}

void assign_task(int task_uid) {
    StorageRead storageRead = {
            .table = TasksTable,
            .keys = "TaskUid=" + std::to_string(task_uid),
    };

    std::string result = storage_read(&storageRead)[0];
    Task task = parse_task(result);
    task.offset++;
    StorageWrite storageWrite = {
            .table = TasksTable,
            .keys = "TaskUid=" + std::to_string(task_uid),
            .values = std::to_string(task.task_uid) + ";" + std::to_string(task.offset) + ";" + task.generator_url,
    };

    storage_write(&storageWrite);
}
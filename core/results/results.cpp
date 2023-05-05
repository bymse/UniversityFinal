#include "results.h"
#include "../storage/storage.h"
#include "../commands/data_parsers.h"
#include "../nodes/nodes.h"
#include "../commands/commands.h"

void save_calculate_result(TaskResult* task_result) {
    StorageRead queryRead = {
      .table = ShardsTable,
      .keys = "TaskUid=" + std::to_string(task_result->task_uid)
    };

    auto shardsRaw = storage_read(&queryRead);
    std::vector<Shard> shards;
    for (int i = 0; i < shardsRaw.size(); ++i) {
        shards.push_back(parse_shard(shardsRaw[i]));
    }
    
    int node;
    for (int i = 0; i < shards.size(); ++i) {
        if (shards[i].offset >= task_result->iteration && task_result->iteration < shards[i].offset + shards[i].length) {
            node = shards[i].node_uid;
        }
    }

    if (node == *current_node) {
        StorageWrite queryWrite = {
                .table = TaskResultsTable,
                .values = std::to_string(task_result->task_uid) + "," + std::to_string(task_result->iteration) + "," +
                          task_result->result.data
        };

        storage_write(&queryWrite);
    } else {
        save_calculate_result_command(task_result);
    }
}
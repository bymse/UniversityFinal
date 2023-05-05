#ifndef UNIVERSITYFINAL_STORAGE_H
#define UNIVERSITYFINAL_STORAGE_H
#include "../tasks/tasks.h"
#include <string>


#define TasksTable "Tasks"
#define NodesTable "Nodes"
#define TaskNodesTable "TaskNodes"
#define TaskResultsTable "TaskResults"
#define ShardsTable "Shards"

struct StorageWrite {
    std::string table;
    std::string keys;
    std::string values;
};

struct StorageRead {
    std::string table;
    std::string keys;
};

void initialize();

void storage_write(StorageWrite* storageWrite);

std::vector<std::string> storage_read(StorageRead* read);

void storage_delete(StorageWrite* storageWrite);


#endif //UNIVERSITYFINAL_STORAGE_H

#ifndef UNIVERSITYFINAL_TASKS_H
#define UNIVERSITYFINAL_TASKS_H

struct TaskData {
    char* data = nullptr;
    int dataLength = 0;
};

struct Task {
    int task_uid;
    int offset;
    std::string generator_url;
    int node_uid;
};

struct TaskNode {
    int task_uid;
    int node_uid;
    int iteration;
};

struct Shard {
    int task_uid;
    int node_uid;
    int offset;
    int length;
};

struct TaskIteration {
    int task_uid;
    int iteration;
    TaskData args;
};

struct TaskResult {
    int task_uid;
    int iteration;
    TaskData result;
};

void start_tasks_watcher(int node_uid);
void start_calculate(TaskIteration *taskIteration);
void restart_calculate(TaskIteration *taskIteration);

Task get_task(int task_uid);
std::vector<Task> get_tasks(int node_uid);

void assign_task(int task_uid);


#endif //UNIVERSITYFINAL_TASKS_H

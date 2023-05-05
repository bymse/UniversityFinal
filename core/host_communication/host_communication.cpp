#include "host_communication.h"
#include <emscripten.h>
#include <string>

void load_wasm_module(std::string task_url, int task_uid) {
    EM_ASM(
        wasmModules.loadModule('$0', $1)
    , task_url, task_uid);
}

void get_iterations(int task_uid, int offset, int count, TaskData** data) {
    *data = (TaskData*) EM_ASM_PTR(
            wasmModules.getModule($0).getData($1, $2)
    , task_uid, offset, count);
}

void send_to_node(int node_uid, void* data) {
    EM_ASM(
            wasmModules.sendToNode('$0', $1)
    , node_uid, data);
}
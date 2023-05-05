#include <thread>
#include <emscripten.h>
#include "commands/commands.h"
#include "nodes/nodes.h"

typedef long int i32;

extern "C" {
EMSCRIPTEN_KEEPALIVE
void handle_command(i32 *command, i32 command_len) {
    std::string type;
    std::string data;
    for (int i = 0; i < command_len; i++) {
        char character = static_cast<char>(command[i]);
        if (type.length() > 0) {
            data.push_back(character);
        } else if (character == '{') {
            continue;
        } else if (character == '}') {
            break;
        } else if (character == ':') {
            type = data;
            data = "";
        } else {
            data += character;
        }
    }

    handle_command_with_data(type, data);
}
}

int main(int node_uid) {
    current_node = &node_uid;
    std::thread thread([node_uid]() {
        start_nodes_watcher(node_uid);
    });

    std::thread thread2([node_uid]() {
        start_tasks_watcher(node_uid);
    });
}
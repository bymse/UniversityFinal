#ifndef UNIVERSITYFINAL_LOGS_H
#define UNIVERSITYFINAL_LOGS_H

void log_node_connected(int node_uid);
void log_node_disconnected(int node_uid);
void log_node_failed(int node_uid);
void log_cluster_recovery();
void log_node_assigned_for_task(int node_uid, int task_uid);
void log_node_connection_request(int node_uid);
void log_id_returned_to_node(int node_uid);

#endif //UNIVERSITYFINAL_LOGS_H

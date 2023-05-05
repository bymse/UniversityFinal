#include "logs.h"
#include <iostream>
#include <ctime>

void log_time() {
    time_t now;
    time(&now);
    char buf[sizeof "2011-10-08T07:07:09Z"];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
    std::cout << "[" << buf << "] ";
}

void log_node_connected(int node_uid) {
    log_time();
    std::cout << "Node " << node_uid << " connected" << std::endl;
}

void log_node_disconnected(int node_uid) {
    log_time();
    std::cout << "Node " << node_uid << " was disconnected" << std::endl;
}

void log_node_failed(int node_uid) {
    log_time();
    std::cout << "Node " << node_uid << " failure detected" << std::endl;
}

void log_cluster_recovery() {
    log_time();
    std::cout << "Cluster recovery started" << std::endl;
}

void log_node_assigned_for_task(int node_uid, int task_uid) {
    log_time();
    std::cout << "Node " << node_uid << " assigned for task " << task_uid << std::endl;
}

void log_node_connection_request(int node_uid) {
    log_time();
    std::cout << "Node connection restore request received. Claimed id " << node_uid << std::endl;
}

void log_id_returned_to_node(int node_uid) {
    log_time();
    std::cout << "Return id " << node_uid << " to node" << std::endl;
}
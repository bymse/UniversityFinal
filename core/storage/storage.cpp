#include "storage.h"
#include <sqlite3.h>

sqlite3* db;
sqlite3_stmt* stmt;

void initialize() {
    sqlite3_open("storage.db", &db);
    
    const char* sql = "CREATE TABLE IF NOT EXISTS Nodes (\n"
                      "    NodeUid TEXT,\n"
                      "    NodeType INTEGER,\n"
                      "    ControlledByNodeUid TEXT\n"
                      ");\n"
                      "\n"
                      "CREATE TABLE IF NOT EXISTS TaskNodes (\n"
                      "    TaskUid TEXT,\n"
                      "    NodeUid TEXT,\n"
                      "    Iteration INTEGER,\n"
                      "    Args BLOB\n"
                      ");\n"
                      "\n"
                      "CREATE TABLE IF NOT EXISTS TaskResults (\n"
                      "    TaskUid TEXT,\n"
                      "    Iteration INTEGER,\n"
                      "    Result BLOB\n"
                      ");\n"
                      "\n"
                      "CREATE TABLE IF NOT EXISTS Tasks (\n"
                      "    TaskUid TEXT,\n"
                      "    ControlNodeUid TEXT,\n"
                      "    Status INTEGER,\n"
                      "    StartedTimestamp INTEGER,\n"
                      "    SuccessCount INTEGER,\n"
                      "    ErrorMessage TEXT,\n"
                      "    Generator BLOB,\n"
                      "    GeneratorArgs BLOB,\n"
                      "    Calculator BLOB,\n"
                      "    GeneratorOffset INTEGER,\n"
                      "    ResultsPurge INTEGER\n"
                      ");\n"
                      "\n"
                      "CREATE TABLE IF NOT EXISTS Shards (\n"
                      "    TaskUid TEXT,\n"
                      "    NodeUid TEXT,\n"
                      "    Offset INTEGER,\n"
                      "    Count INTEGER\n"
                      ");";
    sqlite3_exec(db, sql, NULL, NULL, NULL);
}

void storage_write(StorageWrite *storageWrite) {
    std::string query =
            "INSERT INTO " + storageWrite->table + " (" + storageWrite->keys + ") VALUES (" + storageWrite->values +
            ");";

    sqlite3_exec(db, query, 0, 0, 0);
}

std::vector<std::string> storage_read(StorageRead *read) {
    std::string query = "SELECT * FROM " + read->table + " WHERE " + read->keys + ";";
    sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

    std::vector<std::string> result;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))));
    }
    
    return result;
}

void storage_delete(StorageWrite *storageWrite) {
    std::string query = "DELETE FROM " + storageWrite->table + " WHERE " + storageWrite->keys + ";";
    sqlite3_exec(db, query.c_str(), 0, 0, 0);
}
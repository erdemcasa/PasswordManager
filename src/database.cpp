#include "database.hpp"
#include <iostream>

Database::Database(std::string db_path) : m_path(db_path), m_db(nullptr) {}

Database::~Database() {
    if (m_db) sqlite3_close(m_db);
}

bool Database::init() {
    if (sqlite3_open(m_path.c_str(), &m_db) != SQLITE_OK) return false;

    const char* sql = "CREATE TABLE IF NOT EXISTS passwords ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "SITE TEXT NOT NULL,"
                      "LOGIN TEXT NOT NULL,"
                      "PASS TEXT NOT NULL);";
    
    char* errMsg = nullptr;
    int rc = sqlite3_exec(m_db, sql, nullptr, nullptr, &errMsg);
    return rc == SQLITE_OK;
}

bool Database::addPassword(std::string site, std::string login, std::string pass) {
    const char* sql = "INSERT INTO passwords (SITE, LOGIN, PASS) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    
    sqlite3_bind_text(stmt, 1, site.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, login.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, pass.c_str(), -1, SQLITE_TRANSIENT);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::vector<PasswordEntry> Database::getAll() {
    std::vector<PasswordEntry> entries;
    const char* sql = "SELECT * FROM passwords;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            entries.push_back({
                sqlite3_column_int(stmt, 0),
                (const char*)sqlite3_column_text(stmt, 1),
                (const char*)sqlite3_column_text(stmt, 2),
                (const char*)sqlite3_column_text(stmt, 3)
            });
        }
    }
    sqlite3_finalize(stmt);
    return entries;
}
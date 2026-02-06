#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <vector>
#include "sqlite3.h"

struct PasswordEntry {
    int id;
    std::string site;
    std::string login;
    std::string pass;
};

class Database {
public:
    Database(std::string db_path);
    ~Database();

    bool init();
    bool addPassword(std::string site, std::string login, std::string pass);
    std::vector<PasswordEntry> getAll();

private:
    sqlite3* m_db;
    std::string m_path;
};

#endif
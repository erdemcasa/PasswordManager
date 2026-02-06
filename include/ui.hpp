#ifndef UI_HPP
#define UI_HPP

#include "database.hpp"

class PasswordUI {
public:
    PasswordUI(Database& db);
    void run();

private:
    Database& m_db;
};

#endif
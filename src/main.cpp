#include "database.hpp"
#include "ui.hpp"
#include <iostream>

int main() {
    Database db("passwords.db");
    if (!db.init()) {
        std::cerr << "Erreur d'initialisation de la base de données" << std::endl;
        return 1;
    }

    PasswordUI ui(db);
    ui.run();

    return 0;
}
#include "ui.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

PasswordUI::PasswordUI(Database& db) : m_db(db) {}

void PasswordUI::run() {
    auto screen = ScreenInteractive::TerminalOutput();

    std::string site, login, pass;
    Component input_site  = Input(&site, "Site web");
    Component input_login = Input(&login, "Identifiant");
    Component input_pass  = Input(&pass, "Mot de passe");

    auto btn_add = Button("Ajouter", [&] {
        if (!site.empty() && !pass.empty()) {
            m_db.addPassword(site, login, pass);
            site = ""; login = ""; pass = "";
        }
    });

    auto layout = Container::Vertical({
        input_site,
        input_login,
        input_pass,
        btn_add,
    });

    auto component = Renderer(layout, [&] {
        return vbox({
            text("--- GESTIONNAIRE DE MOTS DE PASSE ---") | bold | center,
            separator(),
            hbox(text(" Site : "), input_site->Render()),
            hbox(text(" Login: "), input_login->Render()),
            hbox(text(" Pass : "), input_pass->Render()),
            separator(),
            btn_add->Render() | center,
        }) | border;
    });

    screen.Loop(component);
}
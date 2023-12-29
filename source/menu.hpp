#pragma once
#include "game.hpp" 

#include <optional>
#include <vector>

class CharacterSelectionMenu : public GameState {
public:
    CharacterSelectionMenu();

    virtual void render();
    virtual void handle_inputs();

private:
    void confirmSelection();

    int displayed_character;
    int selected_character;

    PrintConsole main_printer, sub_printer;
};

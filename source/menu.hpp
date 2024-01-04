#pragma once
#include "game.hpp" 

#include <optional>
#include <vector>

class CharacterSelectionMenu : public GameState {
public:
    CharacterSelectionMenu();
    ~CharacterSelectionMenu();

    virtual void render();
    virtual GameState* handle_inputs();

private:
    GameState* confirmSelection();

    int displayed_character;
    int selected_character;

    PrintConsole main_printer, sub_printer;
};

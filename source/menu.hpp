#pragma once
#include "game.hpp" 
#include "character.hpp"

#include <optional>
#include <vector>

class CharacterSelectionMenu : public GameState {
public:
    CharacterSelectionMenu();
    ~CharacterSelectionMenu();

    virtual void render();
    virtual GameState* handle_inputs();

    virtual void init();
    virtual void deinit();

private:
    GameState* confirmSelection();

    int displayedCharacter_;
    int selectedCharacter_;

    PrintConsole mainPrinter_, subPrinter_;

    std::optional<Faction> firstPlayerFaction_;
    std::optional<Faction> secondPlayerFaction_;
};

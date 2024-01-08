# Might & Magic - Clash of Heroes

This is a partial re-implementation of the game [Might & Magic - Clash of Heroes](https://en.wikipedia.org/wiki/Might_%26_Magic:_Clash_of_Heroes) developped by Ubisoft in 2009 on Nintendo DS.

## Configuration

To setup the VSCode configuration, you need to create a `settings.json` file in the `.vscode` folder, with the following entries:

- `nds_file`: nds file containing the ROM of the game (example: `"${workspaceFolder}/${workspaceFolderBasename}.nds"`)
- `elf_file`: elf file containing the compiled instruction, and debug symbols (example: `"${workspaceFolder}/${workspaceFolderBasename}.elf"`)
- `gdb_port`: Port on which the gdb stub will be spawned for debug (example: `"8888"`)
- `desmume`: The full path of the `desmume` executable (example: `"/usr/bin/desmume"`)
- `nds_disk`: uuid of the disk on which the `.nds` file must be placed (requires the `udiskie` util)

You need to have set the `DEVKITPRO` and `DEVKITARM` environment variable.

Once this is completed, you can use the task `Desmume: Run` to start the project in the emulator, or start a debugging session using the usual VSCode workflow.

## Play

Once you start the game, you can select the character you want to play, for the first player then for the second player. You can switch character with the left-right directions or by touching the screen. After making your choice, confirm using A or pressing the character's portrait, this will either start the selection for the second player or start the game.

Sadly, we were not able to implement the gameplay part, but still worked on implementing all required peripherals. You can select units with the directional arrows, or use the touchscreen. Once a unit is selected, you can press A or touch it on the touchscreen to complete your turn. This won't trigger anything except that the other player will be able to "play". Note that the touchscreen obviously does not work for the player on the main screen.

## Rights

This is a partial re-implementation for educational purposes. All rights for the game goes to Ubisoft. This repository must not be used outside of its original purpose.

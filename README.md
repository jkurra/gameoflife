#Game of Life

##About game of Life

Game of life (or simply Life) was invented by the British mathematician John Horton
Conway. It is a "cellular automaton", that creates lifelike patterns using simple
rules. Life has no players and the game evolves based on predefined rules, that
govern wheter each 'cell' in grid is dead or alive. Rules are applied to cells
when each turn ends.   

##About this implementation

Purpose of this implementation is to give user a chance to create game boards and
observe how "life" evolves when the game progresses. In the future it will give a
possibility of modifying individual cells in game board as well as changing other
variables. Currently it is only possible to modify grid size and game speed.
However it is possible to change game appearance from settings. This implementation
also uses GTK+ and css styles to change basic appearance of the program. It will
be possible to add more stylesheets and change them from the program. However
only default style is currently available. This implementation is currently only
available for Linux environments and uses GTK+ 3.0 and glade for user interface.

##Key features

- Ability to modify grid size.
- Ability to pause game and move step by step forward.
- Ability to change game appearance.

##Install

Clone GameOfLife repository using git:
 `$ git clone https://github.com/jkurra/gameoflife.git`

install dependencies:
    requires GTK+ 3.0

build using `make` command.

Run the game using excecutable in bin folder:
"./bin/gameoflife"

##Other information

Released under MIT-license, for further licensing information read LICENSE.md.

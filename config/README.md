## Directory info
This directory contains all configurations for the game.
Add new file with individual filename to create new configuration.

## json instructions
key-value pairs are as follows "key" : "datatype"
* "grid_rows" : "integer"
  Amount of rows in game grid as integer. [game]
* "grid_cols" : "integer"
  Amount of columns in game grid as integer. [game]
* "interval" : "integer"
  Interval between each update in game as milliseconds. [game]
* "grid_visible" : "boolean"
  Determines wheter grid is drawn between cells. [appearance]
* "col_bg" : "string"
  Background color in game screen [appearance]
* "col_cell" : "string"
  Color of the cells in the game screen [appearance]
* "theme_pth" : "string"
  Path to css theme file. Affects visual appearance of every window.

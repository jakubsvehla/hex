# Hex

A simple hexadecimal editor.

Hex is a modal editor similar to vi. It operates in a normal mode (where keystrokes are interpreted as commands that control the edit session), an insert mode (where typed text is inserted into the document) and a command mode.

## Installation

    $ make install

That's it!

## Usage

### Normal mode

While in the normal mode, you can type `r` to edit the byte under the cursor or `x` to delete it. To move around the document you can use either `h`, `j`, `k`, `l` or arrow keys.

Furthermore, you can for example type `3j` to move three lines down, `2x` to delete two bytes, etc.

### Insert mode

Typing `i` switches the editor to the insert mode. As long as you type hexadecimal values they will be inserted into the document.

Pressing a wrong key or `ESC` leaves the insert mode and switches editor back to the normal mode.

### Command mode

After you make some changes you can type `:w` to save your changes.
When you are done, you can exit the editor by typing `:q`. Typing `:q!` will exit the editor and discard all unsaved changes.

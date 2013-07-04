#!/bin/sh

# Message box
dialog --title "Hello" --msgbox "Bharathi" 20 40
# Input Box.
dialog --title "Input Box" --inputbox "My Name" 10 20 Bharathi
# Calendar
dialog --title "CAL" --calendar "Set Date" 0 0 22 8 2005
# YesNo box.
dialog --title "Yes/No" --yesno "Say yes or no" 15 61
# File Select Box.
dialog --title "Please choose a file" --fselect $HOME/ 20 40
# Time Box.  
dialog --title "TIMEBOX" --timebox "Set Time" 0 0 12 34 56


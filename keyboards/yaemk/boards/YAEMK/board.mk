# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/YAEMK/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/YAEMK

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)

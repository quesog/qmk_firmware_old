# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/RV_YAEMK/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/RV_YAEMK

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)

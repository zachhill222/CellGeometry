CC         = g++

INC_DIR    = ../include
SRC_DIR    = .
OBJ_DIR    = .
BIN_DIR    = .
LIB_DIR    = ../lib

TARGET     = example

SRC        = $(wildcard $(SRC_DIR)/*.cpp)
OBJ        = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS   = -I$(INC_DIR)
CFLAGS     = -O2 -Wall
LDFLAGS    = -L$(LIB_DIR)
LDLIBS     = -lcellgeometry


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ) $(LIB_DIR)/libcellgeometry.a
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rv $(TARGET) $(OBJ)

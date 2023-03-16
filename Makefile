CC         = g++

INC_DIR    = include
SRC_DIR    = src
OBJ_DIR    = obj
LIB_DIR    = lib

TARGET     = $(LIB_DIR)/libcellgeometry.a

SRC        = $(wildcard $(SRC_DIR)/*.cpp)
OBJ        = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS   = -I$(INC_DIR)
CFLAGS     = -O2 -Wall
LDFLAGS    = -L$(LIB_DIR)
LDLIBS     = -lcellgeometry


.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $^
	ranlib $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB_DIR) $(OBJ_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rv $(LIB_DIR) $(OBJ_DIR)
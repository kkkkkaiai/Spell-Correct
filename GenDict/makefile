INC_DIR:= ./
SRC_DIR:= ./
SRCS:= $(wildcard $(SRC_DIR)*.cc)  
CC:= g++
CXXFLAGS:= -g -Wall $(addprefix -I, $(INC_DIR))
LIBS:=
OBJS:= $(patsubst %.cc, %.o, $(SRCS))

BIN_EXE:= Pre.exe

$(BIN_EXE):$(OBJS)
	$(CC) -o $@ $^ $(CXXFLAGS)  $(LIBS)  

%.o:%.cc
	$(CC) -o $@  -c $< $(CXXFLAGS)  $(LIBS)  

print:
	@echo $(OBJS)
clean:
	rm -rf $(OBJS) $(BIN_EXE) 

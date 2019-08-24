COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -o
ALL_OBJS := mem_mgr.o node.o h_map.o

all: dir_sv.bin clean_objs


dir_sv.bin: ${ALL_OBJS}
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} dir_sv.bin

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} ${COMPILER_FLAGS} mem_mgr.c

node.o: node.c node.h
	${COMPILER} ${COMPILER_FLAGS} node.c

h_map.o: h_map.c h_map.h
	${COMPILER} ${COMPILER_FLAGS} h_map.c

all_objs: ${ALL_OBJS}

clean_objs: ${ALL_OBJS}
	rm ${ALL_OBJS}

clean:
	rm dir_sv.bin

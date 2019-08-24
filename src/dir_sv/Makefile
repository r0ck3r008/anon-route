COMPILER := gcc
COMPILER_FLAGS := -g -c
LINKER_FLAGS := -g -o
ALL_OBJS := mem_mgr.o node.o h_map.o udp_workings.o main.o

all: dir_sv.bin clean_objs


dir_sv.bin: ${ALL_OBJS}
	${COMPILER} ${ALL_OBJS} ${LINKER_FLAGS} dir_sv.bin

main.o: main.c
	${COMPILER} ${COMPILER_FLAGS} main.c

udp_workings.o: udp_workings.c udp_workings.h
	${COMPILER} ${COMPILER_FLAGS} udp_workings.c

h_map.o: h_map.c h_map.h
	${COMPILER} ${COMPILER_FLAGS} h_map.c

node.o: node.c node.h
	${COMPILER} ${COMPILER_FLAGS} node.c

mem_mgr.o: mem_mgr.c mem_mgr.h
	${COMPILER} ${COMPILER_FLAGS} mem_mgr.c

all_objs: ${ALL_OBJS}

clean_objs: ${ALL_OBJS}
	rm ${ALL_OBJS}

clean:
	rm dir_sv.bin

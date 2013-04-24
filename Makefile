CC = gcc
CFLAGS = -c -g -pedantic -Wall
CFLAGS += $(shell pkg-config libprotobuf-c --cflags)
LDFLAGS += $(shell pkg-config libprotobuf-c --libs)

SERVER_EXEC = server
CLIENT_EXEC = client

SERVER_SRCS = server.c ping.pb-c.c
SERVER_OBJS = ${SERVER_SRCS:.c=.o}

CLIENT_SRCS = client.c ping.pb-c.c
CLIENT_OBJS = ${CLIENT_SRCS:.c=.o}

all: ping ${SERVER_EXEC} ${CLIENT_EXEC}

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

${SERVER_EXEC}: ${SERVER_OBJS}
	${CC} -o ${SERVER_EXEC} ${SERVER_OBJS} ${LDFLAGS}

${CLIENT_EXEC}: ${CLIENT_OBJS}
	${CC} -o ${CLIENT_EXEC} ${CLIENT_OBJS} ${LDFLAGS}

ping: ping.pb-c.c

ping.pb-c.c:
	protoc-c --c_out . ping.proto

test_server: ${SERVER_EXEC}
	./${SERVER_EXEC} --port=8080

test_client: ${CLIENT_EXEC}
	./${CLIENT_EXEC} --tcp=localhost:8080

clean:
	rm -rf ${SERVER_EXEC} ${CLIENT_EXEC}
	rm -rf ${SERVER_OBJS} ${CLIENT_OBJS}
	rm -rf ping.pb-c.c ping.pb-c.h

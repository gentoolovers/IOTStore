DIR_SRC = ./cgi
DIR_BIN = ../Bin/html/cgi-bin
DIR_RES = ../Res
DIR_SQL = $(DIR_RES)/SQLite3
DIR_HTML = ../Bin/html

SRC:=$(wildcard $(DIR_SRC)/*.c)

TARGETIST:=$(patsubst $(DIR_SRC)/%.c,%,$(SRC))

CC = gcc
AFLAGS = -Wall -g
LDFLAGS = -lsqlite3 -lm
OBJFLAGS = $(DIR_RES)/cgic.c $(DIR_SQL)/*.c 

all: 
	$(foreach TARGET,${TARGETIST},$(CC) $(DIR_SRC)/${TARGET}.c $(OBJFLAGS) -o $(DIR_BIN)/${TARGET}.cgi $(LDFLAGS);)
	$(CC) $(DIR_SRC)/History_StorageFind.c $(OBJFLAGS) -o $(DIR_BIN)/History_StorageFind.cgi $(LDFLAGS);
	$(CC) $(DIR_SRC)/History_DeviceFindPage.c $(OBJFLAGS) -o $(DIR_BIN)/History_DeviceFindPage.cgi $(LDFLAGS);
	cp ./html/*.html $(DIR_HTML);
	
.PHONY:clean
clean:
	rm $(DIR_BIN)/*.cgi;
	rm $(DIR_HTML)/*.html



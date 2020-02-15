CC:=gcc
SRCS:=$(wildcard *.c)                                                                                                                                                                                          
ELFS:=$(SRCS:%.c=%)
all:$(ELFS)

%:%.c
	    $(CC) $< -o $@ -lpthread
.PHONY:clean rebuilt
clean:
		    rm -rf $(ELFS)
rebuilt: clean all

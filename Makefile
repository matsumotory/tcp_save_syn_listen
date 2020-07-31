.PHONY: all clean

all: tcp_save_syn_listen

tcp_save_syn_listen:
	$(CC) -Wall -Wextra -D_GNU_SOURCE -shared -fPIC -o src/$@.so src/$@.c

clean:
	--rm tcp_save_syn_listen.so


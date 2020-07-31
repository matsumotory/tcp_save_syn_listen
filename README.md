# tcp_save_syn_listen

Change sys_listen() to listen() with TCP_SAVE_SYN using LD_PRELOAD

## Build

```
make
```

## Usage

```
LD_PRELOAD=src/tcp_save_syn_listen.so ./your_app
```

## Example 

```
cd test
make
# server don't use TCP_SAVE_SYN
./server
```

- other terminal

```
cd test
./client
```

- result

```
./server
tcpriv[info]: waiting...
tcpriv[info]: connected: 192.168.0.2
tcpriv[info]: syn_len: 0
server: server.c:112: read_saved_syn: Assertion `syn_len == 60' failed.
Aborted (core dumped)
```

However, if you use tcp_save_syn_listen, ./server's listen() set TCP_SAVE_SYN to socket automatically

```
LD_PRELOAD=./tcp_save_syn_listen/src/tcp_save_syn_listen.so ./server
tcpriv[info]: waiting...
tcpriv[info]: connected: 192.168.0.2
tcpriv[info]: syn_len: 60
tcpriv[info]: found tcpriv's information: kind=254 length=10 ExID=0xf991 uid=1000
tcpriv[info]: all test success.
```

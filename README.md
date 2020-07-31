# tcp_save_syn_listen

Change sys_listen() to listen() with TCP_SAVE_SYN using LD_PRELOAD

## Build

```
make
```

## Usage

```
LD_PRELOAD=src/tcp_save_syn_listen ./your_app
```

/*
 * =====================================================================================
 *
 *       Filename:  tcp_save_syn_listen.c
 *
 *    Description:  listen() with TCP_SAVE_SYN option using LD_PRELOAD
 *
 *        Version:  1.0
 *        Created:  07/31/20 12:30:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ryosuke Matsumoto / @matsumotory
 *
 * =====================================================================================
 */

#include <arpa/inet.h>
#include <dlfcn.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/types.h>

#ifndef TCP_SAVE_SYN
#define TCP_SAVE_SYN 27
#endif

#ifndef TCP_SAVED_SYN
#define TCP_SAVED_SYN 28
#endif

static int (*sys_listen)(int sockfd, int backlog);
int listen(int sockfd, int backlog);

__attribute__((constructor))
void tcp_save_syn_listen_init(void)
{
  const char *err;

  sys_listen = dlsym(RTLD_NEXT, "listen");

  err = dlerror();

  if (err != NULL) {
    fprintf(stderr, "tcp_save_syn_listen: dlsym listen() error: %s\n", err);
  }
}

int listen(int sockfd, int backlog)
{
  int old_errno = errno;
  int one = 1;

  if (setsockopt(sockfd, IPPROTO_TCP, TCP_SAVE_SYN, &one, sizeof(one)) < 0) {
    fprintf(stderr, "tcp_save_syn_listen: setsockopt TCP_SAVE_SYN error\n");
  }

  errno = old_errno;

  return sys_listen(sockfd, backlog);
}

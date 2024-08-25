#include "log.h"
#include <arpa/inet.h>
#include <errno.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512

int main(int argc, char *argv[]) {
  if (argc > 1)
    outfile = fopen(argv[1], "wba");
  else
    outfile = stdout;

  int sockfd;
  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    fprintf(stderr, "Couldn't open socket: %s\n", strerror(errno));
    return 1;
  }

  s_buffer buf = {.len = BUFLEN, .data = (u_int8_t *)malloc(BUFLEN)};

  while (1) {
    struct sockaddr addr;
    socklen_t addrs = sizeof(addr);
    int bufsize;

    if ((bufsize = recvfrom(sockfd, buf.data, BUFLEN, 0, &addr,
                            (socklen_t *)&addrs)) < 0) {
      fprintf(stderr, "Couldn't receive from address: %s\n", strerror(errno));
      free(buf.data);
      break;
    }

    buf.len = bufsize;

    recvPacket(&buf);
  }

  close(sockfd);
  free(buf.data);

  return 0;
}

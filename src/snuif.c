#include "log.h"
#include <arpa/inet.h>
#include <errno.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512

int main() {
  int sockfd;

	outfile = fopen("log.txt", "a");

  if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    printf("Couldn't open socket: %s\n", strerror(errno));
    return 1;
  }

  setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, "eth0", 5);

  s_buffer buf = {.len = BUFLEN, .data = (u_int8_t *)malloc(BUFLEN)};

	/* struct ifreq req; */

	/* strncpy(req.ifr_ifrn.ifrn_name, "eth0", IFNAMSIZ); */
	/* req.ifr_ifru.ifru_flags |= IFF_PROMISC; */
	/* ioctl(sockfd, SIOCSIFFLAGS, &req); */
  while (1) {
    struct sockaddr addr;
    socklen_t addrs = sizeof(addr);
    int bufsize;

    if ((bufsize = recvfrom(sockfd, buf.data, BUFLEN, 0, &addr, (socklen_t *)&addrs)) < 0) {
      printf("Couldn't receive from address: %s\n", strerror(errno));
      free(buf.data);
			break;
    }

    buf.len = bufsize;

    recvPacket(&buf);
  }

	/* req.ifr_ifru.ifru_flags ^= IFF_PROMISC; */
	/* ioctl(sockfd, SIOCSIFFLAGS, &req); */
  close(sockfd);
  free(buf.data);

  return 0;
}

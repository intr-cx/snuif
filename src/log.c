#include "log.h"
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <string.h>

FILE *outfile = NULL;

void recvPacket(s_buffer *buf) {
  struct ip *hdr = (struct ip *)(buf->data + sizeof(struct ethhdr));
  logIpHeader(hdr);
  switch (hdr->ip_p) {
  case IPPROTO_ICMP:
    logIcmp(buf);
    break;
  case IPPROTO_TCP:
    logTcp(buf);
    break;
  case IPPROTO_UDP:
    logUdp(buf);
    break;
  }
  fprintf(outfile, "\n");
}

void logIpHeader(struct ip *hdr) {
  struct sockaddr_in src, dst;

  memset(&src, 0, sizeof(src));
  src.sin_addr = hdr->ip_src;

  memset(&dst, 0, sizeof(dst));
  dst.sin_addr = hdr->ip_dst;

  struct protoent *pName = getprotobynumber(hdr->ip_p);

  fprintf(outfile, "%5s", pName == NULL ? (char *)&hdr->ip_p : pName->p_name);
  fprintf(outfile, "%16s →", inet_ntoa(src.sin_addr));
  fprintf(outfile, "%16s ", inet_ntoa(dst.sin_addr));
}

void logUdp(s_buffer *buf) {
  struct iphdr *hdr = (struct iphdr *)(buf->data + sizeof(struct ethhdr));
  uint8_t udpLen = hdr->ihl * 4;

  struct udphdr *udp =
      (struct udphdr *)(buf->data + sizeof(struct ethhdr) + udpLen);
  uint hdrLen = sizeof(struct ethhdr) + udpLen + sizeof(udp);

  fprintf(outfile, "%6d →%6d %04x ", ntohs(udp->uh_sport), ntohs(udp->uh_dport),
         ntohs(udp->uh_sum));

  logData(buf, hdrLen);
}

void logTcp(s_buffer *buf) {
  struct iphdr *hdr = (struct iphdr *)(buf->data + sizeof(struct ethhdr));
  uint8_t tcpLen = hdr->ihl * 4;

  struct tcphdr *tcp =
      (struct tcphdr *)(buf->data + sizeof(struct ethhdr) + tcpLen);
  uint hdrLen = sizeof(struct ethhdr) + tcpLen + sizeof(tcp);

  fprintf(outfile, "%6d →%6d %04x ", ntohs(tcp->th_sport), ntohs(tcp->th_dport),
         ntohs(tcp->th_sum));

  logData(buf, hdrLen);
}

void logIcmp(s_buffer *buf) {
  struct iphdr *hdr = (struct iphdr *)(buf->data + sizeof(struct ethhdr));
  uint8_t icmpLen = hdr->ihl * 4;

  struct icmphdr *icmp =
      (struct icmphdr *)(buf->data + sizeof(struct ethhdr) + icmpLen);
  uint hdrLen = sizeof(struct ethhdr) + icmpLen + sizeof(icmp);

  switch (icmp->type) {
  case 11:
    fprintf(outfile, "%16s", "ttl expired");
    break;
  case ICMP_ECHO:
    fprintf(outfile, "%16s", "echo");
    break;
  case ICMP_ECHOREPLY:
    fprintf(outfile, "%16s", "echo reply");
    break;
  case ICMP_REDIRECT:
    fprintf(outfile, "%16s", "redirect");
    break;
  default:
    fprintf(outfile, "%3d", (uint)icmp->type);
  }
  fprintf(outfile, "%3d %04x ", (uint)icmp->code, icmp->checksum);

  logData(buf, hdrLen);
}

void logData(s_buffer *buf, uint hdrLen) {
  fprintf(outfile, "  ");
  for (uint i = hdrLen; i < buf->len - hdrLen; i++) {
    if (buf->data[i] >= 32 && buf->data[i] <= 128)
      fprintf(outfile, "%c", (uint8_t)buf->data[i]);
    else
      fprintf(outfile, ".");
  }
}

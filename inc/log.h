#ifndef INCLUDE_INC_LOG_H_
#define INCLUDE_INC_LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>

extern FILE *outfile;

typedef struct s_buffer {
	u_int8_t *data;
	int len;
} s_buffer;

void recvPacket(s_buffer *);

void logIpHeader(struct ip *);

void logUdp(s_buffer *);
void logTcp(s_buffer *);
void logIcmp(s_buffer *);

void logData(s_buffer *, uint);

#endif  // INCLUDE_INC_LOG_H_

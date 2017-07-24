#ifndef _PACKETS_H
#define _PACKETS_H

#define MAX_NAME_SIZE 10
#define MAX_MAC_SIZE 12
enum {
	QUERY_BROADCAST, QUERY_UNICAST, HELLO_RESPONSE, CHAT, CHAT_ACK, EXITING,
} EN_PACKET;

typedef struct query_bcast {
	uint8_t type;
	char name[MAX_NAME_SIZE];
	char surname[MAX_NAME_SIZE];
	char mac[MAX_MAC_SIZE];
} query_bcast;

typedef struct query_ucast {
	uint8_t type;
	char mac[MAX_MAC_SIZE];
	char name[MAX_NAME_SIZE];
	char surname[MAX_NAME_SIZE];
	char target_name[MAX_NAME_SIZE];
	char target_surname[MAX_NAME_SIZE];
} query_ucast;

typedef struct hello_response {
	uint8_t type;
	char responder_name[MAX_NAME_SIZE];
	char responder_surname[MAX_NAME_SIZE];
	char queryier_name[MAX_NAME_SIZE];
	char queryier_surname[MAX_NAME_SIZE];
} hello_response;

typedef struct chat {
	uint8_t type;
	short lenght;
	uint8_t packed_id;
	char *message;
} chat;

typedef struct ack {
	uint8_t type;
	uint8_t packed_id;
} ack;

typedef struct exiting {
	uint8_t type;
	char name[MAX_NAME_SIZE];
	char surname[MAX_NAME_SIZE];
} exiting;

#endif


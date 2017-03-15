#ifndef Types_h
#define Types_h
#include <iterator>
#include <vector>

using namespace std;

typedef unsigned char byte;
typedef struct
{
	byte flags : 3;
	byte messageID : 5;
	byte targetService;
	byte sourceService;
	byte packetID;
	byte crc;
	
} packet_header_t;

typedef struct
{
	byte numOfPacketsInMessage;
	byte typeOfMessage;
	byte messageBitfields;
} message_header_t;

typedef struct
{
	packet_header_t packetHeader;
	vector<byte> dataContent;
	
} packet_t;

#define PACKET_SIZE 64
#define PACKET_HEADER_SIZE sizeof(packet_header_t)
#define PACKET_CONTENT_SIZE PACKET_SIZE - PACKET_HEADER_SIZE
#define MESSAGE_HEADER_SIZE 3

#endif

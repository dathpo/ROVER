#include <PortIPAddr.h>
#include <Comms.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#define PORT 1153
#define BUFSIZE 128
#define STARTBYTE 0xFE
#define ENDBYTE 0xFF
struct sockaddr_in myaddr;      /* our address */
struct sockaddr_in remaddr;     /* remote address */
socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
int recvlen;                    /* # bytes received */                         /* our socket */
int fd1;

std::mutex mtx;           // mutex for critical section
PortIPAddr::PortIPAddr(int id) {
	_id = id;
	_start_last = false;
	_end_last = false;
	_packet_start_rcvd = false;
	_buffer.reserve(BUFSIZE);
	  if ((fd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                perror("cannot create socket\n");
        }

        /* bind the socket to any valid IP address and a specific port */

        memset((char *)&myaddr, 0, sizeof(myaddr));
				remaddr.sin_family = AF_INET;
				remaddr.sin_addr.s_addr = inet_addr("169.254.4.41");
				remaddr.sin_port = htons(PORT);
        myaddr.sin_family = AF_INET;
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        myaddr.sin_port = htons(PORT);
	
	if (bind(fd1, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
                perror("bind failed");

        }
}

void PortIPAddr::read() {
	mtx.lock();
	//recvlen = recvfrom(fd1, tempBuffer, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
	char buffer[549];
	struct sockaddr_storage src_addr;
	socklen_t src_addr_len=sizeof(src_addr);
	ssize_t count=recvfrom(fd1,buffer,sizeof(buffer),0,(struct sockaddr*)&src_addr,&src_addr_len);
	if (count==-1) {
    		cout << "ERROR";
	} else if (count==sizeof(buffer)) {
    		//warn("datagram too large for buffer: truncated");
	} else {
    		//handle_datagram(buffer,count);
		for(int i=0; i<count; ++i)
    			std::cout << std::hex << (int)buffer[i];
	}
	handleData(&buffer[0],(int)count);
  mtx.unlock();
}

void PortIPAddr::handleData(char *buffer,int dataSize) {
  for(int buffSize=0;buffSize<dataSize;buffSize++){
    byte b = buffer[buffSize] ;
    //printf ("%d\n",int(b));
    if (b == STARTBYTE) {
      if (_start_last) { // byte-stuffed start byte
        if (_packet_start_rcvd) {
          _buffer.push_back(b);
          _start_last = false;
        }
      } 
      else if (_end_last) {
        if (_packet_start_rcvd) {
          // packet end
          packet_t p = getPacketFromBuffer();
			packetQueue.addPacket(p); //try to add packet to queue, send on if required.
			
		printf ("Packet Contents:");
         	for(int i=0;i<_buffer.size();i++){
				
				printf ("%d",int(_buffer[i]));
			}
			
			printf ("\n");
		//printf ("Testing Packet");
		fflush(stdout);
          // send the packet to the packet queue
          _buffer.clear();
          _packet_start_rcvd = false;
		 try { Message newMessage=packetQueue.checkPacketQueue();  
		 if(newMessage._messageID){messageQueue.addMessage(newMessage);} } catch (const std::exception&) { printf("Error, no packet returned from checkpacketqueue"); }
		 
        }
      } 
      else {
        _start_last = true;
      }
      _end_last = false;
    } 
    else if (b == ENDBYTE) {
      if (_start_last) {
        _packet_start_rcvd = true;
        _start_last = false;
      }
      if (_end_last) { // byte-stuffed end byte
        if (_packet_start_rcvd) {
          _buffer.push_back(b);
          _end_last = false;
        }
      } 
      else {
        _end_last = true;
      }
      _start_last = false;
    } 
    else {
      if (_start_last) {
        // start of new packet
    printf ("START OF NEW PACKET");
        _buffer.clear();
        _start_last = false;
        _packet_start_rcvd = true;
      } 
      else if (_end_last) {
        // something went wrong - we have a single end byte
        _buffer.clear();
        _end_last = false;
        _packet_start_rcvd = false;
      }
      if (_packet_start_rcvd) {
    printf ("%c\n",b);
        _buffer.push_back(b);
      }
    }
  }
}


void PortIPAddr::write(vector<byte> packet) {
	sendto(fd1, packet.data(), packet.size(), 0, (struct sockaddr *)&remaddr, addrlen);
}

packet_t PortIPAddr::getPacketFromBuffer() {
	// Check if buffer has complete packet, if so return
	// TODO - implement Port::getPacketFromBuffer
	packet_header_t tempPacketHeader;
	tempPacketHeader.flags=_buffer[0] & 0x7;
	tempPacketHeader.messageID=_buffer[0] & 0x1F;
	tempPacketHeader.targetService=_buffer[1];
	tempPacketHeader.sourceService=_buffer[2];
	tempPacketHeader.packetID=_buffer[3];
	tempPacketHeader.crc=_buffer[4];
	packet_t testPacket;
	testPacket.packetHeader=tempPacketHeader;

	testPacket.dataContent.reserve(59);
	for(int i=5;i<_buffer.size();i++){

		testPacket.dataContent.push_back(_buffer[i]);
	}

	return testPacket;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <mem.h>
#include <string.h>
#include "ipx.h"
#include <time.h>

#define BUFFER_SIZE 504

typedef struct _fileSegment{
        long int size;
        long int num;
} fileSegment;
unsigned char segmentBuffer[BUFFER_SIZE];

void main(void) {
        long int  SegmentsCounter;
        int i,j;
        FILE* file;
        fileSegment tmp;
        
        static unsigned Socket = 0x4444;
        struct ECB RxECB;
        struct IPX_HEADER RxHeader;
        unsigned char RxBuffer[BUFFER_SIZE];
        char name[256] = "result.jpg";
        file = fopen(name, "wb+");
        if(file==NULL){
                printf("Error creating file!");
                exit(101);
        }
        if(ipx_init() != 0xff) {
                printf("Error initializing IPX!\n"); 
                exit(102);
        }

        if(IPXOpenSocket(SHORT_LIVED, &Socket)) {
                printf("Error opening socket!\n");
                exit(-1);
        };

        memset(&RxECB, 0, sizeof(RxECB));
        RxECB.Socket                    = IntSwap(Socket);
        RxECB.FragmentCnt               = 3;
        RxECB.Packet[0].Address         = &RxHeader;
        RxECB.Packet[0].Size            = sizeof(RxHeader);
        RxECB.Packet[1].Address         = RxBuffer;
        RxECB.Packet[1].Size            = BUFFER_SIZE;
        RxECB.Packet[2].Address         = &tmp;
        RxECB.Packet[2].Size            = 8;
        
        IPXListenForPacket(&RxECB);
        printf("Waiting for a response from the server...\n");
        while(1) {
                if(!RxECB.InUse){
                        printf("Response received!\n");
                        break;
                };
        }
        IPXListenForPacket(&RxECB);
        while(RxECB.InUse){}
        memcpy(&SegmentsCounter, RxBuffer, tmp.size);
        rintf("Receiving data...\n");
        for(i = 0; i <= SegmentsCounter; i++){
                IPXListenForPacket(&RxECB);
                while(RxECB.InUse){}
                for(j = 0; j < tmp.size; j++){
                        fputc(RxBuffer[j],file);
                };
                if(tmp.num == SegmentsCounter){
                        break;
                };
        }

        fclose(file);
        IPXCloseSocket(&Socket);
        printf("Transmission completed successfully!\n");
        exit(0);
}
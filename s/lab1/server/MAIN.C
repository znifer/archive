#include <STDIO.H>
#include <STDLIB.H>
#include <CONIO.H>
#include <MEM.H>
#include <STRING.H>
#include <DOS.H>
#include "IPX.H"

#define BUFFER_SIZE 504

// -1 сегмент - начало передачи
//  0 сегмент - кол-во значащих сегментов
//1-n сегмент - значащие сегменты
//n+1 сегмент - конец передачи

typedef struct _fileSegment{
        long int size;
        long int num;
} fileSegment;

unsigned char segmentBuffer[BUFFER_SIZE];

long int getFileSize(FILE* stream){
        long int size;
        fseek(stream,0,SEEK_END);
        size = ftell(stream);
        fseek(stream,0,SEEK_SET);
        return size;
};

void main(void) {
        //размер файла в байтах
        long int fileSize;
        //кол-во полных сегментов, всего сегментов
        long int fullSegmentsCounter, segmentsCounter;
        //размер неполного последнего сегмента (если 0 то сегмента нету)
        long int lastSegmentSize;
        FILE* file;
        FILE* checkFile;
        fileSegment tmp;
        
        static unsigned Socket = 0x4444;
        struct ECB ServerECB;
        struct IPX_HEADER InHeader, OutHeader;
        unsigned char OutBuffer[BUFFER_SIZE];
        int i;
        char filename[255] = "image.jpg";
        int delayValue = 0;

        printf("Enter delay between segments: ");
        scanf("%i", &delayValue);

        printf("Enter the name of the file you want to transmit: ");
        scanf("%s", filename);

        if(ipx_init() != 0xff) {
                printf("Error initializing IPX!\n"); 
                exit(101);
        }
        if(IPXOpenSocket(SHORT_LIVED, &Socket)) {
                printf("Error opening socket!\n");
                exit(102);
        }

        memset(&ServerECB, 0, sizeof(ServerECB));

        file = fopen(filename, "rb+");
        if(file != NULL){
                fileSize = getFileSize(file);
                fullSegmentsCounter = fileSize / (BUFFER_SIZE - 8);
                lastSegmentSize = fileSize % (BUFFER_SIZE - 8);
                segmentsCounter = fullSegmentsCounter + 1;
                fclose(file);
                file = fopen(filename,"rb+");
                checkFile = fopen("IMG.jpg", "wb+");
        }else{
                printf("Error opening file!\n");
                exit(103);
        };

        printf("Press any key to start...\n");
        getch();


        tmp.size = 0;
        tmp.num = -1;
        segmentBuffer[0] = 0;
       
        memcpy(OutBuffer,&segmentBuffer,BUFFER_SIZE);

        OutHeader.PacketType = 4;
        memset(OutHeader.DestNetwork, 0, 4);
        memset(OutHeader.DestNode, 0xFF, 6);
        OutHeader.DestSocket = IntSwap(Socket);

        ServerECB.Socket                = IntSwap(Socket);
        ServerECB.FragmentCnt           = 3;
        ServerECB.Packet[0].Address     = &OutHeader;
        ServerECB.Packet[0].Size        = sizeof(OutHeader);
        ServerECB.Packet[1].Address     = OutBuffer;
        ServerECB.Packet[1].Size        = BUFFER_SIZE;
        ServerECB.Packet[2].Address     = &tmp;
        ServerECB.Packet[2].Size        = 8;
        IPXSendPacket(&ServerECB);
        printf("Transmission started!\n");

        //Отправляем клиенту количество сегментов
        tmp.num = 0;
        tmp.size = sizeof(segmentsCounter);
        memcpy(segmentBuffer, &segmentsCounter, sizeof(segmentsCounter));
        memcpy(OutBuffer, &segmentBuffer, BUFFER_SIZE);
        IPXSendPacket(&ServerECB);
        
        for(i = 1; i <= fullSegmentsCounter; i++){
                tmp.num = i;   
                tmp.size = BUFFER_SIZE; 
                fread(OutBuffer,1,BUFFER_SIZE,file);
                fwrite(OutBuffer,1,BUFFER_SIZE,checkFile);
                IPXSendPacket(&ServerECB);
                delay(delayValue);
        };
        delay(delayValue);
        tmp.num = segmentsCounter;   
        tmp.size = lastSegmentSize;   
        fread(OutBuffer,1,lastSegmentSize,file);
        fwrite(OutBuffer,1,lastSegmentSize,checkFile);
        IPXSendPacket(&ServerECB);

        printf("Transmission completed successfully!\n");

        fclose(file);
        fclose(checkFile);
        IPXCloseSocket(&Socket);
        exit(0);
}
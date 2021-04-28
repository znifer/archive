#include <stdio.h>


int searchMinPos (int *a, int size){
    int min = a[0], minPos = 0;
    for (int i = 0; i < size; i++){
		if (min > a[i]){
	    	min = a[i];
	 		minPos = i;
		}
    }
    //printf("\n in current seq min is %i\n", minPos+1);
	return minPos;
}

int main(){
    int i = 0, seqSize = 0, readPos = 0, writePos = 0, tmp = 1, flag = 1;
    int a[10] = {9, 1, 9, 9, 0, 7, 1, 8};
    int seq[10];
    seq[i] = a[readPos];
    readPos++; seqSize++;
    i++;
    while (readPos < 9){
        if (a[readPos] == 0){
            for (int k = searchMinPos(seq, seqSize); k < seqSize; k++){
                printf ("%i ", seq[k]);
            }
            printf ("%i ", 0);
           // printf(" rewriting is done\n");
            i = 0;
            seqSize = 0;
            readPos++;
        } else {
            //printf ("checking %i-pos with %i value\n", readPos, a[readPos]);
            seq[i] = a[readPos];
            readPos++; seqSize++;
            i++;
        }
    }
}




int main1(){
    int i = 0, seqSize = 0, readPos = 0, writePos = 0, tmp = 1, flag = 1;
    int a[8] = {9, 1, 9,9, 0, 9, 1, 9};
    int seq[10];
    while (readPos < 9){
        seq[i] = a[readPos];
        readPos++; seqSize++;
        i++;
        if (a[i] == 0){
            for (int k = searchMinPos(seq, seqSize-1); k < seqSize-1; k++){
                printf ("%i ", seq[k]);
            }
        i=0;

        }
    }
}

#include <stdio.h>
#include <stdlib.h>

void inputFileContent (char *filename){
    FILE *f;
    int tmp;
    printf ("Input num`s:\n");
    if ((f = fopen (filename, "wb"))!= NULL){
        while (scanf("%i", &tmp)){
            printf("%i ", tmp);
            fwrite(&tmp, sizeof(int), 1, f);
            //fprintf(f, "%i", tmp);
        }
        printf ("done\n");
        fclose(f);
    } else {
        printf ("err");
        exit(1);
    }
    fclose(f);
}

void outputFileContent (char *filename){
    FILE *f;
    int tmp;
    if ((f = fopen (filename, "rb"))!= NULL){
        while (!feof(f)){
            fread (&tmp, sizeof(int), 1, f);
            printf ("%i, ", tmp);
        }
    } else {
        printf ("err");
        exit(1);
    }
    printf ("done");
    fclose(f);
}

void createFile (char *filename){
    FILE *f;
    if ((f = fopen (filename, "wb")) == NULL){
        printf ("err");
        exit(1);
    }
    fclose(f);
}

int searchBorders (FILE *f, int minPos){
    int tmp, min, length = 1;
    fread (&tmp, sizeof(int), 1, f);
    min = tmp;
    while (tmp != 0 && tmp != EOF){
        if (min > tmp){
            min = tmp;
            minPos = ftell(f)-1;
        }
        length++;
        fread (&tmp, sizeof(int), 1, f);
    }
}

void removeEl (char *filename){
    FILE *f;
    int flag = 1, fileStart, rewritePos, seqStart, seqFin, writePos;
    if ((f = fopen(filename, "r+b")) == NULL){
            printf ("err");
            exit (1);
        }
    rewind(f);
    fileStart = ftell (f);
    while (flag){
        seqStart = ftell(f);
        searchBorders(f, rewritePos);
    }
}

void removeEl1 (char *filename){
    FILE *f;
    int writePos, readPos, startPos, min, minPos, tmp, endPos;
    if ((f = fopen(filename, "r+b")) == NULL){
            printf ("err");
            exit (1);
        }
    rewind(f);
    while (!feof(f)){
        startPos = ftell(f);
        fread (&tmp, sizeof(int), 1, f);
        min = tmp;
        minPos = ftell (f);
        while (tmp != 0){
            fread (&tmp, sizeof(int), 1, f);

        }
    }
    printf ("%i %i", min, minPos);
}


int main(){
    char filename[256];
    printf ("path?\n");
    gets(filename);
    printf("File already created? y/n ");
    char mode = getchar();
    if (mode == 'n'){
        createFile(filename);
        inputFileContent (filename);
    }
    removeEl(filename);
    //outputFileContent(filename);


    return 0;
}

#include <stdio.h>
#include <math.h>
#include "string.h"
float cosine(float x, float precision, FILE*file){
    float result=0;
    float dif=1.;
    int iter=1;
    do{
        result+=dif;
        printf("%s %f", iter!=1?(dif<0?" ":"+"):" ",dif);
        dif*=-x*x/ (float) (2*(iter) * (2*iter - 1));
        iter+=1;
    } while (fabsf(dif)>precision);
    printf("=%f",result);
    return result;
}
float sine(float x, float precision, FILE*file){//calculate sine
    float result=0;
    float dif=x;
    int iter=1;
    do{
        result+=dif;
        fprintf(file,"%s %f", iter!=1?(dif<0?" ":"+"):" ",dif);
        dif*=-x*x/(float) ((iter + 1) * (iter + 2));
        iter+=2;
    } while (fabsf(dif)>precision);
    fprintf(file,"%s %f", iter!=1?(dif<0?" ":"+"):" ",dif);
    fprintf(file, "=%f",result);
    printf("=%f",result);
    return result;
}
int main() {
    float val=-360.;

    FILE* fptr1;
    fptr1=fopen("test.txt", "w");
    if(fptr1!=NULL) {
        for (float i = 0; i <= 1230; i +=50) {
            fprintf(fptr1, "sin(%f)=", i);
            sine(fmodf(i,360.) / 180. * M_PI, 1E-5, fptr1);
            fprintf(fptr1, "\n");
        }
        fprintf(fptr1, "sin(%f)=", 1230.);
        sine(fmodf(1230., 360.) / 180. * M_PI, 1E-5, fptr1);
        fprintf(fptr1, "\n");
        fclose(fptr1);
    } else{
        printf("File not opened!");
    }
    FILE* fptr;
    fptr=fopen("test.txt", "r+");
    FILE *ending;
    ending=fopen("result.bak", "w");
    char content[50];
    if(fptr!=NULL){
        if (ending==NULL){
            printf("The end file is not created!\n");
            return 1;
        }
        printf("File Opened successfully\n");
        do {
            fgets(content, 50, fptr);
            fprintf(ending, "%s", content);
            printf("%s\n", content);
        } while (!feof(fptr));
        fclose(fptr);
        fclose(ending);
        fptr=fopen("result.bak", "r+");
        do {
            fgets(content, 50, fptr);
            printf("%s\n", content);
        } while (!feof(fptr));
        fclose(fptr);
    } else{
        printf("File not open!\n");
    }
}

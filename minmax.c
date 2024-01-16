#include<stdio.h>
int max_min_avg(int fitness[],int len){
    int max=fitness[0],min=fitness[0];
    int sum=0;
    for(int i=0;i<len;i++){

        sum+=fitness[i];

        if(max<fitness[i]){
            max=fitness[i];
        }
        if(min>fitness[i]){
            min=fitness[i];
        }
    }
    double avg=(float)sum/(float)len;
    return printf("highest conflicting edges:%d\nlowest conflicting edges:%d\naverage conflicting edges:%2.lf",max,min,avg);
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define DATASETSIZE 10

void heap_sort(double* srcdata, int len);
int main(void){
    double srcdata[DATASETSIZE];
    int idx, jdx;

    srand(time(NULL));
    for( idx=0; idx<DATASETSIZE; idx++ ){
        srcdata[idx] = rand()*1.0/RAND_MAX;
    }
    for( idx=0; idx<DATASETSIZE; idx++ ){
        if(idx%10 == 0) printf("\n\n");
        printf(" %f, ",srcdata[idx]);
    }
    printf("\n");
    heap_sort(srcdata,DATASETSIZE);
    for( idx=0; idx<DATASETSIZE; idx++ ){
        if(idx%10 == 0) printf("\n\n");
        printf(" %f, ",srcdata[idx]);
    }
    printf("\n");

	return(0);
}

void swap(double* srcdata,int i,int j){
    double temp;

    temp = srcdata[i];
    srcdata[i] = srcdata[j];
    srcdata[j] = temp;
}

int left(int i){
        return 2*i;
}

int right(int i){
        return 2*i+1;
}


void max_heapify(double* srcdata,int len,int i){
        int l = left(i);
        int r = right(i);
        int largest = 0;

        if( l<len && srcdata[l]>srcdata[i] ){
                largest = l;
        }else largest = i;
        if( r<len && srcdata[largest]<srcdata[r] ){
                largest = r;
        }
        if( largest!=i ){
                swap(srcdata,largest,i);
                max_heapify(srcdata,len,largest);
        }
}

void build_max_heap(double* srcdata,int len){
        int idx=0;

        for(idx=(int)(floor(len/2));idx>=0;idx--){
                max_heapify(srcdata,len,idx);
        }
}

void heap_sort(double* srcdata,int len){
        int idx=0;

        build_max_heap(srcdata,len);
        for(idx=len-1;idx>0;idx--){
                swap(srcdata,0,idx);
                len--;
                max_heapify(srcdata,len,0);
        }
}

double heap_maximum(double* srcdata){
	return(srcdata[0]);
}
 
double heap_extract_max(double* srcdata, int len){
	double max;
	if(len<=0){
		printf("heap underflow.\n");
		exit(1);
	}

	max = srcdata[0];
	srcdata[0] = srcdata[len-1];
	len--;
	max_heapify(srcdata,len,0);
	return(max);
}

int parent(int idx){
	return( floor(idx/2) );
}

void heap_increase_key(double* srcdata, int len, int idx, double dValue){
	if(srcdata[idx]<dValue){
		printf("new key is smaller than current key.\n");
		exit(1);
	}
	srcdata[idx] = dValue;

	while( idx>0 && srcdata[parent(idx)]<srcdata[idx] ){
		swap(srcdata,idx,parent(idx));
		idx = parent(idx);
	}
}

void max_heap_insert(double* srcdata, int* len, double dValue){
	*len = *len + 1;
	srcdata[*len-1] = -1;
	heap_increase_key(srcdata,*len,*len,dValue);
}
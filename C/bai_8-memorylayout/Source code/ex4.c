#include <stdio.h>
#include <stdlib.h>
//dynamic memory allocation : cấp phát động
//dangling pointer : con trỏ treo
int main(){
    int size = 5;
    int* ptr = (int*)malloc(size*sizeof(int)); //0x00 , 0x05 , 0x0A , 0x0f , 0x14
    
    if(ptr == NULL){
        printf("không đủ vùng nhớ cấp phát");
        return 1;
    }

    for(int i = 0 ; i < size ; i++){
        ptr[i] = i;
        printf("%d = %d\taddress: %p\n",i,ptr[i],&ptr[i]);
    }

    int new_size = size + 5;
    printf("after\n");

    ptr = (int*)realloc(ptr,new_size*sizeof(int));

    if(ptr == NULL){
        printf("không đủ vùng nhớ cấp phát");
        return 1;
    }
    
    for(int i = 0 ; i < new_size ; i++){
        ptr[i] = i;
        printf("%d = %d\taddress: %p\n",i,ptr[i],&ptr[i]);
    }
    free(ptr); 
    ptr = NULL;
}
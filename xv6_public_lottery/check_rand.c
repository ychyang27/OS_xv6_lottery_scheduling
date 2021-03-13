#include "types.h"
#include "user.h"

// 랜덤함수의 균일성 테스트를 위한 함수.
// reference : https://en.wikipedia.org/wiki/Linear-feedback_shift_register
int lfsr = 0xacbde;
int 
rand(int max){
  int bit = ((lfsr)^(lfsr>>2)^(lfsr>>4)^(lfsr>>7)) & 1;
  lfsr = (lfsr>>1)|(bit<<15);
return lfsr%max;
}


int 
main(int argc, char *argv[])
{   
    
    if(argc !=2){
        printf(2,"Usage : check_rand [loopcount]");
        exit();
    }

    int num_above_500 = 0;
    int num_below_500 = 0;
    int max = 1000;
    int loop_cnt = atoi(argv[1]);
    for(int j=0; j<loop_cnt; j++){   
        int random_number = rand(max);
        printf(1,"random number is %d\n",random_number);
        if(random_number >= 500) num_above_500++;
        else num_below_500++;

    }
    printf(1,"====================================================================\n");
    printf(1,"result :above 500 : %d | below : %d \n",num_above_500,num_below_500);
    exit();
}
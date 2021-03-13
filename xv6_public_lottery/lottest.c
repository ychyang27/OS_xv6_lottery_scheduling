#include "types.h"
#include "user.h"
// lottery scheduling 테스트 함수.
// input 값을 티켓으로 설정하여 해당하는 티켓을 가진 child process 들을 생성한 후, 실행시간을 보여준다.
int main(int argc, char* argv[]){
    if(argc<2) {
        printf(2,"Usage : lottest [child's tix] ...\n");
        exit();
    }
    int parent = getpid();
    printf(1,"### %d <<lottery test>> Parent pid %d is created",uptime(),parent);

    for(int i=1; i<argc; i++){
        const int pid = fork(); // create new process. pid는 부모의 것으로 부터 증가한다.
        const int intix = atoi(argv[i]); // input ticket 값
        if(pid == 0){
            setix(intix); // setix := 티켓설정함수
            // child의 생성때 print한다.
            printf(1,"### %d <<lottery test>> Child pid %d is created (tickets = %d)\n",uptime(),getpid(),intix);
            int pid = getpid();
            int tix = gpinfo(1);
            int tic =uptime();
            // ticks 가 일정 시간이 될때까지 while문을 돌린다.
            while(uptime()<3000){
                      if(uptime() >= tic+20){ // 20초 단위로 프린트하여 현재 정보를 읽어들인다.
                       // 각 시간 별로 pid,winner_ticket,ticket,total tickets,실행시간을 프린트한다.                       
                       printf(1,"### %d  >> pid%d <- WIN %d (tix %d of %d) || time : %d\n",uptime(),pid,gpinfo(3),tix,gpinfo(4),gpinfo(2));
                       
                      tic = uptime();
                      }
                      

            }
            // 종료시 프린트한다.
            printf(1,"### %d <<lottery test>> Child pid %d exit\n",uptime(),getpid());
            exit();
        }
        else if (pid <0){
            printf(2,"fork error\n");
            exit();
        }
    }
    printf(1,"### %d <<lottery test>> Parent exits\n",uptime());
    exit();
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define infinite 110000

int geometric(double rand, double p){
return ceil(log(1-rand)/log(1-p));
}

int main() {

srand((double)time(NULL));
double lambda[2]={1,1};//設0.1進來任務次數少, 設0.9進來任務次數多
double p[2]={0.2,0.2};//設0.1 log0.9=-0.045 產生封包數多, 設0.9 log0.1=-1 ,產生封包數少
double x=0, test=0, total=0, stablesum[4]={0};
int abcd[4][infinite]={0},cost[infinite]={0},finish[infinite]={0}, head[4]={0};
int Bernoulli[4]={0},time=0;
int service=14, i=0, j=0, n=0, taskcount=0, breakcount=0, statistic1[4]={0}, statistic2[4]={0};
int finishtaskcount=0, counts[4]={0} ;


while(finish[10000]==0){
    time++;
    for(j=0;j<2;j++){
        x = (double)rand()/RAND_MAX;
        //lambda =(double)rand()/RAND_MAX;
        test = (double)rand()/RAND_MAX;
        if(lambda[j]>test){
            Bernoulli[j] =1;
        }
        else{
            Bernoulli[j] =0;
        }
    }
    
    if(Bernoulli[0]!=0 || Bernoulli[1]!=0){
        taskcount++;
        
        for(j=0; j<2; j++){
            if(Bernoulli[j]==1){
                abcd[j][taskcount] =geometric(x,p[j]);
            }
        }
        
        if(abcd[0][taskcount]==1)
            statistic1[0]++;
        else if(abcd[0][taskcount]==2)
            statistic2[0]++;//統計數量
        
        
        
//        printf("Time%d 產生任務 task %d\n""a[%d]=%d\t""b[%d]=%d\t""\n",time,taskcount,taskcount,abcd[0][taskcount],taskcount,abcd[1][taskcount]);//每次產生的任務數
        
        //記錄總每個序列的總任務數
        for(j=0;j<2;j++){
            counts[j]+=abcd[j][taskcount];
        }
        
    }
    
    else if(Bernoulli[0]==0 && Bernoulli[1]==0){
        breakcount++;
        //printf("Time%d 休息\n",time);//每次產生的任務數
    }
    
    ///printf("統計：%d個休息\n",breakcount);
    ///printf("統計：%d個任務\n",taskcount);
    
    //為了記錄最前頭
    for(j=0;j<2;j++){
        while(abcd[j][head[j]]==0 && head[j]<taskcount){
            head[j]+=1;
        }
    }
    
//    printf("處理前排在最前面的是\n""a[%d]=%d\t""b[%d]=%d\t""\n", head[0], abcd[0][head[0]], head[1], abcd[1][head[1]]);
    printf("處理前每列總數\n""c1=%d\t""c2=%d\t""\n",counts[0], counts[1] );
    
    
    while(1){
        //先記錄做幾次再動作
        for(n=1;n<=taskcount;n++){
            if(abcd[0][n]!=0 || abcd[1][n]!=0){
                cost[n]= cost[n]+1;
            }
            else{
                finish[n]=1;
            }
        }
        
        //max weight
        if(counts[0]>counts[1]){
            for(j=0; j<service; j++){
                if(abcd[0][head[0]]>0){
                    counts[0]-=1;
                    abcd[0][head[0]]-=1;
                }
                
                else if(abcd[0][head[0]]==0 && counts[0]>0){
                    while(abcd[0][head[0]]==0 && head[0]<taskcount){
                        head[0]+=1;
                    }
                    abcd[0][head[0]]-=1;
                    counts[0]-=1;
                }
            }
            
        }
        
        else if(counts[1]>counts[0]){
            for(j=0; j<service; j++){
                if(abcd[1][head[1]]>0){
                    counts[1]-=1;
                    abcd[1][head[1]]-=1;
                }
                
                else if(abcd[1][head[1]]==0 && counts[1]>0){
                    while(abcd[1][head[1]]==0 && head[1]<taskcount){
                        head[1]+=1;
                    }
                    abcd[1][head[1]]-=1;
                    counts[1]-=1;
                }
            }
        }
            
        
        else if(counts[0]!=0 && counts[0]==counts[1]){
            if(head[0]<=head[1]){
                for(j=0; j<service; j++){
                    if(abcd[0][head[0]]>0){
                        counts[0]-=1;
                        abcd[0][head[0]]-=1;
                    }
                    
                    else if(abcd[0][head[0]]==0 && counts[0]>0){
                        while(abcd[0][head[0]]==0 && head[0]<taskcount){
                            head[0]+=1;
                        }
                        abcd[0][head[0]]-=1;
                        counts[0]-=1;
                    }
                }
            }
            
            else{
                for(j=0; j<service; j++){
                    if(abcd[1][head[1]]>0){
                        counts[1]-=1;
                        abcd[1][head[1]]-=1;
                    }
                    
                    else if(abcd[1][head[1]]==0 && counts[1]>0){
                        while(abcd[1][head[1]]==0 && head[1]<taskcount){
                            head[1]+=1;
                        }
                        abcd[1][head[1]]-=1;
                        counts[1]-=1;
                    }
                }
            }
        }
    
        
        
        printf("處理後每列總數\n""c1=%d\t""c2=%d\t\n""",counts[0], counts[1]);
            break;
        }
    }
    
    
    
    for(j=1;j<=100000;j++){
        if(finish[j]==1){
            printf("Task %d costs %d time(s)\n", j, cost[j]);
            total=total+cost[j];//放在這裡統計，未完成的任務就不計算
            finishtaskcount++;//計算完成的任務
        }
    }
    
    printf("The average costs are %f time(s)\n",total/finishtaskcount);
    printf("任務產生一個的有%d次\t 任務產生兩個的有%d次\n",statistic1[0], statistic2[0]);

    return 0;
}

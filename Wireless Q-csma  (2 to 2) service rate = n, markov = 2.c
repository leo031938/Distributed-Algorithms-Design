#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define infinite 200000

int geometric(double rand, double p){
    return ceil(log(1-rand)/log(1-p));
}


int main() {
    
    srand((double)time(NULL));
    double lambda[4]={1,1};//設0.1進來任務次數少, 設0.9進來任務次數多
    double p[4]={0.2, 0.2};//設0.1 log0.9=-0.045 產生封包數多, 設0.9 log0.1=-1 ,產生封包數少
    double stablesum[4]={0} ;
    double over=5, time=0, zero1=0, zero2=0, zero3=0, x=0, test=0, total=0, change=0, weight[2]={0}, probability[2]={0};
    int abcd[4][infinite]={0},cost[infinite]={0},finish[infinite]={0},counts[4]={0};
    int  service=14, j=0, k=0, N=0, waste=0, secnum=30, taskcount=0, breakcount=0, finishtaskcount=0, n[2]={1, 1};
    int limit[4]={0}, D[4]={0}, Bernoulli[4]={0}, pre1[4]={0}, pre2[4]={0}, transit[4]={0}, head[4]={0}, record[4]={0}, sec[4]={0}, statistic1[4]={0}, statistic2[4]={0}, pretransit[4]={0}, *sectemp= calloc(4, sizeof(int));
    
    
    for(N=100;N<=100;N++){
        printf("%d\n",N);
        for(j=0;j<infinite;j++){
            for(k=0;k<4;k++){
                abcd[k][j]=0;
            }
            cost[j]=0;
            finish[j]=0;
            counts[j]=0;
            head[j]=0;
        }
        time=0;
        total=0;
        taskcount=0;
        breakcount=0;
        finishtaskcount=0;
        zero1=0;
        zero2=0;
        zero3=0;
        
        
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
                
                for(j=0;j<2;j++){
                    if(Bernoulli[j]==1){
                        abcd[j][taskcount] =geometric(x,p[j]);
                    }
                }
                
                /*if(abcd[0][taskcount]==1)
                 statistic1[0]++;
                 else if(abcd[0][taskcount]==2)
                 statistic2[0]++;//統計數量*/
                
//                                printf("Time%.f 產生任務 task %d\n""a[%d]=%d\t""b[%d]=%d\t""\n",time,taskcount,taskcount,abcd[0][taskcount],taskcount,abcd[1][taskcount]);//每次產生的任務數
                
                //記錄總每個序列的總任務數
                for(j=0;j<2;j++){
                    counts[j]+=abcd[j][taskcount];
                }
            }
            
            
            else if(Bernoulli[0]==0 && Bernoulli[1]==0){
                breakcount++;
                //printf("Time%.f 休息\n",time);//休息
            }
            
            
            ///printf("統計：%d個休息\n",breakcount);
            ///printf("統計：%d個任務\n",taskcount);
            
            //為了記錄任務最前頭
            for(j=0;j<2;j++){
                while(abcd[j][head[j]]==0 && head[j]<taskcount){
                    head[j]+=1;
                }
            }
            
                        printf("處理前排在最前面的是\n""a[%d]=%d\t""b[%d]=%d\t""\n", head[0], abcd[0][head[0]], head[1], abcd[1][head[1]]);
            printf("處理前每列總數\n""c1=%d\t""c2=%d\t""\n",counts[0], counts[1]);
            
            
            while(1){
                
                //先記錄做幾次再動作
                for(j=1;j<=taskcount;j++){
                    if(abcd[0][j]!=0 || abcd[1][j]!=0){
                        cost[j]= cost[j]+1;//紀錄每個任務幾次
                    }
                    else{
                        finish[j]=1;
                    }
                }
                
                
                
                //Q-CSMA
                for(j=0;j<2;j++){
                    weight[j]=log(1+counts[j]);
                }
                //傳紀錄上一次的
                
                for(j=0;j<2;j++){
                    
                    pre2[j] = pre1[j];
                    pre1[j] = transit[j];
                
                    if(counts[j] == 0){
                        pre2[j] = 0;
                    }
                    
                    
//                    if(transit[j]==1){
//                        record[j]++;
//                    }
//                    else if(transit[j] == 0){
//                        record[j] = 0;
//                        limit[j] = 0;
//                    }
//                    if(record[j] == over){
//                        pre2[j] = 0;
//                        limit[j] = 1;
//                    }
                    
                }
                //                printf("%d %d\n", transit[0], transit[1]);
                printf("%d %d\n", pre1[0], pre1[1]);
                printf("%d %d\n", pre2[0], pre2[1]);
                
                //以 sec 選區段
                for(j=0;j<2;j++){
                    if(counts[j]>0 && limit[j] == 0){
                        sectemp[j] = rand() % secnum ;
                    }
                    else{
                        sectemp[j]=secnum;
                    }
                    
                }
                
                if( sectemp[0] > sectemp[1] ){
                    sec[0] = secnum;
                }
                else{
                    sec[0] = sectemp[0];
                }
                
                if( sectemp[1] > sectemp[0] ){
                    sec[1] = secnum;
                }
                else{
                    sec[1] = sectemp[1];
                }
                
                
                
                
//                for(j=0;j<2;j++){
//                    printf("sec[%d] =%d\n", j+1, sec[j]);
//                 }
                
                
                
                // 第一序列 聽到前面區塊傳或衝撞
                if( sec[0] >= sec[1]  ){
                    D[0]=0;
                    // 如上一步做什麼就做什麼
                    if(pre2[0]>0 && counts[0]>0){
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
                          
                        transit[0]=1;
                        ///printf("第ㄧ序列不納入D有傳\n");
                    }
                    else{
                        transit[0]=0;
                        ///printf("第一序列不納入D沒傳\n");
                    }
                }
                else{
                    D[0]=1;
                }
                
                // 第二序列 聽到前面區塊傳或衝撞
                if( sec[1] >= sec[0] ){
                    D[1]=0;
                    // 如上一步做什麼就做什麼
                    if(pre2[1]>0 && counts[1]>0){
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
                        
                        transit[1]=1;
                        ///printf("第二序列不納入D有傳\n");
                    }
                    else{
                        transit[1]=0;
                        ///printf("第二序列不納入D沒傳\n");
                    }
                }
                else{
                    D[1]=1;
                }
                
                
                // D{0}
                if(D[0]==1){
                    //neighbor上個時間有傳，做上一次得動作
                    if(pre2[1]!=0){
                        transit[0]=0;
                        ///printf("第一序列前臨傳不傳\n");
                    }
                    
                    //neighbor上個時間沒傳，自己可以傳，算傳的機率
                    else{
                        probability[0]=exp(weight[0])/(1+exp(weight[0]));
                        test = (double)rand()/RAND_MAX;

                        if(counts[0]>0 && probability[0]>test){
                            transit[0]=1;
                            printf("第一序列有傳test=%f pro[1]=%f\n",test,probability[0]);
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
                            transit[0]=0;
                            printf("第一序列不傳%f\n", test );
                            waste++;
                            printf("%d\n", waste);
                        }
                    }
                }
                
                // D{1}
                if(D[1]==1){
                    //neighbor上個時間有傳，做上一次得動作
                    if(pre2[0]!=0){
                        transit[1]=0;
                        ///printf("第二序列前臨傳不傳\n");
                    }
                    
                    //neighbor上個時間沒傳，自己可以傳，算傳的機率
                    else{
                        probability[1]=exp(weight[1])/(1+exp(weight[1]));
                        test = (double)rand()/RAND_MAX;
                        if(counts[1]>0 && probability[1]>test){
                            transit[1]=1;
                            printf("第二序列有傳test=%f pro[1]=%f\n",test,probability[1]);
                            for(j=0; j<service; j++){
                                if(abcd[1][head[1]]>0){
                                    counts[1]-=1;
                                    abcd[1][head[1]]-=1;
                                }
                                
                                else if(abcd[1][head[1]]==0 && counts[1]>0){
                                    while(abcd[1][head[1]]==0 && head[1]<taskcount){
                                        head[1]+=1;
                                    }
                                    counts[1]-=1;
                                    abcd[1][head[1]]-=1;
                                }
                            }
                        }
                        
                        else{
                            transit[1]=0;
                            printf("第二序列不傳\n");
                            waste++;
                            printf("%d\n", waste);
                        
                        }
                    }
                }
                
                //紀錄count=0幾次
                if(counts[0]==0){
                    zero1++;
                }
                if(counts[1]==0){
                    zero2++;
                }
                if(counts[0]==0 && counts[1]==0){
                    zero3++;
                }
                
                
                
                
                printf("處理後每列總數\n" "c1=%d\t" "c2=%d\t" "\n",counts[0], counts[1]);
                
                break;
            }
        }
        
        
        
        
        for(j=1;j<=100000;j++){
            if(finish[j]==1){
                //printf("Task %d costs %d time(s)\n", j, cost[j]);
                total=total+cost[j];//放在這裡統計，未完成的任務就不計算
                finishtaskcount++;//計算完成的任務
            }
        }
        
        printf("waste=%d\ntime=%f \nwaste/time=%f\n", waste, time, waste/time);
        printf("first=%f\n", zero1/time);
        printf("second=%f\n", zero2/time);
        printf("total=%f\n", zero3/time);
        printf("The average costs are %f time(s)\n",total/finishtaskcount);
        //printf("%f\n", change/time);
        //printf("任務產生一個的有%d次\t 任務產生兩個的有%d次\n",statistic1[0], statistic2[0]);
        
    }
    return 0;
}


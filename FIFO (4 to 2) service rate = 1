#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define infinite 100001

int geometric(double rand, double p){
    return ceil(log(1-rand)/log(1-p));
}
int main() {
    srand((double)time(NULL));
    double lambda[4]={0.1,0.04,0.1,0.04};//設0.1進來任務次數少, 設0.9進來任務次數多
    double p[4]={0.275,0.275,0.275,0.275};//設0.1 log0.9=-0.045 產生封包數多, 設0.9 log0.1=-1 ,產生封包數少
    double x=0, test=0, total=0, stablesum[4]={0};
    int a[infinite]={0}, b[infinite]={0}, c[infinite]={0}, d[infinite]={0}, cost[infinite]={0};
    int count1=0, count2=0, count3=0, count4=0, Bernoulli[4]={0}, time=0;
    int i=0, j=0, q=0, w=0, n=0, s=0, t=0, u=0, v=0, taskcount=0, breakcount=0, statistic1[4]={0}, statistic2[4]={0};
    int finishtaskcount=0, button=0;
    for(i=1;i<infinite;i++){
        
        time++;
        x = (double)rand()/RAND_MAX;
        //lambda =(double)rand()/RAND_MAX;
        test = (double)rand()/RAND_MAX;
        if(lambda[0]>test){
            Bernoulli[0] =1;
            a[i] =geometric(x,p[0]);
            if(a[i]==1)
                statistic1[0]++;
            else if(a[i]==2)
                statistic2[0]++;
        }
        else{
            Bernoulli[0] =0;
        }
        //printf("a%d\t""%d\n",i,a[i]);
        
        
        x = (double)rand()/RAND_MAX;
        //lambda =(double)rand()/RAND_MAX;
        test = (double)rand()/RAND_MAX;
        if(lambda[1]>test){
            Bernoulli[1] =1;
            
            b[i] =geometric(x,p[1]);
        }
        else{
            Bernoulli[1] =0;
        }
        //printf("b%d\t%d\n",i,b[i]);
        
        
        x = (double)rand()/RAND_MAX;
        //lambda =(double)rand()/RAND_MAX;
        test = (double)rand()/RAND_MAX;
        if(lambda[2]>test){
            Bernoulli[2] =1;
            c[i] =geometric(x,p[2]);
        }
        else{
            Bernoulli[2] =0;
        }
        //printf("c%d\t%d\n",i,c[i]);
        
        
        x =(double)rand()/RAND_MAX;
        //lambda =(double)rand()/RAND_MAX;
        test = (double)rand()/RAND_MAX;
        if(lambda[3]>test){
            Bernoulli[3] =1;
            d[i] =geometric(x,p[3]);
        }
        else{
            Bernoulli[3] =0;
        }
        //printf("d%d\t%d\n",i,d[i]);
        
        
        
        /*stablesum[0] =Bernoulli[0]/p[0]+Bernoulli[1]/p[1] +stablesum[0];
         printf("%d %f %d %d %f\n",i+1,test,Bernoulli[0],Bernoulli[1],stablesum[0]/(i+1));//確認會不會overflow*/
        
        
        
        if(Bernoulli[0]!=0 || Bernoulli[1]!=0 || Bernoulli[2]!=0 || Bernoulli[3]!=0){
            taskcount++;
            button=0;
            //printf("button=%d\n",button);
            //1printf("Time%d 產生任務 task %d\n""a[%d]=%d\t""b[%d]=%d\t""c[%d]=%d\t""d[%d]=%d\n",time,taskcount,i,a[i],i,b[i],i,c[i],i,d[i]);//每次產生的任務數
        }
        else if(Bernoulli[0]==0 && Bernoulli[1]==0 && Bernoulli[2]==0 && Bernoulli[3]==0){
            breakcount++;
            button=1;
            //printf("button=%d\n",button);
            //2printf("Time%d 休息\n",time);//每次產生的任務數
        }
        //3printf("統計：%d個休息\n",breakcount);
        //4printf("統計：%d個任務\n",taskcount);
        
        //為了記錄每個task需要花多少時間，所以用stuv
        while(a[s]==0 && s!=i){
            s+=1;
        }
        while(b[t]==0 && t!=i){
            t+=1;
        }
        while(c[u]==0 && u!=i){
            u+=1;
        }
        while(d[v]==0 && v!=i){
            v+=1;
        }
        //5printf("處理前排在最前面的是\n""a[%d]=%d\t""b[%d]=%d\t""c[%d]=%d\t""d[%d]=%d\n", s, a[s], t, b[t], u, c[u], v, d[v]);
        
        
        //依演算法需求記錄總每個序列的總任務數
        count1 =count1+a[i];
        count2 =count2+b[i];
        count3 =count3+c[i];
        count4 =count4+d[i];
        
        
        //6printf("處理前每列總數\n""c1=%d\t""c2=%d\t""c3=%d\t""c4=%d\n",count1, count2, count3, count4);//總任務數(第一次是產生的任務數，第二次就是處理過後的總任務數了)
        
        //依演算法需求分兩個計算
        q =count1+count4;
        w =count2+count3;
        
        //7printf("c1+c4=%d\t""c2+c3=%d\n",q,w);
        
        
        while(q>0 || w>0){
            //先記錄做幾次再動作
            for(n=0;n<=taskcount;n++){
                if(a[n]!=0 || b[n]!=0 || c[n]!=0 || d[n]!=0){
                    cost[n]= cost[n]+1;//紀錄每個任務幾次
                }
            }
            
            //自已的演算法 先產生的任務先做，因為一次產生的封包數大部分是1個
            if((s<t && s<u)||(v<t && v<u)){
                if(count1!=0 && count4!=0){
                    a[s]-=1;
                    d[v]-=1;
                    count1 =count1-1;
                    count4 =count4-1;
                }
                else if(count1==0 && count4!=0){
                    d[v]-=1;
                    count4 =count4-1;
                }
                else if(count1!=0 && count4==0){
                    a[s]-=1;
                    count1 =count1-1;
                }
            }
            
            else if((t<s && t<v)||(u<s && u<v)){
                if(count2!=0 && count3!=0){
                    b[t]-=1;
                    c[u]-=1;
                    count2 =count2-1;
                    count3 =count3-1;
                }
                else if(count2==0 && count3!=0){
                    c[u]-=1;
                    count3 =count3-1;
                }
                else if(count2!=0 && count3==0){
                    b[t]-=1;
                    count2 =count2-1;
                }
            }
            
            else{
                if(q>=w){
                    if(count1!=0 && count4!=0){
                        a[s]-=1;
                        d[v]-=1;
                        count1 =count1-1;
                        count4 =count4-1;
                    }
                    else if(count1==0 && count4!=0){
                        d[v]-=1;
                        count4 =count4-1;
                    }
                    else if(count1!=0 && count4==0){
                        a[s]-=1;
                        count1 =count1-1;
                    }
                }
                else if(q<w){
                    if(count2!=0 && count3!=0){
                        b[t]-=1;
                        c[u]-=1;
                        count2 =count2-1;
                        count3 =count3-1;
                    }
                    else if(count2==0 && count3!=0){
                        c[u]-=1;
                        count3 =count3-1;
                    }
                    else if(count2!=0 && count3==0){
                        b[t]-=1;
                        count2 =count2-1;
                    }
                }
            }
            //8printf("處理後每列總數\n""c1=%d\t""c2=%d\t""c3=%d\t""c4=%d\n\n",count1, count2, count3, count4);
            break;
        }
        if(button==1){
            i--;//如果產生休息，倒帶
            //printf("button=%d\t i=%d\n",button,i);
        }
    }
    
    
    
    for(j=1;j<infinite;j++){
        if(a[j]==0 && b[j]==0 && c[j]==0 && d[j]==0){
            printf("Task %d costs %d time(s)\n", j, cost[j]);
            total=total+cost[j];//放在這裡統計，未完成的任務就不計算
            finishtaskcount++;//計算完成的任務
        }
        else if(a[j]!=0 || b[j]!=0 || c[j]!=0 || d[j]!=0){
            printf("Task %d is not finish \n", j);
        }
    }
    
    printf("The average costs are %f time(s)\n",total/finishtaskcount);
    printf("任務產生一個的有%d次\t 任務產生兩個的有%d次\n",statistic1[0], statistic2[0]);
    return 0;
}

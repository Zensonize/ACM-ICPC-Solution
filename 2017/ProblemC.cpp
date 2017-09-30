#include <stdio.h>

int main() {
    int X,Y,steal =0;
    scanf("%d %d",&X,&Y);
    int box[Y][X], Smap[Y],Fmap[X];
    char ismax[Y][X];
    
    // <input data >
    for(int i=0;i<X;i++){
        for(int j=0;j<Y;j++){
            scanf("%d",&box[i][j]);
        }
    }

    // < Map the maximum in side view >
    for(int i=0;i<Y;i++){
        Smap[i] = 0;                        //initialize = 0
        for(int j=0;j<X;j++){
            if(Smap[i]<box[i][j]) Smap[i] = box[i][j];
        }
    }

    // < Map the Maximum in front view >
    for(int i=0;i<X;i++){
        Fmap[i] = 0;                        //initialize = 0
        for(int j=0;j<Y;j++){
            if(Fmap[i]<box[j][i]) Fmap[i] = box [j][i];
        }
    }

    // < Check is maximum box 0 = not_max , 1 = max_Y , 2 = max_X , 3 = max+XY > 
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            ismax[i][j] = '0';              //initialize = '0'
            if(box[i][j] == Smap[i]) ismax[i][j] = '1';
            if(ismax[i][j]=='1' && box[i][j] == Fmap[j]) ismax[i][j] = '3';
            else if(ismax[i][j] == '0' && box[i][j] == Fmap[j]) ismax[i][j] = '2';
        }
    }

    //found 1 --> 3 or 3 --> 1 or 1 --> 1 remove 1 | 2 ways check !remove second max
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            // < Find 1 --> 1 keep first value >
            if(ismax[i][j] == '1'){
                for(int k=j+1;k<X;k++){
                    //printf("checking Y:[%d],X:[%d] with Y:[%d],X:[%d] : ",i,j,i,k);
                    if(ismax[i][j] == ismax[i][k]) {
                        //printf("Y");
                        ismax[i][k] = '0';
                    }
                    //else printf("No");
                    //printf("\n");
                }
            }
            // < Find 3 --> 1 keep 3 >
            if(ismax[i][j] == '3'){
                for(int k=j+1;k<X;k++){
                   if(ismax[i][k] == '1') ismax[i][k] = '0';
                }
            }
            // < Find 1 --> 3 keep 3 2nd-way>
            if(ismax[i][j] == '1'){
                for(int k=X;k>=0;k--){
                    if(k==j) continue;
                    else if(ismax[i][k] == '3') ismax[i][j] = '0';
                }
            }
        }
    }

    /*
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            if(ismax[i][j] == '1'){
                for(int k=j+1;k<X;k++){
                    if(ismax[i][j] == ismax[i][k]) {
                        printf("Y");
                    }
                }
            }
        }
        printf("\n");
    }*/

    //found 2 --> 3 or 3 --> 2 or 2 --> 2 remove 2 | 2 ways check !remove second max

    for(int j=0;j<X;j++){
        for(int i=0;i<Y;i++){
            // < Find 2 --> 2 keep first value >
            if(ismax[i][j] == '2'){
                for(int k=i+1;k<Y;k++){
                    //printf("checking Y:[%d],X:[%d] with Y:[%d],X:[%d] : ",i,j,i,k);
                    if(ismax[i][j] == ismax[k][j]) {
                        //printf("Y");
                        ismax[i][k] = '0';
                    }
                    //else printf("No");
                    //printf("\n");
                }
            }
            // < Find 3 --> 2 keep 3 >
            if(ismax[i][j] == '3'){
                for(int k=i+1;k<Y;k++){
                   if(ismax[k][j] == '2') ismax[k][j] = '0';
                }
            }
            // < Find 2 --> 3 keep 3 2nd-way>
            if(ismax[i][j] == '2'){
                for(int k=Y;k>=0;k--){
                    if(k==i) continue;
                    else if(ismax[k][j] == '3') ismax[i][j] = '0';
                }
            }
        }
    }
    
    // < steal removable block >
    for(int i=0;i<Y;i++){
        for(int j=0;j<X;j++){
            if(ismax[i][j] == '0' && box[i][j]>1){
                steal = steal + (box[i][j]-1);
                box[i][j] = 1;
            }
        }
    }

    // < For debugging >
    for(int i=0;i<Y;i++){
        printf("%d|",Smap[i]);
        for (int j=0;j<X;j++){
            printf("%c ",ismax[i][j]);
        }
        printf("\t");
        for (int j=0;j<X;j++){
            printf("%d ",box[i][j]);
        }
        if(i==(Y-1)) printf("\t Stolen: %d Boxes",steal);
        printf("\n");
    }
    printf(" |");
    for(int i=0;i<X+X-1;i++){
        printf("-");
    }
    printf("\n |");
    for(int i=0;i<X;i++){
        printf("%d ",Fmap[i]);
    }

    return 0;
}
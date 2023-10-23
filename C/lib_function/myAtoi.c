/*
 * @Descripttion: 
 * @Author: cyd
 * @Date: 2021-08-30 13:37:59
 * @LastEditTime: 2021-08-30 13:38:45
 */
#include<stdio.h>
#include<string.h>

int isNum(char *s){
    int i = 0;
    int flag = 0;
    int numflag = 0;
    while(s[i] != 0){
        if((s[i] >= 'a' && s[i] <= 'z') || s[i] == '.' || (s[i] >= 'A' && s[i] <= 'Z')){
                return flag;
        }
        else if(s[i] == '-'){
            s[i] = ' ';
            flag = 1;
        }
        else if(s[i] == '+'){
            s[i] = ' ';
            flag = 2;
        }
        else{
            flag = 2;
        }
        i++;
    }
    
    return flag;
}

int myAtoi(char * s){
    char s2[10] = {0};
    int i = 0, bitflag = 0, j = 0;
    int numflag = isNum(s);
    int num = 0;
    if(!numflag){
        return 0;
    }
    for(i = 0; s[i] != 0; i++){
        if(' ' == s[i]){
            if(bitflag == 0){
                continue;
            }
            else{
                break;
            }
        }
            continue;
        if(s[i] >= '0' && s[i] <= '9'){
            if(j < 9){
                s2[j++] = s[i];
                bitflag = 1;
                continue;
            }
            else{
                if(numflag == 1){
                    return INT_MIN;
                }
                else if(numflag == 2){
                    return INT_MAX;
                }
            }
            
        }
        if(s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z' || s[i] == '.'){
            break;
        }
    }

    for(i = 0; i < j; i++){
        num = num*10 + s[i]; 
    }

    if(numflag == 1){
        return -num;
    }
    else{
        return num;
    }
    
}

int main(){
    char str[] = "43";
    int num = myAtoi(str);

    printf("num = %d\n", num);

    return 0;
}

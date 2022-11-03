#include<stdio.h>
#include<stdlib.h>

typedef struct User{
    int len_coordinate, wid_coordinate;
    int accept; // 紀錄該user的request是否為accepted
    int choices[5]; //紀錄有哪些種類的block可以選
}User;

int check(int num){// 判斷方塊是何種形狀
    int cnt = 0;
    while(num != 1){
        num /= 2;
        cnt++;
    }
    return cnt;
}

int main(){
    int length, width, user_num, cnt = 0;
    scanf("%d %d %d\n", &length, &width, &user_num);

    User * user_arr = (User*)malloc(sizeof(User) * user_num);
    int type_cnt[5] = {0};
    int user_id, block_id, block_len, block_wid, chr;
    for(int i = 0; i < user_num; i++){
        user_arr[i].accept = 0;
        for(int j = 0; j < 5; j++){
            user_arr[i].choices[j] = 0;
        }
        scanf("%d ", &user_id);
        while(1){
            scanf("%dx%d%c", &block_len, &block_wid, &chr);
            block_id = check(block_len);
            type_cnt[block_id]++;
            user_arr[i].choices[block_id] = 1;
            if(chr == '\n')
                break;
        }
        // for(int j = 0; j < 5; j++){
        //     printf("%d ",user_arr[i].choices[j]);
        // }
        // printf("\n");
        
    }
    

}
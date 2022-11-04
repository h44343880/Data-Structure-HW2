#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct user{
    int len_coordinate, wid_coordinate;
    int len_type, wid_type;// 紀錄選擇的block長寬
    int accept; // 紀錄該user的request是否為accepted
    int choices[5]; //紀錄有哪些種類的block可以選
}User;

typedef struct node{
    int id;
    struct node * NextPtr;
}Node;

Node * AddNode(int index){
    Node * new = (Node*)malloc(sizeof(Node));
    new->id = index;
    new->NextPtr = NULL;
    return new;
}

void DeleteNode(int index, Node * CurrentPtr){
    Node * PrePtr;
    while(CurrentPtr->id != index){
       PrePtr = CurrentPtr;
       CurrentPtr = CurrentPtr->NextPtr;
    }
    PrePtr->NextPtr = CurrentPtr->NextPtr;
    free(CurrentPtr);
}

int check(int num){// 判斷方塊是何種形狀
    int cnt = 0;
    while(num != 1){
        num /= 2;
        cnt++;
    }
    return cnt;
}

Node * LastNode(Node * ptr){
    while(ptr->NextPtr != NULL){
        ptr = ptr->NextPtr;
    }
    return ptr;
}

void PrintLinkList(Node * ptr){
    while(ptr != NULL){
        printf("%d ", ptr->id);
        ptr = ptr->NextPtr;
    }
    printf("\n");
}

int main(){
    int length, width, user_num, cnt = 0;
    scanf("%d %d %d\n", &length, &width, &user_num);
    User * user_arr = (User*)malloc(sizeof(User) * user_num);// 紀錄每個user的request

    Node * block_list[5]; //紀錄每個LinkList的起點
    Node * LastNode[5];// 紀錄LinkList的最後一個Node以便新增Node
    for(int i = 0; i < 5; i++){
        block_list[i] = AddNode(-1);
        LastNode[i] = block_list[i];
    }
    
    int type_cnt[5] = {0};

    int user_id, block_id, block_len, block_wid; 
    char chr;

    for(int i = 0; i < user_num; i++){
        // 初始化user
        user_arr[i].accept = 0;
        for(int j = 0; j < 5; j++){
            user_arr[i].choices[j] = 0;
        }

        scanf("%d ", &user_id);
        while(1){
            scanf("%dx%d%c", &block_len, &block_wid, &chr);
            block_id = check(block_len);// 判斷block的形狀
            LastNode[block_id]->NextPtr = AddNode(i);
            LastNode[block_id] = LastNode[block_id]->NextPtr;
            type_cnt[block_id]++;
            user_arr[i].choices[block_id] = 1;
            if(chr == '\n')
                break;
        }
        // 檢查block種類是否記錄正確
        // for(int j = 0; j < 5; j++){
        //     printf("%d ",user_arr[i].choices[j]);
        // }
        // printf("\n");
        
    }
    // 檢查LinkList是否正確建立
    // for(int i = 0; i < 5; i++){
    //     PrintLinkList(block_list[i]);
    // }

    int floor = 0, temp_floor = 0, ceiling = (int)fmin(floor + 16, length), side = 0;
    for(int i = 4; i >= 0 ; i--){
        int block_height = (int)pow(2, i), block_width = (int)pow(2, 4 - i);
        Node * current = block_list[i]->NextPtr;

        while(current != NULL){
            Node * NextPtr = current->NextPtr;
            int target = current->id;
            if(block_height + floor > ceiling)// 若block的高度超過該層高度直接跳過
                break;

            if(temp_floor + block_height > ceiling || temp_floor == ceiling){// 代表放到該層高度上限
                side += block_width;
                temp_floor = floor;
            }

            if(block_height + temp_floor <= ceiling && block_width + side <= width){// 代表可放入
                user_arr[target].accept = 1;
                user_arr[target].len_type = block_height;
                user_arr[target].wid_type = block_width;
                user_arr[target].len_coordinate = temp_floor;
                user_arr[target].wid_coordinate = side;
                temp_floor += block_height;
                for(int j = 0; j < 5; j++){
                    if(user_arr[target].choices[j]){
                        DeleteNode(target, block_list[j]);
                    }
                    // PrintLinkList(block_list[j]);
                }
                cnt++;
            }

            if(block_width + side > width){// 代表該層已放滿
                floor = ceiling;
                temp_floor = floor;
                if(ceiling + block_height > length)
                    break;
                ceiling += block_height;
                side = 0;
            }


            current = NextPtr;
        }
        // 放完後判斷有沒有凸出來的方塊
        if(temp_floor != floor)
            side += block_width;
        temp_floor = floor;
    }

    // 印出結果
    printf("%d\n", cnt);
    for(int i = 0; i < user_num; i++){
        if(user_arr[i].accept)
            printf("%d %dx%d %d %d\n", i, user_arr[i].len_type, user_arr[i].wid_type, user_arr[i].len_coordinate, user_arr[i].wid_coordinate);
    }
}
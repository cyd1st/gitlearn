/*
 * @lc app=leetcode.cn id=19 lang=c
 *
 * [19] 删除链表的倒数第 N 个结点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode* p1 = head;
    struct ListNode* p2 = head;

    for (int i = 1; i <= n; i++){
        p2 = p2->next;
    }
    while(p2 != NULL && p2->next != NULL){
        printf("2\n");
        p1 = p1->next;
        p2 = p2->next;
    }
    /*删除第一个*/
    if(NULL != p1->next && p2 == NULL){
        printf("p1->next->val = [%d]\n", p1->next->val);
        head = p1->next;
        return head;
    }

    if(NULL != p1->next){
        printf("p1->next->val = %d\n", p1->next->val);
        //p1->val = p1->next->val;
        p1->next = p1->next->next;
    }
    else{
        printf("-----\n");
        head = NULL;
    }
    printf("p1 == head : %d\n", p1 == head);
    return head;
}
// @lc code=end


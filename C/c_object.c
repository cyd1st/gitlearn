// https://blog.csdn.net/haoel/article/details/2864
#include <stdio.h>

/* 双向链表 （类似于父类）*/
typedef struct hLinks{
   struct hLinks *bwLink;
   struct hLinks *fwLink;
} hLinks;


/*
 * 一个使用双向链表的结构
 *     （类似于子类）
 */
typedef struct hEnt{
   hLinks links;
   int hData;
   char key[10];
} hEnt;


/*
 *  双向链插入泛型算法 （类似于父数中的成员函数）
 */
Insert( hLinks* elem, hLinks *dest )
{
   if ( !elem || !dest ) return;

   elem->bwLink = dest->bwLink;
   elem->fwLink = dest;
   dest->bwLink->fwLink = elem;
   dest->bwLink = elem;
}


/*
 *  打印 （类似于子类重载父类的成员函数）
 */
PrintLink( hLinks *h )
{
    hEnt *p ;

    for( p = ( hEnt* ) h->fwLink;     /*  <-----------把hLink再转回来  */
         p != ( hEnt* ) h;
         p = ( hEnt* )( (hLinks*)p )->fwLink )
    {
       printf("hData=[%d], key=[%s]\n", p->hData, p->key);
    }
}

 

main()
{
   hLinks head;
   hEnt a[4];
   int i;

   head.bwLink = &head;
   head.fwLink = &head;

   for(i=0;i<4;i++)
   {
      a[i].hData = i*10;
      sprintf(a[i].key,"id=%d", i);

      /*  使用泛型算法构造双向链  */ 
      Insert( (hLinks *) &a[i], (hLinks *) &head ); /*   <-----注意这个强制转换  */
   }

   PrintLink( (hLinks *) &head ); /*   <-------也注意这个强制转换  */
}
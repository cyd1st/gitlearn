#ifndef __MYSET__
#define __MYSET__

typedef struct {} Set;

/*
  初始化集合。
  set: 要初始化的集合。
  match：比较集合中的两个成员是否相等。
  destroy：释放集合的某个成员占用的堆内存。如果不需要释放可以传入 NULL。
 */
void set_init(Set *set, int (*match)(const void *key1, const void *key2),
		void (*destroy)(void *data));

/*
  销毁集合。调用 set_init 中指定的 destroy 函数。
  set: 要销毁的 set
 */
void set_destroy(Set *set);

/*
  集合中插入一个成员。
  set: 要插入的集合。
  data: 要插入的成员的指针。
  返回值：0 表示插入成功; -1 表示插入失败; 1 表示成员已经存在。
 */
int set_insert(Set *set, const void *data);

/*
  移除集合中的一个成员。
  set: 要操作的集合。
  data: 删除与 data 数据域吻合的成员。
  返回值: 0 表式成功移除。-1 表示移除失败。
 */
int set_remove(Set *set, void **data);

/*
  计算两个集合的并集。
  setu: 两个集合的并集的结果。
  set1/set2: 要计算的两个集合。
  返回值：0 表式成功计算并集。-1 表示计算失败。
  note: setu 成员指向 set1/set2 集合的成员（并非复制），所以需要保持 set1/set2 在 setu 被销毁前可用。
 */
int set_union(Set *setu, const Set *set1, const Set *set2);



#endif

// Using a singly-rooted hierarchy
#ifndef OSTACK_H
#define OSTACK_H

class Object {
public:
	virtual ~Object() = 0;
};

// Required definition:
inline Object::~Object() {}

class Stack {
	struct Link {
		Object* data;
		Link* next;
		Link(Object* dat, Link* nxt) : 
		data(dat), next(nxt) {}
	}* head;
public:
	Stack() : head(0) {}
	~Stack(){ 
		while(head)
			delete pop();
	}
	void push(Object* dat) {
		head = new Link(dat, head);
	}
	Object* peek() const { 
		return head ? head->data : 0;
	}
	// pop 使用内联写法是为了简便，一般不建议这么复杂的内联函数
	Object* pop() {
		if(head == 0) return 0;
		Object* result = head->data;
		Link* oldHead = head;
		head = head->next;
		delete oldHead;
		return result;
	}
};
#endif // OSTACK_H ///:~

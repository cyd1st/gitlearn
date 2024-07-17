import queue
import threading
import time

class ProducerThread(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue

    def run(self):
        for i in range(10):
            print('Producer put:', i)
            self.queue.put(i)
            # time.sleep(1)
        # 添加一个None到队列中，表示没有更多的任务
        self.queue.put(None)

class ConsumerThread(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue

    def run(self):
        while True:
            item = self.queue.get()
            if item is None:  # 没有更多的任务
                break
            print('Consumer get:', item)
            self.queue.task_done()

q = queue.Queue()
ProducerThread(q).start()
ConsumerThread(q).start()
q.join()

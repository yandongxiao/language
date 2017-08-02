#! /usr/bin/env python
# encoding: utf-8

import time
import Queue
import threading

 # 唯一标识了一个对象
_sentinel = object()


# A thread that produces data
def producer(out_q):
    n = 3
    while n > 0:
        # Produce some data
        out_q.put(n)
        out_q.put(n)
        print('put:', n)
        print('put:', n)
        out_q.join()    # 只有当队列中元素清空以后，才会被返回
        n -= 1
    # Put the sentinel on the queue to indicate completion
    out_q.put(_sentinel)
    print('Producer shutting down')


# A thread that consumes data
def consumer(in_q):
    while True:
        # Get some data
        data = in_q.get()
        # Check for termination
        if data is _sentinel:
            # 消费者在读到这个特殊值之后立即又把它放回到队列中，将之传递下去。
            # 这样，所有监听这个队列的消费者线程就可以全部关闭了
            in_q.put(_sentinel)
            break
        # Process the data
        time.sleep(1)
        print('Got:', data)
        in_q.task_done()
    print('Consumer shutting down')

if __name__ == '__main__':
    q = Queue.Queue()
    t1 = threading.Thread(target=consumer, args=(q,))
    t2 = threading.Thread(target=producer, args=(q,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()

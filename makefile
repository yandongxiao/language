all:
	gcc tasksink_test2.c -lzmq -o sink
	gcc taskworker_test2.c -lzmq -o worker
	gcc taskvent_test.c -lzmq -o vent
#	gcc taskworker_test.c -lzmq -o worker
#	gcc taskvent_test.c -lzmq -o vent

clean:
	rm sink worker vent

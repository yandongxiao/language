#! /usr/bin/python

jack_score = [60, 70, 80, 90]
avrg_score = sum(jack_score)/len(jack_score)
print ("jack's average score is : %d" % avrg_score)

grace_score = input("please input grace's score : ")
grace_score = grace_score.split()
grace_score = [int(x) for x in grace_score ]
avrg_score = sum(grace_score) / len(grace_score)    # this is different from python 2.x.
print ("grace's average score is : %f" % avrg_score)    #must be %f. If it is %d, the argument @avrg_score will be like int(avrg_score).

#!/usr/bin/env python
# encoding: utf-8

class User:
    def __init__(self, user_id):
        self.user_id = user_id
    def __repr__(self):
        return 'User({})'.format(self.user_id)

users = [User(23), User(3), User(99)]


# method - 1
print sorted(users, key=lambda user: user.user_id)

# method - 2
from operator import attrgetter
getter = attrgetter("user_id")
print sorted(users, key=attrgetter("user_id"))

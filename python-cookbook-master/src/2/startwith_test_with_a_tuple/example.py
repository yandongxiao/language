#!/usr/bin/env python
# encoding: utf-8

import os
print any(name for name in os.listdir(".") if name.endswith(('.py', '.c')))

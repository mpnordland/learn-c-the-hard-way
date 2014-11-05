#! /usr/bin/python

import sys
import subprocess
import asyncio

if len(sys.argv) >=2:
    p = asyncio.create_subprocess_exec(sys.argv[1], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    for pp in p:
        ppp=pp.result()
        print(ppp)
    while True:
        out = p.stdout.readline()
        print(out)
else:
    print("You need to pass the executable")

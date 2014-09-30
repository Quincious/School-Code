#!/usr/bin/python

import sys
import re    

print sys.argv[1]
string = open(sys.argv[1]).read()
nospace = re.sub("\s+"," ",string)
of = open(sys.argv[1], "w")
of.write(nospace)
of.close()


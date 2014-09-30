#Jonathan Hart
#Lab 7 lspython.py

import subprocess

ls_output = subprocess.check_output(['ls', '-al', '/'])

outFile = open("lspython.txt", 'w')
outFile.write(ls_output)
outFile.close()
 

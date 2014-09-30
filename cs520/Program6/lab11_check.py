import os
import subprocess

for filename in os.listdir(os.getcwd()):
	if (filename.startswith('lab11') and filename.endswith('main.c')):
		execname = filename[:-7]
		cmd = ["gcc", "-g", "-Wall", filename, "gc_lib.c", "-std=gnu99", "-o", execname]
		p = subprocess.Popen(cmd)
		p.wait()
		output = subprocess.check_output(["./"+execname])
		outputlist = output.split('\n')	
		if "Roots:" not in outputlist:
			print execname + " failed"
			continue
		idx = outputlist.index("Roots:")
		sublist1 = outputlist[:idx]
		sublist2 = outputlist[idx+1:-1]
	
		if len(set(sublist1))!=len(sublist1):
			print execname + " failed"
			continue
		if sublist1.sort() != sublist2.sort():
			print execname + " failed"
			continue
		print execname + " passed"

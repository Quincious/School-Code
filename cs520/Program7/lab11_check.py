import os
import subprocess

for filename in os.listdir(os.getcwd()):
	if ((filename.startswith('lab11') and filename.endswith('main.c')) or
			 (filename.startswith('hart') and filename.endswith('.c')) or
			 (filename.startswith('lab10') and filename.endswith('main.c')) or
			 (filename.startswith('au') and filename.endswith('.c')) or
			 (filename.startswith('dr') and filename.endswith('.c')) or
			 (filename.startswith('prog6') and filename.endswith('.c'))):
		execname = filename[:-2]
		cmd = ["gcc", "-g", "-Wall", filename, "gc_lib.c", "-lpthread", "-std=gnu99", "-o", execname]
		p = subprocess.Popen(cmd)
		p.wait()
		output = subprocess.check_output(["./"+execname])
		print output

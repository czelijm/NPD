import subprocess
 
#cmd = ""
# Example
# cmd = HelloWorld.c
#print ("Hey this is Python Script Running\n")
#subprocess.call(["gcc",cmd]) #For Compiling


for x in range(100):
	#procMP = subprocess.call("./aOpenMP_test.out") 
	procMP = subprocess.Popen("./aOpenMP.out")
	procMP.wait()

print("")
print("")
print("")
print("")
print("")


#for x in range(100):
#	procSingle = subprocess.Popen("./aSerial.out") 
#s	procSingle.wait()




#end thats all



#params = [...]
#for param for params:
#    proc = subprocess.Popen(['/path/to/CProg', param.., param..])
#    subprocess.call([sys.executable, 'B.py', param.., param...])
#    os.kill(proc.pid, signal.SIGINT)
#    proc.wait()

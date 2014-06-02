import subprocess

args =  ["test"]
while subprocess.call(["./ex10"]+args) != 1:
    args += args

print("Crashed with", len(args), "arguments")

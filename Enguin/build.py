import os, sys

CC = "gcc"
LIBNAME = "debil"

#TODO->clean each .o file in each dir
def clean(dir_):
    #os.system("rm *.o")
    #os.system("rm *.a") 
    
    if dir_=="":
        files = os.listdir()
        for f in files:
            if os.path.isdir(f):
                clean(f)
            if os.path.isfile(f):
                if len(f.split("."))>1 and (f.split(".")[1]=="o" or f.split(".")[1]=="a"):
                    os.system(f"rm {f}")
    else:
        files = os.listdir(dir_)
        for f in files:
            if os.path.isdir(dir_+"/"+f):
                clean(dir_+"/"+f)
            if os.path.isfile(dir_+"/"+f):
                if len(f.split("."))>1 and (f.split(".")[1]=="o" or f.split(".")[1]=="a"):
                    os.system(f"rm {dir_}/{f}")

def findFiles(srcs, dir_):
    if dir_=="":
        files = os.listdir()
        for f in files:
            if os.path.isdir(f):
                findFiles(srcs, f)
            if os.path.isfile(f):
                if len(f.split("."))>1 and f.split(".")[1]=="c":
                    srcs.append(f)
    else:
        files = os.listdir(dir_)
        for f in files:
            if os.path.isdir(dir_+"/"+f):
                findFiles(srcs, dir_+"/"+f)
            if os.path.isfile(dir_+"/"+f):
                if len(f.split("."))>1 and f.split(".")[1]=="c":
                    srcs.append(dir_+"/"+f)

def compile_(srcs):
    objs = []
    for src in srcs:
        f = src.split(".")[0]
        objs.append(f+".o")
        os.system(f"{CC} -c -Wall -Werror -Wextra {f}.c -o {f}.o")
    objs_str = ' '.join(objs)
    os.system(f"ar -rcs lib{LIBNAME}.a {objs_str}")

def main():
    srcs = []
    findFiles(srcs, "")
    compile_(srcs)

if __name__=="__main__":
    if(len(sys.argv)<2):
        main()
    else:
        if sys.argv[1] == "clean":
            clean("")

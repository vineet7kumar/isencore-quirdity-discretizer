#!/usr/bin/python

import subprocess
import os
import shutil
import sys

def run_command(command):
    #    print command
    try:
        p = subprocess.check_output(command, 
                stderr=subprocess.STDOUT, shell=True)
        #ret = p.communicate()[0]
    except CalledProcessError:
        print 'ERROR IN RUNNING BINVOX'
#    return p.output

def main():
    if os.name == 'nt':
        command = 'binvox -d '
    else:    #assuming all other systems follow posix style
        command = './binvox -d ' #binvox executable MUST be in ./
    dval = sys.argv[1] #number of voxels. passed to -d 
    num_down = sys.argv[2] #number of times -down is passed
    in_file_path = sys.argv[3] #path to the input file

    command = command + dval + ' '
    run_command(command + in_file_path)
    for i in range(0, int(num_down)): #0..num_down-1
        command += '-down '
        run_command(command + in_file_path)
main()


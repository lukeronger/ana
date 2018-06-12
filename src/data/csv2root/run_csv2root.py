#!/usr/bin/env python3

import os
import sys

"""
subprocess module may be more modern standard,
but os.system() works better in this use case
"""

##################################################
#                                                #
#                   GLOBALS                      #
#                                                #
##################################################

HERE = os.path.dirname(os.path.realpath(__file__))
HOME = os.path.expanduser("~")

##################################################
#                                                #
#               HELPER FUNCTIONS                 #
#                                                #
##################################################

##################################################
#                                                #
#                   SYSTEM                       #
#                                                #
##################################################

def init(n):
    try:
        os.system("make")
    except:
        print("\nMakefile not found, or broken!\n\n")

def convert(n,i):
    try:
        if i[0] == '~':
            i = HOME + i[1:]
        com  = "./" + n + " " +  i
        os.system(com)
    except:
        print("\n" + n + " converter is brokem, please check and make fixes\n\n")
        
if __name__ == '__main__':
    if sys.argv[1] == "template":
        print("\nCan not run template!\n\n")
    else:
        try:
            os.chdir(HERE)
            os.chdir(sys.argv[1])
            if not(os.path.isfile(sys.argv[1])):
                print("\nRunning specific CSV converter for first time! Compiling...\n\n")
                init(sys.argv[1])
            print("\nConverting CSV file to .root!\n\n")
            convert(sys.argv[1],sys.argv[2])
            print("\nDone!\n\n")
        except:
            print("\nERROR: Specified converter does not exist\n\n")

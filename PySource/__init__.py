"""
This application is the product of Nephi Wright, Shane Transue, and Jon Cappella.  Feel free to thieve
any of its contents.

In order to run this application you will need to have Python 3.2 installed.  In order to use Forester.jar,
also known as Archaeopteryx, to view the newick tree, Java JRE Version 5 or better must be installed
and configured appropriately.  Further, this program has only been tested on Windows 7, and may not function
at all in Linux or Mac.  This application is given to you as is, with no guarantee that it will operate properly.
"""

##
# \mainpage GeneticTreeProject
# This program was written for Ivo Georgiev's Spring 2011 Object Oriented 
# Software Development class.  This is the third homework assignment and entailed
# the creation of a python/c++ program that would ETL a fasta file, run pairwise
# comparisons on it, and ultimately multi-sequencing parsing to create a newick
# tree.  The program is due May 8, 2011 and will be delivered via a link to google
# code in an email.  The code was developed using Python 3.2, and g++ compiler
# from MinGW, and the vc++ compiler that comes with visual studio 10.  The program
# has been successfully run on Windows 7 (32 and 64 bit) machines, but not Mac nor
# Linux.  The installation and operation of this code is at the users own risk,
# we do not promise successful operation or this code on your machine.  Our code
# makes use of forester.jar for displaying the tree in a more friendly manner, it
# is open source code, and more information can be found here: http://code.google.com/p/forester/
#
# @author Nephi Wright (nwright9@mscd.edu)
# @author Shane Transue (stransu1@mscd.edu)
# @author Jon Cappella (jcappella@mscd.edu)
# @version 2
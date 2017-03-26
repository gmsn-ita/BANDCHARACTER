# BANDCHARACTER
Program to see the contribution of each orbital of each atom for a band, from VASP results. Version 1.1 MAR 2017

This program sum the contribution of each orbital for each atom for all kpoints in a band. The results are given in percentage.
The PROCAR and OUTCAR files of VASP are necessary. 

Compile using:

g++ -o bandcharacter bandcharacter1.1.c


Run given as argument the number of the band you want to analize. Ex: bandcharacter 20

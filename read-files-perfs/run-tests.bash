#!/bin/bash
# 
# File:   run-tests.bash
# Author: bernard
#
# Created on 15 janv. 2017, 00:31:56
#

outdir=$(uname)-perfs
outfile=$(date "+%y%m%d-%H%M%S").perfs

exe=read-files-perfs

mkdir -p ${outdir}
touch ${outdir}/${outfile}

uname -a >> ${outdir}/${outfile}
echo >> ${outdir}/${outfile}
for exedir in 'dist/gcc_Release/GNU-Linux' 'dist/icc_Release/Intel-Linux' 'dist/sun_Release/OracleDeveloperStudio-Linux'
do
	${exedir}/${exe}
done | sort -k 7 >> ${outdir}/${outfile}
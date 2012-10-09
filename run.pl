#!/usr/bin/perl
use strict;
use warnings;

my @size=(1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288);
#my @size=(8,40,72,104,136,168,200,232,264,296,328,360,392,424,456,488,520);

foreach my $i (@size) {
	open(OUT, ">", "submit") or die "cannot open > output.txt: $!";
	print(OUT"#!/bin/bash\n");
	print(OUT"#PBS -q normal\n");
	print(OUT"#PBS -l nodes=1:ppn=16:native\n");
	print(OUT"#PBS -l walltime=00:30:00\n");
	print(OUT"#PBS -N sn_pingpong_$i\n");
	print(OUT"#PBS -o Out/singlenode_size_$i.out\n");
	print(OUT"#PBS -e Log/singlenode_size_$i.out\n");
	print(OUT"#PBS -A TG-CCR120040\n");
	print(OUT"#PBS -M gregory.petropoulos\@colorado.edu\n");
	print(OUT"#PBS -m abe\n");
	print(OUT"#PBS -V\n");
	print(OUT"# Start of user commands - comments start with a hash sign (#)\n");
	print(OUT"cd /oasis/scratch/gregp/temp_project/cs_5576/four\n");
	print(OUT"mpirun -np 16 -hostfile \$PBS_NODEFILE sn_pingpong $i 100000\n");
	close OUT;
	
	system("qsub submit");
}

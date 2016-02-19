#!/bin/bash

HOMEARG=/home/adcastel/argobots
HOMEQTH=/home/adcastel/qthreads
HOMEMTH=/home/adcastel/massivethreads_wf
HOMEGLT=/home/adcastel/GLT/src

echo "Loading environment variables for GLT..."
echo "Select the library: "
echo "	Argobots (1)"	
echo "	Qthreads (2)"	
echo "	MassiveThreads (3)"	

read lib

echo "Number of OS threads?"

read numthreads

export GLT_NUM_THREADS=$numthreads

if [ $lib -eq "1" ];
then
	echo "Number of pools?"
	read numpools
	export GLT_NUM_POOLS=$numpools
	HOM=$HOMEARG
	HOMEGLT=$HOMEGLT/argobots
else
	if [ $lib -eq "2" ];
	then
		echo "Number of workers per Shepherd"
		read numworkers
		export GLT_NUM_WORKERS_PER_THREAD=$numworkers
		HOM=$HOMEQTH
		HOMEGLT=$HOMEGLT/qthreads
	else
		if [ $lib -eq "3" ];
		then
			HOM=$HOMEMTH
			HOMEGLT=$HOMEGLT/massivethreads
		else
			echo "Error. $lib is not a valid value"
			return
		fi
	fi
fi

export LD_LIBRARY_PATH=$HOMEGLT:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$HOM:$LD_LIBRARY_PATH


#!/bin/bash

t0=0	#start time	
t1=500	#end time
n="$1"	#number of cars


/home/jacky/bin/sumo-0.21.0/tools/trip/randomTrips.py -n manhattan.net.xml -b $t0 -e $t1  -p $(bc -l <<< "(($t1 - $t0) / $n)") -o ${n}_manhattan.trips.xml --min-distance 250 -r ${n}_manhattan.rou.xml


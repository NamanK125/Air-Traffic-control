# Air-Traffic-control

Technology used: Operating Systems
Air Traffic controller: Forking, Mesage queue, Inter-Process Communication(ITC)
Airport: Threading, mutex, Semaphore
Threads are used to handle multiple operations on a single airport.
To handle multiple operaions on a runway, semaphore is used.
Process linking:
Plane requests ATC||
ATC requests Airport||
Airport approves ATC||
ATC approves Plane||
Successfully takeoff||
Plane requests ATC||
ATC requests Airport||
Airport approves ATC||
ATC approves Plane||
Successfully land||
Deboard||

################
Sample Test Case:
Number of airports = 5

Airport number: 1
Number of runways: 2
Capacity(kg): 4000 1200

Airport number: 2
Number of runways: 2
Capacity(kg): 3800 1255

Airport number: 3
Number of runways: 2
Capacity(kg): 4320 3200

Airport number: 4
Number of runways: 4
Capacity(kg): 4800 1250 5200 1200

Airport number: 5
Number of runways: 2
Capacity(kg): 4000 3600

Plane number: 1
Type = Cargo
Total number of items: 80
Average weight: 45

Plane number: 2
Type: Passenger
Number of Seats occupied: 5
Passenger weight: 46, 56, 75, 41, 65
Luggage weight: 14, 16, 15, 19, 7
####################

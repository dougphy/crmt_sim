# `crmt` is ...

-- A rewrite of MT_Toy (which is poorly written for CINT)
   http://github.com/dougphy/CRMT_Software
-- A way to seperate event generation and simulated event display

    ./crmt -g,--generate [file name] [# events] 

    ./crmt -d,--display -t,--true [file name] [event #] 

    ./crmt -d,--display -s,--sim [file name] [event #] 

    ./crmt -p,--parameters *display parameters*

In the end, simulation and reconstruction will be a single software.
Reconstruction currently being developed at http://github.com/vgenty/crmt_feb
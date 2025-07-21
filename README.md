Yep Lily_TTT has solved Tic Tac Toe! This took 4 hours bro I need to sleep...

Usage:
Lily_TTT uses uci-like commands, just pass them in through stdin
see docs/uti_compliance.txt for info. Here is an example session:
```
<- uti
-> id name Lily
-> id author CeriseSky
-> utiok
<- position
<- go
-> bestmove A
<- position A
<- go
-> bestmove E
<- quit
```
Arrows aren't part of the commands by the way, they just show the direction
the message is going (<- to the engine, -> from the engine)

list message TCP:
GAMES, from:server [GAMES␣n***]
OGAME, from:server [OGAME␣m␣s***]

NEWPL, from:client [NEWPL␣id␣port***]
REGIS, from:client [REGIS␣id␣port␣m***]

REGOK, from:server [REGOK␣m***]
REGNO, from:server [REGNO***]

START, from:client [START***]
UNREG, from:client [UNREG***]

UNROK, from:server [UNROK␣m***]
DUNNO, from:server [DUNNO***]

SIZE?, from:client [SIZE?␣m***]

SIZE!, from:server [SIZE!␣m␣h␣w***]

LIST?, from:client [LIST?␣m***]

LIST!, from:server [LIST!␣m␣s***]
PLAYR, from:server [PLAYR␣id***]

GAME?, from:client [GAME?***]

WELCO, from:server [WELCO␣m␣h␣w␣f␣ip␣port***]
POSIT, from:server [POSIT␣id␣x␣y***]

UPMOV, from:client [UPMOV␣d***]
DOMOV, from:client [DOMOV␣d***]
LEMOV, from:client [LEMOV␣d***]
RIMOV, from:client [RIMOV␣d***]

MOVE!, from:server [MOVE!␣x␣y***]
MOVEF, from:server [MOVEF␣x␣y␣p***]

IQUIT, from:client [IQUIT***]

GOBYE, from:server [GOBYE***]

GLIS?, from:client [GLIS?***]

GLIS!, from:server [GLIS!␣s***]
GPLYR, from:server [GPLYR␣id␣x␣y␣p***]

MALL?, from:client [MALL?␣mess***]

MALL!, from:server [MALL!***]

SEND?, from:client [SEND?␣id␣mess***]

SEND!, from:server [SEND!***] 
NSEND, from:server [NSEND***]

list message UDP:
FANT, SCORE, MESSA, ENDGA et MESSP

RIMOV 004***DOMOV 001***UPMOV 001***LEMOV 002***UPMOV 001***RIMOV 001***LEMOV 002***RIMOV 001***UPMOV 002***LEMOV 001***RIMOV 004***
RIMOV 001***UPMOV 002***LEMOV 001***RIMOV 004***
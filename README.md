# recursive-decent-parser
A basic recursive decent parser implemented in both C++ and Java. The program takes a text file and recognizes if it follows the grammar specified by the BNF.
## Grammar
* A -> I = E 
* E -> P O P | P 
* O -> + | - | * | / | ** 
* P -> I | L | UI | UL | (E) 
* U -> + | - | ! 
* I -> C | CI 
* C -> a | b | ... | y | z 
* L -> D | DL 
* D -> 0 | 1 | ... | 8 | 9 

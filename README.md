# Graph_Coloring
Minor Project on the Graph Coloring Problem
<br>
<b>Compile:</b> gcc -o opt main.c -lm
<br>
<b>Run:</b> ./opt myciel3.col
<br>
<p>
<b>NOTE:</b>
The rate at which the blue zone approaches fitness 1 needs to be change. Currently it grows linearly with respect to the generation. A better growth function for the blue zone would grow slower i.e. linear when the chromosomes are exploring the surrounding solution space and faster (maybe like exponential) when the chromosomes are settling in a local minima.
</p>

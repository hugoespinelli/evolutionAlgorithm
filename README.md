# evolutionAlgorithm
An algorithm to demonstrate evolution of a random string. It's a type of genetic algorithm. Only study purpose.

### How it works
This algorithm purpose is to simulate darwinism (theory of biological evolution). We have two phrases, our begin phrase that is
randomly generated and our final phrase (final objective). On each step of evolution generates several children and each one
has a chance to be mutated. Like natural selection, we select the phrase that is most similar to our final phrase. That process repeat
until both phrase are equal.

### Script params
You can call script with these follow args:<br />
`./main -p3 -g50 -f myfile.txt MY PHRASE`
+ p: percent of mutation of a single letter change. Default: `5`
+ g: number of children generated on each step. Default: `100`
+ f: file where you can put the final phrase. Default: `CELACANTO PROVOCA MAREMOTO` <br />
You also can input the final phrase without a file, just type the phrase right after script call.<br /><br />
**CAUTION**: The algorithm only works with UPPERCASE letters, so you must enter on this way.

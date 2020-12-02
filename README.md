# Weasel Program
Modified implementation of the [weasel program]() described by Richard Dawkins in the third chapter of [The Blind Watchmaker](https://en.wikipedia.org/wiki/The_Blind_Watchmaker).

<p align="center">
    <img width="590" height="351" src="images/weasel_program.png">
</p>


## Installation

Run the following command to compile the code:

```bash
make
```



## Usage

Run the weasel program as:

```bash
./bin/weasel_program "sentence"
```

Where `sentence` is the desired target for the algorithm. It has to be delimited by `"`. 

Results will be saved by default in `results/fitness.txt`. To generate a plot run:

```bash
gnuplot src/plot.p
```

Plot will be saved in `results`.



<p align="center">
  <img width="600" height="400" src="results/fitness.png">
</p>


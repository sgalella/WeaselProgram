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

After running the code, a plot of the fitness over iterations will be saved by default in `results/`. 



<p align="center">
  <img width="600" height="400" src="results/fitness.png">
</p>


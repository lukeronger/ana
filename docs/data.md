# General 

## .root

**.root** is the standard and will not not be converted.

# CLAS12

## hipo2root

**hipo2root** will convert a chain of ```.hipo``` files to ```.root```.

If more banks are created, simply navigate to the ```src/data/hipo2root``` directoy and add them to ```banks/hipo```.

Then navigate back to ```src/data/hipo2root``` and run the following commands

```
rm hipo2root*

./make_hipo2root.py -a

make
```
# Chain Structure

The naming scheme of a chain of hipo or root files given the head of the chain to file number *n* is:

```
data.hipo # head file
data_1.hipo
data_2.hipo
.
.
.
data_n.hipo
```

# Argument to Ana

The full path of the head of the data file chain needs to be provided as an argument to Ana. Here is an example of said argument modeled on the chain structure above:

```
~/Data/proton_experiment/data.hipo
```


                                            ***Autocorrect PJC Homework***

**Assignment**
Write a program to perform autocorrection of a word or set of words passed as arguments. Final program will have single threaded implementation, as well as implementation using more threads. User will be able to choose between them.

*Input*: 
- --dictionary, -d  [words in the dictionary] [words to correct]
- --file, -f "path"  [words to correct]
             
*Output*: 
original word (if nothing close is in the dictionary or word is in the dictionary) or set of words representing closest corrections on one line

**Implementation** 
Provided dictionary or path to the file is loaded into a dictionary{*char* : *set of words* } (this prevents duplicates), I have also decided to make the program case sensitive. So *Cancer* != *cancer*
I have decided to use Levenstein distance as a string metric, single threaded implementation is using slightly faster and optimised version of algorithm.
After geting the words on std input program will run it through dictionary looking for closest words in the dictionary and return them.

**Benchmarks**

| number of words | single threaded | parallel |
|-----------------|-----------------|----------|
| 50              | 386 ms          | 100 ms   |
| 200             | 2211 ms         | 575 ms   |
| 1000            | 9970 ms         | 2668 ms  |

Testing was performed on MBP 2015 with these characteristics:
- Processor Name:    Intel Core i7
- Processor Speed:    2.2 GHz
- Number of Processors:    1
- Total Number of Cores:    4
- L2 Cache (per Core):    256 KB
- L3 Cache:    6 MB
- Memory:    16 GB
                         
readme is wrtten for the commit 428805d, GitHub is displaying md tables in a weird way, maybe just download the file and view it locally.
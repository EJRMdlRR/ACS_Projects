# Data Profiling


## Introduction

Significant improvements can be achieved with pre-knowledge of the data to be handled. Notably, when the set of unique data has a low cardinality dictionary encoding can store this relatively small set of unique elemnts as condensed codes. 

## Strategy

The first thing was to analyze the data. A quick python script to count the unique elements and implement a rough Huffman coding proved that such a coding was viable. The distribution of unique elemnts seems fairly normal, which lowers the encoding's efficiency, but it still has an theoretical optimal improvement of up to ~80% depending on the input file. 

Initial results were limited by the fact that it was saving the binary huffman code as a string, trading one ascii string for another. If the dataset's elemnts are exceedingly large this can still be valuable, but that was not true in this case. 

Converting all the bit strings into integers saved space, with the integers varying from 5-3 digits, much more efficient than the 14-9 of the input. But not efficient enough when considering that each character is a byte, meaning it is base 256, but each integer is only base 10, thus discarding over 95% of possible encoding compressions.

After research, a full 256 bit encoding was not viable, largely because there is no encoding that supports it as text characters. ASCII only supports 127 symbols, with 0-31 being control characters and the last bit being reserved for coding extensions such as UTF-8. A common encoding is base64 encoding, but that uses only 6 bits to a byte. Therefore a base95 encoding was implemented to use as much of 7 bits as possible. The 8th bit was designated as a flag to denote the start of a symbol, this way the separators could be removed from the file further increasing efficiency. 

A bug arose late into development as when converting bit strings to integers the leading zeroes were unknowingly being discarded. To fix this all huffman codes were set to start with a leading 1, this means that they are all 1 bit larger as a penalty, however.

## Results

| File               | Analysis  | Encoding  | Writing   | Code Loading | Decoding  | Total Elements | Unique Elements | Repetition Ratio | Old Size   | New Size  | Improvement |
|--------------------|-----------|-----------|-----------|--------------|-----------|----------------|-----------------|------------------|------------|-----------|-------------|
| Small-Size-Column  | 0.026281s | 0.001252s | 0.037308s | 0.000634s    | 0.000634s | 119649         | 1000            | 119.65           | 932 KB     | 234 KB    | 3.98x       |
| Medium-Size-Column | 0.335359s | 0.027797s | 0.368561s | 0.005207s    | 4.00054s  | 1199755        | 10000           | 119.98           | 9,382 KB   | 3,282 KB  | 2.86x       |
| Large-Size-Column  | 16.1509s  | 0.728605s | 19.807s   | 0.192698s    | 86.707s   | 23574717       | 195427          | 120.63           | 184,132 KB | 68,182 KB | 2.70x       |

## Conclusion

Knowing what data is to be stored ahead of time is invaluable, but choosing the proper encoding equally so. When the codes where being stored as bit strings the number of unique words meant that at times the code was longer than the word. Furthermore, although the base95 encoding was chose to stay faithful to ASCII coding and thus ensure readability on as many machines as possible, it leaves almost a quarter of the 7-bit space wasted. More research needs to be done on whether including control characters would corrupt the file.

## Hardware Info

### Windows `Get-ComputerInfo` Dump

```
BiosCharacteristics                                     : {7, 9, 11, 12...}
BiosFirmwareType                                        : Uefi
BiosManufacturer                                        : LENOVO
BiosName                                                : N22ET72W (1.49 )
CsManufacturer                                          : LENOVO
CsNetworkAdapters                                       : {Ethernet 2, vEthernet (Default Switch), Ethernet, Wi-Fi...}
CsNetworkServerModeEnabled                              : True
CsNumberOfLogicalProcessors                             : 8
CsNumberOfProcessors                                    : 1
CsProcessors                                            : {Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz}
CsRoles                                                 : {LM_Workstation, LM_Server, NT}
CsStatus                                                : OK
CsSystemFamily                                          : ThinkPad T480s
CsSystemType                                            : x64-based PC
CsTotalPhysicalMemory                                   : 8480333824
CsPhyicallyInstalledMemory                              : 8388608
CsWakeUpType                                            : PowerSwitch
CsWorkgroup                                             : WORKGROUP
OsType                                                  : WINNT
OsVersion                                               : 10.0.19043
OsBuildType                                             : Multiprocessor Free
OsCodeSet                                               : 1252
OsForegroundApplicationBoost                            : Maximum
OsTotalVisibleMemorySize                                : 8281576
OsFreePhysicalMemory                                    : 969924
OsTotalVirtualMemorySize                                : 21079540
OsFreeVirtualMemory                                     : 2920824
OsInUseVirtualMemory                                    : 18158716
OsTotalSwapSpaceSize                                    :
OsSizeStoredInPagingFiles                               : 12797964
OsFreeSpaceInPagingFiles                                : 9408100
OsMaxNumberOfProcesses                                  : 4294967295
OsMaxProcessMemorySize                                  : 137438953344
OsArchitecture                                          : 64-bit
```
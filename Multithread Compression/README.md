# Multithread Compression Susing ZSTD Library

## Introduction

Compressing objects is a slow, but largely parallelizable operation. By sacrificing possible optimal compression, individual chunks can be compressed at near optimal ratios in parallel. This means that by separating the reading, compression, and writing into separate threads compression speed can be significantly improved.

## Installation

This project presumes you have zstd* already installed. If this is not true you can install it by running:

```sudo apt update && sudo apt install zstd```

After this the code can be downloaded by cloning the repository or downloading it through the github desktop GUI as a zip and then extracting it. Navigate to the folder in which this README is present and compile the code with:

```g++ -std=c++11 -Wall -g *.cpp -o ./main.o -lzstd -pthread```

The code can then be run with the following command:

```./main.o <INPUT_FILE> [<OUTPUT_FILE> <# THREADS>]```

The output file and desired number of threads are optional arguments. Either can appear, and will be autodetected based on whether the argument is an integer. If both appear they must appear in order.

\* ZSTD version 1.4.4 was used, but is not required to be that version.


## Design Choices

*   A common choice for parallel program tasks is a queue because it is quick to access, easy to make threadsafe, and has variable length. Thus, although reading the file could be parallelized as the file is contiguous memory and the size of each contiguous chunk is known, reading the file was done serially. Furthermore, reading the file was not the bottlenex in compression thus making that part faster would deliver marginal benefits if any. In fact, parallelizing reads may hurt performance as the non-sequential aspect of multithreading may harm any locality advantages given from reading contiguous data sequentially. Finally, reading is a largely IO process with minimal CPU usage, thus parallelizing it would not improve CPU usage much.
*   For similar performance reasons, writing to memory is also done serially.
*   Although both reading and writing are done serially, they are done serially in parallel. Or technically, concurrently. A common strategy to improve performance when working with IO streams is to have a separate thread receive frames/blocks/chunks and put them in a queue so the slower processing can happen without losing frames/blocks/chunks of data. This is commonly seen in sensor applications and is why reading and writing were set to run concurrently.
*   A thread-safe queue was implemented to store the tasks to be completed by parallel processes as the tasks can be performed in any order. Mutex locks on the read (pop-front) and writes (push-back) add overhead, but protect the data.
*   Although blocks can be read and compressed in any order, they must be written in the same order the uncompressed blocks exist in the original file. Thus a queue was not ideal for storing the compressed blocks as it does not store the block order. Sorting could be done to ensure the blocks are ordered, but that would lead to even more overhead than a thread-safe queue already has. So instead a vector was used.

    The value in the vector is found in its ordered positions. Each block can only write to the vector position it falls in after modulus arithmetic `(block_id % vector_size)`. The vector size in this case was chosen to be *16 * the number of threads*. This means that each thread can perform 16 compression operations before filling the vector. Divvying memory locations ensures that no two threads attempt to write to the same memory location.

    Various other rules are implemented to ensure it is thread-safe. Namely, a vector cannot write to a space that is already full. A location is not emptied until that data has been written to storage by the writer thread. The writer thread starts with a pointer to the first element in the vector and, once it sees it has data, writes that data to storage, erases the element data, and increases the pointer to point to the second element. Then it waits until the second element has data. Thus the writer can write data continuously as long as the data itself is continuous. If one thread is slower at compressing its data the other threads have 15 tasks left as a buffer before the vector is full. Once the vecotor is full all threads must wait until the writer has freed up space.

    There is a risk for collisions. This risk happens when the reader queues up blocks farther than *16 * the number of threads* blocks ahead of the current **next block to be written**. At this point there is an overlap in the modulus arithmetic and it is possible for two threads to pick data for the same block. This can cause a race condition.

    Example:
    8 threads are used. Compressing block #7 is slow. Block #135 is read and queued as a task. Before block #7 can be written to the empty space in the vector at position 7, block #135 is compressed and written there instead. This means that block #7 cannot write to the vector until position 7 is freed, but position 7 will never be freed until blocks #7-135 are written to storage. Considering this relies on the other threads being 16x faster than any given thread, the chances of this ocurring are relatively low. If reading was done in parallel and not sequentially this would be a more significant issue.



## Testing

A more thorough testing gauntlet still needs implementation.

## Summary



## Hardware Details

### Windows `systeminfo` Dump

```
OS Name:                   Microsoft Windows 10 Education
OS Version:                10.0.19043 N/A Build 19043
OS Manufacturer:           Microsoft Corporation
OS Configuration:          Standalone Workstation
OS Build Type:             Multiprocessor Free
System Manufacturer:       LENOVO
System Model:              20L8S36Y00
System Type:               x64-based PC
Processor(s):              1 Processor(s) Installed.
                           [01]: Intel64 Family 6 Model 142 Stepping 10 GenuineIntel ~1792 Mhz
BIOS Version:              LENOVO N22ET72W (1.49 ), 11/17/2021
Total Physical Memory:     8,087 MB
Available Physical Memory: 887 MB
Virtual Memory: Max Size:  20,596 MB
Virtual Memory: Available: 3,012 MB
Virtual Memory: In Use:    17,584 MB
Network Card(s):           5 NIC(s) Installed.
                           [01]: Cisco AnyConnect Secure Mobility Client Virtual Miniport Adapter for Windows x64
                                 Connection Name: Ethernet 2
                                 DHCP Enabled:    No
                                 IP address(es)
                                 [01]: 128.213.86.221
                                 [02]: fe80::98b4:d890:b1b2:8a3a
                                 [03]: 2620:0:2820:bc::283
                           [02]: Hyper-V Virtual Ethernet Adapter
                                 Connection Name: vEthernet (WSL)
                                 DHCP Enabled:    No
                                 IP address(es)
                                 [01]: 172.26.176.1
                                 [02]: fe80::f:498f:e661:5214
                           [03]: Intel(R) Ethernet Connection (4) I219-V
                                 Connection Name: Ethernet
                                 Status:          Media disconnected
                           [04]: Intel(R) Dual Band Wireless-AC 8265
                                 Connection Name: Wi-Fi
                                 DHCP Enabled:    Yes
                                 DHCP Server:     192.168.1.1
                                 IP address(es)
                                 [01]: 192.168.1.14
                                 [02]: fe80::e842:325:a783:5a26
                           [05]: Bluetooth Device (Personal Area Network)
                                 Connection Name: Bluetooth Network Connection
                                 Status:          Media disconnected
```
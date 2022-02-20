# Single Instruction Multiple Data (SIMD) General Matrix Multiplication (gemm) Tests

## Introduction

This project will explore the advantages of using SIMD intrinsincs to optimize matrix multiplication, a common operation in most fields of computing.

## Design Choices

* No templating is done because templating is slow. (Testing needs to be done to dertermine if diff is negligible.)
* By saving matrices as 1D matrices of size length x width entire matrix is contiguous. Makes memory access slightly faster as there are no lookups.
* Since matrices are of known size, allocate memory ahead of time. Removes penalty of changing vector size mid-matrix creation.
* The transpose is generated at the same time as the matrix. This wastes twice as much memory, but prevents O(length*width) operations each time a transpose for a multiplication is needed. Thus the more frequently a matrix is used as the second operand the lower the cost of that memory. (future implementations might leverage caching instead.)
* All 2D matrix dimensions are set as uint32_t, meaning it can reach a maximum size of ~4.3E9x4.2E9 elements. (Even though it is unlikely to exceed the uint16_t capacity of ~65E3x65E3)
* AVX was chosen over SSE as it has larger vector implementations (256 bits vs 128 bits). The best implementation would likely be a combination of the two so that if you can't fill the 256 bits you don't have to fall abck on classical techniques, as is done here currently.

## Compiling

As the goal is speed and AVX 2 is used the following flags need to be selected in the g++ compiler.

* -O3
* -march=native
* -mavx2

```g++  -O3 -march=native -mavx2 *.cpp *.h -o main```

## Testing

A more thorough testing gauntlet still needs implementation.

## Summary

The Intel SIMD Intrinsics were easy to use, but tricky to debug. By packing the data and sending it off to registers it's difficult at times to see where the error lies.

## Windows `systeminfo` Dump

```
Host Name:                 DESKTOP-2GFU4SV
OS Name:                   Microsoft Windows 10 Education
OS Version:                10.0.19043 N/A Build 19043
OS Manufacturer:           Microsoft Corporation
OS Configuration:          Standalone Workstation
OS Build Type:             Multiprocessor Free
Registered Owner:          hammei
Registered Organization:   
Product ID:                00328-20090-00000-AA602
Original Install Date:     10/16/2020, 3:42:47 PM
System Boot Time:          1/22/2022, 4:25:04 PM
System Manufacturer:       LENOVO
System Model:              20L8S36Y00
System Type:               x64-based PC
Processor(s):              1 Processor(s) Installed.
                           [01]: Intel64 Family 6 Model 142 Stepping 10 GenuineIntel ~1792 Mhz
BIOS Version:              LENOVO N22ET72W (1.49 ), 11/17/2021
Windows Directory:         C:\WINDOWS
System Directory:          C:\WINDOWS\system32
Boot Device:               \Device\HarddiskVolume2
System Locale:             en-us;English (United States)
Input Locale:              en-us;English (United States)
Time Zone:                 (UTC-05:00) Eastern Time (US & Canada)
Total Physical Memory:     8,087 MB
Available Physical Memory: 887 MB
Virtual Memory: Max Size:  20,596 MB
Virtual Memory: Available: 3,012 MB
Virtual Memory: In Use:    17,584 MB
Page File Location(s):     C:\pagefile.sys
Domain:                    WORKGROUP
Logon Server:              \\DESKTOP-2GFU4SV
Hotfix(s):                 14 Hotfix(s) Installed.
                           [01]: KB5008876
                           [02]: KB4562830
                           [03]: KB4577266
                           [04]: KB4577586
                           [05]: KB4580325
                           [06]: KB4586864
                           [07]: KB4589212
                           [08]: KB4593175
                           [09]: KB4598481
                           [10]: KB5000736
                           [11]: KB5009543
                           [12]: KB5006753
                           [13]: KB5007273
                           [14]: KB5005699
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
Hyper-V Requirements:      A hypervisor has been detected. Features required for Hyper-V will not be displayed.
```
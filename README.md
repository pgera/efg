# About

This project provides an efficient implementation for traversing large compressed graphs on GPUs. Graphs are compressed with Elias-Fano encoding (on the CPU), and the breadth first search (BFS) implementation traverses such graphs on the GPU. Since GPU memory capacity is limited, this approach can accomodate larger graphs in device memory. Graphs are compressed by a factor of 1.5x on average relative to the compressed spare row (CSR) format. If the graphs still do not fit in memory, unified virtual memory (UVM) is used to transfer data at runtime from the host.

# Build Requirements

 - Ubuntu 22.04
 - [CUDA 12](https://developer.nvidia.com/cuda-downloads)
 - [folly v2023.05.22.00](https://github.com/facebook/folly/releases/tag/v2023.05.22.00)


## Build

- `sudo apt install g++ libboost-all-dev libssl-dev libgoogle-glog-dev libdouble-conversion-dev`
- Build and install folly at <scratch_path>
    ```
    git clone https://github.com/facebook/folly.git
    cd folly
    git checkout v2023.05.22.00
    sudo ./build/fbcode_builder/getdeps.py install-system-deps --recursive
    python3 ./build/fbcode_builder/getdeps.py --allow-system-packages --scratch-path <scratch_path> build --no-tests
    ```
- Clone this project. In the project's Makefile: 
    - Set `FOLLY_INSTALL_DIR` to <scratch_path\>/installed/folly
    - Set `FMT_INSTALL_DIR` to <scratch_path\>/installed/fmt-XXX, where XXX will be a string generated during the folly build process.
 - `make -j` 

## Input Graph Format
Input graphs need to be in the Compressed Sparse Row (CSR) format consisting of two binary files, `vertex.CSR` and `edge.CSR`. `vertex.CSR` contains row-offsets and is of length `|V| + 1`. `edge.CSR` contains column indices and is of length `|E|`.  Each neighbour list in `edge.CSR` should be in sorted order. The data type for the input graphs should be 64-bits. This is merely done to simplify the input handling and has no bearing on the compression. The reported compression ratio is relative to the optimal CSR size.

Small sample graphs are included in the repository under `sample_graphs`. These can be used for basic tests, but are meaningless for any performance measurements. Larger graphs are available at https://p.gera.io/public/graphs/.

## Run

`./ef_bfs sample_graphs/tiny`

Usage:

    ./ef_bfs [OPTIONS] INPUT_DIR
    OPTIONS:
      -h [ --help ]           Print help
      -n [ --num ] arg (=100) Number of traversals
      -m [ --mapfile ] arg    Mapfile for remapping vertex ids. If provided, map[x]
                              will be used instead of x for starting a traversal
      -u [ --uvm ]            Use UVM for memory allocations
      -d [ --nosort ]         Disable the frontier sorting optimisation
      -r [ --root ] arg       Root for the traversal. Random roots will be used if 
                              unspecified

 - The `mapfile` option is useful for comparing the performance between reordered versions of the same graph. For example, the dataset above include graphs in their natural order and graphs reordered with HALO, and the reordered graphs include a mapfile. When running the the traversal on reordered graphs, the mapfile should be passed as an argument to get the same traversals.
 - The `-d` flag disables the partial frontier sorting optimisation. This should generally not be required, but it saves memory. It can be useful if the compressed graph barely fits in the GPU. For example, this is required for the `uk-2007-05`graph on a 12 GiB GPU.
 - The `-u`flag enables UVM allocations, which is useful for massive graphs that do not fit even after compression. DO NOT use `-d`along with `-u` as the performance will be very poor without the sorting optimisation in the UVM regime.

## Performance
BFS results averaged over 100 traversals from random sources:

| Graph              | \|V\| (\|E\|)     | CSR Size<br>(GiB) | EFG Size<br>(GiB) | Performance<br>Titan Xp (12 GiB Mem) | Performance<br>V100 (32 GiB Mem) |
|--------------------|-------------------|-------------------|-------------------|--------------------------------------|----------------------------------|
| twitter (d)        | 41.6 M (1.47 B)   | 5.63              | 3.33              | 238 ms<br>5.58 GTEPS                   | 127 ms<br>10.47 GTEPS          |
| gsh-h-15 (d)       | 68.66 M (1.8 B)   | 6.97              | 4.73              | 174 ms<br>7.57 GTEPS                   | 120 ms<br>10.94 GTEPS          |
| frndster (u)       | 65.61 M (3.61 B)  | 13.7              | 9.15              | 1006 ms<br>3.59 GTEPS                  | 349 ms<br>10.35 GTEPS          |
| uk-07-05 (d)       | 105.22 M (3.74 B) | 14.32             | 10.31             | 212 ms<br>11.06 GTEPS                  | 117 ms<br>20.02 GTEPS          |
| kron27_s (u)       | 63.07 M (4.22 B)  | 15.97             | 9.23              | 997 ms<br>4.27 GTEPS                   | 370 ms<br>11.43 GTEPS          |

The last three graphs would not have fit in memory on the Titan Xp GPU without compression.

## UVM
Graphs that do not fit even after compression use UVM. Compression is still beneficial for reducing the data transferred over the interconnect. The following graphs use UVM on the Titan Xp GPU

| Graph              | \|V\| (\|E\|)     | CSR Size<br>(GiB) | EFG Size<br>(GiB) | Performance<br>Titan Xp (12 GiB Mem) | Performance<br>V100 (32 GiB Mem) |
|--------------------|-------------------|-------------------|-------------------|--------------------------------------|----------------------------------|
| molr16 (u)         | 30.22 M (6.68 B)  | 25.1              | 14.5              | 2148 ms (UVM)<br>3.07 GTEPS          | 296 ms<br>22.32 GTEPS          |
| uk-75_s (u)       | 105.22 M (6.62 B) | 25.47             | 15.43             | 2825 ms (UVM)<br>2.34 GTEPS           | 284 ms<br>23.25 GTEPS          |

## Documentation
Please refer to the IPDPS '23 [paper](https://p.gera.io/public/papers/gera-ipdps23.pdf) for more details.

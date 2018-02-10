# mrmr-datareader

Transform `.csv` files into a optimized binary format.

The .csv data must meet the following requirements:

  - Each feature (column) can have up to 256 different values
    - We use a byte to encode values, so we only can represent numbers from 0 to 255.
  - The number of examples (rows) must be multiple of 16
    - This is because an optimization for the GPU version, feel free to repeat some examples to meet this requirement.
  
  
## Explanation
  
The access pattern of mRMR to the dataset is by feature in contrast to many other machine learning algorithms
in which data is procesed by pattern.

Ahough being a low-level technical nuance this aspect can significantly degrade mRMR performance since random access 
has a much greater cost than block-wise access. This is specially important in the case of GPU where data has to be transferred from CPU memory to GPU global memory.

Data is received in a sample-wise manner as it is shown in the next figure. After processing the data all values are reorganized by feature
Thus, the manner in which data is stored in memory is altered to allow access to all the values of a feature in 
a block-wise memory operation. 


![.mrmr data structure](/image.png)

# Fireworks Simulator

A firework simulator written in C! Available in both text or graphical simulation mode.


# Design Patterns
- All higher-level functions are located in main. Main contains the simulation loop 
- Memory allocation, physics calculation, graphical and text simulation are all separated to ensure modularity. 
- A custom linked-list library is fully implemented, some linked list functions have been modified to include function pointers as parameters. 
- Command line args...
- Dynamic memory allocation...

# Nyquist–Shannon Sampling Theorem 

The theorem guides us to sample at twice the rate of any frequency we want to capture. So let’s
consider the math. 

We will compute our time using the VY we read in from the file. We expect the magnitude of VY to be
greater than the magnitude of VX because these are fireworks that are being launched nearly vertically
so that they go off harmlessly high in the sky. We will compute this time once per firework before we
start the simulation loop and not update it in the loop as the firework changes velocity.

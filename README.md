### Quirdity discretizer

This is the source code for the discretizer module written as part of
Isencore's Quirdity software. Isencore was a startup that I co-founded. Its
first product Quirdity was aimed at 3D printing industry to programatically
stress test the products printed using 3D printing. Its aim was to cut on the
costs of manual testing on actual physical products by computationally testing
on a 3D simulated model.

The discretizer part was built on top of the freely available software Binvox
that is used to voxelize a 3D model at a given level of detail. This
discretizer module generates an N-level voxel tree for a 3D model and gives
other useful results like coordinates of each voxel and its 8 corners, whether
it is inside the model or not, etc. 

Now that original Isencore is shut down, I have decided to open source this
code since at the time we did not find any existing solution to the problem
solved by it. 

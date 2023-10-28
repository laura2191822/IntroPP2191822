/*

  Purpose:

    This program exemplifies parallelized heat diffusion simulation using the MPI (Message Passing Interface) library.

  Licensing:

    This code is distributed under the GNU LGPL license.

  Modified:

    27 October 2023

  Author:
  PRACE 
  MPI Modification:
  27 October 2023 by Laura Andrea Rodríguez Mejía, Universidad Industrial de Santander laura2191822@correo.uis.edu.co                
  The original code has been parallelized to distribute the workload efficiently across multiple MPI processes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include "heat.h"

int main(int argc, char **argv) {
    double a = 0.5;             //!< Diffusion constant
    field current, previous;    //!< Current and previous temperature fields
    double dt;                  //!< Time step
    int nsteps;                 //!< Number of time steps
    int image_interval = 500;   //!< Image output interval
    int restart_interval = 200; //!< Checkpoint output interval
    parallel_data parallelization; //!< Parallelization info
    int iter, iter0;            //!< Iteration counter
    double dx2, dy2;            //!< delta x and y squared
    double start_clock;         //!< Time stamps

    MPI_Init(&argc, &argv);
    initialize(argc, argv, &current, &previous, &nsteps, &parallelization, &iter0);

    int rank = parallelization.rank;
    int size = parallelization.size;

    /* Output the initial field */
    write_field(&current, iter0, &parallelization);
    iter0++;

    /* Largest stable time step */
    dx2 = current.dx * current.dx;
    dy2 = current.dy * current.dy;
    dt = dx2 * dy2 / (2.0 * a * (dx2 + dy2));

    /* Get the start time stamp */
    start_clock = MPI_Wtime();

    /* Calculate the workload for each process */
    int local_nsteps = nsteps / size;
    int extra_nsteps = nsteps % size;

    /* Time evolve */
    for (iter = iter0; iter < iter0 + local_nsteps + (rank < extra_nsteps ? 1 : 0); iter++) {
        exchange_init(&previous, &parallelization);
        evolve_interior(&current, &previous, a, dt);
        exchange_finalize(&parallelization);
        evolve_edges(&current, &previous, a, dt);
        if (iter % image_interval == 0) {
            write_field(&current, iter, &parallelization);
        }
        /* write a checkpoint now and then for easy restarting */
        if (iter % restart_interval == 0) {
            write_restart(&current, &parallelization, iter);
        }
        /* Swap current field so that it will be used
            as previous for the next iteration step */
        swap_fields(&current, &previous);
    }

    /* Determine the CPU time used for the iteration */
    if (rank == 0) {
        printf("Iteration took %.3f seconds.\n", (MPI_Wtime() - start_clock));
        printf("Reference value at 5,5: %f\n", previous.data[idx(5, 5, current.ny + 2)]);
    }

    write_field(&current, iter, &parallelization);
    finalize(&current, &previous, &parallelization);
    MPI_Finalize();

    return 0;
}

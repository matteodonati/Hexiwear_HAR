/**
 *	Libraries.
 */ 
 
/* Inclusion of data.h. */
#include "data.h"


/**
 *	Variables definition.
 */

/* Accelerometer buffer. */
volatile float accel_data[(int)DIM_BUFFER][N_AXES];

/* Gyroscope buffer. */
volatile float gyro_data[(int)DIM_BUFFER][N_AXES];

/* Input of the neural network to be filled with accelerometer data and gyroscope data. */
float model_input[N_SAMPLES][N_SENSORS];

/* Array which stores the offsets value. */
int offsets[(int)N_OFFSETS];


/**
 *	Function definition.
 */

/* init_offsets function that initializes offsets. */
void init_offsets()
{
    /* Iterate over offsets' elements. */
    for(int i = 0; i < (int)N_OFFSETS; i++)
		
		/* Initialize offsets[i]. */
		offsets[i] = (i * N_SAMPLES) * (1 - OVERLAP);
}

/* copy_data function that fills the model_input array with accelerometer data and gyroscope data. */
void copy_data(int start_offset)
{
	/* Local variables. */
	int i, j, k;
	
	/* Iterate over accel_data and gyro_data elements. */
	for(i = 0, j = start_offset; i < N_SAMPLES; i++, j++)
	{
		/* Iterate over accel_data[j % (int)DIM_BUFFER] and gyro_data[j % (int)DIM_BUFFER] elements. */
		for(k = 0; k < N_AXES; k++)
		{
			/* Copy accelerometer value. */
			model_input[i][k] = accel_data[j % (int)DIM_BUFFER][k];
			
			/* Copy gyroscope value. */
			model_input[i][k + N_AXES] = gyro_data[j % (int)DIM_BUFFER][k];
		}
	}
}
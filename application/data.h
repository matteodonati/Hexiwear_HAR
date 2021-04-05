#ifdef __cplusplus
extern "C" {
#endif

/**
 * Symbolic constats.
 */

/* Number of axis for each sensor (x, y, z). */
#define N_AXES 3

/* Number of sensors. */
#define N_SENSORS (N_AXES * 2)

/* Sampling frequency in Hertz. */
#define FREQUENCY 50

/* Duration of the sliding window in seconds. */
#define WINDOW_TIME 3

/* Number of samples stored by the sliding window. */
#define N_SAMPLES (FREQUENCY * WINDOW_TIME)

/* Dimension of accel_data and gyro_data buffers. */
#define DIM_BUFFER  225

/* Overlap percentage of two consecutive windows. */
#define OVERLAP 0.5f

/* Number of indexes which determine when to run an inference. */
#define N_OFFSETS (DIM_BUFFER / (N_SAMPLES * (1 - OVERLAP)))


/**
 * Variables declaration.
 */
 
/* Accelerometer buffer. */
extern volatile float accel_data[][N_AXES];

/* Gyroscope buffer. */
extern volatile float gyro_data[][N_AXES];

/* Input of the neural network to be filled with accelerometer data and gyroscope data. */
extern float model_input[][N_SENSORS];

/* Array which stores the offsets value. */
extern int offsets[];


/**
 * Functions declaration.
 */

/* Function that initializes offsets. */
void init_offsets();

/* Function that fills the model_input array with accelerometer data and gyroscope data. */
void copy_data(int);

#ifdef __cplusplus
}
#endif

/**
 *	Libraries.
 */

/* Inclusion of mbed.h */
#include "mbed.h"

/* Inclusion of model.h */
#include "model.h"

/* Inclusion of FXOS8700.h. */
#include "FXOS8700.h"

/* Inclusion of FXAS21002.h. */
#include "FXAS21002.h"

/* Inclusion of ctime.h. */
#include <ctime>

/* Inclusion of data.h. */
#include "data.h"

/* Inclusion of all_ops_resolver.h. */
#include "all_ops_resolver.h"

/* Inclusion of micro_error_reporter.h. */
#include "micro_error_reporter.h"

/* Inclusion of micro_interpreter.h. */
#include "micro_interpreter.h"

/* Inclusion of schema/schema_generated.h. */
#include "schema_generated.h"

/* Inclusion of version.h. */
#include "version.h"

/* Inclusion of kernel_util.h. */
#include "kernel_util.h"

/* Inclusion of images.h. */
#include "images.h"

/* Inclusion of oled.h. */
#include "oled.h"

/* Use tflite namespace. */
using namespace tflite;


/**
 *	Symbolic constants.
 */
 
/* Number of classes. */
#define N_CLASSES 6


/**
 *	Global variables.
 */
 
/* Activities array. */
const char labels[N_CLASSES][32] = {"Sitting", "Lying", "Standing", "Jumping", "Walking", "Running"};

/* Serial object that allows serial communication. */
Serial pc(USBTX, USBRX, 115200);

/* MicroMutableOpResolver object used in order to make use of the different types of layers. */
MicroMutableOpResolver<8> micro_op_resolver;

/* Pointer to a ErrorReporter object used to print errors. */
ErrorReporter* error_reporter = nullptr;

/* Pointer to a Model object. */
const Model* model = nullptr;

/* Pointer to a MicroInterpreter object used to run inferences. */
MicroInterpreter* interpreter = nullptr;

/* Pointer to the TfLiteTensor tensor that stores the input values to the neural network. */
TfLiteTensor* input = nullptr;

/* Pointer to the TfLiteTensor tensor that stores the output values of the neural network. */
TfLiteTensor* output = nullptr;

/* Fixed number of bytes used to store working tensors. */
const int k_tensor_arena_size = 32768;

/* Working tensors' dedicated memory. */
alignas(16) uint8_t tensor_arena[k_tensor_arena_size];

/* FXOS8700 object that represents the accelerometer. */
FXOS8700 accel(PTC11, PTC10);

/* FXAS21002 object that represents the gyroscope. */
FXAS21002 gyro(PTC11, PTC10);

/* Thread used to sample from accelerometer and gyroscope at 50Hz. */
Thread sampling_thread(osPriorityNormal, 512);

/* Variable used to store the index of the current sample. */
volatile int curr_sample;

/* Variable used to store an index of windows_offset. */
volatile int offset_index;

/* String used to store the output activity. */
char activity[32];

/* Classes. */
const char classes[N_CLASSES][32] = {"Sitting", "Lying", "Standing", "Jumping", "Walking", "Running"};


/**
 *	Functions declaration.
 */

/* Function that initializes all the variables and objects. */
void setup();

/* Function that runs the application. */
void loop();

/* Function used to sample and store new accelerometer and gyroscope values. */
void sample();

/* Function used to normalize the model_input data. */
void normalize_data();

/* Function used to run the inference. */
void evaluate();

/* Function used to refresh the display. */
void refresh_display();


/**
 *	Functions definition.
 */

/* main function. */
int main() 
{	
	/* Initialize variables and objects. */
	setup();
	
	/* Run the application. */
	loop();
	
	/* Return zero. */
	return 0;
}

/* setup function used to initializes variables and objects. */
void setup()
{
	/* Add the Quantize operator. */
	micro_op_resolver.AddQuantize();
	
	/* Add the ReLU operator. */
	micro_op_resolver.AddRelu();
	
	/* Add the Reshape operator. */
	micro_op_resolver.AddReshape();
	
	/* Add the Conv2D operator. Reshape and Conv2D implements the Conv1D operation. */
	micro_op_resolver.AddConv2D();
	
	/* Add the MaxPool2D operator. Reshape and MaxPool2D implements the MaxPool1D operation. */
	micro_op_resolver.AddMaxPool2D();
	
	/* Add the FullyConnected operator. */
	micro_op_resolver.AddFullyConnected();
	
	/* Add the Softmax operator. */
	micro_op_resolver.AddSoftmax();
	
	/* Add the Dequantize operator. */
	micro_op_resolver.AddDequantize();
	
	/* New MicroErrorReporter object. */
	static MicroErrorReporter micro_error_reporter;
	
	/* error_reporter initialization. */
	error_reporter = &micro_error_reporter;
	
	/* model initialization. */
	model = tflite::GetModel(g_model);

	/* New MicroInterpreter object. */
	static MicroInterpreter static_interpreter(model, micro_op_resolver, tensor_arena, k_tensor_arena_size, error_reporter);
	
	/* interpreter initialization. */
	interpreter = &static_interpreter;
	
	/* Memory allocation for all the necessary tensors. */
	interpreter->AllocateTensors();

	/* input initialization. */
	input = interpreter->input(0);
	
	/* output initialization. */
	output = interpreter->output(0);
	
	/* accel initialization. */
	accel.accel_config();
	
	/* gyo initialization. */
	gyro.gyro_config();
	
	/* offsets initialization. */
	init_offsets();
	
	/* curr_sample initialization. */
	curr_sample = 0;
	
	/* Display initialization. */
	init_oled();
	
	/* Print the logo image. */
    print_image(logo_image, 0, 25);
	
	/* Print the border image. */
	print_image(activity_border_image, 0, 57);
	
	/* Print the string "Initializing". */
	print_text("Initializing", 10, 59, 76, 15);
}

/* loop function used to run the application. */
void loop()
{
	/* Start to sample and store values. */
	sampling_thread.start(sample);
	
	/* Infinite loop. */
	while(true)
	{
		/* Decrease the semaphore counter by one. */
		semaphore.wait();
		
		/* Copy accelerometer data and gyroscope data into model_input starting from a specific index. */
		copy_data((offsets[offset_index] + (int)DIM_BUFFER - N_SAMPLES) % (int)DIM_BUFFER);
		
		/* Normalize the data. */
		normalize_data();
		
		/* Run the inference. */
		evaluate();
		
		/* Refresh the display. */
		refresh_display();
	}
}

/* sample function used to sample and store new accelerometer and gyroscope values. */
void sample()
{
	/* Local variable used to store the initial time of the current sampling step. */
	std::clock_t t_0;
	
	/* Local variable used to store the duration of the current sampling step. */
	float duration;
	
	/* Local variable used determine whether the buffer has been filled at least once. */
	bool is_first_cycle = true;
	
	/* Infinite loop that allows infinite sampling. */
	while(true)
	{
		/* Store the initial time. */
		t_0 = std::clock();
		
		/* Sample from accelerometer. */
		accel.acquire_accel_data_g(accel_data[curr_sample]);
		
		/* Sample from gyroscope. */
		gyro.acquire_gyro_data_dps(gyro_data[curr_sample]);
			
		/* Update of the current sample. */
		curr_sample++;
		
		/* Check if the working buffer is now full. */
		if(curr_sample == (int)DIM_BUFFER)
		{
			/* Reset curr_sample to zero. */
			curr_sample = 0;
			
			/* If it is the first time the buffer has been filled then set is_first_cycle to false. */
			if(is_first_cycle)
				
				/* Set is_first_cycle to false. */
				is_first_cycle = false;
		}
		
		/* Iterate over windows_offset. */
		for(int i = 0; i < (int)N_OFFSETS && !is_first_cycle; i++)
			
			/* Check if it is time to run an inference. */
			if(curr_sample == offsets[i])
			{
				/* Set offset_index equal to i. */
				offset_index = i;
				
				/* Increment the value of semaphore. */
				semaphore.release();
			}
			
		/* Get the duration of the current sampling step. */
		duration = (std::clock() - t_0) / (float)CLOCKS_PER_SEC;
	    
		/* Check if duration if less than 20ms. */
		if(duration < 0.02)
			
			/* Wait for (20ms - duration)ms. */
			wait(0.02 - duration);
	}
}

/* normalize_data function used to normalize the model_input data. */
void normalize_data()
{
	/* Iterate over samples. */
	for(int i = 0; i < N_SAMPLES; i++)

		/* Iterate over sensors. */
		for(int j = 0; j < N_SENSORS; j++)
			
			/* Normalize data. */
			model_input[i][j] /= ((j < N_AXES) ? 2 : 2000);
}

/* evaluate function used to run the inference. */
void evaluate()
{
	/* Iterate over model_input elements. */
	for(int i = 0; i < N_SAMPLES * N_SENSORS; i++)
		
		/* Set the input tensor to be equal to model_input. */
		input->data.f[i] = model_input[i / N_SENSORS][i % N_SENSORS];
	
	/* Run the inference. */
	interpreter->Invoke();
		
	/* Local variable used to store the maximum output value. */
	float max_output = 0;
	
	/* Local variable used to store the index of the maximum output value. */
	int max_index = 0;

	/* Iterate over classes. */
	for (int i = 0; i < N_CLASSES; i++) 
	{
		/* Store the current output. */
		float curr_output = output->data.f[i];
		
		/* Check if the current probability is greater than the maximum probability. */
		if (curr_output > max_output) 
		{
			/* Update max_output. */
			max_output = curr_output;
			
			/* Update max_index. */
			max_index = i;
		}
	}
	
	/* Update activity. */
	memcpy(activity, classes[max_index], 32);
}

/* refresh_display function used to refresh the display. */
void refresh_display()
{
	/* Print the current activity. */
	print_text(activity, 10, 59, 76, 15);
}
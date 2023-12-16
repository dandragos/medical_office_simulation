# Multithreaded Medical Office Simulation

This C program simulates the activity of a medical office, where a specified number of patient threads wait for the availability of resources representing doctors. The consultation involves blocking access to a doctor's structure and displaying the doctor's ID. Clients (patients) occupy the doctor resource for a randomly generated period within a specified limit. Each patient is generated at a random interval for a given time period. After consultation, the program displays the patient's waiting time and consultation time.

# Program Overview
## Doctors: 
The program creates a number of doctors (represented by structures) for simulation. Each doctor structure contains an ID and is protected by a mutex to ensure mutual exclusion.

## Patients: 
The number of patients is determined by the constant NUM_PATIENTS. Each patient is represented by a thread that simulates waiting for a doctor's availability and interacting with the doctor.

## Simulation Logic
### Initialization: 
The program initializes the doctors and their associated mutexes.

### Patient Threads: 
Threads representing patients are created. Each patient is generated at random intervals and waits for a doctor's availability.

### Doctor Availability Check: 
Patients check the availability of doctors. If a doctor is available, the patient acquires a lock on the doctor's mutex, updates the doctor's status, and proceeds with the consultation.

### Consultation and Timing: 
The patient simulates a consultation by occupying the doctor's structure for a random consultation time. The program records the start and end times to calculate the total waiting time.

### Release Doctor and Display Results: 
After the consultation, the patient releases the doctor's mutex and displays the waiting time and consultation time.

### Thread Cleanup: 
The main function waits for all patient threads to finish.

## Parameters
NUM_PATIENTS: Number of patient threads in the simulation.
## Notes
The program uses random intervals for generating patients and random consultation times to introduce variability in the simulation.
Each doctor's structure is protected by a mutex to ensure thread safety.
The program displays waiting times and consultation times for each patient.
Feel free to modify the program or experiment with different parameters to observe how the simulation behaves.


*made by Dan Dragos

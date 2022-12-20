The dining philosophers problem contains five philosophers sitting on a round
table can perform only one among two actions – eat and think. For eating, each
of them requires two forks, one kept beside each person. Typically, allowing
unrestricted access to the forks may result in a deadlock.

Philosophers have been simulated using threads, and the forks using global variables.
Deadlock has been resolved by utilization of semaphores to access the resources.

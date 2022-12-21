
The dining philosophers problem contains five philosophers sitting on a round
table can perform only one among two actions – eat and think. For eating, each
of them requires two forks, one kept beside each person. Typically, allowing
unrestricted access to the forks may result in a deadlock.

A1)
Philosophers have been simulated using threads, and the forks using global variables.
Deadlock has been resolved by utilization of semaphores to access the resources.

A2)
Deadlock has been resolved by strict ordering of resource requests.

B)
Repeated the above system only using semaphores now with a system that
also has two sauce bowls. The user would require access to one of the two sauce
bowls to eat, and can access any one of them at any point of time.



# Philosophers

## 🗣️ About

Philosophers is a project involving threads in C language. It relies on a well-known CS problem called "The dining philosophers problem" by Djikstra (https://en.wikipedia.org/wiki/Dining_philosophers_problem). 

The goal is quite simple : A given number of philosophers are gathered around a table. There is an infinite quantity of pasta located at the center of the table. Every philosopher needs to eat, then needs to sleep. No philosopher should starve, and they cannot communicate with each other. Moreover, there is only one fork per philosophers and one philosopher needs two forks to be able to eat. A philosopher can only access the fork located at his right and the fork located at his left.

More detailled information about the project can be found on the PDF.

## ⚙️ CS Concepts

This project is mainly about threads and their managment. Threads are basically allowing the program to run different chunks of code concurrently, and not line by line. This is very handy because in modern computers got multiple cores, so the OS can accomplish different tasks at the same time.

However, it does not come without some drawbacks. As some data can be accessed and/or modified by several threads, you need to that there is no data races (concurrent access or modification of data) in order to protect the program from potential errors. 

The use of mutexes is the mandatory. A mutex will make sure that a given datum will not be accessed or modified by more than one thread at once. If it is the case, it will make the program wait until the datum is available. This solution, however, have two major caveats. First, it can be really slow if many threads are waiting (sometimes longer than a more traditionnal one process/one thread solution !!!). Second, when you have several mutexes, deadlocks can happen. A deadlock is a situation when two threads are mutually waiting for each other to finish a task because of at least two mutexes involved. This situation will result in your program blocking infinitely and should be avoided at all costs !

## 🛠️ Resources

You can check those resources for more information and more detailed explanations :

--> For a comprehensive presentation and explanation of thread management in C, check this series of videos of CodeVault Youtube channel : https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

## 💿 Compilation and Execution

The program is furnished with a Makefile. Just write ```make```to create object files and an executable. To launch the executable, write ```philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]```. 

Note that the last parameter is optionnal (if not present, note that the program should run infinitely, as soon as you provide a reasonnable amount of philosophers (no more than 200, with a decent hardware).

## 🗑️ Deletion

The provided Makefile can also take care of deletion. Just write ```make fclean``` to remove executable and object files and ```make clean```to remove objects files only.

## ✅ Validation

This project has been validated with a mark of 100/100.

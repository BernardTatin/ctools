## libctools

Data structures...

## Notes
When a memory allocation fails, I _exit(1)_ without error messages on the console. In that case, I'm not sure that printing won't call another memory allocation. Even if it doesn't call any allocation, the system is in such a state that exiting without notification is better.

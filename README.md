[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Qiz9msrr)
# mini-project-1-template

## Spec - 2
- Using strtok to first tokenise wrt to ; and then with & and finally with ' '.

### Assumptions:
- Not allowing commands which have ; followed by & (just like bash)
- Atmost 4096 commands.
- Using perror to print errors.

## Spec - 3
- 

- If in multiple commands, one of them is wrong, then I print the error for that and continue instead of breaking
- Assuming a maximum length of 4096 characters
- `-` is the most recent directory, if i have hop home class, then i do hop -, we will go to home directory. (this is only for space seperated directories.)

## Spec - 4

- Printing an error for wrong flags 
- printing in lexographic order (case sensitive)

## Spec - 5
- for log execute, not storing the command which is running
- I am storing erroneous commmands as well.


## Spec - 6
- If time taken for command is > 2, then printing command in the next prompt.
- Printing the whole command in the next prompt if the command takes more than 2 seconds.


## Spec - 7
- Reference: https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat
- Virtual memory units is bytes.
- If permissions arent there, then I am not printing anything.

## Spec - 8
- Printing error for wrong flags.

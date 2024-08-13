[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description

# Assumptions

1. Piping and I/O redirection for background processes has not been implemented as told in the doubts document, Q.No 237

2. Ctrl + Z has not been implemented but to check the code for the cases where the process is needed to be in stopped state, ping <pid> 20 or ping <pid> 19 can be used to stop the process

3. Quotation marks are not been taken care of so piping may not work as expected in cases where sed grep or awk are used but piping and redirection works fine for the cases of the commands where there are no quotation marks involved

4. It is assumed that the input and output redirections are given at the end of the command that is,
    'echo > a.txt hi' is not a valid command but 'echo hi > a.txt ' is 
    if you wish to give both input and output please make sure that they are given at the end of the command i.e., after the arguments

5. Output Redirection has been implemented for userdefined processes but Input Redirection has not been implemented. 
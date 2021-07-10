# The Banker's Algorithm 
  
  Banker’s algorithm includes:  
1. The safety algorithm
2. The request algorithm  

Inputs :  
• Allocation and Maximum matrices and the available resources vector as in the
following example  

![image](https://user-images.githubusercontent.com/68311964/125160834-7847ce00-e17f-11eb-9f87-51e67c1a1cf2.png)

• The user can enquiry if the system is in a safe state  
• The user can enquiry if a certain immediate request by one of the processes can be
granted  
Example: If a request from process P1 arrives for (0, 4, 2, 0), can the request be
granted immediately?



Output:  
• Need matrix  
• If asked about safe state : Answer with yes or no , showing the sequence of
processes that will create a safe state if yes. 
Answer for mentioned example would be like this :
Yes , Safe state <P0,P2,P3,P4,P1>  
• If asked about immediate requests : Answer with yes or no , showing the
sequence of processes that will create a safe state if yes.    
Answer for mentioned example would be like this :  
Yes request can be granted with safe state , Safe state <P1req,P0,P2,P3,..>


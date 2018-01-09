# Full_Duplex_Chat_App_Using_FIFO
Full_Duplex_Chat_Application_Using_FIFO

#Project : FULL_DUPLEX_CHAT_USING_FIFO
                                          #Author : Sajan Kumar Jha

Description : This project performs the full duplex operation using two FIFO.Here the two process communicate with each other by using one of the FIFO for read/write operation.
so let us assume that there are FIFO1,FIFO2

FIFO1 : let us configure this to be used for read purpose by process1 and write purpose by process2

FIFO2 : let us configure this to be used for write purpose by process1 and read purpose by process2

so the complete process goes on like this:
                                        
                                        process1   ---->sends data-----> process2
                                        [write]                          [read]
                                        
                                        process2   ---->sends data------> process1
                                        [write]                            [read]

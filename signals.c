#include "headers.h"

void Signal_Handler1(int signal)
{
    if (signal == SIGINT)
    {
        if (Foreground != 0)
        {
            kill(Foreground, SIGINT);
        }
    }
}
// void Signal_Handler2(int signal)
// {
//     if (signal == SIGTSTP)
//     {
//         if (Foreground != 0)
//         {
//             int k = -1;
//             for (int i = 0; i < BACKGROUNDCOUNT; i++)
//             {
//                 if (Array[i].emptyflag == 1)
//                 {
//                     k = i;
//                     break;
//                 }
//             }
//             if (k == -1)
//             {
//                 printf("Error: The maximum number of background processes has been exceeded.\n");
//                 return;
//             }
//             else
//             {
//                 Array[k].emptyflag = 0;
//                 Array[k].processid = Foreground;
//                 strcpy(Array[k].Command, Dofrramingo);
//                 Array[k].Command[0] = toupper(Array[k].Command[0]);
//             }
//             kill(Foreground, SIGTSTP);
//         }
//     }
// }
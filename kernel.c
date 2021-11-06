/*  Dabana Intenque & Kefron Grant
  We did all five steps of this project and, each step is working fine.
   You can verify each step if it's working
   by uncommenting the line that contains comments. */
void printString(char*);
void readString(char*);
void readSector(char*,int);
void handleInterrupt21(int, int, int, int);

void main() {


  /*  char line[80];
    printString("Enter a line: ");
    readString(line);
    printString(line);

    char buffer[512];
    readSector(buffer, 30);
    printString(buffer);
  */


   // makeInterrupt21();
    //handleInterrupt21(0x21, 0,0,0,0);
    //interrupt(0x21,0,"hello",0,0);




    char line[80];
    makeInterrupt21();
    interrupt(0x21,1,line,0,0);
    interrupt(0x21,0,line,0,0);
 

 //    printString("Hello word");

    while(1);
}

void printString(char *letter){

      char al = '\n';

       while (*letter != '\0'){

          al = *letter;

         interrupt(0x10,0x0e*256+al,0,0,0);
          letter++;
    }
}



void readString(char *string){
    int i = 0;
    int length = 80;
    int endStr = 0x0;
    int lineFeed = 0xa;
    int bSpace = 0x8;
    int entr = 0xd;
//    char last[80];
 while(i != length){

    string[i]= interrupt(0x16,0,0,0,0);

    if(i == 78){
        string[i] = lineFeed;
        string[i+1] = endStr;
        break;
        }
    else if(string[i] == entr){
        string[i] = lineFeed;
        string[i+1] = endStr;
        break;
        }
    i++;

    }
}



void readSector(char* buffer, int sector){
    int AX = 2*256+1;
    int CX = 0*256+sector+1;
    int DX = 0*256+0x80; 
    interrupt(0x13,AX,buffer,CX,DX);

}

void handleInterrupt21(int ax, int bx, int cx, int dx){

    if(ax == 0){
    printString(bx);

    }
    else if(ax == 1){
    printString("Enter Line:");
    readString(bx);

    }
    else if(ax == 2){
    readSector(bx,cx);
    }
    else if(ax > 3){
    printString("An error occurred");
    }


}

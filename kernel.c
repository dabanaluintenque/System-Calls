/*  Dabana Intenque & Kefron Grant
  We did all six steps of this project and, each step is working fine.
   You can verify each step if it's working
   by uncommenting the line that contains comments. */
void printChar(char);
void printString(char*);
void readString(char*);
void readSector(char*,int);
void handleInterrupt21(int, int, int, int);
void readFile(char*, char*, char*);
void executeProgram(char*);
void terminate();

void main() {
  /*  char line[80];
    printString("Enter a line: ");
    readString(line);
    printString(line);
    char buffer[512];
    readSector(buffer, 30);
    printString(buffer);

    makeInterrupt21();
    handleInterrupt21(0x21, 0,0,0,0);
    interrupt(0x21,0,"hello",0,0);

    char line[80];
    makeInterrupt21();
    interrupt(0x21,1,line,0,0);
    interrupt(0x21,0,line,0,0);


    char buffer[13312];     // this is the maximum size of a file
    int sectorsRead;
   makeInterrupt21();

//    printString("Hello");
  interrupt(0x21,3,"messag",buffer, &sectorsRead);  // read the file into buffer
    if(sectorsRead>0)
      interrupt(0x21,0,buffer,0,0);  //print out the file
    else
      interrupt(0x21, 0,"messag not found in this sector.\r\n",0,0);
     //printString("Hello word");   */

      makeInterrupt21();
      interrupt(0x21,4,"shell",0,0);
    while(1);

}
  void printChar( char letter){
     interrupt(0x10,0xe*256+letter,0,0,0);
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
    else if(ax ==1){
    printString("Enter Line:");
    readString(bx);
    }
    else if(ax ==2){
    readSector(bx,cx);
    }
    else if(ax==3) {

     readFile(bx, cx, dx);
    }
   else if(ax==4){
    executeProgram(bx);
    }
  else if( ax==5){
    terminate();
    }
     else{

    printString("An error occurred when ax>5");
    }
}
  void readFile( char*filename, char*buffer){

    int *sectorsred;
    char dir [512];
     int fileentry;
     int sector;
    int foundfile;
    int entry;
    int i;

//    handleInterrupt21(3,*filename, *buffer, *sectorsred);
     readSector(dir,2);
   for(entry=0; entry<512; entry+=32){
       foundfile=1;
      for(fileentry=0; fileentry<6; fileentry++){

             //   printChar(dir[fileentry+entry]);

           //  printChar(filename[fileentry]);
      if(filename[fileentry]!=dir[fileentry+entry]){
       foundfile=0;
      //   entry+=6;
        //printChar(fileentry);
    break;
         }
      }
     if(foundfile==1){

break;

}
   }
//handle match=0, set to 0 and ret
//handle match=1 case
       if(foundfile==0){
     *sectorsred=0;
      return;
}
       for(i=6; i<26; i++){
          sector=dir[entry+i];
        if(sector==0)
      break;
    readSector(buffer, sector);
    buffer=buffer+512;
   *sectorsred=*sectorsred+1;
   }

}

 void executeProgram(char*name){
       char buffer[13312];
        int i;
        int segment =0x2000;
           readFile(name,buffer);
      while(i<13312){
     putInMemory(segment,i,buffer[i]);
    i++;

  }

   launchProgram(segment);
}

 void terminate(){

	char shellname[6];
	shellname[0]= 's';
	shellname[1] = 'h';
	shellname[2]='e';
	shellname[3]='l';
	shellname[4]='l';
	shellname[5]='\0';
	executeProgram(shellname);
}

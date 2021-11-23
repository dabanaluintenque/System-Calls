char buffer[13312];
char line[80];
int x;
int y;
int z;
char fileName[6];
char command[4];
void main(){
	while(1){
syscall(0, "SHELL>");
syscall(1,line);
	if(line[0] == 't' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e'){
			syscall(3,line+5,buffer);
			if(buffer[0] == '\0'){
				syscall(0,"file not found"); // because the file does not exist
			}
			else{
				syscall(0,buffer);
				buffer[0] = '\0';
			}
		}
		else if(line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c'){
			syscall(4,line+5);
         } else{
            syscall(4,"cannot be found");
      }
  }	
}

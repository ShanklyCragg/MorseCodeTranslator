#define ipblen 100
#define ashblen 300
#define textblen 100

const int ledpin = 13;      //The number of the LED Pin
int exclamationMarkTime = 1;    //Units of time to flash the "!" symbol
int asteriskTime = 2;           //Units of time to flash the "*" symbol
int atTime = 4;                 //Units of time to flash the "@" symbol
int interElementGapTime = 1;    //Units of time between flashes of symbols making up a single character e.g. in the representation of "d" between the "*" and the "!"
int slashTime = 4;              //Units of time to flash the "/" symbol, which represents the gap between characers forming a word. e.g. in the representation of "hi" between "!**" and "!!"
int spaceTime = 8;              //Units of time to flash a " ". Represents the gap between 2 words.

int potentiometer = 20;         //Declared globally because it can then be accessed from many differant functions

int redLED = 5;                 //Red pin for translated ascii to ash
int blueLED = 11;               //Blue pin for unmodified ash

char input[100];            //Size of array "input"
char ash[300];              //Size of array "ash"
char text[100];             //Size of array "text"

char ash_a[] = "*";
char ash_b[] = "!!*";
char ash_c[] = "!!@";
char ash_d[] = "*!";
char ash_e[] = "!";
char ash_f[] = "!*!";
char ash_g[] = "**";
char ash_h[] = "!**";
char ash_i[] = "!!";
char ash_j[] = "*!!";
char ash_k[] = "*@";
char ash_l[] = "!*@";
char ash_m[] = "!*";
char ash_n[] = "!@";
char ash_o[] = "@*";
char ash_p[] = "!@!";
char ash_q[] = "*!@";
char ash_r[] = "!@*";
char ash_s[] = "@!";
char ash_t[] = "@";
char ash_u[] = "@@";
char ash_v[] = "**!";
char ash_w[] = "***";
char ash_x[] = "*@!";
char ash_y[] = "!@@";
char ash_z[] = "**@";
char ash_1[] = "@!!*";
char ash_2[] = "@!!@";
char ash_3[] = "@!*!";
char ash_4[] = "@!**";
char ash_5[] = "@!*@";
char ash_6[] = "@!@!";
char ash_7[] = "@!@*";
char ash_8[] = "@!@@";
char ash_9[] = "@*!!";
char ash_0[] = "@!!!";
char ash_period[] = "@!!";
char ash_comma[] = "@!*";
char ash_apostrophe[] = "@*!";
char ash_questionMark[] = "@**";
char ash_exclamationMark[] = "@*@";
char ash_plus[] = "@@!";
char ash_minus[] = "@@*";
char ash_multiply[] = "@@@";
char ash_divide[] = "@!@";
char ash_space[] = " ";
char ash_error[] = "x";

void setup() {
  Serial.begin(9600);
}

void string2ashstring (char * ip, char * buf, int buflen) { //Ascii to ASH. This changes "Hello World" into "!**/!/!*@/!*@/@*  ***/@*/!@*/!*@/*!"
  buf[0] = '\0';                                            //Empties the buf everytime this function is called (Well effectively, in reality by setting the first character as a null it is seen as the end of the array, and since it is the first character it is "empty")
  for (int i ; ip[i] != '\0' ; i++) {                       //A for loop which stops looping once we reach the end of array "ip", signified by the null terminator
    strcat(buf, char2ash(ip[i]));                           //Runs char2ash to convert the ascii character to its ash, then puts it into the array called buf, attached at the end.
    if (ip[i] == '\0' || ip[i + 1] == '\0' || ip[i] == ' ' || ip[i + 1] == ' ') { //This code prevents a "/" from being added if the next character is a space or there is no more to come (Represented by the null terminator)
    }
    else {                                                  //Adds a slash to the buffer if the above criteria are not meant, so it the next character is a "@", "!" or a "*", and the previous character was a "@", "!" or "*"
      strcat(buf, "/");
    }
  }
}

void ashstring2charstring (char * ip, char * buf, int buflen) {    //This changes "!**/!/!*@/!*@/@*  ***/@*/!@*/!*@/*!" into "Hello World"
  int i = 0;                                                       //Initialising a bunch of counters for my input array
  int ashWordCounter = 0;
  int bufferCounter = 0;
  char temp;                                                       //Creating a variable to store the converted ash to temporarily
  char ashWord[256];                                               //This is my 3rd temporary buffer, this is where we build up the ash character symbols (! then * then !), pass this to ash2char.
  buf[0] = '\0';                                                   //Declaring the array "buf" as null
  do {
    if (ip[i] == ' ') {                                 //If we reach a space, this means we are at the end of an ash word
      temp = ash2char(ashWord);                         //Give the variable "temp" the converted ash string, which was stored in ash in the array "ashWord'
      buf[bufferCounter] = temp;                        //Array "buf" position "buferCounter" gets the ascii character from var "temp"
      ashWord[0] = '\0';                                //AshWord is reset to be a blank array, eady for the next word to be put into it
      ashWordCounter = 0;                               //The counter for ashWord is reset
      bufferCounter++;                                  //Buf counter is incremented so that it is set to the next position
      buf[bufferCounter] = ' ';                         //Adds in the space to seperate the ascii words
      bufferCounter++;                                  //Bufcounter again incrementred to the next position
    }
    else if (ip[i] == '/') {
      temp = ash2char(ashWord);                        //Give the variable "temp" the converted ash string, which was stored in ash in the array "ashWord'
      buf[bufferCounter] = temp;                       //Array "buf" position "bufferCounter" gets the character from var "temp"
      ashWord[0] = '\0';                               //AshWord is reset to be a blank array
      ashWordCounter = 0;                              //The counter for ashWord is reset
      bufferCounter++;                                 //Buf counter is incremented
    }
    else if (ip[i] == '\0') {
      temp = ash2char(ashWord);                        //Give the variable "temp" the converted ash string, which was stored in ash, in the array "ashWord"
      buf[bufferCounter] = temp;                       //Array "buf" position "bufferCounter" gets the character from var "temp"
      ashWord[0] = '\0';                               //AshWord is reset to be a blank array
      ashWordCounter = 0;                              //The counter for ashWord is reset
      bufferCounter++;
      break;                                           //This lets us espace the loop when we reach the null character from input buffer
    }
    else {
      ashWord[ashWordCounter] = ip[i];                 //This happens when you read an ash symbol. I copy the symbol from ip to ashWord
      ashWordCounter++;                                //Counter for ashWord is incremented
      ashWord[ashWordCounter] = '\0';
    }
    i++;                                               //Counter for the input array is incremented
  } while (i < buflen);                                //loop ends when reach the end of the buffer length
}

//This is turning my ash back to the letters that you input
char ash2char (char * m) {
  if (strcmp(m, ash_a) == 0) {
    return 'a';
  }
  else if (strcmp(m, ash_b) == 0) {
    return 'b';
  }
  else if (strcmp(m, ash_c) == 0) {
    return 'c';
  }
  else if (strcmp(m, ash_d) == 0) {
    return 'd';
  }
  else if (strcmp(m, ash_e) == 0) {
    return 'e';
  }
  else if (strcmp(m, ash_f) == 0) {
    return 'f';
  }
  else if (strcmp(m, ash_g) == 0) {
    return 'g';
  }
  else if (strcmp(m, ash_h) == 0) {
    return 'h';
  }
  else if (strcmp(m, ash_i) == 0) {
    return 'i';
  }
  else if (strcmp(m, ash_j) == 0) {
    return 'j';
  }
  else if (strcmp(m, ash_k) == 0) {
    return 'k';
  }
  else if (strcmp(m, ash_l) == 0) {
    return 'l';
  }
  else if (strcmp(m, ash_m) == 0) {
    return 'm';
  }
  else if (strcmp(m, ash_n) == 0) {
    return 'n';
  }
  else if (strcmp(m, ash_o) == 0) {
    return 'o';
  }
  else if (strcmp(m, ash_p) == 0) {
    return 'p';
  }
  else if (strcmp(m, ash_q) == 0) {
    return 'q';
  }
  else if (strcmp(m, ash_r) == 0) {
    return 'r';
  }
  else if (strcmp(m, ash_s) == 0) {
    return 's';
  }
  else if (strcmp(m, ash_t) == 0) {
    return 't';
  }
  else if (strcmp(m, ash_u) == 0) {
    return 'u';
  }
  else if (strcmp(m, ash_v) == 0) {
    return 'v';
  }
  else if (strcmp(m, ash_w) == 0) {
    return 'w';
  }
  else if (strcmp(m, ash_x) == 0) {
    return 'x';
  }
  else if (strcmp(m, ash_y) == 0) {
    return 'y';
  }
  else if (strcmp(m, ash_z) == 0) {
    return 'z';
  }
  else if (strcmp(m, ash_1) == 0) {
    return '1';
  }
  else if (strcmp(m, ash_2) == 0) {
    return '2';
  }
  else if (strcmp(m, ash_3) == 0) {
    return '3';
  }
  else if (strcmp(m, ash_4) == 0) {
    return '4';
  }
  else if (strcmp(m, ash_5) == 0) {
    return '5';
  }
  else if (strcmp(m, ash_6) == 0) {
    return '6';
  }
  else if (strcmp(m, ash_7) == 0) {
    return '7';
  }
  else if (strcmp(m, ash_8) == 0) {
    return '8';
  }
  else if (strcmp(m, ash_9) == 0) {
    return '9';
  }
  else if (strcmp(m, ash_0) == 0) {
    return '0';
  }
  else if (strcmp(m, ash_period) == 0) {
    return '.';
  }
  else if (strcmp(m, ash_comma) == 0) {
    return ',';
  }
  else if (strcmp(m, ash_apostrophe) == 0) {
    return '\'';
  }
  else if (strcmp(m, ash_questionMark) == 0) {
    return '?';
  }
  else if (strcmp(m, ash_exclamationMark) == 0) {
    return '!';
  }
  else if (strcmp(m, ash_plus) == 0) {
    return '+';
  }
  else if (strcmp(m, ash_minus) == 0) {
    return '-';
  }
  else if (strcmp(m, ash_multiply) == 0) {
    return '*';
  }
  else if (strcmp(m, ash_divide) == 0) {
    return '/';
  }
  else if (strcmp(m, ash_space) == 0) {
    return ' ';
  }
  else {
    return '\0';
  }
}

char  * char2ash(char c) {
  c = tolower(c);
  switch (c) {

    case 'a':
      return ash_a;
      break;

    case 'b':
      return ash_b;
      break;

    case 'c':
      return ash_c;
      break;

    case 'd':
      return ash_d;
      break;

    case 'e':
      return ash_e;
      break;

    case 'f':
      return ash_f;
      break;

    case 'g':
      return ash_g;
      break;

    case 'h':
      return ash_h;
      break;

    case 'i':
      return ash_i;
      break;

    case 'j':
      return ash_j;
      break;

    case 'k':
      return ash_k;
      break;

    case 'l':
      return ash_l;
      break;

    case 'm':
      return ash_m;
      break;

    case 'n':
      return ash_n;
      break;

    case 'o':
      return ash_o;
      break;

    case 'p':
      return ash_p;
      break;

    case 'q':
      return ash_q;
      break;

    case 'r':
      return ash_r;
      break;

    case 's':
      return ash_s;
      break;

    case 't':
      return ash_t;
      break;

    case 'u':
      return ash_u;
      break;

    case 'v':
      return ash_v;
      break;

    case 'w':
      return ash_w;
      break;

    case 'x':
      return ash_x;
      break;

    case 'y':
      return ash_y;
      break;

    case 'z':
      return ash_z;
      break;

    case '1':
      return ash_1;
      break;

    case '2':
      return ash_2;
      break;

    case '3':
      return ash_3;
      break;

    case '4':
      return ash_4;
      break;

    case '5':
      return ash_5;
      break;

    case '6':
      return ash_6;
      break;

    case '7':
      return ash_7;
      break;

    case '8':
      return ash_8;
      break;

    case '9':
      return ash_9;
      break;

    case '0':
      return ash_0;
      break;

    case '.':
      return ash_period;
      break;

    case ',':
      return ash_comma;
      break;

    case '\'':
      return ash_apostrophe;
      break;

    case '?':
      return ash_questionMark;
      break;

    case '!':
      return ash_exclamationMark;
      break;

    case '+':
      return ash_plus;
      break;

    case '-':
      return ash_minus;
      break;

    case '*':
      return ash_multiply;
      break;

    case '/':
      return ash_divide;
      break;

    case ' ':
      return ash_space;
      break;

    default:
      return ash_error;
  }
}

void promptReadln(char * userStuff, char * input, int promptLen) {  
  int i = 0;
  while (!Serial.available());                //This means the code only runs when the user enters input
  while (Serial.available()) {                //While there is data on the serial line
    input[i] = Serial.read();                 //then put the next character into array "ip" poition[i].
    delay(10);                                //The arduino reads information too fast so we need to slow it down to avoid missing characters
    i++;                                      //Increment [i] so that next character on the serial gets put in the next space in the array.
  }
}


void potentiometerDelay() {
  pinMode(A0, INPUT);                         //Sets the potentiometer to the 
  potentiometer = (analogRead(A0) / 2.046);   //Sets variable "potentiometer" to the value from the potentiometer, the maximum value the potentiometer can reach is 1023, dividing this by 2.046 makes the largest value 500 so it increses linearly
  if (potentiometer < 20) {                   //Ensures that 1 unit of time can never be shorter than 20ms (the minimum from the spec)
    potentiometer = 20;                       //Sets the value to the minimum if it wants to be shorter
  }
  else if (potentiometer > 500) {             //Ensures that 1 unit of time can never be longer than 500ms (the maximum from the spec)
    potentiometer = 500;                      //Sets the value to the maximum if it wants to go higher than 500ms (It shouldn't but this is as a fail safe)
  }
  /*Serial.print("potentiometer value is ");
  Serial.print(potentiometer);
  Serial.println(" milliseconds");*/
}

void unModifiedAsh2led(char * buf, int pin, int potentiometer) { //This function is called when the input was ash code
  int i = 0;
  pinMode(11, OUTPUT);                                           //Sets the blue led to output so that it lights up
  for (i = 0 ; buf[i] != '\0' ; i++) {                           //For loops which ends once we reach the end of the string
    if (buf[i] == '!') {                                         //If the character is an "!" then shine the LED for the relative unit of time for an exclamation mark, multiplied by the value on the potentiometer (As the "!" is worth 1 unit, it will be between 20 and 500 as per specification)
      digitalWrite(blueLED, HIGH);          
      delay(exclamationMarkTime * potentiometer);
      digitalWrite(blueLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == '*') {                          //These other "else ifs" act in a very similar way to the one above, but with differant delays
      digitalWrite(blueLED, HIGH);                     //Turn on the blue LED
      delay(asteriskTime * potentiometer);             //Leave the LED on for the relative unit of time an asterisk should flash for, multiplied by the value of the potentiometer (between 20-500ms)
      digitalWrite(blueLED, LOW);                      //Turn the LED off
      delay(interElementGapTime * potentiometer);      //Between every flash there needs to be a delay betweenm messages
    }
    else if (buf[i] == '@') {
      digitalWrite(blueLED, HIGH);
      delay(atTime * potentiometer);
      digitalWrite(blueLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == '/') {
      digitalWrite(blueLED, HIGH);
      delay(slashTime * potentiometer);
      digitalWrite(blueLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == ' ') {
      digitalWrite(blueLED, HIGH);
      delay(spaceTime * potentiometer);
      digitalWrite(blueLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
  }
}

void modifiedAsh2led(char * buf, int pin, int potentiometer) {  //This is called when you enter ascii and it is converted to ASH
  int i = 0;
  pinMode(5, OUTPUT);                                           //Sets the red led to output so that it lights up
  for (i = 0 ; buf[i] != '\0' ; i++) {
    if (buf[i] == '!') {
      digitalWrite(redLED, HIGH);
      delay(exclamationMarkTime * potentiometer);
      digitalWrite(redLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == '*') {
      digitalWrite(redLED, HIGH);
      delay(asteriskTime * potentiometer);
      digitalWrite(redLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == '@') {
      digitalWrite(redLED, HIGH);
      delay(atTime * potentiometer);
      digitalWrite(redLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == '/') {
      digitalWrite(redLED, HIGH);
      delay(slashTime * potentiometer);
      digitalWrite(redLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
    else if (buf[i] == ' ') {
      digitalWrite(redLED, HIGH);
      delay(spaceTime * potentiometer);
      digitalWrite(redLED, LOW);
      delay(interElementGapTime * potentiometer);
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  promptReadln("New message", input, ipblen);                     //Call function to read user input
  if (input[0] == '*' || input[0] == '!' || input[0] == '@') {    //Checks if user input was ASH
    strcpy(ash, input);                                           //makes a copy of the users input
    ashstring2charstring(input, text, textblen);                  //Calls a function which converts the ash to ascii
  }
  else {
    strcpy(text, input);                                          //If the users input was not ASH, that must mean it was ascii
    string2ashstring(input, ash, ashblen);                        //Calls a function which converts the ascii to ASH
  }
  potentiometerDelay();                                           //Sets the transmission speed by reading the value of the potentiometer
  if (input[0] == '*' || input[0] == '!' || input[0] == '@') {    //If users input was ash, trasmit on the blue LED
    Serial.println(text);                                           //Prints out the ascii
    unModifiedAsh2led(ash, blueLED, potentiometer);
  }
  else {                                             //If the input was ascii transmit using the red LED
    Serial.println(ash);                                            //Pritns out the ash
    modifiedAsh2led(ash, redLED, potentiometer);
  }
  memset(&input[0], 0, sizeof(input));               //Resetting some arrays to be empty
  memset(&text[0], 0, sizeof(text));
}

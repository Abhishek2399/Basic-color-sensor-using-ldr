#define r A0 // ldr connected to A0, red 
#define g A2 // ldr connected to A2, green

int red_op = 9; // red led display output 
int grn_op = 10;// green led display output 


int r_ref = 1130; // taking ref value using "white" light through red filter 
int g_ref = 800;  // taking ref value using "white" light through green filter 

int r_data;
int g_data;

/* rgb led used for back light */
int red = 3 ;
int grn = 5 ;
int blu = 9 ; 
/* -------<>-------- */

int t = 1000 ; // delay for time 't'

char color ; 
int data ;

/* function used for testing various color input values */
void glow(char data){
  if (data == 'r'){
  digitalWrite(red, 0);
  digitalWrite(grn, 255);
  digitalWrite(blu, 255);
  
  }
  else if(data == 'g'){
  digitalWrite(red, 255);
  digitalWrite(grn, 0);
  digitalWrite(blu, 255);
 
  }
  else if(data == 'b'){
  digitalWrite(red, 255);
  digitalWrite(grn, 255);
  digitalWrite(blu, 0);
  
  }
  else if(data == 'w'){
  digitalWrite(red, 0);
  digitalWrite(grn, 0);
  digitalWrite(blu, 0);
    
  }
  else if(data == 'o'){
    off();
  }

}

/* switching off the back light */
void off(){
  digitalWrite(red, 255);
  digitalWrite(grn, 255);
  digitalWrite(blu, 255);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(op_led, OUTPUT);

pinMode(r, INPUT); 
pinMode(g, INPUT);

pinMode(red, OUTPUT);
pinMode(grn, OUTPUT);

}

void loop() {
if (Serial.available()>0){
  color = Serial.read();
}
glow(color);

// reading vlaues passing through the red filter 
r_data = analogRead(b); 
Serial.print("r_data -->"); 
Serial.println(r_data);

// reading vlaues passing through the green filter 
g_data =analogRead(b); 
Serial.print("g_data -->"); 
Serial.println(g_data); 

b_data = analogRead(b); 
Serial.print("b_data -->"); 
Serial.println(b_data); 

/* comparing the values passing through filter for various objects */

/* more the difference between ref value of particular color and input value, indicates that the following color is absent */

if((r_ref-r_data) < (g_ref-g_data)){ 
  Serial.println("red detected");
  analogWrite(red_op, 0);
  analogWrite(grn_op, 255);
}

else if((r_ref-r_data) > (g_ref-g_data)){
  Serial.println("green detected");
  analogWrite(red_op, 255);
  analogWrite(grn_op, 0);
}

else{
  off();
}

delay(500); 

}

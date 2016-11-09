float Kp = 25, Ki = 0.05, Kd = 30;
float err = 0;
float sum_err = 0, diff_err = 0 , last_err = 0;
int power = 0;
int ac_power = 0;
int sensor[5] = {0, 0, 0, 0, 0 };
int max_power = 50 ;
int l_power = 0;
int r_power = 0;
int x = 0;

// test
void setup()
{
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

  delay(500);
  drive(69, 80);
  delay(500);
  drive(0, 0);
}

void loop()
{
  for (int i = 0 ; i < 6 ; i++)
  {
    int j = analogRead(i);
    sensor[i] = ( j < 500 ) ? 1 : 0 ;

  }








  if      ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))    err = 6 / 4; //01111
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))    err = 5 / 4; //00111
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))    err = 4 / 4; //00001
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))    err = 3 / 4; //00011
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 0))    err = 2 / 4; //00010
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))    err = 1 / 4; //00110
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))    err = 0;  //01110
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))    err = 0;  //00100
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))    err = -1 / 4; //01100
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))    err = -2 / 4; //01000
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))    err = -3 / 4; //11000
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))    err = -4 / 4; //10000
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))    err = -5 / 4; //11100
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))    err = -6 / 4; //11110
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)) {
    if (err < 0 ) err = -7 / 4;
    else err = 7 / 4;
  }

  if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0) && analogRead(A5) < 500 )
  {
    

    
    drive(50, 50);
    delay(100);
    x += 1;
  }



  //P = err;
  sum_err += err;
  sum_err = constrain(sum_err, -400, 400);
  diff_err = err - last_err;
  ac_power = int((Kp * err) + (Ki * sum_err) + (Kd * diff_err));
  last_err = err;
  //previous_I = I;
  // previous_err = err;

  power = constrain(ac_power, -max_power, max_power);
  if (power > 0) {
    l_power = max_power + power ;
    r_power = max_power - power;
  }
  else {
    l_power = max_power + power ;
    r_power = max_power - power;
  }


  //track_line_2();
  drive(l_power, r_power);
  delay(10);
  //  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
  //  {
  //    drive(-20, -20); delay(50);
  //    drive(100, 100); delay(700);
  //    while(1)
  //    {
  //       drive(0, 0);
  //    }
  //
  //  }
}




void drive(int va, int vb) {
  va = constrain(va, -255, 255);
  vb = constrain(vb, -255, 255);

  if (va >= 0) {
    analogWrite(11, va);
    digitalWrite(6, 0);
    digitalWrite(5, 1);
  } else {
    analogWrite(11, va);
    digitalWrite(6, 1);
    digitalWrite(5, 0);
  }

  if (vb >= 0) {
    analogWrite(3, vb);
    digitalWrite(9, 0);
    digitalWrite(10, 1);
  } else {
    analogWrite(3, vb);
    digitalWrite(9, 1);
    digitalWrite(10, 0);
  }
}
void track_line_1()
{

  if (sensor[4] == 1) {

    left(70, 70);
  }
  else if (sensor[0] == 1) {

    right(70, 70);
  }
  else forward(70, 70);
}

void track_line_2()
{

  if (sensor[3] == 1) {

    left(70, 70);
  }
  else if (sensor[1] == 1) {

    right(70, 70);
  }
  else forward(70, 70);
}


void _break(int x , int y)
{
  analogWrite(11, x);
  analogWrite(3, y);
  digitalWrite(9, 1);
  digitalWrite(5, 1);
}
void forward(int x , int y)
{
  analogWrite(11, x);
  analogWrite(3, y);
  digitalWrite(10, 1);
  digitalWrite(5, 1);
}
void left(int x , int y)
{
  analogWrite(11, x);
  analogWrite(3, y);
  digitalWrite(10, 1);
  digitalWrite(5, 0);
}

void right(int x , int y)
{
  analogWrite(11, x);
  analogWrite(3, y);
  digitalWrite(10, 0);
  digitalWrite(5, 1);
}








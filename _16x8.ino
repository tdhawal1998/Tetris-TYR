boolean win=true;
const int rows=16;
const int cols=8;
int value[rows][cols];
unsigned long a=0;
unsigned long time=0;
int interval=500;
int inLeft=10, inRight=4, inRotate=9;
  int outRow1[] = {23,25,27,29,31,33,35,37}; //8 outputs for top 
  int outCol2[] = {38,40,42,44,46,48,50,52}; //8 outputs for lower 
  int outCol1[] = {22,24,26,28,30,32,34,36}; //8 outputs for top square
  int outRow2[] = {39,41,43,45,47,49,51,53}; //8 outputs for lower square
  
void setup()
{
  digitalWrite(inLeft,LOW);
  digitalWrite(inRight,LOW);
  digitalWrite(inRotate,LOW);
  Serial.begin(9600);
  for (int i=0;i<rows;i++)
  {
  for (int j=0;j<cols;j++)
  {
  value[i][j]=0;
  }
  }
  pinMode(inLeft,INPUT);
  pinMode(inRight,INPUT);
  pinMode(inRotate,INPUT);
  for(int i=0;i<8;i++)  
  {
    pinMode(outRow1[i],OUTPUT);
    pinMode(outRow2[i],OUTPUT);
  }
  for(int i=0;i<8;i++)  
  {
    pinMode(outCol1[i],OUTPUT);
    pinMode(outCol2[i],OUTPUT);
  }
  randomSeed(analogRead(0));
  
}
void loop()
{ 
  if (win) {
  if (a==0)
  {
  create();
  for (int i=0;i<rows/2;i++)
  {
    digitalWrite(outRow1[i],LOW);
    digitalWrite(outCol1[i],HIGH);
 digitalWrite(outRow2[i],LOW);
    digitalWrite(outCol2[i],HIGH);  }
  }
  time = millis();
  //Serial.println(time);
  //Serial.println(a);
  
  if (time>=a*interval)
  {
    output();
  moveDown();
  a++;
  /*for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      Serial.print(value[i][j]);
      
    }
    Serial.println();
  }
  Serial.println();
  */
  }
 
  int left = analogRead(inLeft);
  int right = analogRead(inRight);
  int rott = analogRead(inRotate);
  
  if(left>512)  
  { moveLeft();
 for (int i=0;i<5;i++)
{
  delay(10);
  output();
} 
  }
  if(right>512) { 
   moveRight(); 
for (int i=0;i<5;i++)
{
  delay(10);
  output();
} 
}
  if(rott>512)  { rotate(); 
 for (int i=0;i<5;i++)
{
  delay(10);
  output();
} 
}
  
  
  output();
  } 
}
void output()
{
  
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<cols;j++)
    {
      boolean flag=false;
      if(value[i+8][j]!=0 )
      {
        
        flag=true;
        digitalWrite(outRow1[i],HIGH);
        digitalWrite(outCol1[j],LOW);
        
        
      }
      if(value[i][j]!=0 )
      {
        
        flag=true;
        digitalWrite(outRow2[i],HIGH);
        digitalWrite(outCol2[j],LOW);
        
      }
     if (flag)
     delay(1);   
        digitalWrite(outRow1[i],LOW);
        digitalWrite(outCol1[j],HIGH);
        digitalWrite(outRow2[i],LOW);
        digitalWrite(outCol2[j],HIGH);
//        digitalWrite(outCol2[j],LOW);
      
      /*else
      {
      digitalWrite(outRow1[i],LOW);
      digitalWrite(outCol1[j],HIGH);
      //digitalWrite(outCol2[j],HIGH);
      } */
    }
  }
  /*for(int i=8;i<rows;i++)
  {
    for(int j=0;j<cols;j++)
    {
      if(value[i][j]!=0 )
      {
        digitalWrite(outRow2[i-8],HIGH);
       // digitalWrite(outCol1[j],LOW);
        digitalWrite(outCol2[j],LOW);
      }
      else
      {
        digitalWrite(outRow2[i-8],LOW);
        //digitalWrite(outCol1[j],HIGH);
        digitalWrite(outCol2[j],HIGH);
      }
    }
  } */
}
void moveLeft()
{
  boolean check=true;
  for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      if (value[i][j]==2)
      {
        if (j==0) check=false;
        else
        {
          if (value[i][j-1]==1) check=false;
        }
      }
    }
  }
  output();
  if (check)
  {
    for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      if (value[i][j]==2)
      {
        value[i][j-1]=2;
        value[i][j]=0;
      }
    }
  }
  }
}
void moveRight()
{
   boolean check=true;
  for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      if (value[i][j]==2)
      {
        if (j==cols-1) check=false;
        else
        {
          if (value[i][j+1]==1) check=false;
        }
      }
    }
  }
  output();
  if (check)
  {
    for (int i=rows-1;i>=0;i--)
  {
    for (int j=cols-1;j>=0;j--)
    {
      if (value[i][j]==2)
      {
        value[i][j+1]=2;
        value[i][j]=0;
      }
    }
  }
  } 
}
void moveDown()
{
     boolean check=true;
  for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      
      if (value[i][j]==2)
      {
        output();
        if (i==rows-1) check=false;
        else
        {
          if (value[i+1][j]==1) check=false;
        }
      }
    }
  }
  output();
  if (check)
  {
    
    for (int i=rows-1;i>=0;i--)
  {
    for (int j=cols-1;j>=0;j--)
    {
      if (value[i][j]==2)
      {
        value[i+1][j]=2;
        value[i][j]=0;
      }
    }
  }
  }
 else
{
  for (int i=rows-1;i>=0;i--)
  {
    for (int j=cols-1;j>=0;j--)
    {
      if (value[i][j]==2)
      {
        value[i][j]=1;
      }
    }
  }
  Remove();
  checkLoss();
  if(win)
  create();
} 
}
void checkLoss()
{
for (int j=0;j<cols;j++)
{
if (value[0][j]==1)
win=false;
}
if (!win)
{
  for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      value[i][j]=0;
    }
  }
while (1>0)
{
  for(int i=0;i<8;i++)
  {
    for (int j=0;j<8;j++)
    {
      if (i==j || i==7-j) {
   digitalWrite(outRow1[i],HIGH);
  digitalWrite(outCol1[j],LOW); 
  digitalWrite(outRow2[i],HIGH);
  digitalWrite(outCol2[j],LOW); 
  delay(1);
  digitalWrite(outRow1[i],LOW);
  digitalWrite(outCol1[j],HIGH); 
  digitalWrite(outRow2[i],LOW);
  digitalWrite(outCol2[j],HIGH); 
  }}}
}
}}
void Remove(){
int c=0; 
for(int r=0; r<rows; r++){
 c=0; 
for (int j=0;j<cols;j++)
{
  if(value[r][j]== 1)
  {
    c=c+1;
  }
}
if(c==8){
    for(int i=r;i>0;i--){
    for(int j=0; j<cols; j++){
      value[i][j]=value[i-1][j];
    }
  }
  for(int j=0; j<cols; j++){
    value[0][j]=0;
  }
}
}
}
void rotate()
{
  int oldco[4][2];
  int newco[4][2];
  for (int i=0;i<4;i++)
  {
    oldco[i][0]=0;
    oldco[i][1]=0;
    newco[i][0]=0;
    newco[i][1]=0;
  }
  //convert coordinates
  int k=0;
  for (int i=0;i<rows;i++)
  {
    for (int j=0;j<cols;j++)
    {
      if (value[i][j]==2) {
      oldco[k][0]=i;
      oldco[k][1]=j;
      k++; }
    }
  }
  double pivotx=((double)oldco[0][0]+oldco[1][0]+oldco[2][0]+oldco[3][0])/4;
  double pivoty=((double)oldco[0][1]+oldco[1][1]+oldco[2][1]+oldco[3][1])/4;
  output();
  int px=(int)pivotx;
  int py=(int)pivoty;
 // Serial.println(px);
  //Serial.println(py);
  if (pivotx-px>=0.5) px++; //CHANGED
  if (pivoty-py>=0.5) py++; //CHANGED
  int oldvector[4][2];
  int newvector[4][2];
  for (int i=0;i<4;i++)
  {
    oldvector[i][0]=oldco[i][0]-px;
    oldvector[i][1]=oldco[i][1]-py;
  }
  for (int i=0;i<4;i++)
  {
    newvector[i][0]=oldvector[i][1];
    newvector[i][1]=-oldvector[i][0];
  }
  for (int i=0;i<4;i++)
  {
    newco[i][0]=newvector[i][0]+px;
    newco[i][1]=newvector[i][1]+py; //CHANGED
  }
  
  //done converting
  boolean check=true;
  
  for (int i=0;i<4;i++)
  {
    
    if (newco[i][0]<0 || newco[i][0]>=rows)
    check=false;
    if (newco[i][1]<0 || newco[i][1]>=cols)
    check=false;
    if (check)
    {
    if (value[newco[i][0]][newco[i][1]]==1)
    check=false;
    }
  }
  if (check)
  {
    
    for (int i=0;i<4;i++)
    {
      
        value[oldco[i][0]][oldco[i][1]]=0;
   //CHANGED  
   }
    for (int i=0;i<4;i++)
    {
        value[newco[i][0]][newco[i][1]]=2;
    }
  }
  
}
void on(int i,int j)
{
  value[i][j]=2;
}
void create()
{
  int n=0; boolean check=false;;
  //randomly select a number from 1 to 7
  n=random(7);
  //n=n%7;
  n++;
  //Serial.println(n);
  //delay(1000);
  //create a piece
  while(!check) //check==false => a piece has not been created yet
  {
    switch(n)
    {
      case 1: check = square(); Serial.println("square"); break;
      case 2: check = T(); Serial.println("T"); break;
      case 3: check = Z_left(); Serial.println("Z left"); break;
      case 4: check = Z_right();Serial.println("Z right"); break;
      case 5: check = line(); Serial.println("line"); break;
      case 6: check = L_right();Serial.println("l right");  break;
      case 7: check = L_left(); Serial.println("l left"); break;
    }
  }
}      
        
boolean square()
{
  //randomly select column from 0 to 6
  int j=random(7);
  //j = j%7;
  //Serial.println(j);
  if(value[0][j]==0&&value[0][j+1]==0&&value[1][j]==0&&value[1][j+1]==0)
  {
    //switching on requisite LEDs
    on(0,j);on(0,j+1);on(1,j);on(1,j+1);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean T()
{
  //randomly select column from 0 to 6
  int j=random(7);
 
  if(value[0][j]==0&&value[1][j]==0&&value[1][j+1]==0&&value[2][j]==0) //checking if each reqd block is empty
  {
    //switching on requisite LEDs
    on(0,j);on(1,j);on(1,j+1);on(2,j);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean Z_right()
{
  //randomly select column from 0 to 6
  int j=random(7);
  
  if(value[0][j+1]==0&&value[1][j]==0&&value[1][j+1]==0&&value[2][j]==0) //checking if each reqd block is empty
  {
    //switching on requisite LEDs
    on(0,j+1);on(1,j);on(1,j+1);on(2,j);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean Z_left()
{
  //randomly select column from 0 to 6
  int j=random(7);
  
  if(value[0][j]==0&&value[1][j]==0&&value[1][j+1]==0&&value[2][j+1]==0) //checking if each reqd block is empty
  {
    //switching on requisite LEDs
    on(0,j);on(1,j);on(1,j+1);on(2,j+1);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean line()
{
  //randomly select column from 0 to 7
  int j=random(8);
  
  if(value[0][j]==0&&value[1][j]==0&&value[2][j]==0&&value[3][j]==0) //checking if each reqd block is empty
  {
    //switching on requisite LEDs
    on(0,j);on(1,j);on(2,j);on(3,j);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean L_left()
{
  //randomly select column from 0 to 6
  int j=random(7);
  
  if(value[0][j+1]==0&&value[1][j+1]==0&&value[2][j+1]==0&&value[2][j]==0) //checking if each reqd block is empty
  {
    on(0,j+1);on(1,j+1);on(2,j+1);on(2,j);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
  
}
boolean L_right()
{
  int j=random(7);
  
  if(value[0][j]==0&&value[1][j]==0&&value[2][j]==0&&value[2][j+1]==0) //checking if each reqd block is empty
  {
    on(0,j);on(1,j);on(2,j);on(2,j+1);
    return true; //piece created
  }
  else
  {
    return false; //piece could not be created
  }
}

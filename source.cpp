#include <LiquidCrystal.h>
int contrast = 75;
LiquidCrystal lcd(12 ,11 ,5 ,4 ,3 ,2 );
const int buttonPin = 7;



bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool gameStarted = false;


int playerY = 1; 
const char player = '>';

int enemyX = 15;
int enemyY = 1;
const char enemy = '<';

int score = 0;


void playerMove()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH)
  {
    delay(50);
    playerY = (playerY == 0)? 1:0; 
    drawGame(); 
    }
    lastButtonState = buttonState; 
}





void enemyMove()
{
  enemyX--;
  if (enemyX < 0)
  {
    enemyX = 15;
    enemyY = random(0,2);
  }
  drawGame();  
}



void drawGame()
{
  lcd.clear();
  lcd.setCursor(0,playerY);
  lcd.print(player);
  lcd.setCursor(enemyX, enemyY);
  lcd.print(enemy);   
}




void menu()
{
  pinMode(buttonPin, INPUT_PULLUP);
  analogWrite(6, contrast);
  lcd.begin(16,2);
  lcd.setCursor(3,0);
  lcd.print("Horizontal");
  lcd.setCursor(3,1);
  lcd.print("Invaders!");
}

void startGame()
{
  gameStarted = true;
  drawGame();
}


void theGame()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH)
  {
    delay(50);
    if (digitalRead(buttonPin) == LOW)
    {
      gameStarted = true;
      startGame();    
    }
  }  
  lastButtonState = buttonState;  
}


void restart()
{
  enemyX = 15;
  enemyY = random(0,2);
  playerY = 1;
  score = 0;
  lcd.clear();
  drawGame();
}


void gameOver()
{
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Game over!");
  lcd.setCursor(3,1);
  lcd.print("Score: ");
  lcd.print(score);
  gameStarted = false; 
  enemyX = 15;

  while (digitalRead(buttonPin) == HIGH);
  delay(300);
  restart();
}



void scores()
{
  if(enemyX == 0 && enemyY != playerY)
  {
    score++;
  }  
}

void menuSetUp()
{
  randomSeed(analogRead(A0));
  menu();
  
}

void coreGame()
{
  if(!gameStarted)
  {
    theGame();
  }
  else 
  {
    playerMove();
    enemyMove();
    scores();
    delay(50);
    if(enemyX == 0 && playerY == enemyY)
    {
      gameOver();
    }
  }  
}

 
void setup() 
{
  menuSetUp();
}

void loop() 
{
  coreGame();
}

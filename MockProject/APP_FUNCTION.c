
#include "APP_FUNCTION.h"

/*===================================================================
											DEFINES & MACROS
===================================================================*/
#define TickMicroSecond (1u)
#define Softtimer_START (0u)
#define Softtimer_Alarm (1u)
#define ButtonValue (0u)
#define LengthData (100u)
/*=================================================================*/

/*===================================================================
											TYPEDEFS & ENUM
===================================================================*/
typedef struct DayTime_typedef
{
  unsigned char Hour;
  unsigned char Minute;
  unsigned char Second;
  unsigned char Day;
  unsigned char Month;
  unsigned char Year;
}DayTime_typedef;

typedef enum TimeMode_enum
{
  ZERO,
  AM,
  PM,
  HG,
  START
}TimeMode_enum;

typedef enum TRUE_FALSE
{
  FALSE,
  TRUE
}TrueFalse_enum;

typedef enum MenuSelect
{
  No_Menu_Select,
  Menu_ConfigTime,
  Menu_TimerAlarm,
  SelectPos
}Menu_enum;
/*=================================================================*/

/*===================================================================
											LOCAL VARIABLE
===================================================================*/
static DayTime_typedef Watch;
static DayTime_typedef SetTimer;

static unsigned int GetButton1;
static unsigned int GetButton2;

static volatile unsigned char Time_Mode;
static volatile unsigned char FlagStart;
static volatile unsigned char FlagHG;  
static volatile unsigned char FlagLedAlarm;

static unsigned char Data_Read[LengthData];
static volatile unsigned int Length_Data_Read;

static unsigned char SelectMenu;
static unsigned char SelectPosition;

static unsigned char LED_ERR[10]={ '[','E','R','R','O','R','L','E','D',']' };

/*=================================================================*/

/*===================================================================
											LOCAL FUNCTIONS
===================================================================*/

/* Init Button & Led */
static void LED_BUTTON_INIT(void)
{
  Gpio_Init();
}

/* App Init */
static void APP_Init(void)
{
  LED_BUTTON_INIT();

  Watch.Hour=0;
  Watch.Minute=0;
  Watch.Second=0;

  BufferClear(Data_Read,sizeof(Data_Read));

  Time_Mode = ZERO;
  Length_Data_Read=0;
  Time_Mode=0;
  FlagStart=0;
  FlagHG=0;    
  SelectMenu=0;
  SelectPosition=0;
  GetButton1=0;
  GetButton2=0;
  FlagLedAlarm=0;
}

/* LED bao nhan nut config */
static void LED_BLINK_CONFIG(void)
{
  Gpio_SetPinValue(PortD,LEDRED,LOW);
  LPIT_Delay_ms(200);
  Gpio_SetPinValue(PortD,LEDRED,HIGH);
  LPIT_Delay_ms(200);
  Gpio_SetPinValue(PortD,LEDRED,LOW);
  LPIT_Delay_ms(200);
  Gpio_SetPinValue(PortD,LEDRED,HIGH);
  LPIT_Delay_ms(200); 
  Gpio_SetPinValue(PortD,LEDRED,LOW);
  LPIT_Delay_ms(1000);
  Gpio_SetPinValue(PortD,LEDRED,HIGH);  
}

/* Hien thi dong ho len LCD */
static void Watch_Display(void)
{
  if(Watch.Second >= 59) 
  {
    Watch.Second=0;
    if(Watch.Minute >= 59) 
    {
			Watch.Minute=0;
      if(Time_Mode == AM) /* AM */
      {
        if( Watch.Hour>=12 ) Watch.Hour=1;
        else Watch.Hour++;
      }
      else /* PM */ 
      {
        if( Watch.Hour>=23 ) Watch.Hour=0;
        else Watch.Hour++;
      }

    }
    else Watch.Minute++;
    
  }
  else Watch.Second++;
  
}

/* Noi 2 so thanh 1 so */
static void Link_Number(unsigned char *Des, unsigned char *a, unsigned char *b)
{
	*Des = ( ((*a) * 10) + (*b) );
}

/*Kiem tra gio, phut, giay 
  AM: gio>=1 & gio<=12
  PM: gio>=0 & gio<=23
      phut>=0 & phut<=59
      giay>=0 & giay<=59 */
static unsigned char CheckRuleTime(DayTime_typedef *Time)
{
  unsigned char Result=FALSE;

  if(Time_Mode == AM) /* 1->12->1 */
  {
    if( (Time->Hour>=1) && (Time->Hour<=12) ) /* AM thi khong co 0h */
    {
      if( (Time->Minute<=59) )
      {
        if( (Time->Second<=59) ) Result=TRUE;
      }
    }
  }
  else /* PM: 1->23->0->1 */
  {
    if( (Time->Hour<=23) )
    {
      if( (Time->Minute<=59) )
      {
        if( (Time->Second<=59) ) Result=TRUE;
      }
    }
  }

  return Result;
}

/* Kiem tra ki tu nhan tu UART co phai la cac so tu 0-9 khong */
static unsigned char CheckRuleNumber(unsigned char *Data)
{
  unsigned char Count=0;
  unsigned char Result=FALSE;

  for(Count=3; Count<=8; Count++)
  {
    if( (Data[Count]>=48) && (Data[Count]<=57) ) Result=TRUE;
    else break;
  }

  return Result;
}

/* Giai ma Data UART */
static void Decode_Data(void)
{
  DayTime_typedef NewTime;
  unsigned char count=0;
  unsigned char TimeData[10];

  for(count=3; count<=8; count++)
  {
    TimeData[count] = Data_Read[count]-'0';
  }
  Link_Number(&NewTime.Hour, &TimeData[3], &TimeData[4]);
  Link_Number(&NewTime.Minute, &TimeData[5], &TimeData[6]);
  Link_Number(&NewTime.Second, &TimeData[7], &TimeData[8]);

  if( (Data_Read[1]=='S') && (Data_Read[2]=='T') ) /* START */
  {
    FlagStart=START; 
  }
  else 
  {
    if( CheckRuleNumber(Data_Read)==TRUE ) /* Kiem tra dung la cac ki tu so */
    {
      if ( (Data_Read[1]=='H') && (Data_Read[2]=='G') )  /* Hen gio */
      {
        if( (Time_Mode==AM)||(Time_Mode==PM) )
        {
          if( CheckRuleTime(&NewTime)==TRUE )  /* Kiem tra dung dieu kien Time */
          {
            FlagHG=HG;
            SetTimer = NewTime;
          }
        }
      }
      else if ( (Data_Read[1]=='A') && (Data_Read[2]=='M') ) /* AM */
      {    
        Time_Mode=AM;
        if( CheckRuleTime(&NewTime)==TRUE ) Watch = NewTime; /* Kiem tra dung dieu kien Time */
      }
      else if ( (Data_Read[1]=='P') && (Data_Read[2]=='M') ) /* PM */
      {
        Time_Mode=PM;
        if( CheckRuleTime(&NewTime)==TRUE ) Watch = NewTime; /* Kiem tra dung dieu kien Time */
      }
      else {}

    }/* CheckRuleNumber */

  } /* else START */

}

/* LED bao hen gio */
static void LED_Alarm(void)
{
  static unsigned char Step=0;
  if(Step==0)
  {
    Gpio_SetPinValue(PortD,LEDBLUE,LOW);
    Gpio_SetPinValue(PortD,LEDGREEN,HIGH);
    Gpio_SetPinValue(PortD,LEDRED,HIGH);
    Step++;
  }
  else if(Step==1)
  {
    Gpio_SetPinValue(PortD,LEDBLUE,HIGH);
    Gpio_SetPinValue(PortD,LEDGREEN,LOW);
    Gpio_SetPinValue(PortD,LEDRED,HIGH);
    Step++;
  }
  else 
  {
    Gpio_SetPinValue(PortD,LEDBLUE,HIGH);
    Gpio_SetPinValue(PortD,LEDGREEN,HIGH);
    Gpio_SetPinValue(PortD,LEDRED,LOW);
    Step=0;
  }
}

/* Dung LED hen gio */
static void STOP_LED_Alarm(void)
{
  Gpio_SetPinValue(PortD,LEDBLUE,HIGH);
  Gpio_SetPinValue(PortD,LEDGREEN,HIGH);
  Gpio_SetPinValue(PortD,LEDRED,HIGH);
  Softtimer_StopTimer(Softtimer_Alarm);
}

/* Kiem tra co Start -> Bat dau dem */
static void CheckAction_START(void)
{
  if( (Time_Mode==AM) || (Time_Mode==PM) )
  {
    if(FlagStart==START)
    {
      Softtimer_StartTimer(Softtimer_START,1000,CONTINUE,&Watch_Display);
    }
  }
}

/* Kiem tra hen gio  */
static void CheckTIMER_Alarm(void)
{
  static unsigned char Step=0;

  if( FlagHG==HG )
  {
    if( (Watch.Hour == SetTimer.Hour) &&  
        (Watch.Minute == SetTimer.Minute) &&
        (Watch.Second == SetTimer.Second))
    {
      if(FlagLedAlarm==0) Step=1;
    }
  }

  if(Step==1)
  {
    Softtimer_StartTimer(Softtimer_Alarm,1000,CONTINUE,&LED_Alarm);
    FlagLedAlarm=1;
    LED_Alarm();
    Step=2;
  }
  else{}
}

/* Doc va kiem tra Data nhan tu UART */
static void Check_Data_UART(void)
{
  static unsigned char CheckFrame=0;
  unsigned char Count=0;

  if( (Length_Data_Read!=0) )
  {
    if( (Data_Read[0]=='[') && ((Data_Read[6]==']')||(Data_Read[9]==']')) )
    {
      for(Count=0; Count<Length_Data_Read; Count++)
      {
        if( ((Data_Read[Count]>=48)&&(Data_Read[Count]<=57)) ||\
            ((Data_Read[Count]>=65)&&(Data_Read[Count]<=90)) ||\
            (Data_Read[Count]=='[') || (Data_Read[Count]==']') )
        {
          CheckFrame=1; /* Neu Frame dung */
        }
        else 
        {
          Length_Data_Read=0;
          CheckFrame=0;
          break;
        }
      }

      if(CheckFrame == 1) /* Neu Frame dung */
      {
        Decode_Data();
        CheckAction_START();
        CheckFrame=0;
        Length_Data_Read=0;
      }

    }
    else Length_Data_Read=0;      
  }

}

/* Chop tat so tren LED */
static void LED_Blink(unsigned char Number)
{
  static unsigned int TickBlink=0;
  static unsigned char StepBlink=0;
  if(StepBlink==0)
  {
    LCD_TurnOff(Number);
    TickBlink = Tick_ms;
    StepBlink=1;
  }
  else if(StepBlink==1)
  {
    if( (unsigned int)(Tick_ms-TickBlink)>=(500*TickMicroSecond) )
    {
      if(SelectMenu==Menu_ConfigTime) LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);
      else LCD_TimeDisplay(SetTimer.Hour, SetTimer.Minute, SetTimer.Second);
      TickBlink = Tick_ms;
      StepBlink=2;
    }
  }
  else
  {
    if( (unsigned int)(Tick_ms-TickBlink)>=(500*TickMicroSecond) )
    {
      TickBlink = Tick_ms;
      StepBlink=0;
    }
  }
  
}

/* Nhan giu de vao Menu */
static void SelectMainMenu(void)
{
  static unsigned int Tickbutton1=0;
  static unsigned int Tickbutton2=0;

  if(FlagStart==START)
  {
    if(GetButton1!=ButtonValue) /* Press hold Button 1 -> Set Watch */
    {
      if( (unsigned int)(Tick_ms-Tickbutton1)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
      {
        LED_BLINK_CONFIG();

        if(SelectMenu==No_Menu_Select) SelectMenu=Menu_ConfigTime;
      }
      else 
      {
        if(FlagLedAlarm==1)  /* Neu Led hen gio dang ON -> OFF */
        {
          STOP_LED_Alarm();
          FlagLedAlarm=0;
        }
      } 
    }
    else Tickbutton1=Tick_ms;

    if(GetButton2!=ButtonValue) /* Press hold Button 2 -> Set Alarm */
    {
      if( (unsigned int)(Tick_ms-Tickbutton2)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
      {
        LED_BLINK_CONFIG();

        if(SelectMenu==No_Menu_Select) 
        {
          SelectMenu=Menu_TimerAlarm;
          LCD_TimeDisplay(SetTimer.Hour, SetTimer.Minute, SetTimer.Second);
        }
      }
      else 
      {
        if(FlagLedAlarm==1) /* Neu Led hen gio dang ON -> OFF */
        {
          STOP_LED_Alarm();
          FlagLedAlarm=0;
        }
      } 
    }
    else Tickbutton2=Tick_ms;

  }
}

/*  Chon vi tri so de thay doi 
    Nhan giu 2 nut de luu */
static unsigned char SelectBabyMenu(DayTime_typedef *Time, unsigned char *NumberPos)
{
  unsigned char Result=FALSE;
  static unsigned int Tickbutton=0;
  static unsigned int LastButton1=0;
  static unsigned int LastButton2=0;

  if( (GetButton1!=ButtonValue)&&(GetButton2!=ButtonValue) )
  {
    if( (unsigned int)(Tick_ms-Tickbutton)>=(3000*TickMicroSecond) ) /* Nhan giu 3s */
    {
      LED_BLINK_CONFIG();
      Result=TRUE;
      SelectPosition=SelectPos;
    }
  }
  else 
  {
    Tickbutton=Tick_ms;

    if(GetButton1!=LastButton1) /* Press button 1 */
    {
      if(GetButton1!=ButtonValue)
      {
        if(*NumberPos>=7) *NumberPos=1;
        else *NumberPos+=3;
      }
      LastButton1=GetButton1;
    }

    if(GetButton2!=LastButton2) /* Press button 2 */
    {
      if(GetButton2!=ButtonValue)
      {
        if(*NumberPos==1) 
        {
          if(Time->Second>=59) Time->Second=0;
          else Time->Second++;
        }
        else if(*NumberPos==4)
        {
          if(Time->Minute>=59) Time->Minute=0;
          else Time->Minute++;
        }
        else
        {
          if(Time_Mode==AM)
          {
            if(Time->Hour>=12) Time->Hour=1;
            else Time->Hour++;
          }
          else 
          {
            if(Time->Hour>=23) Time->Hour=0;
            else Time->Hour++;            
          }

        }
      }
      LastButton2=GetButton2;
    }
  }

  return Result;
}

/* Menu chinh */
static void MAIN_MENU(void)
{
  static unsigned char PosNumber=1;
  static unsigned char StepChoice=0;

  if(SelectMenu==No_Menu_Select) SelectMainMenu();

  if(SelectMenu==Menu_ConfigTime) /* Menu time config */
  {
    if(StepChoice==0) /* STOP Softtimer Watch */
    {
      Softtimer_StopTimer(Softtimer_START);
      StepChoice=1;
    }
    else if(StepChoice==1) /* Choice position number */
    {
      LED_Blink(PosNumber);
      if( SelectBabyMenu(&Watch,&PosNumber)==TRUE )
      {
        if(SelectPosition==SelectPos) StepChoice=2;
      }
      
    }
    else 
    {
      Softtimer_StartTimer(Softtimer_START,1000,CONTINUE,&Watch_Display);
      SelectMenu=No_Menu_Select;
      PosNumber=1;
      StepChoice=0;
    }
  }
  else if(SelectMenu==Menu_TimerAlarm) /* Menu hen gio */
  {
    if(StepChoice==0) /* Choice position number */
    {
      LED_Blink(PosNumber);
      if( SelectBabyMenu(&SetTimer,&PosNumber)==TRUE )
      {
        if(SelectPosition==SelectPos) StepChoice=1;
      }
      
    }
    else 
    {
      SelectMenu=No_Menu_Select;
      PosNumber=1;
      StepChoice=0;
    }
  }
  else  /* LED Display */
  {
    LCD_TimeDisplay(Watch.Hour, Watch.Minute, Watch.Second);
  }
}

static void ACTION(void)
{
  Check_Data_UART();
  CheckTIMER_Alarm();
  
  MAIN_MENU();
}

/*=================================================================*/

/*===================================================================
											GLOBAL FUNCTIONS
===================================================================*/
void MAIN_APP(void)
{
  SOSC_Init_8Mhz();
	SPLL_Init(Div_2,Div_2);
	Run_Mode_Clock(SPLLDIV2_CLK, RunDiv_2, RunDiv_2, RunDiv_3);
	
  Softtimer_Init();
  Uart_Init();
  SPI1_Init();
  LPIT_Init(60000);
  APP_Init();

  while( MAX7219_Init()==LED_Timeout ) /* Kiem tra ket noi voi LED */
  {
    Uart_Transmit(LED_ERR,10);
    Uart_TxMainFunction();
    LPIT_Delay_ms(2);
  }

  while(1)
  {
    Gpio_GetPinValue(PortC,BUTTON_1,&GetButton1);
    Gpio_GetPinValue(PortC,BUTTON_2,&GetButton2);

    if( Uart_GetReceiveState()==NOT_EMP )
    {
      Length_Data_Read = Uart_GetReceiveData(Data_Read);
    }
    else 
    {
      ACTION();
    }
    
    Softtimer_MainFunction();
    Uart_TxMainFunction();

    LPIT_Delay_ms(2);
  }

}
/*=================================================================*/


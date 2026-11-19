#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std ;


enum enLevel {easy=1,med=2,hard=3,mix=4};
enum enOperationType {add=1,sub=2,mul=3,Div=4,max=5};
enum enPassFaild {pass=1,faild=2};
int RandNumber(int From, int To)
{
	int randNum= rand()%(To - From + 1 )+ From;
	return randNum;
}

struct stQution 
{
    int FristNumber ;
    int SecondNumber;
    int QurrentRoundNumber;
    int NumberOfRounds;
    enLevel Levels ;
    enOperationType TypeOfOperation;
    int Answer;
    bool StateOfPlayerAnswer;
    int RightAnswer;

};
struct stGameInfo 
{
    stQution Quizelist ;
    short NumberOfTheRound;
    enLevel Level;
    enOperationType OpType;
    int NumberOfWrogeAnser;
    int NumberOfRightAnser;
    enPassFaild States;
};



int ReadNubmer ()
{
    int Num;
    cin>>Num;
    return Num;
}

void ColorScreen (stQution RoundInfo)
{
   
	switch (RoundInfo.StateOfPlayerAnswer)
	{
	case true:
	system("color 2F");
	return ;

	case false:
	system("color 4F");
	cout<<"\a";
	return ;


	}

}

string PrintLevel (enLevel Level)
{
    string NameLevel[4] {"Easy","Medium","Hard","d"};
    return NameLevel[Level-1];

}

string PrintOperType (enOperationType Type)
{
    string NameOpType[4] {"Add","Sub","Div","Max"};
    return NameOpType[Type-1];

}

string PrintOperTypeAsQuarcter (enOperationType Type)
{
    string NamePassFail [4] {"+","-","/","!"};
    return NamePassFail [Type-1];
}

void ResetScreen ()
{
		system("color 0F");
		system("cls");
}

int HowManyRounds()
{
	int Num;
	do{
		cout<<"how Many Round? enter form 1-10 "<<endl;
		cin>>Num;
		
	}while(Num<0);
	return Num; 
}

string Tap (int Num)
{
	string t="";

	for (short i =0;i<Num;i++)
	{
		t+="\t";
	}

	return t;
}

string ShowPassOrFaild (enPassFaild stats)
{
    if (stats==enPassFaild::pass)
    {
        return "Pass :-)\n";
    }
    else if (stats==enPassFaild::faild)
    {
        return "Faild :-(\n";
    }
    else 
    {
        return "somthing Wrong in ShowPassFaild Function \n";
    }
}

void ShowFinalResult (stGameInfo Game)

{
    cout<<"_______________________________________________________________\n";
    cout<<"Final Resutl is "<<ShowPassOrFaild(Game.States);
    cout<<"_______________________________________________________________\n";
}

enLevel ReadTheLevel ()
{
    int ChocieLevel=0 ;
    cout<<"please Enter The Level [1]:Easy, [2]:Miduim, [3]:Hard ,[4]Mix ?\n";
    cin>>ChocieLevel;

    return (enLevel)ChocieLevel;
}

enOperationType ReadOpType ()
{
    int ChocieLevel=0 ;
    cout<<"please Enter The Level [1]:Add, [2]:Sub, [3]:muti ,[4]Max ?\n";
    cin>>ChocieLevel;

    return (enOperationType)ChocieLevel;
}

enLevel GetRandomLevel ()
{
    return (enLevel)RandNumber(1,4);
}

int GetRondomNumber (enLevel Level)
{
    if (Level==enLevel::mix)
    {
        Level=GetRandomLevel();
    }
    if(Level==enLevel::easy)
    {
        return RandNumber(1,10);
    }

    else if(Level==enLevel::med)
    {
        return RandNumber(11,30);
    }

    else if(Level==enLevel::hard)
    {
        return RandNumber(31,50);
    }    
}

enOperationType GetRandomOpType ()
{
    return (enOperationType)RandNumber(1,4);
} 

enOperationType GetOpTypeOfRound (enOperationType OpType)
{
    if (OpType == enOperationType::max)
    {
        OpType = GetRandomOpType();
    }
    return OpType;

}


void PrintQuation (stQution Round)
{
    cout<<"\n\n Question ["<<Round.QurrentRoundNumber<<"/"<<Round.NumberOfRounds<<"]\n\n";
        cout<<Round.FristNumber<<endl;
        cout<<Round.SecondNumber<<"  "<<PrintOperTypeAsQuarcter(Round.TypeOfOperation) <<endl;
        cout<<"________________\n";
}
    
int RightAnswer (stQution Round)
{
    switch (Round.TypeOfOperation)
    {
    case enOperationType::add:
    {
        return Round.FristNumber+Round.SecondNumber;
    }
    case enOperationType::sub:
    {
         return Round.FristNumber-Round.SecondNumber;
    }    
    case enOperationType::Div:
    {
         return Round.FristNumber/Round.SecondNumber;
    }    
    case enOperationType::mul:
    {
         return Round.FristNumber*Round.SecondNumber;
    }    

    default:
        cout<<"sth in RightAnswer Function wents wronge  ";
    }
}

void CheckResult (stQution & Round)
{
    if(Round.RightAnswer==Round.Answer)
    {
       cout<<"Rigth Answer  :-)\n";
       Round.StateOfPlayerAnswer = true;
    }
    else 
    {
        cout<<"Wrong Answer  :-(\n";
        Round.StateOfPlayerAnswer = false;
        cout<<"The Right Answer is :"<<Round.RightAnswer<<endl;
    }
}

enPassFaild CheckFainalResult(stGameInfo Game)
{
    if(Game.NumberOfRightAnser>=Game.NumberOfWrogeAnser)
    {
       return enPassFaild::pass;
    }
    else if (Game.NumberOfRightAnser<Game.NumberOfWrogeAnser)
    {
        return enPassFaild::faild;
    }
}

stGameInfo PlayStart (int NumberOFRound)
{
    stGameInfo Game;
    stQution Round;
    Game.NumberOfRightAnser=0;
    Game.NumberOfWrogeAnser=0;
    Game.Level=ReadTheLevel();
    Game.OpType=ReadOpType();
    Game.NumberOfTheRound=NumberOFRound;

    for (int i=1;i<= NumberOFRound;i++)
    {
        Round.NumberOfRounds=NumberOFRound;
        Round.QurrentRoundNumber=i;
        Round.FristNumber     = GetRondomNumber (Game.Level);
        Round.SecondNumber    = GetRondomNumber (Game.Level);
        Round.TypeOfOperation = GetOpTypeOfRound(Game.OpType);
        Round.RightAnswer     = RightAnswer(Round);
        PrintQuation(Round);
        Round.Answer = ReadNubmer();
        CheckResult(Round);

        ColorScreen(Round);

        if(Round.StateOfPlayerAnswer==true)
        {
            Game.NumberOfRightAnser++;
        }

        else if (Round.StateOfPlayerAnswer==false)
        {
            Game.NumberOfWrogeAnser++;
        }

    }
    Game.States=CheckFainalResult(Game);

    return Game;
}

void PrintGameResult (stGameInfo Game)
{
    cout<<"Number of Question: "<<Game.NumberOfTheRound<<endl;
    cout<<"Question Level    : "<<Game.Level<<endl;
    cout<<"OpType            : "<<PrintOperType(Game.OpType)<<endl;
    cout<<"Number of Right Answer: "<<Game.NumberOfRightAnser<<endl;
    cout<<"Number of Wrong Answer: "<<Game.NumberOfWrogeAnser<<endl;
    cout<<"_______________________________________________________________\n";

}

void GameStared ()
{
    char PlayAgain='y';
    do
    {
        ResetScreen();

        stGameInfo GameInfo = PlayStart(HowManyRounds());


        ShowFinalResult(GameInfo);
        PrintGameResult(GameInfo);

        cout<<"Do you Want`s to Play Again ?(Y/N)\n";
        cin>>PlayAgain;
    } while (PlayAgain=='y'||PlayAgain=='Y');
    

}

int main ()
{
	
 	srand((unsigned)time(NULL));    

    GameStared();

    return 0;

}
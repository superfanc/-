#include "userdata.h"

UserData::UserData()
{

}



void User1::GetPsw1(char *Password)
{
    Password = this->Password;
}

void User1::GetBalance(int Balance)
{
    Balance = this->Balance;
}

void User1::SetBalance(int Balance)
{
    this->Balance = Balance;
}


void User2::GetPsw2(char *Password)
{
    Password = this->Password;
}

void User2::GetBalance(int Balance)
{
    Balance = this->Balance;
}

void User2::SetBalance(int Balance)
{
    this->Balance = Balance;
}

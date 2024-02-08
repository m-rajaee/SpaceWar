//Developed By Mohammad Amin Rajaee

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma warning (disable:4996)
#define PLAYER1_UP 'W'
#define PLAYER1_DOWN 'S'
#define PLAYER1_LEFT 'A'
#define PLAYER1_RIGHT 'D'
#define PLAYER1_SHOOT 'C'
#define PLAYER2_UP 'I'
#define PLAYER2_DOWN 'K'
#define PLAYER2_LEFT 'J'
#define PLAYER2_RIGHT 'L'
#define PLAYER2_SHOOT 'N'
#define PLAYER1_C4 'E'
#define PLAYER2_C4 'U'
#define gotoxy(x,y) wprintf(L"\033[%d;%dH", (y), (x))
//---------------------------------------------
// Variables
//---------------------------------------------
struct users {
	char username[20];
	char email[40];
	char password[20];
};
struct score {
	char winner[20];
	char loser[20];
};
struct users user1, user2, searchusers;
struct score score, searchscores;
char move1 = ' ', move2 = ' ', moveb1 = ' ', moveb2 = ' ';
int logged1 = 0, logged2 = 0, player = 1, lives1 = 5, lives2 = 5, gamefinished = 0, Menu_Music = 1;
int round = 1, b1 = 0, b2 = 0, score1 = 0, score2 = 0, wins1 = 0, wins2 = 0, c41 = 0, c42 = 0;
int heart = 1, double_bullet_p1 = 0, double_bullet_p2 = 0, double_bullet1 = 1, double_bullet2 = 1;
int  twotir1 = 0, twotir2 = 0, ghost1 = 0; ghost2 = 0, ghost_ = 1, bomb_ = 1, bomb1 = 0, bomb2 = 0;
int allwins1 = 0, allwins2 = 0, allloses1 = 0, allloses2 = 0, seconds1 = 0, seconds2 = 0, explode = 0;
char map[23][93] = { 0 };
char tempmap[23][93] = { 0 };
FILE* usersdata = NULL;
FILE* temp = NULL;
FILE* scores = NULL;
COORD player1_c4;
COORD player2_c4;
//---------------------------------------------
// functions
//--------------------------------------------
COORD moveDirection(COORD position, int dx, int dy) {
	position.X += dx;
	position.Y += dy;
	return position;
}
BOOL keyPressed(int key) {
	//This function returns a short integer that indicates whether a particular key is pressed or not.
	return GetAsyncKeyState(key);
	//returns a non-zero value if the key is currently pressed. If not, it will return 0.
}
void drawmap1();
void drawmap2();
void drawmap3();
void printmap();
void signup1(FILE* usersdata);
void signup2(FILE* usersdata);
void login1(FILE* usersdata);
void login2(FILE* usersdata);
void loginpage();
void Menu();
void play();
void end();

//---------------------------------------------
// main
//---------------------------------------------
int main() {
	_setmode(_fileno(stdout), _O_U8TEXT);
	//Loading Screen
	wprintf(L"\033[96m\n\n\n\n\n\n\n\t\t\t\t  Welco\u03FBe \u01AEo \u01AEhe \u0405pace War!\n\n\n\t\t\t\t\t  Loading...");
	wprintf(L"\n\n\t\t\t\t \033[96m");
	for (int i = 1; i <= 25; i++)
	{
		Sleep(35);
		wprintf(L"\u2588");
	}
	Sleep(300);
	wprintf(L"\033[0m");
	///////////////
	PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (1) {
		loginpage();
		Menu_Music = 1;
		Menu();
	}
}




//---------------------------------------------
// functions
//---------------------------------------------
void signup1(FILE* usersdata) {
	usersdata = fopen("users.bin", "rb+");
	system("cls || clear");
	int exist = 0;
	//Username
	wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter an Username : \033[92m");
	while (1) {
		wscanf(L"%S", user1.username);
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.username, user1.username) == 0) {
				exist = 1; break;
			}
		}if (exist == 0)
			break;
		else if (exist == 1) {
			system("cls || clear");
			wprintf(L"\a\n\n\n\n\n\n\n\n\n\t\t \033[31mThat Username Has Already Taken!\n\t      \033[36mEnter an Username : \033[92m");
			exist = 0;
			continue;
		}
	}
	//Email
	wprintf(L"\n\t      \033[36mEnter Your Email : \033[92m");
	exist = 0;
	while (1) {
		wscanf(L"%S", user1.email);
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.email, user1.email) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			if (strstr(user1.email, "@") != NULL && strstr(user1.email, ".com") != NULL)
				break;
			else {
				wprintf(L"\a\n\t\t \033[31mWrong Email!\n\t      \033[36mEnter Your Email : \033[92m");
				continue;
			}
		}
		else if (exist == 1) {
			wprintf(L"\a\n\t\t \033[31mThat Email Already Exists!\n\t      \033[36mEnter Your Email : \033[92m");
			exist = 0;
			continue;
		}
	}
	//Password
	wprintf(L"\n\t      \033[36mEnter Password : \033[92m");
	int n, i = 0;
	while (1) {
		i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; user1.password[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				user1.password[i++] = (char)n;
				wprintf(L"*");
			}
		}
		user1.password[i] = '\0';
		if (strlen(user1.password) < 8) {
			wprintf(L"\a\n\t\t \033[36m\033[31mYour Password Must have at Least 8 Characters!\n\t      \033[36mEnter a New Password : \033[92m");
			continue;
		}
		else
			break;
	}
	//Reenter The Password
	wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
	char reentered[20];
	while (1) {
		int n, i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				reentered[i++] = (char)n;
				wprintf(L"*");
			}
		}
		reentered[i] = '\0';
		if (strcmp(reentered, user1.password) != 0) {
			wprintf(L"\a\n\t\t \033[31mThe Passwords Doesen't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
			continue;
		}
		else {
			break;
		}
	}
	wprintf(L"\033[0m");
	fwrite(&user1, sizeof(struct users), 1, usersdata);
	fclose(usersdata);
}
void signup2(FILE* usersdata) {
	usersdata = fopen("users.bin", "rb+");
	system("cls || clear");
	int exist = 0;
	//Username
	wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter an Username : \033[92m");
	while (1) {
		wscanf(L"%S", user2.username);
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.username, user2.username) == 0) {
				exist = 1; break;
			}
		}if (exist == 0)
			break;
		else if (exist == 1) {
			system("cls || clear");
			wprintf(L"\a\n\n\n\n\n\n\n\n\n\t\t \033[31mThat Username Has Already Taken!\n\t      \033[36mEnter an Username : \033[92m");
			exist = 0;
			continue;
		}
	}
	//Email
	wprintf(L"\n\t      \033[36mEnter Your Email : \033[92m");
	exist = 0;
	while (1) {
		wscanf(L"%S", user2.email);
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.email, user2.email) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			if (strstr(user2.email, "@") != NULL && strstr(user2.email, ".com") != NULL)
				break;
			else {
				wprintf(L"\a\n\t\t \033[31mWrong Email!\n\t      \033[36mEnter Your Email : \033[92m");
				continue;
			}
		}
		else if (exist == 1) {
			wprintf(L"\a\n\t\t \033[31mThat Email Already Exists!\n\t      \033[36mEnter Your Email : \033[92m");
			exist = 0;
			continue;
		}
	}
	//Password
	wprintf(L"\n\t      \033[36mEnter Password : \033[92m");
	int n, i = 0;
	while (1) {
		i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; user2.password[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				user2.password[i++] = (char)n;
				wprintf(L"*");
			}
		}
		user2.password[i] = '\0';
		if (strlen(user2.password) < 8) {
			wprintf(L"\a\n\t\t \033[36m\033[31mYour Password Must have at Least 8 Characters!\n\t      \033[36mEnter a New Password : \033[92m");
			continue;
		}
		else
			break;
	}
	//Reenter The Password
	wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
	char reentered[20];
	while (1) {
		int n, i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				reentered[i++] = (char)n;
				wprintf(L"*");
			}
		}
		reentered[i] = '\0';
		if (strcmp(reentered, user2.password) != 0) {
			wprintf(L"\a\n\t\t \033[31mThe Passwords Doesen't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
			continue;
		}
		else {
			break;
		}
	}
	wprintf(L"\033[0m");
	fwrite(&user2, sizeof(struct users), 1, usersdata);
	fclose(usersdata);
}
void login1(FILE* usersdata) {
	usersdata = fopen("users.bin", "rb");
	system("cls || clear");
	int exist = 0;
	//Username
	wprintf(L"\033[36m\n\n\n\n\n\n\n\n\n\t      Enter Your Username : \033[92m");
	while (1) {
		wscanf(L"%S", user1.username);
		wprintf(L"\033[36m");
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.username, user1.username) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			system("cls || clear");
			wprintf(L"\a\n\n\n\n\n\n\n\n\n\t      \033[31mUsername Not found\n\t      \033[36mEnter Your Username : \033[92m");
			continue;
		}
		else if (exist == 1)
			break;
	}
	exist = 0;
	int n, i = 0;
	//Password
	while (1) {
		wprintf(L"\n\t      \033[36mEnter Your Password : \033[92m");
		i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; user1.password[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				user1.password[i++] = (char)n;
				wprintf(L"*");
			}
		}
		user1.password[i] = '\0';
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.password, user1.password) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			wprintf(L"\a\n\n\t      \033[31mWrong Password!\033[0m");
			rewind(usersdata);
			continue;
		}
		else if (exist == 1) {
			wprintf(L"\n\t\t\t\t    \033[92mYou've Logged in!\033[0m");
			Sleep(1000);
			logged1 = 1;
			break;
		}
	}
	strcpy(user1.email, searchusers.email);
	fclose(usersdata);
}
void login2(FILE* usersdata) {
	usersdata = fopen("users.bin", "rb");
	system("cls || clear");
	int exist = 0;
	//Username
	wprintf(L"\033[36m\n\n\n\n\n\n\n\n\n\t      Enter Your Username : \033[92m");
	while (1) {
		wscanf(L"%S", user2.username);
		wprintf(L"\033[36m");
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.username, user2.username) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			system("cls || clear");
			wprintf(L"\a\n\n\n\n\n\n\n\n\n\t      \033[31mUsername Not found\n\t      \033[36mEnter Your Username : \033[92m");
			continue;
		}
		else if (exist == 1)
			break;
	}
	exist = 0;
	int n, i = 0;
	//Password
	while (1) {
		wprintf(L"\n\t      \033[36mEnter Your Password : \033[92m");
		i = 0;
		while ((n = _getch()) != 13 && n != 32) {
			if (n == 8) {
				if (i == 0)
					continue;
				else {
					i--; user2.password[i] = '\0'; wprintf(L"\b\x1B[1P");
				}
			}
			else {
				user2.password[i++] = (char)n;
				wprintf(L"*");
			}
		}
		user2.password[i] = '\0';
		rewind(usersdata);
		while (!feof(usersdata)) {
			fread(&searchusers, sizeof(struct users), 1, usersdata);
			if (strcmp(searchusers.password, user2.password) == 0) {
				exist = 1; break;
			}
		}if (exist == 0) {
			wprintf(L"\a\n\n\t      \033[31mWrong Password!\033[0m");
			rewind(usersdata);
			continue;
		}
		else if (exist == 1) {
			wprintf(L"\n\t\t\t\t    \033[92mYou've Logged in!\033[0m");
			Sleep(1000);
			logged2 = 1;
			break;
		}
	}
	strcpy(user2.email, searchusers.email);
	fclose(usersdata);
}
void loginpage() {
	while (1) {
		system("cls || clear");
		if (player == 1 && logged1 == 1)
			wprintf(L"\n\n\n\t\t\t\t\t\033[36mPlayer 1\033[0m\n\t\t\t\t       \033[92m %S\n\n\t\t\t\t\033[0mPress \033[33m0\033[0m to change the player\n", user1.username);
		else if (player == 2 && logged2 == 1)
			wprintf(L"\n\n\n\t\t\t\t\t\033[36mPlayer 2\033[0m\n\t\t\t\t       \033[92m %S\n\n\t\t\t\t\033[0mPress \033[33m0\033[0m to change the player\n", user2.username);
		else
			wprintf(L"\n\n\n\t\t\t\t\t\033[36mPlayer %d\033[0m\n\t\t\t\t      \033[31mNot logged in\033[0m\n\n\t\t\t       Press \033[33m0\033[0m to change the player", player);
		wprintf(L"\n\n\t\t\t       Press \033[33mEnter\033[0m To Go To The Menu!\n\n\t\t\t\t     \033[36m1 . Sign in\n\n\t\t\t\t     2 . Sign Up\n\n\t\t\t\t     3 . Forgot Password\n\n\t\t\t\t     4 . Exit\033[0m");
		int login = getch();
		while (login != '1' && login != '2' && login != '3' && login != '4' && login != 13 && login != '0')
			login = getch();
		if (login == '1') {
			//Log in
			if (player == 1) {
				login1(usersdata);
			}
			else if (player == 2) {
				login2(usersdata);
			}
		}
		else if (login == '2') {
			//Signup
			if (player == 1)
				signup1(usersdata);
			else if (player == 2)
				signup2(usersdata);

		}
		else if (login == '3') {
			//Forgot password
			if (player == 1) {
				int exist = 0;
				usersdata = fopen("users.bin", "rb+");
				temp = fopen("temp.bin", "wb");
				system("cls || clear");
				//Username
				wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your Username : \033[92m");
				while (1) {
					wscanf(L"%S", user1.username);
					rewind(usersdata);
					while (!feof(usersdata)) {
						fread(&searchusers, sizeof(struct users), 1, usersdata);
						if (strcmp(searchusers.username, user1.username) == 0) {
							exist = 1; break;
						}
					}if (exist == 0) {
						system("cls || clear");
						wprintf(L"\a\n\n\n\n\n\n\n\n\n\t\t \033[31mUsername Not found");
						wprintf(L"\n\t      \033[36mEnter Your Username : \033[92m");
						continue;
					}
					else if (exist == 1)
						break;
				}
				//Email
				wprintf(L"\n\t      \033[36mEnter Your Email : \033[92m");
				exist = 0;
				while (1) {
					wscanf(L"%S", user1.email);
					if (strcmp(searchusers.email, user1.email) == 0) {
						exist = 1; break;
					}
					if (exist == 1) {
						exist = 0;
						break;
					}
					else if (exist == 0) {
						wprintf(L"\a\n\t      \033[31mWrong Email!\n\t      \033[36mEnter Your Email : \033[92m");
						continue;
					}
				}
				//New Password
				wprintf(L"\n\t      \033[36mEnter The New Password : \033[92m");
				int n, i = 0;
				while (1) {
					i = 0;
					while ((n = _getch()) != 13 && n != 32) {
						if (n == 8) {
							if (i == 0)
								continue;
							else {
								i--; user1.password[i] = '\0'; wprintf(L"\b\x1B[1P");
							}
						}
						else {
							user1.password[i++] = (char)n;
							wprintf(L"*");
						}
					}
					user1.password[i] = '\0';
					if (strlen(user1.password) < 8) {
						wprintf(L"\a\n\t      \033[31mYour Password must have at least 8 characters!\n\t\t\t\t     \033[36mEnter a New Password : \033[92m");
						continue;
					}
					else
						break;
				}
				wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
				char reentered[20];
				while (1) {
					i = 0;
					while ((n = _getch()) != 13 && n != 32) {
						if (n == 8) {
							if (i == 0)
								continue;
							else {
								i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
							}
						}
						else {
							reentered[i++] = (char)n;
							wprintf(L"*");
						}
					}
					reentered[i] = '\0';
					if (strcmp(reentered, user1.password) != 0) {
						wprintf(L"\a\n\t      \033[31mThe Passwords Doesen't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
						continue;
					}
					else {
						break;
					}
				}
				//Changing The Password
				rewind(usersdata);
				rewind(temp);
				while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
					if (strcmp(searchusers.username, user1.username) != 0) {
						fwrite(&searchusers, sizeof(struct users), 1, temp);
					}
				}
				fwrite(&user1, sizeof(struct users), 1, temp);
				fclose(usersdata); fclose(temp);
				remove("users.bin"); rename("temp.bin", "users.bin");
				continue;
			}
			else if (player == 2) {
				int exist = 0;
				usersdata = fopen("users.bin", "rb+");
				temp = fopen("temp.bin", "wb");
				system("cls || clear");
				//Username
				wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your Username : \033[92m");
				while (1) {
					wscanf(L"%S", user2.username);
					rewind(usersdata);
					while (!feof(usersdata)) {
						fread(&searchusers, sizeof(struct users), 1, usersdata);
						if (strcmp(searchusers.username, user2.username) == 0) {
							exist = 1; break;
						}
					}if (exist == 0) {
						system("cls || clear");
						wprintf(L"\a\n\n\n\n\n\n\n\n\n\t\t \033[31mUsername Not found");
						wprintf(L"\n\t      \033[36mEnter Your Username : \033[92m");
						exist = 0;
						continue;
					}
					else if (exist == 1)
						break;
				}
				//Email
				wprintf(L"\n\t      \033[36mEnter Your Email : \033[92m");
				exist = 0;
				while (1) {
					wscanf(L"%S", user2.email);
					if (strcmp(searchusers.email, user2.email) == 0) {
						exist = 1; break;
					}
					if (exist == 0) {
						wprintf(L"\a\n\t      \033[31mWrong Email!\n\t      \033[36mEnter Your Email : \033[92m");
						continue;
					}
					else if (exist == 1) {
						exist = 0;
						break;
					}
				}
				//New Password
				wprintf(L"\n\t      \033[36mEnter The New Password : \033[92m");
				int n, i = 0;
				while (1) {
					i = 0;
					while ((n = _getch()) != 13 && n != 32) {
						if (n == 8) {
							if (i == 0)
								continue;
							else {
								i--; user2.password[i] = '\0'; wprintf(L"\b\x1B[1P");
							}
						}
						else {
							user2.password[i++] = (char)n;
							wprintf(L"*");
						}
					}
					user2.password[i] = '\0';
					if (strlen(user2.password) < 8) {
						wprintf(L"\a\n\t      \033[31mYour Password must have at least 8 characters!\n\t\t\t\t     \033[36mEnter a New Password : \033[92m");
						continue;
					}
					else
						break;
				}
				wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
				char reentered[20];
				while (1) {
					i = 0;
					while ((n = _getch()) != 13 && n != 32) {
						if (n == 8) {
							if (i == 0)
								continue;
							else {
								i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
							}
						}
						else {
							reentered[i++] = (char)n;
							wprintf(L"*");
						}
					}
					reentered[i] = '\0';
					if (strcmp(reentered, user2.password) != 0) {
						wprintf(L"\a\n\t      \033[31mThe Passwords Doesen't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
						continue;
					}
					else {
						break;
					}
				}
				//Changing The Password
				rewind(usersdata);
				rewind(temp);
				while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
					if (strcmp(searchusers.username, user2.username) != 0) {
						fwrite(&searchusers, sizeof(struct users), 1, temp);
					}
				}
				fwrite(&user2, sizeof(struct users), 1, temp);
				fclose(usersdata); fclose(temp);
				remove("users.bin"); rename("temp.bin", "users.bin");
				continue;
			}
		}
		else if (login == '4') {
			//Exit
			system("cls || clear");
			wprintf(L"\n\n\t\t\t\t         \033[36mGoodBye!\033[36m\n\n\n\n");
			exit(0);
		}
		else if (login == '0') {
			//Change Player
			if (player == 1)
				player = 2;
			else if (player == 2)
				player = 1;
			continue;
		}
		else if (login == 13) {
			//Entering The Menu
			if (player == 1 && logged1 == 1)
				return;
			else if (player == 2 && logged2 == 1)
				return;
			else {
				system("cls || clear");
				wprintf(L"\a\n\n\n\n\n\n\n\t\t\t          \033[31mPlayer %d Not Logged In!", player);
				Sleep(1000);
				continue;
			}
		}
	}
}
void Menu() {
	while (1) {
		//Checking if Music Was Playing Or Not
		if (Menu_Music == 0)
			PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls || clear");
		if (player == 1)
			wprintf(L"\n\n\n\t\t\t\t\t\033[36m\n\n\n\t\t\t\t     \033[36mPlayer %d\n\t\t\t\t     \033[93m%S\033[36m\n\n\t\t\t\t     1 . Play!\n\n\t\t\t\t     2 . Change Account Information\n\n\t\t\t\t     3 . History\n\n\t\t\t\t     4 . Back to The Login Page\033[0m", player, user1.username);
		else if (player == 2)
			wprintf(L"\n\n\n\t\t\t\t\t\033[36m\n\n\n\t\t\t\t     \033[36mPlayer %d\n\t\t\t\t     \033[93m%S\033[36m\n\n\t\t\t\t     1 . Play!\n\n\t\t\t\t     2 . Change Account Information\n\n\t\t\t\t     3 . History\n\n\t\t\t\t     4 . Back to The Login Page\033[0m", player, user2.username);
		int menu = getch();
		while (menu != '1' && menu != '2' && menu != '3' && menu != '4' && menu != '0')
			menu = getch();
		if (menu == '1') {
			//Starting The Game
			if (logged1 == 1 && logged2 == 1) {
				system("cls || clear");
				wprintf(L"\n\n\n\n\t\t\t\t\033[36mEnter The Number of Players Lives : \033[31m");
				int temp;
				scanf("%d", &temp);
				wprintf(L"\033[96m\n\n\n\t\t\t\t\t  Loading ...\n\t\t\t\t ");
				for (int i = 1; i <= 25; i++)
				{
					Sleep(35);
					wprintf(L"\u2588");
				}
				Sleep(300);
				wprintf(L"\033[0m");
				system("cls || clear");
				Menu_Music = 0;
				PlaySound(0, 0, 0);
				while (gamefinished != 1) {
					lives1 = lives2 = temp;
					play();
				}
				round = 1; wins1 = wins2 = gamefinished = score1 = score2 = 0;
				continue;
			}
			else if (logged1 == 0 && logged2 == 1) {
				wprintf(L"\a\n\n\t\t\t\t  \033[31mPlayer 1 Not Logged In!\033[0m\n\n\n\n");
				Sleep(1000);
				continue;
			}
			else if (logged1 == 1 && logged2 == 0) {
				wprintf(L"\a\n\n\t\t\t\t  \033[31mPlayer 2 Not Logged In!\033[0m\n\n\n\n");
				Sleep(1000);
				continue;
			}
			else if (logged1 == 0 && logged2 == 0) {
				wprintf(L"\a\n\n\t\t\t\t  \033[31mPlayers Not Logged In!\033[0m\n\n\n\n");
				Sleep(1000);
				continue;
			}
		}

		else if (menu == '2') {
			//Changing Account Information
			if (player == 1) {
				while (1) {
					system("cls || clear");
					wprintf(L"\n\n\n\n\n\n\n\n\t\t\t\t\033[36mWhat Do You Want to Change?\n\n\t\t\t\t     1. Username\n\n\t\t\t\t     2. Email\n\n\t\t\t\t     3. Password\n\n\t\t\t\t     4. Back To The Menu\033[0m");
					int change = getch();
					while (change != '1' && change != '2' && change != '3' && change != '4')
						change = getch();
					if (change == '1') {
						char olduser[20];
						strcpy(olduser, user1.username);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						int exist = 0;
						wprintf(L"\n\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your New Username : \033[92m");
						while (1) {
							wscanf(L"%S", user1.username);
							rewind(usersdata);
							while (!feof(usersdata)) {
								fread(&searchusers, sizeof(struct users), 1, usersdata);
								if (strcmp(searchusers.username, user1.username) == 0) {
									exist = 1; break;
								}
							}if (exist == 1) {
								wprintf(L"\a\n\t      \033[31mUsername Already Exist!");
								wprintf(L"\n\t      \033[36mEnter Your New Username : \033[92m");
								exist = 0;
								continue;
							}
							else if (exist == 0) {
								break;
							}
						}
						//changing users
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.username, olduser) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user1, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						// changing scores
						scores = fopen("score.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						while (fread(searchscores.winner, sizeof(searchscores.winner), 1, scores)) {
							if (strcmp(searchscores.winner, olduser) == 0) {
								fwrite(user1.username, sizeof(searchscores.winner), 1, temp);
							}
							else if (strcmp(searchscores.winner, olduser) != 0) {
								fwrite(searchscores.winner, sizeof(searchscores.winner), 1, temp);
							}
						}
						fclose(scores); fclose(temp);
						remove("score.bin"); rename("temp.bin", "score.bin");
						continue;
					}
					else if (change == '2') {
						//changing email
						char oldemail[40];
						strcpy(oldemail, user1.email);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						int exist = 0;
						wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your New Email : \033[92m");
						while (1) {
							wscanf(L"%S", user1.email);
							rewind(usersdata);
							while (!feof(usersdata)) {
								fread(&searchusers, sizeof(struct users), 1, usersdata);
								if (strcmp(searchusers.email, user1.email) == 0) {
									exist = 1; break;
								}
							}if (exist == 0) {
								if (strstr(user1.email, "@") != NULL && strstr(user1.email, ".com") != NULL)
									break;
								else {
									wprintf(L"\a\n\t      \033[31minvalid Email!\n\t      \033[36mEnter Your New Email : \033[92m");
									continue;
								}
							}
							else if (exist == 1) {
								wprintf(L"\a\n\t      \033[31mEmail Already Exit!\033[36m");
								wprintf(L"\n\t      Enter Your New Email : \033[92m");
								exist = 0;
								continue;
							}
						}
						//changing
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.email, oldemail) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user1, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						continue;
					}
					else if (change == '3') {
						char oldpass[20];
						strcpy(oldpass, user1.password);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						//changing password
						wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter a New Password : \033[92m");
						int n, i = 0;
						while (1) {
							i = 0;
							while ((n = _getch()) != 13 && n != 32) {
								if (n == 8) {
									if (i == 0)
										continue;
									else {
										i--; user1.password[i] = '\0'; wprintf(L"\b\x1B[1P");
									}
								}
								else {
									user1.password[i++] = (char)n;
									wprintf(L"*");
								}
							}
							user1.password[i] = '\0';
							if (strlen(user1.password) < 8) {
								wprintf(L"\a\n\t      \033[31mYour Password Must Have at Least 8 Characters!\033[36m\n\t      Please Enter a New Password : \033[92m");
								continue;
							}
							else
								break;
						}
						wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
						char reentered[20];
						while (1) {
							i = 0;
							while ((n = _getch()) != 13 && n != 32) {
								if (n == 8) {
									if (i == 0)
										continue;
									else {
										i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
									}
								}
								else {
									reentered[i++] = (char)n;
									wprintf(L"*");
								}
							}
							reentered[i] = '\0';
							if (strcmp(reentered, user1.password) != 0) {
								wprintf(L"\a\n\t      \033[31mThe Passwords Doesn't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
								continue;
							}
							else {
								break;
							}
						}
						//changing
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.password, oldpass) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user1, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						continue;
					}
					else if (change == '4') {
						break;
					}
				}
			}

			else if (player == 2) {
				while (1) {
					system("cls || clear");
					wprintf(L"\n\n\n\n\n\n\n\n\t\t\t\t\033[36mWhat Do You Want to Change?\n\n\t\t\t\t     1. Username\n\n\t\t\t\t     2. Email\n\n\t\t\t\t     3. Password\n\n\t\t\t\t     4. Back To The Menu\033[0m");
					int change = getch();
					while (change != '1' && change != '2' && change != '3' && change != '4')
						change = getch();
					if (change == '1') {
						char olduser[20];
						strcpy(olduser, user2.username);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						int exist = 0;
						wprintf(L"\n\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your New Username : \033[92m");
						while (1) {
							wscanf(L"%S", user2.username);
							rewind(usersdata);
							while (!feof(usersdata)) {
								fread(&searchusers, sizeof(struct users), 1, usersdata);
								if (strcmp(searchusers.username, user2.username) == 0) {
									exist = 1; break;
								}
							}if (exist == 1) {
								wprintf(L"\a\n\t      \033[31mUsername Already Exist!");
								wprintf(L"\n\t      \033[36mEnter Your New Username : \033[92m");
								exist = 0;
								continue;
							}
							else if (exist == 0) {
								break;
							}
						}
						//changing users
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.username, olduser) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user2, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						// changing scores
						scores = fopen("score.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						while (fread(searchscores.winner, sizeof(searchscores.winner), 1, scores)) {
							if (strcmp(searchscores.winner, olduser) == 0) {
								fwrite(user1.username, sizeof(searchscores.winner), 1, temp);
							}
							else if (strcmp(searchscores.winner, olduser) != 0) {
								fwrite(searchscores.winner, sizeof(searchscores.winner), 1, temp);
							}
						}
						fclose(scores); fclose(temp);
						remove("score.bin"); rename("temp.bin", "score.bin");
						continue;
					}
					else if (change == '2') {
						//changing email
						char oldemail[40];
						strcpy(oldemail, user2.email);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						int exist = 0;
						wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter Your New Email : \033[92m");
						while (1) {
							wscanf(L"%S", user2.email);
							rewind(usersdata);
							while (!feof(usersdata)) {
								fread(&searchusers, sizeof(struct users), 1, usersdata);
								if (strcmp(searchusers.email, user2.email) == 0) {
									exist = 1; break;
								}
							}if (exist == 0) {
								if (strstr(user2.email, "@") != NULL && strstr(user2.email, ".com") != NULL)
									break;
								else {
									wprintf(L"\a\n\t      \033[31minvalid Email!\n\t      \033[36mEnter Your New Email : \033[92m");
									continue;
								}
							}
							else if (exist == 1) {
								wprintf(L"\a\n\t      \033[31mEmail Already Exit!\033[36m");
								wprintf(L"\n\t      Enter Your New Email : \033[92m");
								exist = 0;
								continue;
							}
						}
						//changing
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.email, oldemail) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user2, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						continue;
					}
					else if (change == '3') {
						char oldpass[20];
						strcpy(oldpass, user2.password);
						usersdata = fopen("users.bin", "rb+");
						temp = fopen("temp.bin", "wb");
						system("cls || clear");
						//changing password
						wprintf(L"\n\n\n\n\n\n\n\n\n\t      \033[36mEnter a New Password : \033[92m");
						int n, i = 0;
						while (1) {
							i = 0;
							while ((n = _getch()) != 13 && n != 32) {
								if (n == 8) {
									if (i == 0)
										continue;
									else {
										i--; user2.password[i] = '\0'; wprintf(L"\b\x1B[1P");
									}
								}
								else {
									user2.password[i++] = (char)n;
									wprintf(L"*");
								}
							}
							user2.password[i] = '\0';
							if (strlen(user2.password) < 8) {
								wprintf(L"\a\n\t      \033[31mYour Password Must Have at Least 8 Characters!\033[36m\n\t      Please Enter a New Password : \033[92m");
								continue;
							}
							else
								break;
						}
						wprintf(L"\n\t      \033[36mReEnter The Password : \033[92m");
						char reentered[20];
						while (1) {
							i = 0;
							while ((n = _getch()) != 13 && n != 32) {
								if (n == 8) {
									if (i == 0)
										continue;
									else {
										i--; reentered[i] = '\0'; wprintf(L"\b\x1B[1P");
									}
								}
								else {
									reentered[i++] = (char)n;
									wprintf(L"*");
								}
							}
							reentered[i] = '\0';
							if (strcmp(reentered, user2.password) != 0) {
								wprintf(L"\a\n\t      \033[31mThe Passwords Doesn't Match!\n\t      \033[36mEnter Your Password Again Correctly : \033[92m");
								continue;
							}
							else {
								break;
							}
						}
						//changing
						rewind(usersdata);
						rewind(temp);
						while (fread(&searchusers, sizeof(struct users), 1, usersdata)) {
							if (strcmp(searchusers.password, oldpass) != 0) {
								fwrite(&searchusers, sizeof(struct users), 1, temp);
							}
						}
						fwrite(&user2, sizeof(struct users), 1, temp);
						fclose(usersdata); fclose(temp);
						remove("users.bin"); rename("temp.bin", "users.bin");
						continue;
					}
					else if (change == '4') {
						break;
					}
				}
			}

		}

		else if (menu == '3') {
			//Show Player History
			system("cls || clear");
			scores = fopen("score.bin", "rb");
			int count;
			if (player == 1) {
				count = 1;
				while (!feof(scores)) {
					fread(&score, sizeof(struct score), 1, scores);
					if (strcmp(score.winner, user1.username) == 0 || strcmp(score.loser, user1.username) == 0) {
						for (int i = 1; i <= 3; i++) {
							if (feof(scores))
								break;
							if (i == 1) {
								wprintf(L"\t\t      \033[36mMatch %d :\033[34m \n\t\t      Round %d : \033[92mWinner : %S  \t\033[31mLoser : %S\033[0m\n", count, i, score.winner, score.loser);
							}
							else {
								fread(&score, sizeof(struct score), 1, scores);
								wprintf(L"\t\t      \033[34m\n\t\t      Round %d : \033[92mWinner : %S  \t\033[31mLoser : %S\033[0m\n", i, score.winner, score.loser);
							}
						}
						fread(score.winner, sizeof(score.winner), 1, scores);
						if (feof(scores))
							break;
						wprintf(L"\n\t\t\t\t\033[36mThe Winner of the Match : %S\n\n\n\n\033[0m", score.winner);
						count++;
						if (strcmp(score.winner, user1.username) == 0)
							allwins1++;
						else if (strcmp(score.loser, user1.username) == 0)
							allloses1++;
					}
					else {
						continue;
					}
				}
				fclose(scores);
				wprintf(L"\n\t\t\t\t\033[36mTotal Number of Matchs : %d\n\t\t\t\t\033[92mTotal Number of Wins : %d\n\t\t\t\t\033[31mTotal Number of Loses : %d\n\t\t\t\t \033[0m\n\n\t\t\t Press Any Key to Continue", allwins1 + allloses1, allwins1, allloses1);
				allwins1 = 0; allloses1 = 0;
			}
			else if (player == 2) {
				count = 1;
				while (!feof(scores)) {
					fread(&score, sizeof(struct score), 1, scores);
					if (strcmp(score.winner, user2.username) == 0 || strcmp(score.loser, user2.username) == 0) {
						for (int i = 1; i <= 3; i++) {
							if (feof(scores))
								break;
							if (i == 1) {
								wprintf(L"\t\t      \033[36mMatch %d :\033[34m \n\t\t      Round %d : \033[92mWinner : %S  \t\033[31mLoser : %S\033[0m\n", count, i, score.winner, score.loser);
							}
							else {
								fread(&score, sizeof(struct score), 1, scores);
								wprintf(L"\t\t      \033[34m\n\t\t      Round %d : \033[92mWinner : %S  \t\033[31mLoser : %S\033[0m\n", i, score.winner, score.loser);
							}
						}
						fread(score.winner, sizeof(score.winner), 1, scores);
						if (feof(scores))
							break;
						wprintf(L"\n\t\t\t\t\033[0mThe Winner of the Match : %S\n\n\n\n\033[0m", score.winner);
						count++;
						if (strcmp(score.winner, user2.username) == 0)
							allwins2++;
						else if (strcmp(score.loser, user2.username) == 0)
							allloses2++;
					}
					else {
						continue;
					}
				}
				fclose(scores);
				wprintf(L"\n\t\t\t\t\033[36mTotal Number of Matchs : %d\n\t\t\t\t\033[92mTotal Number of Wins : %d\n\t\t\t\t\033[31mTotal Number of Loses : %d\n\t\t\t\t \033[0m\n\n\t\t\t Press Any Key to Continue", allwins2 + allloses2, allwins2, allloses2);
				allwins2 = 0; allloses2 = 0;
			}
			int n;
			if (n = _getch())
				continue;
		}

		else if (menu == '4')
			return;
	}
}
void drawmap1() {
	register int i, y, x;
	//BombSide1
	memset(*(map + 8) + 29, '*', 14);
	memset(*(map + 11) + 29, '*', 14);
	for (i = 8; i <= 11; i++)
		map[i][29] = '*';
	for (i = 8; i <= 11; i++)
		map[i][42] = '*';
	//BombSide2
	memset(*(map + 11) + 50, '*', 14);
	memset(*(map + 14) + 50, '*', 14);
	for (i = 11; i <= 14; i++)
		map[i][50] = '*';
	for (i = 11; i <= 14; i++)
		map[i][63] = '*';
	/////
	memset(*(map + 4) + 13, '[', 7);
	for (i = 4; i <= 16; i++)
		map[i][19] = '[';
	memset(*(map + 16) + 13, '[', 7);
	map[19][9] = 't';
	map[16][28] = '@';
	map[5][20] = '|'; map[6][20] = '|'; map[14][20] = '|'; map[15][20] = '|';
	map[2][26] = '['; map[3][26] = '['; map[2][27] = '|'; map[3][27] = '|';
	map[18][26] = '['; map[19][26] = '[';
	memset(*(map + 13) + 33, '[', 8);
	for (i = 5; i <= 9; i++)
		map[i][46] = '[';
	map[10][46] = '|';
	for (i = 11; i <= 15; i++)
		map[i][46] = '[';
	if (heart == 1)
		map[3][46] = 'h';
	else map[3][46] = ' ';
	memset(*(map + 6) + 52, '[', 8);
	map[19][63] = '|'; map[18][63] = '|'; map[18][64] = '['; map[19][64] = '[';
	map[2][64] = '['; map[3][64] = '['; map[3][70] = '@'; map[5][69] = '|'; map[6][69] = '|';
	map[14][69] = '|'; map[15][69] = '|';
	memset(*(map + 4) + 70, '[', 7);
	for (i = 4; i <= 16; i++)
		map[i][70] = '[';
	memset(*(map + 16) + 70, '[', 7);
	map[19][83] = 'T';
	//Checking C4
	for (y = 1; y < 23; y++) {
		for (x = 0; x < 93; x++) {
			if (tempmap[y][x] == 'C')
				map[y][x] = 'C';
		}
	}

}
void drawmap2() {
	register int i, y, x;
	//BombSide1
	memset(*(map + 2) + 30, '*', 12);
	memset(*(map + 5) + 30, '*', 12);
	for (i = 2; i <= 5; i++)
		map[i][30] = '*';
	for (i = 2; i <= 5; i++)
		map[i][41] = '*';
	//BombSid2
	memset(*(map + 2) + 48, '*', 12);
	memset(*(map + 5) + 48, '*', 12);
	for (i = 2; i <= 5; i++)
		map[i][48] = '*';
	for (i = 2; i <= 5; i++)
		map[i][59] = '*';
	/////
	//Wall & Mirror
	for (i = 6; i <= 12; i++)
		map[i][11] = '|';
	map[2][27] = '['; map[3][27] = '['; map[2][28] = '|';
	map[6][36] = '['; map[7][35] = '['; map[8][34] = '['; map[9][33] = '['; map[10][34] = '[';
	map[10][35] = '|'; map[11][35] = '['; map[12][36] = '[';
	map[16][27] = '['; map[17][27] = '['; map[16][28] = '|';
	map[4][46] = '['; map[4][44] = '['; map[4][45] = '['; map[4][46] = '['; map[6][45] = '[';
	map[7][45] = '['; map[7][44] = '['; map[7][43] = '['; map[7][42] = '[';
	map[8][42] = '['; map[9][42] = '['; map[9][41] = '|'; map[9][41] = '['; map[9][40] = '['; map[9][43] = '|';
	map[15][44] = '['; map[15][45] = '['; map[15][46] = '[';
	map[9][49] = '['; map[9][50] = '['; map[9][51] = '['; map[9][52] = '['; map[10][49] = '['; map[11][49] = '[';
	map[11][48] = '['; map[11][47] = '['; map[11][46] = '['; map[11][45] = '['; map[12][45] = '['; map[2][61] = '['; map[3][61] = '[';
	map[3][60] = '|'; map[6][56] = '['; map[7][57] = '['; map[8][58] = '['; map[8][57] = '|';
	map[9][59] = '['; map[10][58] = '['; map[11][57] = '['; map[12][56] = '[';
	map[16][61] = '['; map[17][61] = '['; map[17][60] = '|';
	for (i = 6; i <= 12; i++)
		map[i][81] = '|';
	//2Tir
	if (double_bullet1 == 1)
		map[7][28] = 'e';
	else
		map[7][28] = ' ';
	if (double_bullet2 == 1)
		map[7][64] = 'E';
	else
		map[7][64] = ' ';
	//Teleport
	map[17][8] = 't';
	map[17][82] = 'T';
	//Heart
	if (heart == 1)
		map[9][45] = 'h';
	else map[9][45] = ' ';
	//Bomb
	if (bomb_ == 1)
		map[14][45] = 'b';
	else
		map[14][45] = ' ';
	if (ghost_ == 1)
		map[2][45] = 'g';
	else
		map[2][45] = ' ';
	//at
	map[10][43] = '@'; map[8][47] = '@'; map[13][45] = '@';
	for (y = 1; y < 23; y++) {
		for (x = 0; x < 93; x++) {
			if (tempmap[y][x] == '#')
				map[y][x] = ' ';
			else if (tempmap[y][x] == 'C')
				map[y][x] = 'C';
		}
	}
}
void drawmap3() {
	register int i, y, x;
	//BombSide1
	memset(*(map + 11) + 24, '*', 14);
	memset(*(map + 14) + 24, '*', 14);
	for (i = 11; i <= 14; i++)
		map[i][24] = '*';
	for (i = 11; i <= 14; i++)
		map[i][37] = '*';
	//BombSid2
	memset(*(map + 4) + 52, '*', 14);
	memset(*(map + 7) + 52, '*', 14);
	for (i = 4; i <= 7; i++)
		map[i][52] = '*';
	for (i = 4; i <= 7; i++)
		map[i][65] = '*';
	/////

	//khat-chap
	for (i = 6; i <= 12; i++)
		map[i][11] = '|';
	//4gooshe
	map[2][26] = '['; map[3][26] = '['; map[3][27] = '|';
	map[16][26] = '['; map[17][26] = '['; map[17][27] = '|';
	map[2][63] = '['; map[3][63] = '['; map[2][62] = '|';
	map[16][63] = '['; map[17][63] = '['; map[16][62] = '|';
	//bala-chap
	map[5][12] = '['; map[4][13] = '['; map[3][15] = '['; map[3][18] = '['; map[3][17] = '[';
	map[3][18] = '['; map[3][19] = '['; map[3][20] = '['; map[3][21] = '[';
	//paein-chap
	map[3][22] = '['; map[3][23] = '['; map[3][24] = '[';
	map[13][12] = '['; map[14][13] = '['; map[16][15] = '[';
	memset(*(map + 17) + 15, '[', 10);
	//paein-rast
	map[13][80] = '['; map[14][79] = '['; map[16][77] = '['; map[15][77] = '[';
	memset(*(map + 16) + 65, '[', 12);
	//bala-rast
	map[5][80] = '['; map[4][79] = '['; map[3][77] = '[';
	memset(*(map + 3) + 65, '[', 12);
	//marpiche-bala
	map[9][33] = '['; map[8][34] = '['; map[7][35] = '['; map[6][36] = '[';
	memset(*(map + 6) + 37, '[', 10);
	map[7][47] = '['; map[8][48] = '[';
	//marpiche-paein
	map[9][42] = '['; map[10][43] = '['; map[11][44] = '[';
	memset(*(map + 12) + 45, '[', 10);
	map[11][54] = '['; map[10][55] = '['; map[9][56] = '[';
	//khat-rast
	for (i = 6; i <= 12; i++)
		map[i][81] = '|';
	//at
	map[10][44] = '@'; map[11][49] = '@'; map[9][47] = '@';
	//heart
	if (heart == 1)
		map[11][46] = 'h';
	else map[11][46] = ' ';
	//tir
	if (double_bullet1 == 1)
		map[7][28] = 'e';
	else
		map[7][28] = ' ';
	if (double_bullet2 == 1)
		map[11][53] = 'E';
	else
		map[11][53] = ' ';
	//teleport
	map[2][12] = 't'; map[2][81] = 'T';
	//bomb
	if (bomb_ == 1)
		map[5][35] = 'b';
	else
		map[5][35] = ' ';
	//ghost
	if (ghost_ == 1)
		map[2][46] = 'g';
	else
		map[2][46] = ' ';

	for (y = 1; y < 23; y++) {
		for (x = 0; x < 93; x++) {
			if (tempmap[y][x] == '#')
				map[y][x] = ' ';
			else if (tempmap[y][x] == 'C')
				map[y][x] = 'C';
		}
	}
}
void printmap() {
	register int y, x;
	for (y = 1; y < 23; y++) {
		for (x = 0; x < 93; x++) {
			if (map[y][x] == '[')
				wprintf(L"\u2588");
			else if (map[y][x] == '.') {
				if (b1 == 1 && bomb1 == 1)
					wprintf(L"\033[92m\u01A1\033[0m");
				else if (b2 == 1 && bomb2 == 1)
					wprintf(L"\033[92m\u01A1\033[0m");
				else {
					if ((b1 == 1 && twotir1 > 0) || (b2 == 1 && twotir2 > 0)) {
						if ((b1 == 1 && ghost1 > 0) || (b2 == 2 && ghost2 > 0))
							wprintf(L":");
						else
							wprintf(L"\033[92m:\033[0m");
					}
					else {
						if ((b1 == 1 && ghost1 > 0) || (b2 == 1 && ghost2 > 0))
							wprintf(L"\u2022");
						else
							wprintf(L"\033[92m\u2022\033[0m");
					}
				}
			}
			else if (map[y][x] == '1') {
				if (ghost1 > 0)
					wprintf(L"\u25D9");
				else
					wprintf(L"\033[34m\u25D9\033[0m");
			}
			else if (map[y][x] == '2') {
				if (ghost2 > 0)
					wprintf(L"\u25D9");
				else
					wprintf(L"\033[31m\u25D9\033[0m");
			}
			else if (map[y][x] == '|')
				wprintf(L"\u2551");
			else if (map[y][x] == 't' || map[y][x] == 'T')
				wprintf(L"\033[33m\u058D\033[0m");
			else if (map[y][x] == '@')
				wprintf(L"\033[90m@\033[0m");
			else if (map[y][x] == 'h')
				wprintf(L"\033[31m\u2665\033[0m");
			else if (map[y][x] == 'e' || map[y][x] == 'E')
				wprintf(L"\033[92m\u2591\033[0m");
			else if (map[y][x] == 'g')
				wprintf(L"\033[35m\u0571\033[0m");
			else if (map[y][x] == 'b')
				wprintf(L"\033[92m\u01A1\033[0m");
			else if (map[y][x] == 'C') {
				if (c41 == 1 && player1_c4.X == x && player1_c4.Y == y) {
					if ( seconds1 == 65)
						wprintf(L"\033[34m\u2460\033[0m");
					else if (57 < seconds1 && seconds1 <= 64)
						wprintf(L"\033[34m\u2461\033[0m");
					else if (50 < seconds1 && seconds1 <= 57)
						wprintf(L"\033[34m\u2462\033[0m");
					else if (43 < seconds1 && seconds1 <= 50)
						wprintf(L"\033[34m\u2463\033[0m");
					else if (36 < seconds1 && seconds1 <= 43)
						wprintf(L"\033[34m\u2464\033[0m");
					else if (29 < seconds1 && seconds1 <= 36)
						wprintf(L"\033[34m\u2465\033[0m");
					else if (22 < seconds1 && seconds1 <= 29)
						wprintf(L"\033[34m\u2466\033[0m");
					else if (15 < seconds1 && seconds1 <= 22)
						wprintf(L"\033[34m\u2467\033[0m");
					else if (8 <= seconds1 && seconds1 <= 15)
						wprintf(L"\033[34m\u2468\033[0m");
					else if (0 <= seconds2 && seconds1 <= 8)
						wprintf(L"\033[34m\u2469\033[0m");
				}
				if (c42 == 1 && player2_c4.X == x && player2_c4.Y == y) {
					if (seconds2 == 65)
						wprintf(L"\033[31m\u2460\033[0m");
					else if (57 < seconds2 && seconds2 <= 64)
						wprintf(L"\033[31m\u2461\033[0m");
					else if (50 < seconds2 && seconds2 <= 57)
						wprintf(L"\033[31m\u2462\033[0m");
					else if (43 < seconds2 && seconds2 <= 50)
						wprintf(L"\033[31m\u2463\033[0m");
					else if (36 < seconds2 && seconds2 <= 43)
						wprintf(L"\033[31m\u2464\033[0m");
					else if (29 < seconds2 && seconds2 <= 36)
						wprintf(L"\033[31m\u2465\033[0m");
					else if (22 < seconds2 && seconds2 <= 29)
						wprintf(L"\033[31m\u2466\033[0m");
					else if (15 < seconds2 && seconds2 <= 22)
						wprintf(L"\033[31m\u2467\033[0m");
					else if (8 < seconds2 && seconds2 <= 15)
						wprintf(L"\033[31m\u2468\033[0m");
					else if (1 < seconds2 && seconds2 <= 8)
						wprintf(L"\033[31m\u2469\033[0m");
				}
			}
			else if (map[y][x] == '*')
				wprintf(L".");
			else if (map[y][x] == 'F')
				wprintf(L"\033[33m\u2593\033[0m");
			else
				wprintf(L"%c", map[y][x]);
		}
	}
}
void end() {
	scores = fopen("score.bin", "ab+");
	if (lives1 <= 0) {
		score2 += 10;
		wins2++;
		strcpy(score.winner, user2.username);
		strcpy(score.loser, user1.username);
		fwrite(&score, sizeof(struct score), 1, scores);
		wprintf(L"\t\t\t\t\t\033[93m%S\033[92m Won This Round!\033[0m", user2.username);
		Sleep(1200);
		if (round == 3) {
			if (score1 < score2) {
				fwrite(user2.username, sizeof(user2.username), 1, scores);
				system("cls || clear");
				wprintf(L"\n\n\n\n\t\t\t\t\t\033[93m%S\033[92m Won The Game\033[0m", user2.username);
				Sleep(2000);
			}
			else if (score1 > score2) {
				fwrite(user1.username, sizeof(user1.username), 1, scores);
				system("cls || clear");
				wprintf(L"\n\n\n\n\t\t\t\t\t\033[93m%S\033[92m Won The Game\033[0m", user1.username);
				Sleep(2000);
			}
		}
		fclose(scores);
		round++;
		return;
	}
	else if (lives2 <= 0) {
		score1 += 10;
		wins1++;
		strcpy(score.winner, user1.username);
		strcpy(score.loser, user2.username);
		fwrite(&score, sizeof(struct score), 1, scores);
		wprintf(L"\t\t\t\t\t\033[93m%S\033[92m Won This Round!\033[0m", user1.username);
		Sleep(1200);
		if (round == 3) {
			if (score1 < score2) {
				fwrite(user2.username, sizeof(user2.username), 1, scores);
				system("cls || clear");
				wprintf(L"\n\n\n\n\t\t\t\t\t\033[93m%S\033[92m Won The Game\033[0m", user2.username);
				Sleep(1200);
			}
			else if (score1 > score2) {
				fwrite(user1.username, sizeof(user1.username), 1, scores);
				system("cls || clear");
				wprintf(L"\n\n\n\n\t\t\t\t\t\033[93m%S\033[92m Won The Game\033[0m", user1.username);
				Sleep(1200);
			}
		}
		fclose(scores);
		round++;
		return;
	}
}
void play() {
	register int i, j, y, x;
	COORD player1_pos = { 9, 9 };
	COORD player2_pos = { 83, 9 };
	COORD player1_bullet = { -1, -1 };
	COORD player2_bullet = { -1, -1 };
	player1_c4.X = -1; 	player1_c4.X = -1;
	player2_c4.X = -1;	player2_c4.Y = -1;
	bomb1 = 0; bomb2 = 0; bomb_ = 1; heart = 1; double_bullet1 = 1; double_bullet2 = 1; double_bullet_p1 = 0,twotir1=0,twotir2=0;
	double_bullet_p2 = 0; ghost_ = 1; ghost1 = 0; ghost2 = 0; c41 = 0; c42 = 0; seconds1 = 0; seconds2 = 0, explode = 0;
	//Clean Temp Map
	memset(tempmap, ' ', sizeof(tempmap));
	if (round == 1)
		PlaySound(TEXT("round1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (round == 2)
		PlaySound(TEXT("round2.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else if (round == 3)
		PlaySound(TEXT("round3.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (1) {
		if (lives1 <= 0 || lives2 <= 0) {
			end();
			return;
		}
		// Clean map
		memset(map, ' ', sizeof(tempmap));
		//C4 Check
		if (c41 == 0) {
			tempmap[player1_c4.Y][player1_c4.X] = ' ';
			player1_c4.X = -1; player1_c4.Y = -1;
		}
		if (c42 == 0) {
			tempmap[player2_c4.Y][player2_c4.X] = ' ';
			player2_c4.X = -1; player2_c4.Y = -1;
		}

		//Draw C4
		if (player1_c4.X <= 92 && player1_c4.X != -1 && player1_c4.Y <= 22 && player1_c4.Y >= 1)
			tempmap[player1_c4.Y][player1_c4.X] = 'C';
		if (player2_c4.X <= 92 && player2_c4.X != -1 && player2_c4.Y <= 22 && player2_c4.Y >= 1)
			tempmap[player2_c4.Y][player2_c4.X] = 'C';

		////Draw Map
		if (round == 1)
			drawmap1();
		else if (round == 2)
			drawmap2();
		else if (round == 3)
			drawmap3();
		else {
			gamefinished = 1;
			return;
		}
		//////////////

		// Draw players
		map[player1_pos.Y][player1_pos.X] = '1';
		map[player2_pos.Y][player2_pos.X] = '2';

		//////Print Map
		gotoxy(0, 0);
		wprintf(L"\033[93m%10S \033[34mWins:%d   \033[31m%d\u2665\t\t\t\033[92m  Round %d\033[93m\t\t%10S \033[34mWins:%d \t\033[31m%d\u2665\033[0m\n", user1.username, wins1, lives1, round, user2.username, wins2, lives2);
		/////////////////
		
		// Input handling for Player 1
		if (keyPressed(PLAYER1_UP)) {
			if (player1_pos.Y != 1 && map[player1_pos.Y - 1][player1_pos.X] != '[' && map[player1_pos.Y - 1][player1_pos.X] != '|') {
				player1_pos = moveDirection(player1_pos, 0, -1); ghost1--;
			}
			else if (player1_pos.Y != 1 && ghost1 > 0) {
				player1_pos = moveDirection(player1_pos, 0, -1); ghost1--;
			}
			if (b1 == 0)
				move1 = 'u';
		}
		if (keyPressed(PLAYER1_DOWN)) {
			if (player1_pos.Y != 22 && map[player1_pos.Y + 1][player1_pos.X] != '[' && map[player1_pos.Y + 1][player1_pos.X] != '|') {
				player1_pos = moveDirection(player1_pos, 0, 1); ghost1--;
			}
			else if (player1_pos.Y != 22 && ghost1 > 0) {
				player1_pos = moveDirection(player1_pos, 0, 1); ghost1--;
			}
			if (b1 == 0)
				move1 = 'd';
		}
		if (keyPressed(PLAYER1_LEFT)) {
			if (player1_pos.X != 0 && map[player1_pos.Y][player1_pos.X - 1] != '[' && map[player1_pos.Y][player1_pos.X - 1] != '|') {
				player1_pos = moveDirection(player1_pos, -1, 0); ghost1--;
			}
			else if (player1_pos.X != 0 && ghost1 > 0) {
				player1_pos = moveDirection(player1_pos, -1, 0); ghost1--;
			}
			if (b1 == 0)
				move1 = 'l';
		}
		if (keyPressed(PLAYER1_RIGHT)) {
			if (player1_pos.X != 92 && map[player1_pos.Y][player1_pos.X + 1] != '[' && map[player1_pos.Y][player1_pos.X + 1] != '|') {
				player1_pos = moveDirection(player1_pos, 1, 0); ghost1--;
			}
			else if (player1_pos.X != 92 && ghost1 > 0) {
				player1_pos = moveDirection(player1_pos, 1, 0); ghost1--;
			}
			if (b1 == 0)
				move1 = 'r';
		}
		if (keyPressed(PLAYER1_SHOOT)) {
			if (b1 == 0 && move1 != ' ') {
				player1_bullet = player1_pos; b1 = 1; twotir1--; ghost1--;
				PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		if (keyPressed(PLAYER1_C4)) {
			if ((round == 1 && player1_pos.X >= 50 && player1_pos.X <= 63 && player1_pos.Y >= 11 && player1_pos.Y <= 14)
				|| (round == 2 && player1_pos.X >= 48 && player1_pos.X <= 59 && player1_pos.Y >= 2 && player1_pos.Y <= 5) ||
				(round == 3 && player1_pos.X >= 52 && player1_pos.X <= 65 && player1_pos.Y >= 4 && player1_pos.Y <= 7)) {
				if (c41 == 0 && map[player1_pos.Y][player1_pos.X] == ' ' && tempmap[player1_pos.Y][player1_pos.X] != 'C') {
					PlaySound(TEXT("c4.wav"), NULL, SND_FILENAME | SND_ASYNC);
					player1_c4 = player1_pos;
					c41 = 1; map[player1_c4.Y][player1_c4.X] = 'C';
					seconds1 = 0;
				}
			}
			else if (c42 == 1 && tempmap[player1_pos.Y][player1_pos.X] == 'C') {
				c42 = 0; c41 = 0; seconds2 = 0; lives1++; PlaySound(TEXT("defused.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}


		// Input handling for Player 2
		if (keyPressed(PLAYER2_UP)) {
			if (player2_pos.Y != 1 && map[player2_pos.Y - 1][player2_pos.X] != '[' && map[player2_pos.Y - 1][player2_pos.X] != '|') {
				player2_pos = moveDirection(player2_pos, 0, -1); ghost2--;
			}
			else if (player2_pos.Y != 1 && ghost2 > 0) {
				player2_pos = moveDirection(player2_pos, 0, -1); ghost2--;
			}
			if (b2 == 0)
				move2 = 'u';
		}
		if (keyPressed(PLAYER2_DOWN)) {
			if (player2_pos.Y != 22 && map[player2_pos.Y + 1][player2_pos.X] != '[' && map[player2_pos.Y + 1][player2_pos.X] != '|') {
				player2_pos = moveDirection(player2_pos, 0, 1); ghost2--;
			}
			else if (player2_pos.Y != 22 && ghost2 > 0) {
				player2_pos = moveDirection(player2_pos, 0, 1); ghost2--;
			}
			if (b2 == 0)
				move2 = 'd';
		}
		if (keyPressed(PLAYER2_LEFT)) {
			if (player2_pos.X != 0 && map[player2_pos.Y][player2_pos.X - 1] != '[' && map[player2_pos.Y][player2_pos.X - 1] != '|') {
				player2_pos = moveDirection(player2_pos, -1, 0); ghost2--;
			}
			else if (player2_pos.X != 0 && ghost2 > 0) {
				player2_pos = moveDirection(player2_pos, -1, 0); ghost2--;
			}
			if (b2 == 0)
				move2 = 'l';
		}
		if (keyPressed(PLAYER2_RIGHT)) {
			if (player2_pos.X != 92 && map[player2_pos.Y][player2_pos.X + 1] != '[' && map[player2_pos.Y][player2_pos.X + 1] != '|') {
				player2_pos = moveDirection(player2_pos, 1, 0); ghost2--;
			}
			else if (player2_pos.X != 92 && ghost2 > 0) {
				player2_pos = moveDirection(player2_pos, 1, 0); ghost2--;
			}
			if (b2 == 0)
				move2 = 'r';
		}
		if (keyPressed(PLAYER2_SHOOT)) {
			if (b2 == 0 && move2 != ' ') {
				player2_bullet = player2_pos; b2 = 1; twotir2--; ghost2--;
				PlaySound(TEXT("shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		if (keyPressed(PLAYER2_C4)) {
			if ((round == 1 && player2_pos.X >= 29 && player2_pos.X <= 42 && player2_pos.Y >= 8 && player2_pos.Y <= 11)
				|| (round == 2 && player2_pos.X >= 30 && player2_pos.X <= 41 && player2_pos.Y >= 2 && player2_pos.Y <= 5) ||
				(round == 3 && player2_pos.X >= 24 && player2_pos.X <= 37 && player2_pos.Y >= 11 && player2_pos.Y <= 14)) {
				if (c42 == 0 && map[player2_pos.Y][player2_pos.X] == ' ' && tempmap[player2_pos.Y][player2_pos.X] != 'C') {
					PlaySound(TEXT("c4.wav"), NULL, SND_FILENAME | SND_ASYNC);
					player2_c4 = player2_pos;
					c42 = 1; tempmap[player2_c4.Y][player2_c4.X] = 'C';
					seconds2 = 0;
				}
			}
			else if (c41 == 1 && map[player2_pos.Y][player2_pos.X] == 'C') {
				c41 = 0; c42 = 0; seconds1 = 0; lives2++; PlaySound(TEXT("defused.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}


		//Update-C4
		if (player1_c4.X != -1) {
			if (seconds1 >= 65) {
				lives2 -= 2; c41 = 1;
				tempmap[player1_c4.Y][player1_c4.X] = ' ';
				player1_c4.X = -1; player1_c4.Y = -1;
				seconds1 = 0;
				system("COLOR 1E");
				Sleep(100);
				system("COLOR 07");
			}
			else {
				seconds1++;
			}
		}
		if (player2_c4.X != -1) {
			if (seconds2 >= 65) {
				lives1 -= 2;  c42 = 1;
				tempmap[player2_c4.Y][player2_c4.X] = ' ';
				player2_c4.X = -1; player2_c4.Y = -1;
				seconds2 = 0;
				system("COLOR 4E");
				Sleep(100);
				system("COLOR 07");
			}
			else {
				seconds2++;
			}
		}

		//Double Bullet Check
		if (twotir1 <= 0)
			double_bullet_p1 = 0;
		if (twotir2 <= 0)
			double_bullet_p2 = 0;


		//Update bullet Positions
		if (player1_bullet.X != -1) {
			if (b1 == 1) {
				switch (move1) {
				case 'u':
					player1_bullet.Y--;
					break;
				case 'd':
					player1_bullet.Y++;
					break;
				case 'l':
					player1_bullet.X--;
					break;
				case 'r':
					player1_bullet.X++;
					break;
				}
			}
		}
		if (player2_bullet.X != -1) {
			if (b2 == 1) {
				switch (move2) {
				case 'u':
					player2_bullet.Y--;
					break;
				case 'd':
					player2_bullet.Y++;
					break;
				case 'l':
					player2_bullet.X--;
					break;
				case 'r':
					player2_bullet.X++;
					break;
				}
			}
		}

		//Item Taking:
		//at
		if (map[player1_pos.Y][player1_pos.X] == '@' && ghost1 <= 0) {
			player1_pos.X = 6; player1_pos.Y = 9;
			lives1--;
		}
		if (map[player2_pos.Y][player2_pos.X] == '@' && ghost2 <= 0) {
			player2_pos.X = 83; player2_pos.Y = 9;
			lives2--;
		}
		//Teleporter
		if (map[player1_pos.Y][player1_pos.X] == 't') {
			for (y = 1; y < 23; y++) {
				for (x = 0; x < 93; x++) {
					if (map[y][x] == 'T') {
						player1_pos.Y = y - 1; player1_pos.X = x;
						break;
					}
				}
			}
		}
		if (map[player1_pos.Y][player1_pos.X] == 'T') {
			for (y = 1; y < 23; y++) {
				for (x = 0; x < 93; x++) {
					if (map[y][x] == 't') {
						player1_pos.Y = y - 1; player1_pos.X = x;
						break;
					}
				}
			}
		}
		if (map[player2_pos.Y][player2_pos.X] == 't') {
			for (y = 1; y < 23; y++) {
				for (x = 0; x < 93; x++) {
					if (map[y][x] == 'T') {
						player2_pos.Y = y - 1; player2_pos.X = x;
						break;
					}
				}
			}
		}
		if (map[player2_pos.Y][player2_pos.X] == 'T') {
			for (y = 1; y < 23; y++) {
				for (x = 0; x < 93; x++) {
					if (map[y][x] == 't') {
						player2_pos.Y = y - 1; player2_pos.X = x;
						break;
					}
				}
			}
		}
		//Heart
		if (map[player1_pos.Y][player1_pos.X] == 'h') {
			PlaySound(TEXT("heart.wav"), NULL, SND_FILENAME | SND_ASYNC);
			lives1 += 5;
			heart = 0;
		}
		if (map[player2_pos.Y][player2_pos.X] == 'h') {
			PlaySound(TEXT("heart.wav"), NULL, SND_FILENAME | SND_ASYNC);
			lives2 += 5;
			heart = 0;
		}
		//Double Bullet
		if (map[player1_pos.Y][player1_pos.X] == 'e') {
			PlaySound(TEXT("load.wav"), NULL, SND_FILENAME | SND_ASYNC);
			twotir1 = 6;
			double_bullet_p1 = 1;
			double_bullet1 = 0;
		}
		if (map[player2_pos.Y][player2_pos.X] == 'e') {
			PlaySound(TEXT("load.wav"), NULL, SND_FILENAME | SND_ASYNC);
			twotir2 = 6;
			double_bullet_p2 = 1;
			double_bullet1 = 0;
		}
		if (map[player1_pos.Y][player1_pos.X] == 'E') {
			PlaySound(TEXT("load.wav"), NULL, SND_FILENAME | SND_ASYNC);
			twotir1 = 6;
			double_bullet_p1 = 1;
			double_bullet2 = 0;
		}
		if (map[player2_pos.Y][player2_pos.X] == 'E') {
			PlaySound(TEXT("load.wav"), NULL, SND_FILENAME | SND_ASYNC);
			twotir2 = 6;
			double_bullet_p2 = 1;
			double_bullet2 = 0;
		}
		//Ghost
		if (map[player1_pos.Y][player1_pos.X] == 'g') {
			PlaySound(TEXT("ghost.wav"), NULL, SND_FILENAME | SND_ASYNC);
			ghost1 = 8;
			ghost_ = 0;
		}
		if (map[player2_pos.Y][player2_pos.X] == 'g') {
			PlaySound(TEXT("ghost.wav"), NULL, SND_FILENAME | SND_ASYNC);
			ghost2 = 8;
			ghost_ = 0;
		}
		//Bomb
		if (map[player1_pos.Y][player1_pos.X] == 'b') {
			bomb_ = 0; bomb1 = 1;
		}
		if (map[player2_pos.Y][player2_pos.X] == 'b') {
			bomb_ = 0; bomb2 = 1;
		}

		//Bullet Hitting Things:
		//Mirror & Bullet1
		if (bomb1 == 0) {
			if (((move1 == 'r' && map[player1_bullet.Y][player1_bullet.X + 1] == '|') ||
				(move1 == 'l' && map[player1_bullet.Y][player1_bullet.X - 1] == '|') ||
				(move1 == 'd' && map[player1_bullet.Y-1][player1_bullet.X] == '|')||
				(move1 == 'u' && map[player1_bullet.Y+1][player1_bullet.X] == '|')) && ghost1 <= 0) {
				if (move1 == 'u')
					move1 = 'd';
				else if (move1 == 'd')
					move1 = 'u';
				else if (move1 == 'r')
					move1 = 'l';
				else if (move1 == 'l')
					move1 = 'r';
			}
		}
		else {
			if (map[player1_bullet.Y][player1_bullet.X] == '|' && ghost1 <= 0) {
				PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
				b1 = 0; bomb1 = 0;
				tempmap[player1_bullet.Y][player1_bullet.X] = '#';
				explode = 1;
				for (i = -1; i <= 1; i++) {
					for (j = -1; j <= 1; j++) {
						for (j = -1; j <= 1; j++) {
							if (map[player1_bullet.Y + i][player1_bullet.X + j] == '1')
								lives1--;
							if (map[player1_bullet.Y + i][player1_bullet.X + j] == '2')
								lives2--;
							if (i != 0 || j != 0)
								tempmap[player1_bullet.Y + i][player1_bullet.X + j] = 'F';
						}
					}
				}
			}
		}
	    //Mirror & Bullet2
			if (bomb2 == 0) {
				if (((move2 == 'r' && map[player2_bullet.Y][player2_bullet.X + 1] == '|') ||
					(move2 == 'l' && map[player2_bullet.Y][player2_bullet.X - 1] == '|') ||
					(move2 == 'd' && map[player2_bullet.Y - 1][player2_bullet.X] == '|') ||
					(move2 == 'u' && map[player2_bullet.Y + 1][player2_bullet.X] == '|')) && ghost2 <= 0) {
					if (move2 == 'u')
						move2 = 'd';
					else if (move2 == 'd')
						move2 = 'u';
					else if (move2 == 'r')
						move2 = 'l';
					else if (move2 == 'l')
						move2 = 'r';
				}
			}
			else {
				if (map[player2_bullet.Y][player2_bullet.X] == '|' && ghost2 <= 0) {
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
					b2 = 0; bomb2 = 0;
					tempmap[player2_bullet.Y][player2_bullet.X] = '#';
					explode = 1;
					for (i = -1; i <= 1; i++) {
						for (j = -1; j <= 1; j++) {
							if (map[player2_bullet.Y + i][player2_bullet.X + j] == '1')
								lives1--;
							if (map[player2_bullet.Y + i][player2_bullet.X + j] == '2')
								lives2--;
							if (i != 0 || j != 0)
								tempmap[player2_bullet.Y + i][player2_bullet.X + j] = 'F';
						}
					}
				}
			}
			//Wall
			if (map[player1_bullet.Y][player1_bullet.X] == '[' && ghost1 <= 0) {
				if (bomb1 == 0)
					b1 = 0;
				else {
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
					b1 = 0; bomb1 = 0;
					explode = 1;
					for (i = -2; i <= 2; i++) {
						for (j = -2; j <= 2; j++) {
							if (map[player1_bullet.Y + i][player1_bullet.X + j] == '1')
								lives1--;
							if (map[player1_bullet.Y + i][player1_bullet.X + j] == '2')
								lives2--;
							if (i != 0 || j != 0)
								tempmap[player1_bullet.Y + i][player1_bullet.X + j] = 'F';
						}
					}
				}
			}
			if (map[player2_bullet.Y][player2_bullet.X] == '[' && ghost2 <= 0) {
				if (bomb2 == 0)
					b2 = 0;
				else {
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
					b2 = 0; bomb2 = 0;
					explode = 1;
					for (i = -2; i <= 2; i++) {
						for (j = -2; j <= 2; j++) {
							if (map[player2_bullet.Y + i][player2_bullet.X + j] == '1')
								lives1--;
							if (map[player2_bullet.Y + i][player2_bullet.X + j] == '2')
								lives2--;
							if (i != 0 || j != 0)
								tempmap[player2_bullet.Y + i][player2_bullet.X + j] = 'F';
						}
					}
				}
			}
			//Check if Bullet Getting Out of map
			if (player1_bullet.X == 93 || player1_bullet.Y == 23 || player1_bullet.X == -1 || player1_bullet.Y == 0)
				b1 = 0;
			if (player2_bullet.X == 93 || player2_bullet.Y == 23 || player2_bullet.X == -1 || player2_bullet.Y == 0)
				b2 = 0;
			//Bullet Hitting Player
			if (player1_bullet.X == player2_pos.X && player1_bullet.Y == player2_pos.Y) {
				if (bomb1 == 1)
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
				else
					PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (double_bullet_p1 == 0)
					lives2--;
				else
					lives2 -= 2;
				b1 = 0;
			}
			if (player2_bullet.X == player1_pos.X && player2_bullet.Y == player1_pos.Y) {
				if (bomb2 == 1)
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
				else
					PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (double_bullet_p2 == 0)
					lives1--;
				else
					lives1 -= 2;
				b2 = 0;
			}
			if (player1_bullet.X == player1_pos.X && player1_bullet.Y == player1_pos.Y) {
				if (bomb1 == 1)
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
				else
					PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (double_bullet_p1 == 0)
					lives1--;
				else
					lives1 -= 2;
				b1 = 0;
			}
			if (player2_bullet.X == player2_pos.X && player2_bullet.Y == player2_pos.Y) {
				if (bomb2 == 1)
					PlaySound(TEXT("explode.wav"), NULL, SND_FILENAME | SND_ASYNC);
				else
					PlaySound(TEXT("hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (double_bullet_p2 == 0)
					lives2--;
				else
					lives2 -= 2;
				b2 = 0;
			}
			//Bullet Check
			if (b1 == 0) {
				player1_bullet.X = -1; player1_bullet.Y = -1;
			}
			if (b2 == 0) {
				player2_bullet.X = -1; player2_bullet.Y = -1;
			}

			// Draw bullets
			if (player1_bullet.X <= 92 && player1_bullet.X != -1 && player1_bullet.Y <= 22 && player1_bullet.Y >= 1)
				map[player1_bullet.Y][player1_bullet.X] = '.';
			if (player2_bullet.X <= 92 && player2_bullet.X != -1 && player2_bullet.Y <= 22 && player2_bullet.Y >= 1)
				map[player2_bullet.Y][player2_bullet.X] = '.';

			//Print Map
			if (explode == 0)
				printmap();
			else if (explode == 1) {
				for (y = 1; y < 23; y++) {
					for (x = 0; x < 93; x++) {
						if (tempmap[y][x] == 'F')
							map[y][x] = 'F';
					}
				}
				printmap();
				Sleep(500);
				explode = 0;
			}
		}
	}

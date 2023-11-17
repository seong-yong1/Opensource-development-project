#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <string.h> //문자열 함수사용을 위한 전처리기 구문

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //문자열 함수사용을 위해

typedef struct
{
    int state; //좌석확인
    char name[20]; // 이름
} seat; //구조체를 정의하고, seat으로 선언

typedef struct
{
    int phone_backnum; // 뒤의 번호 4자리를 받는 부분
    char m_name[20];  // 이름
} ID; // 구조체를 정의하고, ID로 선언

int Mode1(); // mode 선택 부분 
void Admin(); // 관리자 모드 함수
void User(); // 사용자 모드 함수
void print_state(); // 출력함수
int cancel_reservation(); // 예약 취소함수
int make_membership(); // 멤버쉽 등록
int check_membership(); // 멤버쉽 확인
int reservation(); // 예약하기 위한 함수
int check_state(); // 예약을 확인하기 위한 함수
int check_price(); // 매출액을 확인하기 위한 함수
int change_price(); // 각 좌석의 가격을 변경하기 위한 함수
int reservations(); // 여러 명 예약을 위한 ㅎ마수
int print_checkmembership(); // 멤버쉽 확인을 위한 함수

#define MAX 80 // 최대값을 79으로 지정

seat g_seat[MAX]; //모든 좌석의 변수
ID membership[MAX]; // 멤버쉽 등록

// 변수 선언 부분
int g_count;

// main 함수 부분
int main()
{

}

int Mode1()
{
    int input; // 사용자가 입력한 값을 저장하기 위한 함수

    printf("사용자 모드를 사용하시려면 1을 입력\n\n관리자 모드를 사용하시려면 2를 입력\n\n");
    scanf("%d", &input);
    printf("\n");

    return input;  // input 값을 반환
}

void User()
{
    int menu; //메뉴를 골라주는 함수

    g_count = 0;

    while (1)  //while문의 조건을 1으로 하면 계속 반복됨
    {
        printf("\n-------------MENU-------------\n");
        printf("1. 좌석 예약하기\n");
        printf("2. 현재 좌석의 상태\n");
        printf("3. 예약 취소 하기\n");
        printf("4. 종료\n\n");
        printf("5. 관리자 모드\n");
        printf("6. 멤버쉽 등록하기\n");
        printf("------------------------------\n");

        scanf("%d", &menu);
        getchar();

        switch (menu)
        {
        case 1:
            reservation();
            break;
        case 2:
            check_state();
            break;
        case 3:
            cancel_reservation();
            break;
        case 4:
            break;
        case 5:
            Admin();
            break;
        case 6:
            make_membership();
            break;
        default:
            printf("잘못 입력하셨습니다.\n");
            break;
        }
        if (menu == 4) break; //3번 메뉴(종료)를 선택하면 break를 이용하여 종료
    }
}

void print_state() //예약 상태를 출력하는 함수
{
    int i; //for문을 돌릴때 사용
    int area = 1, count = 1;

    printf("예약된 좌석은 ■로, 예약이 안된 좌석은 □으로 표시\n\n");
    printf("\t1\t2\t3\t4\t5\t6\t7\t8");

    for (i = 0; i < MAX; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n\n");
            count++;

            if (count % 2 == 0)
            {
                printf("%d구역  ", area);
                area++;
            }
        }

        if (g_seat[i].state == 1) //좌석이 1이면 이미 예약되어있으므로 그 자리에 ■를 입력
        {
            printf("\t■ ");
        }
        else //좌석에 0의 수가 들어가있으면 그 좌석은 예약이 안되어있으므로 그 자리에 □를 입력
        {
            printf("\t□");
        }
    }
    printf("\n");
}


///////
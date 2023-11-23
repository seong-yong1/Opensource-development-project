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
} ID;

int Mode1(); // mode 선택 부분 
void Admin(); // 관리자 모드 함수
void User(); // 사용자 모드 함수
void print_state(); // 출력함수
int cancel_reservation(); // 예약 취소함수
int make_membership(); // 멤버쉽 등록
int check_membership(); // 멤버쉽 확인 -> 계산될 때 멤버쉽 확인 위한 함수
int reservation(); // 예약하기 위한 함수
int check_state(); // 예약을 확인하기 위한 함수
int check_price(); // 매출액을 확인하기 위한 함수
int change_price(); // 각 좌석의 가격을 변경하기 위한 함수
int reservations(); // 여러 명 예약을 위한 함수
int print_checkmembership(); // 멤버쉽 확인을 위한 함수


#define MAX 80 // 최대값을 79으로 지정

seat g_seat[MAX]; //모든 좌석의 변수
ID membership[MAX]; // 멤버쉽 등록

int y; //y는 좌석번호
int g_count; //예약된 좌석의 갯수
int vp = 5, sp = 4, rp = 3, ap = 2, bp = 1; //vp, sp, rp, ap, bp는 각각 좌석 등급의 지정된 처음 가격
int v = 0, s = 0, r = 0, a = 0, b = 0; //좌석등급별 매수
int c, x;
int membership_count = 0;
double membership_price_count = 0;

//g_seat에 모든 좌석 변수를 설정하고 예약된 좌석 개수를 g_count에 받기 위해 변수를 설정함
int main()
{
    int mode;

    while (1)
    {
        mode = Mode1();
        if (mode == 1 || mode == 2)
        {
            if (mode == 1)//사용자 모드
            {
                User();
                break;
            }
            else if (mode == 2)//관리자 모드
            {
                Admin();
                break;
            }
        }
        else
            printf("다시 입력하세요 \n");
    }
}

int Mode1()
{
    int input;

    printf("사용자 모드를 사용하시려면 1을 입력\n\n관리자 모드를 사용하시려면 2를 입력\n\n");
    scanf("%d", &input);
    printf("\n");

    return input;
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

// 이미 예약되어있으면 -1리턴, 정상적으로 예약되었으면 0리턴
int reservation()
{
    printf("예약하고자하는 매수를 입력해주십시오. : ");
    scanf("%d", &x);

    for (c = 1; c < x + 1; c++)
    {
        reservations();
    }
    return 0;
}

int reservations()
{
    int i = 0;
    int sec;
    int member = 0;

    if (MAX <= g_count) //좌석이 꽉 차있을 경우
    {
        printf("더 이상 좌석이 없습니다.\n");
        return -1;
    }
    else //좌석 예약 가능
    {
        printf("현재 좌석 현황입니다.\n");
        print_state();

        while (1) {
            printf("%d번째 예매를시작하겠습니다.\n", c);
            printf("구역을 선택하십시오.(1~5) : ");

            scanf("%d", &sec);

            if (sec < 0 || sec > 5) //구역을 1~5이외의 숫자를 넣었을 경우
            {
                printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                continue;
            }
            switch (sec)
            {
            case 1:
                v++; //매출액 확인시 사용
                printf("좌석 종류 = 1  2  3  4  5  6  7  8 \n            9 10 11 12 13 14 15 16\n");
                printf("원하는 좌석을 입력하시오. ");
                printf("\n번호(1~16) : ");
                scanf("%d", &y);

                if (y < 0 || y > 16) //좌석을 1~16이외의 숫자를 넣었을 경우
                {
                    printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("VIP석은 %.1f만원입니다.\n\n", (float)vp - 0.5);
                    y--; //예약확인시 사용
                    break;
                }
                else
                {
                    printf("VIP석은 %d만원입니다.\n\n", vp);
                    y--; //예약확인시 사용
                    break;
                }

            case 2:
                s++;
                printf("좌석 종류 = 17 18 19 20 21 22 23 24\n            25 26 27 28 29 30 31 32\n");
                printf("원하는 좌석을 입력하시오. ");
                printf("\n번호(17~32) : ");

                scanf("%d", &y);

                if (y < 16 || y > 32) //좌석을 17~32이외의 숫자를 넣었을 경우
                {
                    printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("S석은 %.1f만원입니다.\n\n", (float)sp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("S석은 %d만원입니다.\n\n", sp);
                    y--;
                    break;
                }

            case 3:
                r++;
                printf("좌석 종류 = 33 34 35 36 37 38 39 40\n            41 42 43 44 45 46 47 48\n");
                printf("원하는 좌석을 입력하시오. ");
                printf("\n번호(33~48) : ");

                scanf("%d", &y);

                if (y < 32 || y > 48) //좌석을 33~48이외의 숫자를 넣었을 경우
                {
                    printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("R석은 %.1f만원입니다.\n\n", (float)rp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("R석은 %d만원입니다.\n\n", rp);
                    y--;
                    break;
                }

            case 4:
                a++;
                printf("좌석 종류 = 49 50 51 52 53 54 55 56\n            57 58 59 60 61 62 63 64\n");
                printf("원하는 좌석을 입력하시오. ");
                printf("\n번호(49~64) : ");

                scanf("%d", &y);

                if (y < 48 || y > 64) //좌석을 49~64이외의 숫자를 넣었을 경우
                {
                    printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("A석은 %.1f만원입니다.\n\n", (float)ap - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("A석은 %d만원입니다.\n\n", ap);
                    y--;
                    break;
                }

            case 5:
                b++;
                printf("좌석 종류 = 65 66 67 68 69 70 71 72\n            73 74 75 76 77 78 79 80\n");
                printf("원하는 좌석을 입력하시오. ");
                printf("\n번호(65~80) : ");

                scanf("%d", &y);

                if (y < 64 || y > 80) //좌석을 65~80이외의 숫자를 넣었을 경우
                {
                    printf("잘못 입력하셨습니다. 다시 입력하십시오.\n\n");
                    continue;
                }

                member = check_membership();
                getchar(); // 버퍼 대기

                if (member == 1)
                {
                    membership_price_count++;
                    printf("B석은 %.1f만원입니다.\n\n", (float)bp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("B석은 %d만원입니다.\n\n", bp);
                    y--;
                    break;
                }
            }

            if (g_seat[y].state == 1) //그 좌석의 상태가 예약되었을 경우 경고문을출력하고 전단계로복귀
            {
                printf("이미 예약된 좌석입니다. 다른 좌석을 입력해 주십시오.\n");
                continue;
            }
            else // 좌석의 상태가 1이 아닌 경우. 예약되지 않은 경우.
            {
                printf("성함을 입력하시오 : ");
                gets_s(g_seat[y].name); //성함을 적음

                g_seat[y].state = 1; //예약된 좌석에 1을 넣어줌. 예약상태

                printf("정상적으로 예약되었습니다. 좌석(%d번)\n\n", y + 1);
                g_count++;
                return 0;
            }
            return 0;
        }
    }
}

int check_state()
{
    char name[80];
    int idx[MAX], i, k = 0;

    print_state(); //현재 좌석을 확인

    printf("성함을 입력하십시오. :");
    gets_s(name); //이름을 적음

    for (i = 0, k = 0; i < MAX; i++)
    {
        if (g_seat[i].state == 1 && strcmp(name, g_seat[i].name) == 0)
        {
            idx[k++] = i;
        }
    }
    if (k > 0)
    {
        printf("%s고객님께서는", name);

        for (i = 0; i < k; i++)
        {
            printf("%d ", idx[i] + 1);
        }
        printf("번째 자리에 예약하셨습니다.\n");
    }
    else
    {
        printf("%s고객님께서는 예약하신 내역이 없습니다. \n", name);
    }

    return 0;
}

void Admin()
{
    int menu; //메뉴를 골라주는 함수

    while (1)
    {
        printf("\n-------------MENU-------------\n");
        printf("1. 매출액 확인하기\n");
        printf("2. 등급 별 좌석 가격 변경하기\n");
        printf("3. 멤버쉽 여부 확인\n");
        printf("4. 종료\n\n\n");
        printf("\n");
        printf("5. 사용자 모드\n");
        printf("6. 초기화면으로\n");
        printf("------------------------------\n");

        scanf("%d", &menu); getchar();

        switch (menu)
        {
        case 1:
            check_price();
            break;
        case 2:
            change_price();
            break;
        case 3:
            print_checkmembership();
            break;
        case 4:
            break;
        case 5:
            User();
            break;
        case 6:
            main();
            break;
        default:
            printf("잘못 입력하셨습니다.\n");
            break;
        }

        if (menu == 4)
            break; //4번 메뉴(종료)를 선택하면 break를 이용하여 종료
    }
}


int check_price()
{
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, sum = 0; //각 좌석의 매출액과 총 매출액
    double discount = 0;
    //매출액 = 각 좌석의 예매 매수 * 각 좌석의 가격
    c1 = v * vp;
    c2 = s * sp;
    c3 = r * rp;
    c4 = a * ap;
    c5 = b * bp;

    printf("등급별 예매 매수와 매출액\n");
    printf("VIP석 : %d장\t%d만원\n", v, c1);
    printf(" S 석 : %d장\t%d만원\n", s, c2);
    printf(" R 석 : %d장\t%d만원\n", r, c3);
    printf(" A 석 : %d장\t%d만원\n", a, c4);
    printf(" B 석 : %d장\t%d만원\n", b, c5);
    printf(" 멤버쉽 할인 받은 회원 : %lf명\n\n", membership_price_count);

    sum = c1 + c2 + c3 + c4 + c5;
    discount = membership_price_count * 0.5;
    printf("총 매출액은 %.1f만원입니다.\n", (double)sum - discount);

    return 0;
}

int change_price()
{
    printf("변경을 원하는 VIP좌석의 가격 : ");
    scanf("%d", &vp);
    printf("\n");
    printf("변경을 원하는  S 좌석의 가격 : ");
    scanf("%d", &sp);
    printf("\n");
    printf("변경을 원하는  R 좌석의 가격 : ");
    scanf("%d", &rp);
    printf("\n");
    printf("변경을 원하는  A 좌석의 가격 : ");
    scanf("%d", &ap);
    printf("\n");
    printf("변경을 원하는  B 좌석의 가격 : ");
    scanf("%d", &bp);
    printf("\n");

    return 0;
}

int cancel_reservation()
{
    char name[80];
    int idx[MAX], i, k = 0;

    print_state(); //현재 좌석을 확인

    printf("성함을 입력하십시오. :");
    gets_s(name); //이름을 적음

    for (i = 0, k = 0; i < MAX; i++)
    {
        if (g_seat[i].state == 1 && strcmp(name, g_seat[i].name) == 0)
        {
            idx[k++] = i;
            g_seat[i].state = 0;
        }
    }
    if (k > 0)
    {
        printf("%s고객님께서는", name);

        for (i = 0; i < k; i++)
        {
            printf("%d ", idx[i] + 1);
        }
        printf("번째 자리에 예약을 취소 하셨습니다.\n");
    }
    else
    {
        printf("%s고객님께서는 예약하신 내역이 없습니다. \n", name);
    }

    User();

    return 0;
}

int make_membership()  //멤버쉽 등록정보를 알려준다.
{
    int back_number;
    char name[80];

    printf("멤버쉽 등록을 위해서 이름과 전화번호 뒷자리4자리 입력이 필요합니다.\n");

    printf("이름을 입력하시오: ");
    gets_s(name);

    printf("전화번호 뒷자리 4자리를 입력하시오: ");
    scanf("%d", &back_number);

    membership[membership_count].phone_backnum = back_number;
    strcat(membership[membership_count].m_name, name);

    membership_count++;  // 멤버쉽 인원이 추가되었음을 알려준다.
    return 0;
}

int check_membership()
{
    int back_number;
    char name[80];

    printf("전화번호 뒷자리 4자리를 입력하시오: ");
    scanf("%d", &back_number);

    printf("이름을 입력하시오: ");
    scanf("%s", &name);

    for (int i = 0; i < membership_count; i++)
    {
        if (membership[i].phone_backnum == back_number && strcmp(name, membership[i].m_name) == 0)
        {
            return 1; // 멤버쉽 회원이다.
        }
    }
    return 0;
}

int print_checkmembership()
{
    char name[80];
    int back_number;

    printf("이름을 입력하시오 : ");
    scanf("%s", name);

    printf("번호를 입력하시오 : ");
    scanf("%d", &back_number);

    for (int i = 0; i < membership_count; i++)
    {
        if (membership[i].phone_backnum == back_number && strcmp(name, membership[i].m_name) == 0)
        {
            printf("%s님은 멤버쉽에 가입되어 있습니다.\n", name);
            return 1; // 멤버쉽 회원이다.
        }
    }

    printf("%s님은 멤버쉽에 가입되어 있지 않습니다.\n", name);
}
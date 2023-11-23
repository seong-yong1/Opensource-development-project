#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //���ڿ� �Լ������ ����

typedef struct
{
    int state; //�¼�Ȯ��
    char name[20]; // �̸�
} seat; //����ü�� �����ϰ�, seat���� ����

typedef struct
{
    int phone_backnum; // ���� ��ȣ 4�ڸ��� �޴� �κ�
    char m_name[20];  // �̸�
} ID;

int Mode1(); // mode ���� �κ� 
void Admin(); // ������ ��� �Լ�
void User(); // ����� ��� �Լ�
void print_state(); // ����Լ�
int cancel_reservation(); // ���� ����Լ�
int make_membership(); // ����� ���
int check_membership(); // ����� Ȯ�� -> ���� �� ����� Ȯ�� ���� �Լ�
int reservation(); // �����ϱ� ���� �Լ�
int check_state(); // ������ Ȯ���ϱ� ���� �Լ�
int check_price(); // ������� Ȯ���ϱ� ���� �Լ�
int change_price(); // �� �¼��� ������ �����ϱ� ���� �Լ�
int reservations(); // ���� �� ������ ���� �Լ�
int print_checkmembership(); // ����� Ȯ���� ���� �Լ�


#define MAX 80 // �ִ밪�� 79���� ����

seat g_seat[MAX]; //��� �¼��� ����
ID membership[MAX]; // ����� ���

int y; //y�� �¼���ȣ
int g_count; //����� �¼��� ����
int vp = 5, sp = 4, rp = 3, ap = 2, bp = 1; //vp, sp, rp, ap, bp�� ���� �¼� ����� ������ ó�� ����
int v = 0, s = 0, r = 0, a = 0, b = 0; //�¼���޺� �ż�
int c, x;
int membership_count = 0;
double membership_price_count = 0;

//g_seat�� ��� �¼� ������ �����ϰ� ����� �¼� ������ g_count�� �ޱ� ���� ������ ������
int main()
{
    int mode;

    while (1)
    {
        mode = Mode1();
        if (mode == 1 || mode == 2)
        {
            if (mode == 1)//����� ���
            {
                User();
                break;
            }
            else if (mode == 2)//������ ���
            {
                Admin();
                break;
            }
        }
        else
            printf("�ٽ� �Է��ϼ��� \n");
    }
}

int Mode1()
{
    int input;

    printf("����� ��带 ����Ͻ÷��� 1�� �Է�\n\n������ ��带 ����Ͻ÷��� 2�� �Է�\n\n");
    scanf("%d", &input);
    printf("\n");

    return input;
}

void User()
{
    int menu; //�޴��� ����ִ� �Լ�

    g_count = 0;

    while (1)  //while���� ������ 1���� �ϸ� ��� �ݺ���
    {
        printf("\n-------------MENU-------------\n");
        printf("1. �¼� �����ϱ�\n");
        printf("2. ���� �¼��� ����\n");
        printf("3. ���� ��� �ϱ�\n");
        printf("4. ����\n\n");
        printf("5. ������ ���\n");
        printf("6. ����� ����ϱ�\n");
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
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
            break;
        }
        if (menu == 4) break; //3�� �޴�(����)�� �����ϸ� break�� �̿��Ͽ� ����
    }
}

void print_state() //���� ���¸� ����ϴ� �Լ�
{
    int i; //for���� ������ ���
    int area = 1, count = 1;

    printf("����� �¼��� ���, ������ �ȵ� �¼��� ������ ǥ��\n\n");
    printf("\t1\t2\t3\t4\t5\t6\t7\t8");

    for (i = 0; i < MAX; i++)
    {
        if (i % 8 == 0)
        {
            printf("\n\n");
            count++;

            if (count % 2 == 0)
            {
                printf("%d����  ", area);
                area++;
            }
        }

        if (g_seat[i].state == 1) //�¼��� 1�̸� �̹� ����Ǿ������Ƿ� �� �ڸ��� �Ḧ �Է�
        {
            printf("\t�� ");
        }
        else //�¼��� 0�� ���� �������� �� �¼��� ������ �ȵǾ������Ƿ� �� �ڸ��� �ฦ �Է�
        {
            printf("\t��");
        }
    }
    printf("\n");
}

// �̹� ����Ǿ������� -1����, ���������� ����Ǿ����� 0����
int reservation()
{
    printf("�����ϰ����ϴ� �ż��� �Է����ֽʽÿ�. : ");
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

    if (MAX <= g_count) //�¼��� �� ������ ���
    {
        printf("�� �̻� �¼��� �����ϴ�.\n");
        return -1;
    }
    else //�¼� ���� ����
    {
        printf("���� �¼� ��Ȳ�Դϴ�.\n");
        print_state();

        while (1) {
            printf("%d��° ���Ÿ������ϰڽ��ϴ�.\n", c);
            printf("������ �����Ͻʽÿ�.(1~5) : ");

            scanf("%d", &sec);

            if (sec < 0 || sec > 5) //������ 1~5�̿��� ���ڸ� �־��� ���
            {
                printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                continue;
            }
            switch (sec)
            {
            case 1:
                v++; //����� Ȯ�ν� ���
                printf("�¼� ���� = 1  2  3  4  5  6  7  8 \n            9 10 11 12 13 14 15 16\n");
                printf("���ϴ� �¼��� �Է��Ͻÿ�. ");
                printf("\n��ȣ(1~16) : ");
                scanf("%d", &y);

                if (y < 0 || y > 16) //�¼��� 1~16�̿��� ���ڸ� �־��� ���
                {
                    printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("VIP���� %.1f�����Դϴ�.\n\n", (float)vp - 0.5);
                    y--; //����Ȯ�ν� ���
                    break;
                }
                else
                {
                    printf("VIP���� %d�����Դϴ�.\n\n", vp);
                    y--; //����Ȯ�ν� ���
                    break;
                }

            case 2:
                s++;
                printf("�¼� ���� = 17 18 19 20 21 22 23 24\n            25 26 27 28 29 30 31 32\n");
                printf("���ϴ� �¼��� �Է��Ͻÿ�. ");
                printf("\n��ȣ(17~32) : ");

                scanf("%d", &y);

                if (y < 16 || y > 32) //�¼��� 17~32�̿��� ���ڸ� �־��� ���
                {
                    printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("S���� %.1f�����Դϴ�.\n\n", (float)sp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("S���� %d�����Դϴ�.\n\n", sp);
                    y--;
                    break;
                }

            case 3:
                r++;
                printf("�¼� ���� = 33 34 35 36 37 38 39 40\n            41 42 43 44 45 46 47 48\n");
                printf("���ϴ� �¼��� �Է��Ͻÿ�. ");
                printf("\n��ȣ(33~48) : ");

                scanf("%d", &y);

                if (y < 32 || y > 48) //�¼��� 33~48�̿��� ���ڸ� �־��� ���
                {
                    printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("R���� %.1f�����Դϴ�.\n\n", (float)rp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("R���� %d�����Դϴ�.\n\n", rp);
                    y--;
                    break;
                }

            case 4:
                a++;
                printf("�¼� ���� = 49 50 51 52 53 54 55 56\n            57 58 59 60 61 62 63 64\n");
                printf("���ϴ� �¼��� �Է��Ͻÿ�. ");
                printf("\n��ȣ(49~64) : ");

                scanf("%d", &y);

                if (y < 48 || y > 64) //�¼��� 49~64�̿��� ���ڸ� �־��� ���
                {
                    printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                    continue;
                }

                member = check_membership();
                getchar();

                if (member == 1)
                {
                    membership_price_count++;
                    printf("A���� %.1f�����Դϴ�.\n\n", (float)ap - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("A���� %d�����Դϴ�.\n\n", ap);
                    y--;
                    break;
                }

            case 5:
                b++;
                printf("�¼� ���� = 65 66 67 68 69 70 71 72\n            73 74 75 76 77 78 79 80\n");
                printf("���ϴ� �¼��� �Է��Ͻÿ�. ");
                printf("\n��ȣ(65~80) : ");

                scanf("%d", &y);

                if (y < 64 || y > 80) //�¼��� 65~80�̿��� ���ڸ� �־��� ���
                {
                    printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��Ͻʽÿ�.\n\n");
                    continue;
                }

                member = check_membership();
                getchar(); // ���� ���

                if (member == 1)
                {
                    membership_price_count++;
                    printf("B���� %.1f�����Դϴ�.\n\n", (float)bp - 0.5);
                    y--;
                    break;
                }
                else
                {
                    printf("B���� %d�����Դϴ�.\n\n", bp);
                    y--;
                    break;
                }
            }

            if (g_seat[y].state == 1) //�� �¼��� ���°� ����Ǿ��� ��� ���������ϰ� ���ܰ�κ���
            {
                printf("�̹� ����� �¼��Դϴ�. �ٸ� �¼��� �Է��� �ֽʽÿ�.\n");
                continue;
            }
            else // �¼��� ���°� 1�� �ƴ� ���. ������� ���� ���.
            {
                printf("������ �Է��Ͻÿ� : ");
                gets_s(g_seat[y].name); //������ ����

                g_seat[y].state = 1; //����� �¼��� 1�� �־���. �������

                printf("���������� ����Ǿ����ϴ�. �¼�(%d��)\n\n", y + 1);
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

    print_state(); //���� �¼��� Ȯ��

    printf("������ �Է��Ͻʽÿ�. :");
    gets_s(name); //�̸��� ����

    for (i = 0, k = 0; i < MAX; i++)
    {
        if (g_seat[i].state == 1 && strcmp(name, g_seat[i].name) == 0)
        {
            idx[k++] = i;
        }
    }
    if (k > 0)
    {
        printf("%s���Բ�����", name);

        for (i = 0; i < k; i++)
        {
            printf("%d ", idx[i] + 1);
        }
        printf("��° �ڸ��� �����ϼ̽��ϴ�.\n");
    }
    else
    {
        printf("%s���Բ����� �����Ͻ� ������ �����ϴ�. \n", name);
    }

    return 0;
}

void Admin()
{
    int menu; //�޴��� ����ִ� �Լ�

    while (1)
    {
        printf("\n-------------MENU-------------\n");
        printf("1. ����� Ȯ���ϱ�\n");
        printf("2. ��� �� �¼� ���� �����ϱ�\n");
        printf("3. ����� ���� Ȯ��\n");
        printf("4. ����\n\n\n");
        printf("\n");
        printf("5. ����� ���\n");
        printf("6. �ʱ�ȭ������\n");
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
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
            break;
        }

        if (menu == 4)
            break; //4�� �޴�(����)�� �����ϸ� break�� �̿��Ͽ� ����
    }
}


int check_price()
{
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, sum = 0; //�� �¼��� ����װ� �� �����
    double discount = 0;
    //����� = �� �¼��� ���� �ż� * �� �¼��� ����
    c1 = v * vp;
    c2 = s * sp;
    c3 = r * rp;
    c4 = a * ap;
    c5 = b * bp;

    printf("��޺� ���� �ż��� �����\n");
    printf("VIP�� : %d��\t%d����\n", v, c1);
    printf(" S �� : %d��\t%d����\n", s, c2);
    printf(" R �� : %d��\t%d����\n", r, c3);
    printf(" A �� : %d��\t%d����\n", a, c4);
    printf(" B �� : %d��\t%d����\n", b, c5);
    printf(" ����� ���� ���� ȸ�� : %lf��\n\n", membership_price_count);

    sum = c1 + c2 + c3 + c4 + c5;
    discount = membership_price_count * 0.5;
    printf("�� ������� %.1f�����Դϴ�.\n", (double)sum - discount);

    return 0;
}

int change_price()
{
    printf("������ ���ϴ� VIP�¼��� ���� : ");
    scanf("%d", &vp);
    printf("\n");
    printf("������ ���ϴ�  S �¼��� ���� : ");
    scanf("%d", &sp);
    printf("\n");
    printf("������ ���ϴ�  R �¼��� ���� : ");
    scanf("%d", &rp);
    printf("\n");
    printf("������ ���ϴ�  A �¼��� ���� : ");
    scanf("%d", &ap);
    printf("\n");
    printf("������ ���ϴ�  B �¼��� ���� : ");
    scanf("%d", &bp);
    printf("\n");

    return 0;
}

int cancel_reservation()
{
    char name[80];
    int idx[MAX], i, k = 0;

    print_state(); //���� �¼��� Ȯ��

    printf("������ �Է��Ͻʽÿ�. :");
    gets_s(name); //�̸��� ����

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
        printf("%s���Բ�����", name);

        for (i = 0; i < k; i++)
        {
            printf("%d ", idx[i] + 1);
        }
        printf("��° �ڸ��� ������ ��� �ϼ̽��ϴ�.\n");
    }
    else
    {
        printf("%s���Բ����� �����Ͻ� ������ �����ϴ�. \n", name);
    }

    User();

    return 0;
}

int make_membership()  //����� ��������� �˷��ش�.
{
    int back_number;
    char name[80];

    printf("����� ����� ���ؼ� �̸��� ��ȭ��ȣ ���ڸ�4�ڸ� �Է��� �ʿ��մϴ�.\n");

    printf("�̸��� �Է��Ͻÿ�: ");
    gets_s(name);

    printf("��ȭ��ȣ ���ڸ� 4�ڸ��� �Է��Ͻÿ�: ");
    scanf("%d", &back_number);

    membership[membership_count].phone_backnum = back_number;
    strcat(membership[membership_count].m_name, name);

    membership_count++;  // ����� �ο��� �߰��Ǿ����� �˷��ش�.
    return 0;
}

int check_membership()
{
    int back_number;
    char name[80];

    printf("��ȭ��ȣ ���ڸ� 4�ڸ��� �Է��Ͻÿ�: ");
    scanf("%d", &back_number);

    printf("�̸��� �Է��Ͻÿ�: ");
    scanf("%s", &name);

    for (int i = 0; i < membership_count; i++)
    {
        if (membership[i].phone_backnum == back_number && strcmp(name, membership[i].m_name) == 0)
        {
            return 1; // ����� ȸ���̴�.
        }
    }
    return 0;
}

int print_checkmembership()
{
    char name[80];
    int back_number;

    printf("�̸��� �Է��Ͻÿ� : ");
    scanf("%s", name);

    printf("��ȣ�� �Է��Ͻÿ� : ");
    scanf("%d", &back_number);

    for (int i = 0; i < membership_count; i++)
    {
        if (membership[i].phone_backnum == back_number && strcmp(name, membership[i].m_name) == 0)
        {
            printf("%s���� ������� ���ԵǾ� �ֽ��ϴ�.\n", name);
            return 1; // ����� ȸ���̴�.
        }
    }

    printf("%s���� ������� ���ԵǾ� ���� �ʽ��ϴ�.\n", name);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <string.h> //���ڿ� �Լ������ ���� ��ó���� ����

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
} ID; // ����ü�� �����ϰ�, ID�� ����

int Mode1(); // mode ���� �κ� 
void Admin(); // ������ ��� �Լ�
void User(); // ����� ��� �Լ�
void print_state(); // ����Լ�
int cancel_reservation(); // ���� ����Լ�
int make_membership(); // ����� ���
int check_membership(); // ����� Ȯ��
int reservation(); // �����ϱ� ���� �Լ�
int check_state(); // ������ Ȯ���ϱ� ���� �Լ�
int check_price(); // ������� Ȯ���ϱ� ���� �Լ�
int change_price(); // �� �¼��� ������ �����ϱ� ���� �Լ�
int reservations(); // ���� �� ������ ���� ������
int print_checkmembership(); // ����� Ȯ���� ���� �Լ�

#define MAX 80 // �ִ밪�� 79���� ����

seat g_seat[MAX]; //��� �¼��� ����
ID membership[MAX]; // ����� ���

// ���� ���� �κ�
int g_count;

// main �Լ� �κ�
int main()
{

}

int Mode1()
{
    int input; // ����ڰ� �Է��� ���� �����ϱ� ���� �Լ�

    printf("����� ��带 ����Ͻ÷��� 1�� �Է�\n\n������ ��带 ����Ͻ÷��� 2�� �Է�\n\n");
    scanf("%d", &input);
    printf("\n");

    return input;  // input ���� ��ȯ
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


///////